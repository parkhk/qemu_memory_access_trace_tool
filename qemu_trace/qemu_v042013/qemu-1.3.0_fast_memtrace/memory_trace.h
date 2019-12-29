#ifndef __QEMU_FILE_H_INCLUDED__
#define __QEMU_FILE_H_INCLUDED__

/*
 * Appended by parkhk for memory trace
 */
#define TRACE_DUMP_SIZE 0x40000000
#define TRACE_DUMP_SIZE_2 0x40001000
//volatile static unsigned long trace_addr[32][TRACE_DUMP_SIZE];
//volatile static unsigned long trace_count[32];
//volatile unsigned long long trace_order;
//FILE *trace_fp[32];

volatile unsigned long trace_s_addr;
volatile unsigned long trace_e_addr;
volatile unsigned long raw_trace[3][TRACE_DUMP_SIZE_2];
volatile unsigned long raw_trace_idx;

volatile unsigned long *trace_paddr;
volatile unsigned long *trace_vaddr;
volatile unsigned long trace_inst_idx;

volatile unsigned int memtrace;
volatile unsigned int trace_recoding;
volatile unsigned int memtrace_code;
volatile unsigned int memtrace_data;
volatile unsigned int memtrace_interrupt;
/*volatile unsigned long mem_trace_cnt;
volatile unsigned long mem_ktrace_cnt;
volatile unsigned long mem_atrace_cnt;*/
FILE *trace_all_fp;
/*FILE *trace_kall_fp;
FILE *trace_aall_fp;
FILE *trace_pc_fp;
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

