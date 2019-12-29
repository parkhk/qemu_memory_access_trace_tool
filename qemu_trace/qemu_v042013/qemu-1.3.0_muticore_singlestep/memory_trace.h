#ifndef __QEMU_FILE_H_INCLUDED__
#define __QEMU_FILE_H_INCLUDED__

/*
 * Appended by parkhk for memory trace
 */
#define TRACE_DUMP_SIZE 0x8000000
#define TRACE_DUMP_SIZE_2 0x8001000
//volatile static unsigned long trace_addr[32][TRACE_DUMP_SIZE];
//volatile static unsigned long trace_count[32];
//volatile unsigned long long trace_order;
//FILE *trace_fp[32];

volatile unsigned long trace_s_addr;
volatile unsigned long trace_e_addr;
/*req. type : phy. addr : virt. addr : pc(code) : cr3(pgd) : cpu_id*/
volatile unsigned long raw_trace[6][TRACE_DUMP_SIZE_2];
/*cpu id : # of inst. at one time*/
volatile unsigned long cpu_inst_num[2][TRACE_DUMP_SIZE_2];
/*Total # of inst. per each core*/
volatile unsigned long cpu_ins_num[4];
/*Total size of Weighted inst. per each core(weight = instruction size)*/
volatile unsigned long count_cpu_inst[4];
volatile unsigned long cpu_inst_idx;
volatile unsigned long raw_trace_idx;
volatile unsigned long app_trace_idx;


volatile unsigned long tb_paddr_cache;
volatile unsigned long tb_vaddr_cache;
volatile unsigned long tb_lvaddr_cache;
volatile unsigned long tb_pc_cache;
volatile unsigned long tb_cr3_cache;
volatile unsigned long tb_code_size;

volatile unsigned long app_vaddr; 
volatile unsigned long app_pgd; 

volatile unsigned int memtrace;
volatile unsigned int trace_recoding;
volatile unsigned int memtrace_code;
/*volatile unsigned long mem_trace_cnt;
volatile unsigned long mem_ktrace_cnt;
volatile unsigned long mem_atrace_cnt;*/
FILE *trace_all_fp;

FILE *trace_kall_fp;
FILE *trace_aall_fp;
FILE *trace_aw_fp;
FILE *trace_ar_fp;
FILE *trace_ai_fp;
FILE *trace_cpuinst_fp[4];
/*FILE *trace_pc_fp;
FILE *trace_read_fp;
FILE *trace_write_fp;
FILE *trace_inst_fp;
FILE *trace_aread_fp;
FILE *trace_awrite_fp;
FILE *trace_ainst_fp;
FILE *trace_kread_fp;
FILE *trace_kwrite_fp;
FILE *trace_kinst_fp;
*/
/*
 * End of modified source -  by parkhk 
 */

#endif //__QEMU_FILE_H

