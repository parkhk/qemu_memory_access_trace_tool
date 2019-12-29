#ifndef __QEMU_FILE_H_INCLUDED__
#define __QEMU_FILE_H_INCLUDED__

/*
 * Appended by parkhk for memory trace
 */
#define TRACE_DUMP_SIZE 0x10000000
#define TRACE_DUMP_SIZE_2 0x10001000

volatile unsigned long raw_trace[3][TRACE_DUMP_SIZE_2];
volatile unsigned long raw_trace_idx;

volatile unsigned long tb_paddr_cache;
volatile unsigned long tb_vaddr_cache;
volatile unsigned long tb_lvaddr_cache;

volatile unsigned long app_vaddr; 
volatile unsigned long app_pgd; 

volatile unsigned int memtrace;
volatile unsigned int trace_recoding;
volatile unsigned int memtrace_code;

FILE *trace_all_fp;
/*
 * End of modified source -  by parkhk 
 */

#endif //__QEMU_FILE_H

