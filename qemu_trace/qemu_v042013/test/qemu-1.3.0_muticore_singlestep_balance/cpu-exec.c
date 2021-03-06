/*
 *  emulator main execution loop
 *
 *  Copyright (c) 2003-2005 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#include "config.h"
#include "cpu.h"
#include "disas.h"
#include "tcg.h"
#include "qemu-barrier.h"
#include "qtest.h"
#include "memory_trace.h"



int tb_invalidated_flag;

//#define CONFIG_DEBUG_EXEC

bool qemu_cpu_has_work(CPUState *cpu)
{
    return cpu_has_work(cpu);
}

void cpu_loop_exit(CPUArchState *env)
{
    env->current_tb = NULL;
    longjmp(env->jmp_env, 1);
}

/* exit the current TB from a signal handler. The host registers are
   restored in a state compatible with the CPU emulator
 */
#if defined(CONFIG_SOFTMMU)
void cpu_resume_from_signal(CPUArchState *env, void *puc)
{
    /* XXX: restore cpu registers saved in host registers */

    env->exception_index = -1;
    longjmp(env->jmp_env, 1);
}
#endif

/* Execute the code without caching the generated code. An interpreter
   could be used if available. */
static void cpu_exec_nocache(CPUArchState *env, int max_cycles,
                             TranslationBlock *orig_tb)
{
    tcg_target_ulong next_tb;
    TranslationBlock *tb;

    /* Should never happen.
       We only end up here when an existing TB is too long.  */
    if (max_cycles > CF_COUNT_MASK)
        max_cycles = CF_COUNT_MASK;

    tb = tb_gen_code(env, orig_tb->pc, orig_tb->cs_base, orig_tb->flags,
                     max_cycles);
	tb->trace_paddr = tb_paddr_cache;
	tb->trace_vaddr = tb_vaddr_cache;
	tb->trace_lvaddr = tb_lvaddr_cache;
	tb->trace_pc = tb_pc_cache;
	tb->trace_cr3 = tb_cr3_cache;
	tb->code_size = tb_code_size;
	tb_code_size = 0;
    env->current_tb = tb;

	//parkhk
	if(trace_recoding){
		raw_trace[0][raw_trace_idx] = 0x22;
		raw_trace[1][raw_trace_idx] = tb->trace_paddr;
		raw_trace[2][raw_trace_idx]= tb->trace_vaddr;
		raw_trace[3][raw_trace_idx] = tb->trace_pc;
		raw_trace[4][raw_trace_idx] = tb->trace_cr3;
		raw_trace[5][raw_trace_idx++] = env->cpuid_apic_id;
		tb_lvaddr_cache = tb->trace_lvaddr;
		count_cpu_inst[env->cpuid_apic_id]+=tb->code_size;
	}
    /* execute the generated code */
    next_tb = tcg_qemu_tb_exec(env, tb->tc_ptr);
    env->current_tb = NULL;

    if ((next_tb & 3) == 2) {
        /* Restore PC.  This may happen if async event occurs before
           the TB starts executing.  */
        cpu_pc_from_tb(env, tb);
    }
    tb_phys_invalidate(tb, -1);
    tb_free(tb);
}

static TranslationBlock *tb_find_slow(CPUArchState *env,
                                      target_ulong pc,
                                      target_ulong cs_base,
                                      uint64_t flags)
{
    TranslationBlock *tb, **ptb1;
    unsigned int h;
    tb_page_addr_t phys_pc, phys_page1;
    target_ulong virt_page2;

    tb_invalidated_flag = 0;

    /* find translated block using physical mappings */
    phys_pc = get_page_addr_code(env, pc);
    phys_page1 = phys_pc & TARGET_PAGE_MASK;
    h = tb_phys_hash_func(phys_pc);
    ptb1 = &tb_phys_hash[h];
    for(;;) {
        tb = *ptb1;
        if (!tb)
            goto not_found;
        if (tb->pc == pc &&
            tb->page_addr[0] == phys_page1 &&
            tb->cs_base == cs_base &&
            tb->flags == flags) {
            /* check next page if needed */
            if (tb->page_addr[1] != -1) {
                tb_page_addr_t phys_page2;

                virt_page2 = (pc & TARGET_PAGE_MASK) +
                    TARGET_PAGE_SIZE;
                phys_page2 = get_page_addr_code(env, virt_page2);
                if (tb->page_addr[1] == phys_page2)
                    goto found;
            } else {
                goto found;
            }
        }
        ptb1 = &tb->phys_hash_next;
    }
 not_found:
   /* if no translated code available, then translate it now */
    tb = tb_gen_code(env, pc, cs_base, flags, 0);
	tb->trace_paddr = tb_paddr_cache;
	tb->trace_vaddr = tb_vaddr_cache;
	tb->trace_lvaddr = tb_lvaddr_cache;
	tb->trace_pc = tb_pc_cache;
	tb->trace_cr3 = tb_cr3_cache;
	tb->code_size = tb_code_size;
	tb_code_size = 0;
 found:
    /* Move the last found TB to the head of the list */
    if (likely(*ptb1)) {
        *ptb1 = tb->phys_hash_next;
        tb->phys_hash_next = tb_phys_hash[h];
        tb_phys_hash[h] = tb;
    }
    /* we add the TB in the virtual pc hash table */
    env->tb_jmp_cache[tb_jmp_cache_hash_func(pc)] = tb;
    return tb;
}

static inline TranslationBlock *tb_find_fast(CPUArchState *env)
{
    TranslationBlock *tb;
    target_ulong cs_base, pc;
    int flags;

    /* we record a subset of the CPU state. It will
       always be the same before a given translated block
       is executed. */

    cpu_get_tb_cpu_state(env, &pc, &cs_base, &flags);
    tb = env->tb_jmp_cache[tb_jmp_cache_hash_func(pc)];
    if (unlikely(!tb || tb->pc != pc || tb->cs_base != cs_base ||
                 tb->flags != flags)) {
        tb = tb_find_slow(env, pc, cs_base, flags);
    }

	//parkhk
	if(trace_recoding){
		trace_window++;
		raw_trace[0][raw_trace_idx] = 0x2;
		raw_trace[1][raw_trace_idx] = tb->trace_paddr;
		raw_trace[2][raw_trace_idx]= tb->trace_vaddr;
		raw_trace[3][raw_trace_idx] = tb->trace_pc;
		raw_trace[4][raw_trace_idx] = tb->trace_cr3;
		raw_trace[5][raw_trace_idx++] = env->cpuid_apic_id;
		tb_lvaddr_cache = tb->trace_lvaddr;
		count_cpu_inst[env->cpuid_apic_id]+=tb->code_size;
	}
	return tb;
}

static CPUDebugExcpHandler *debug_excp_handler;

void cpu_set_debug_excp_handler(CPUDebugExcpHandler *handler)
{
    debug_excp_handler = handler;
}

static void cpu_handle_debug_exception(CPUArchState *env)
{
    CPUWatchpoint *wp;

    if (!env->watchpoint_hit) {
        QTAILQ_FOREACH(wp, &env->watchpoints, entry) {
            wp->flags &= ~BP_WATCHPOINT_HIT;
        }
    }
    if (debug_excp_handler) {
        debug_excp_handler(env);
    }
}

/* main execution loop */

volatile sig_atomic_t exit_request;

int cpu_exec(CPUArchState *env)
{
	CPUState *cpu = ENV_GET_CPU(env);
	int ret, interrupt_request;
	TranslationBlock *tb;
	uint8_t *tc_ptr;
	tcg_target_ulong next_tb;

	if (env->halted) {
		if (!cpu_has_work(cpu)) {
			return EXCP_HALTED;
		}

        env->halted = 0;
    }

    cpu_single_env = env;

    if (unlikely(exit_request)) {
		env->exit_request = 1;
	}

#if defined(TARGET_I386)
    /* put eflags in CPU temporary format */
    CC_SRC = env->eflags & (CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);
    DF = 1 - (2 * ((env->eflags >> 10) & 1));
    CC_OP = CC_OP_EFLAGS;
    env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);
#elif defined(TARGET_SPARC)
#elif defined(TARGET_M68K)
    env->cc_op = CC_OP_FLAGS;
    env->cc_dest = env->sr & 0xf;
    env->cc_x = (env->sr >> 4) & 1;
#elif defined(TARGET_ALPHA)
#elif defined(TARGET_ARM)
#elif defined(TARGET_UNICORE32)
#elif defined(TARGET_PPC)
    env->reserve_addr = -1;
#elif defined(TARGET_LM32)
#elif defined(TARGET_MICROBLAZE)
#elif defined(TARGET_MIPS)
#elif defined(TARGET_OPENRISC)
#elif defined(TARGET_SH4)
#elif defined(TARGET_CRIS)
#elif defined(TARGET_S390X)
#elif defined(TARGET_XTENSA)
    /* XXXXX */
#else
#error unsupported target CPU
#endif
    env->exception_index = -1;

    /* prepare setjmp context for exception handling */
    for(;;) {
        if (setjmp(env->jmp_env) == 0) {
            /* if an exception is pending, we execute it here */
            if (env->exception_index >= 0) {
                if (env->exception_index >= EXCP_INTERRUPT) {
                    /* exit request from the cpu execution loop */
                    ret = env->exception_index;
                    if (ret == EXCP_DEBUG) {
                        cpu_handle_debug_exception(env);
                    }
                    break;
                } else {
#if defined(CONFIG_USER_ONLY)
                    /* if user mode only, we simulate a fake exception
                       which will be handled outside the cpu execution
                       loop */
#if defined(TARGET_I386)
                    do_interrupt(env);
#endif
                    ret = env->exception_index;
                    break;
#else
                    do_interrupt(env);
                    env->exception_index = -1;
#endif
                }
            }

            next_tb = 0; /* force lookup of first TB */
            for(;;) {
                interrupt_request = env->interrupt_request;
                if (unlikely(interrupt_request)) {
                    if (unlikely(env->singlestep_enabled & SSTEP_NOIRQ)) {
                        /* Mask out external interrupts for this step. */
                        interrupt_request &= ~CPU_INTERRUPT_SSTEP_MASK;
                    }
                    if (interrupt_request & CPU_INTERRUPT_DEBUG) {
                        env->interrupt_request &= ~CPU_INTERRUPT_DEBUG;
                        env->exception_index = EXCP_DEBUG;
                        cpu_loop_exit(env);
                    }
#if defined(TARGET_ARM) || defined(TARGET_SPARC) || defined(TARGET_MIPS) || \
    defined(TARGET_PPC) || defined(TARGET_ALPHA) || defined(TARGET_CRIS) || \
    defined(TARGET_MICROBLAZE) || defined(TARGET_LM32) || defined(TARGET_UNICORE32)
                    if (interrupt_request & CPU_INTERRUPT_HALT) {
                        env->interrupt_request &= ~CPU_INTERRUPT_HALT;
                        env->halted = 1;
                        env->exception_index = EXCP_HLT;
                        cpu_loop_exit(env);
                    }
#endif
#if defined(TARGET_I386)
#if !defined(CONFIG_USER_ONLY)
                    if (interrupt_request & CPU_INTERRUPT_POLL) {
                        env->interrupt_request &= ~CPU_INTERRUPT_POLL;
                        apic_poll_irq(env->apic_state);
                    }
#endif
                    if (interrupt_request & CPU_INTERRUPT_INIT) {
                            cpu_svm_check_intercept_param(env, SVM_EXIT_INIT,
                                                          0);
                            do_cpu_init(x86_env_get_cpu(env));
                            env->exception_index = EXCP_HALTED;
                            cpu_loop_exit(env);
                    } else if (interrupt_request & CPU_INTERRUPT_SIPI) {
                            do_cpu_sipi(x86_env_get_cpu(env));
                    } else if (env->hflags2 & HF2_GIF_MASK) {
                        if ((interrupt_request & CPU_INTERRUPT_SMI) &&
                            !(env->hflags & HF_SMM_MASK)) {
                            cpu_svm_check_intercept_param(env, SVM_EXIT_SMI,
                                                          0);
                            env->interrupt_request &= ~CPU_INTERRUPT_SMI;
                            do_smm_enter(env);
                            next_tb = 0;
                        } else if ((interrupt_request & CPU_INTERRUPT_NMI) &&
                                   !(env->hflags2 & HF2_NMI_MASK)) {
                            env->interrupt_request &= ~CPU_INTERRUPT_NMI;
                            env->hflags2 |= HF2_NMI_MASK;
                            do_interrupt_x86_hardirq(env, EXCP02_NMI, 1);
                            next_tb = 0;
                        } else if (interrupt_request & CPU_INTERRUPT_MCE) {
                            env->interrupt_request &= ~CPU_INTERRUPT_MCE;
                            do_interrupt_x86_hardirq(env, EXCP12_MCHK, 0);
                            next_tb = 0;
                        } else if ((interrupt_request & CPU_INTERRUPT_HARD) &&
                                   (((env->hflags2 & HF2_VINTR_MASK) && 
                                     (env->hflags2 & HF2_HIF_MASK)) ||
                                    (!(env->hflags2 & HF2_VINTR_MASK) && 
                                     (env->eflags & IF_MASK && 
                                      !(env->hflags & HF_INHIBIT_IRQ_MASK))))) {
                            int intno;
                            cpu_svm_check_intercept_param(env, SVM_EXIT_INTR,
                                                          0);
                            env->interrupt_request &= ~(CPU_INTERRUPT_HARD | CPU_INTERRUPT_VIRQ);
                            intno = cpu_get_pic_interrupt(env);
                            qemu_log_mask(CPU_LOG_TB_IN_ASM, "Servicing hardware INT=0x%02x\n", intno);
                            do_interrupt_x86_hardirq(env, intno, 1);
                            /* ensure that no TB jump will be modified as
                               the program flow was changed */
                            next_tb = 0;
#if !defined(CONFIG_USER_ONLY)
                        } else if ((interrupt_request & CPU_INTERRUPT_VIRQ) &&
                                   (env->eflags & IF_MASK) && 
                                   !(env->hflags & HF_INHIBIT_IRQ_MASK)) {
                            int intno;
                            /* FIXME: this should respect TPR */
                            cpu_svm_check_intercept_param(env, SVM_EXIT_VINTR,
                                                          0);
                            intno = ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.int_vector));
                            qemu_log_mask(CPU_LOG_TB_IN_ASM, "Servicing virtual hardware INT=0x%02x\n", intno);
                            do_interrupt_x86_hardirq(env, intno, 1);
                            env->interrupt_request &= ~CPU_INTERRUPT_VIRQ;
                            next_tb = 0;
#endif
                        }
                    }
#elif defined(TARGET_PPC)
                    if ((interrupt_request & CPU_INTERRUPT_RESET)) {
                        cpu_reset(cpu);
                    }
                    if (interrupt_request & CPU_INTERRUPT_HARD) {
                        ppc_hw_interrupt(env);
                        if (env->pending_interrupts == 0)
                            env->interrupt_request &= ~CPU_INTERRUPT_HARD;
                        next_tb = 0;
                    }
#elif defined(TARGET_LM32)
                    if ((interrupt_request & CPU_INTERRUPT_HARD)
                        && (env->ie & IE_IE)) {
                        env->exception_index = EXCP_IRQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_MICROBLAZE)
                    if ((interrupt_request & CPU_INTERRUPT_HARD)
                        && (env->sregs[SR_MSR] & MSR_IE)
                        && !(env->sregs[SR_MSR] & (MSR_EIP | MSR_BIP))
                        && !(env->iflags & (D_FLAG | IMM_FLAG))) {
                        env->exception_index = EXCP_IRQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_MIPS)
                    if ((interrupt_request & CPU_INTERRUPT_HARD) &&
                        cpu_mips_hw_interrupts_pending(env)) {
                        /* Raise it */
                        env->exception_index = EXCP_EXT_INTERRUPT;
                        env->error_code = 0;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_OPENRISC)
                    {
                        int idx = -1;
                        if ((interrupt_request & CPU_INTERRUPT_HARD)
                            && (env->sr & SR_IEE)) {
                            idx = EXCP_INT;
                        }
                        if ((interrupt_request & CPU_INTERRUPT_TIMER)
                            && (env->sr & SR_TEE)) {
                            idx = EXCP_TICK;
                        }
                        if (idx >= 0) {
                            env->exception_index = idx;
                            do_interrupt(env);
                            next_tb = 0;
                        }
                    }
#elif defined(TARGET_SPARC)
                    if (interrupt_request & CPU_INTERRUPT_HARD) {
                        if (cpu_interrupts_enabled(env) &&
                            env->interrupt_index > 0) {
                            int pil = env->interrupt_index & 0xf;
                            int type = env->interrupt_index & 0xf0;

                            if (((type == TT_EXTINT) &&
                                  cpu_pil_allowed(env, pil)) ||
                                  type != TT_EXTINT) {
                                env->exception_index = env->interrupt_index;
                                do_interrupt(env);
                                next_tb = 0;
                            }
                        }
                    }
#elif defined(TARGET_ARM)
                    if (interrupt_request & CPU_INTERRUPT_FIQ
                        && !(env->uncached_cpsr & CPSR_F)) {
                        env->exception_index = EXCP_FIQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
                    /* ARMv7-M interrupt return works by loading a magic value
                       into the PC.  On real hardware the load causes the
                       return to occur.  The qemu implementation performs the
                       jump normally, then does the exception return when the
                       CPU tries to execute code at the magic address.
                       This will cause the magic PC value to be pushed to
                       the stack if an interrupt occurred at the wrong time.
                       We avoid this by disabling interrupts when
                       pc contains a magic address.  */
                    if (interrupt_request & CPU_INTERRUPT_HARD
                        && ((IS_M(env) && env->regs[15] < 0xfffffff0)
                            || !(env->uncached_cpsr & CPSR_I))) {
                        env->exception_index = EXCP_IRQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_UNICORE32)
                    if (interrupt_request & CPU_INTERRUPT_HARD
                        && !(env->uncached_asr & ASR_I)) {
                        env->exception_index = UC32_EXCP_INTR;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_SH4)
                    if (interrupt_request & CPU_INTERRUPT_HARD) {
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_ALPHA)
                    {
                        int idx = -1;
                        /* ??? This hard-codes the OSF/1 interrupt levels.  */
                        switch (env->pal_mode ? 7 : env->ps & PS_INT_MASK) {
                        case 0 ... 3:
                            if (interrupt_request & CPU_INTERRUPT_HARD) {
                                idx = EXCP_DEV_INTERRUPT;
                            }
                            /* FALLTHRU */
                        case 4:
                            if (interrupt_request & CPU_INTERRUPT_TIMER) {
                                idx = EXCP_CLK_INTERRUPT;
                            }
                            /* FALLTHRU */
                        case 5:
                            if (interrupt_request & CPU_INTERRUPT_SMP) {
                                idx = EXCP_SMP_INTERRUPT;
                            }
                            /* FALLTHRU */
                        case 6:
                            if (interrupt_request & CPU_INTERRUPT_MCHK) {
                                idx = EXCP_MCHK;
                            }
                        }
                        if (idx >= 0) {
                            env->exception_index = idx;
                            env->error_code = 0;
                            do_interrupt(env);
                            next_tb = 0;
                        }
                    }
#elif defined(TARGET_CRIS)
                    if (interrupt_request & CPU_INTERRUPT_HARD
                        && (env->pregs[PR_CCS] & I_FLAG)
                        && !env->locked_irq) {
                        env->exception_index = EXCP_IRQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
                    if (interrupt_request & CPU_INTERRUPT_NMI) {
                        unsigned int m_flag_archval;
                        if (env->pregs[PR_VR] < 32) {
                            m_flag_archval = M_FLAG_V10;
                        } else {
                            m_flag_archval = M_FLAG_V32;
                        }
                        if ((env->pregs[PR_CCS] & m_flag_archval)) {
                            env->exception_index = EXCP_NMI;
                            do_interrupt(env);
                            next_tb = 0;
                        }
                    }
#elif defined(TARGET_M68K)
                    if (interrupt_request & CPU_INTERRUPT_HARD
                        && ((env->sr & SR_I) >> SR_I_SHIFT)
                            < env->pending_level) {
                        /* Real hardware gets the interrupt vector via an
                           IACK cycle at this point.  Current emulated
                           hardware doesn't rely on this, so we
                           provide/save the vector when the interrupt is
                           first signalled.  */
                        env->exception_index = env->pending_vector;
                        do_interrupt_m68k_hardirq(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_S390X) && !defined(CONFIG_USER_ONLY)
                    if ((interrupt_request & CPU_INTERRUPT_HARD) &&
                        (env->psw.mask & PSW_MASK_EXT)) {
                        do_interrupt(env);
                        next_tb = 0;
                    }
#elif defined(TARGET_XTENSA)
                    if (interrupt_request & CPU_INTERRUPT_HARD) {
                        env->exception_index = EXC_IRQ;
                        do_interrupt(env);
                        next_tb = 0;
                    }
#endif
                   /* Don't use the cached interrupt_request value,
                      do_interrupt may have updated the EXITTB flag. */
                    if (env->interrupt_request & CPU_INTERRUPT_EXITTB) {
                        env->interrupt_request &= ~CPU_INTERRUPT_EXITTB;
                        /* ensure that no TB jump will be modified as
                           the program flow was changed */
                        next_tb = 0;
                    }
                }
                if (unlikely(env->exit_request)) {
                    env->exit_request = 0;
                    env->exception_index = EXCP_INTERRUPT;
                    cpu_loop_exit(env);
                }
#if defined(DEBUG_DISAS) || defined(CONFIG_DEBUG_EXEC)
                if (qemu_loglevel_mask(CPU_LOG_TB_CPU)) {
                    /* restore flags in standard format */
#if defined(TARGET_I386)
                    env->eflags = env->eflags | cpu_cc_compute_all(env, CC_OP)
                        | (DF & DF_MASK);
                    log_cpu_state(env, CPU_DUMP_CCOP);
                    env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);
#elif defined(TARGET_M68K)
                    cpu_m68k_flush_flags(env, env->cc_op);
                    env->cc_op = CC_OP_FLAGS;
                    env->sr = (env->sr & 0xffe0)
                              | env->cc_dest | (env->cc_x << 4);
                    log_cpu_state(env, 0);
#else
                    log_cpu_state(env, 0);
#endif
                }
#endif /* DEBUG_DISAS || CONFIG_DEBUG_EXEC */
                //parkhk
				if(memtrace){
					if(raw_trace_idx > TRACE_DUMP_SIZE){
						unsigned long i, icn=0,  c_cpu = raw_trace[5][0];
						for(i=0 ; i<raw_trace_idx ; i++){
							if(raw_trace[5][i] < 4 && c_cpu != raw_trace[5][i]){
								cpu_inst_num[0][cpu_inst_idx] = c_cpu;
								cpu_inst_num[1][cpu_inst_idx++] = icn; 
								c_cpu = raw_trace[5][i];
								icn=0;
							}
							if(raw_trace[0][i] == 0x2){
								icn++;
								cpu_ins_num[c_cpu]++;
							}
							fprintf(trace_all_fp, "%lx 0x%lx [0x%lx] %lu\n", raw_trace[0][i], raw_trace[1][i], raw_trace[2][i], raw_trace[5][i]);
							if(raw_trace[2][i] < 0x800000000000 && app_pgd == raw_trace[4][i]){
								fprintf(trace_aall_fp, "%lx 0x%lx [0x%lx]\n", raw_trace[0][i], raw_trace[1][i], raw_trace[2][i]);
								if(raw_trace[0][i] == 0){
									fprintf(trace_ar_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}else if(raw_trace[0][i] == 1){
									fprintf(trace_aw_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}else if(raw_trace[0][i] == 2){
									fprintf(trace_ai_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}
								//fprintf(trace_kall_fp, "%lx 0x%lx\n", raw_trace[0][i], raw_trace[2][i]);
							}
							//if(raw_trace[0][i] == 0x2 && raw_trace[1][i] == raw_trace[1][i+1] && raw_trace[2][i] == raw_trace[2][i+1])
							//	i++;
						}
						for(i=0 ; i<cpu_inst_idx ; i++){
							fprintf(trace_cpuinst_fp[cpu_inst_num[0][i]], "%lu\n", cpu_inst_num[1][i]);
						}
						cpu_inst_idx = 0;
                        raw_trace_idx = 0;
                    }
                    if(!trace_s_addr)
                        trace_recoding = 1;
                }else{
                    if(unlikely(raw_trace_idx)){
                        unsigned long i, icn=0,  c_cpu = raw_trace[5][0];
						for(i=0 ; i<raw_trace_idx ; i++){
							if(raw_trace[5][i] < 4 &&c_cpu != raw_trace[5][i]){
								cpu_inst_num[0][cpu_inst_idx] = c_cpu;
								cpu_inst_num[1][cpu_inst_idx++] = icn; 
								c_cpu = raw_trace[5][i];
								icn=0;
							}
							if(raw_trace[0][i] == 0x2){
								icn++;
								cpu_ins_num[c_cpu]++;
							}
							fprintf(trace_all_fp, "%lx 0x%lx [0x%lx] %lu\n", raw_trace[0][i], raw_trace[1][i], raw_trace[2][i], raw_trace[5][i]);
							if(raw_trace[2][i] < 0x800000000000 && app_pgd == raw_trace[4][i]){
								fprintf(trace_aall_fp, "%lx 0x%lx [0x%lx]\n", raw_trace[0][i], raw_trace[1][i], raw_trace[2][i]);
								if(raw_trace[0][i] == 0){
									fprintf(trace_ar_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}else if(raw_trace[0][i] == 1){
									fprintf(trace_aw_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}else if(raw_trace[0][i] == 2){
									fprintf(trace_ai_fp, "0x%lx 0x%lx [0x%lx]\n", app_trace_idx++, raw_trace[1][i], raw_trace[2][i]);
								}
								//fprintf(trace_kall_fp, "%lx 0x%lx\n", raw_trace[0][i], raw_trace[2][i]);
							}
							//if(raw_trace[0][i] == 0x2 && raw_trace[1][i] == raw_trace[1][i+1] && raw_trace[2][i] == raw_trace[2][i+1])
							//	i++;
						}
						for(i=0 ; i<cpu_inst_idx ; i++){
							fprintf(trace_cpuinst_fp[cpu_inst_num[0][i]], "%lu\n", cpu_inst_num[1][i]);
						}
						fprintf(trace_cpuinst_fp[0], "cpu 0 = %lu | cpu 1 = %lu | cpu 2 = %lu | cpu 3 = %lu  \n",  cpu_ins_num[0], cpu_ins_num[1],  cpu_ins_num[2], cpu_ins_num[3]);
						fprintf(trace_cpuinst_fp[0], "(instsize) cpu 0 = %lu | cpu 1 = %lu | cpu 2 = %lu | cpu 3 = %lu  \n",  count_cpu_inst[0], count_cpu_inst[1],  count_cpu_inst[2], count_cpu_inst[3]);

						cpu_inst_idx = 0;
						raw_trace_idx = 0;
					}
					trace_recoding = 0;
					app_pgd = 0;
					app_vaddr = 0;
                }
                spin_lock(&tb_lock);
                tb = tb_find_fast(env);
                /* Note: we do it here to avoid a gcc bug on Mac OS X when
                   doing it in tb_find_slow */
                if (tb_invalidated_flag) {
                    /* as some TB could have been invalidated because
                       of memory exceptions while generating the code, we
                       must recompute the hash index here */
                    next_tb = 0;
                    tb_invalidated_flag = 0;
                }
#ifdef CONFIG_DEBUG_EXEC
                qemu_log_mask(CPU_LOG_EXEC, "Trace %p [" TARGET_FMT_lx "] %s\n",
                             tb->tc_ptr, tb->pc,
                             lookup_symbol(tb->pc));
#endif
                /* see if we can patch the calling TB. When the TB
                   spans two pages, we cannot safely do a direct
                   jump. */
                /*if (next_tb != 0 && tb->page_addr[1] == -1) {
                    tb_add_jump((TranslationBlock *)(next_tb & ~3), next_tb & 3, tb);
                }*/
                spin_unlock(&tb_lock);

                /* cpu_interrupt might be called while translating the
                   TB, but before it is linked into a potentially
                   infinite loop and becomes env->current_tb. Avoid
                   starting execution if there is a pending interrupt. */
                env->current_tb = tb;
                
				if(trace_window>500 && trace_recoding){
					//parkhk
					trace_window = 0;
					env->exit_request = 1;
					raw_trace_idx--;
				}

                barrier();

                if (likely(!env->exit_request) ) {
                    tc_ptr = tb->tc_ptr;
                    /* execute the generated code */
                    next_tb = tcg_qemu_tb_exec(env, tc_ptr);
                    if ((next_tb & 3) == 2) {
                        /* Instruction counter expired.  */
                        int insns_left;
                        tb = (TranslationBlock *)(next_tb & ~3);
                        /* Restore PC.  */
                        cpu_pc_from_tb(env, tb);
                        insns_left = env->icount_decr.u32;
                        if (env->icount_extra && insns_left >= 0) {
                            /* Refill decrementer and continue execution.  */
                            env->icount_extra += insns_left;
                            if (env->icount_extra > 0xffff) {
                                insns_left = 0xffff;
                            } else {
                                insns_left = env->icount_extra;
                            }
                            env->icount_extra -= insns_left;
                            env->icount_decr.u16.low = insns_left;
                        } else {
                            if (insns_left > 0) {
                                /* Execute remaining instructions.  */
                                cpu_exec_nocache(env, insns_left, tb);
                            }
                            env->exception_index = EXCP_INTERRUPT;
                            next_tb = 0;
                            cpu_loop_exit(env);
                        }
                    }
                }
				env->current_tb = NULL;
                /* reset soft MMU for next block (it can currently
				   only be set by a memory fault) */
			} /* for(;;) */
        } else {
            /* Reload env after longjmp - the compiler may have smashed all
             * local variables as longjmp is marked 'noreturn'. */
            env = cpu_single_env;
        }
    } /* for(;;) */


#if defined(TARGET_I386)
    /* restore flags in standard format */
    env->eflags = env->eflags | cpu_cc_compute_all(env, CC_OP)
        | (DF & DF_MASK);
#elif defined(TARGET_ARM)
    /* XXX: Save/restore host fpu exception state?.  */
#elif defined(TARGET_UNICORE32)
#elif defined(TARGET_SPARC)
#elif defined(TARGET_PPC)
#elif defined(TARGET_LM32)
#elif defined(TARGET_M68K)
    cpu_m68k_flush_flags(env, env->cc_op);
    env->cc_op = CC_OP_FLAGS;
    env->sr = (env->sr & 0xffe0)
              | env->cc_dest | (env->cc_x << 4);
#elif defined(TARGET_MICROBLAZE)
#elif defined(TARGET_MIPS)
#elif defined(TARGET_OPENRISC)
#elif defined(TARGET_SH4)
#elif defined(TARGET_ALPHA)
#elif defined(TARGET_CRIS)
#elif defined(TARGET_S390X)
#elif defined(TARGET_XTENSA)
    /* XXXXX */
#else
#error unsupported target CPU
#endif

    /* fail safe : never use cpu_single_env outside cpu_exec() */
    cpu_single_env = NULL;
    return ret;
}
