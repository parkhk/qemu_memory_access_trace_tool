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

/* [request type(L(0)/S(1)/I(2)] [CPU ID] [Physical Address] [DATA SIZE] [Virtual Address]*/
volatile unsigned long raw_trace[5][TRACE_DUMP_SIZE_2];
volatile unsigned long raw_trace_idx;
volatile unsigned long trace_order;

volatile unsigned long tb_paddr_cache; //physical address of code
volatile unsigned long inst_size; //virtual address of PC + instruction size

volatile unsigned int memtrace;
volatile unsigned int trace_recoding;
volatile unsigned int memtrace_code;

volatile unsigned long jiffies_info; //time information

FILE *trace_all_fp;
FILE *trace_cpu_fp[4];
/*
 * End of modified source -  by parkhk 
 */

#endif //__QEMU_FILE_H

