#ifndef __QEMU_FILE_H_INCLUDED__
#define __QEMU_FILE_H_INCLUDED__

/*
 * Appended by parkhk for memory trace
 */
//#define TRACE_DUMP_SIZE 100000
//volatile static unsigned long trace_op[32][TRACE_DUMP_SIZE];
//volatile static unsigned long trace_addr[32][TRACE_DUMP_SIZE];
#define MEM_CNT 0x2000000
#define TRACE_CNT 0x2000000
unsigned long trace_read_cnt[MEM_CNT];
unsigned long trace_write_cnt[MEM_CNT];
unsigned long trace_inst_cnt[MEM_CNT];
//volatile static unsigned long trace_count[32];
//volatile unsigned long long trace_order;
//FILE *trace_fp[32];
unsigned int mem_trace;
unsigned int mem_trace_started;
unsigned long mem_trace_index;
char file_name[8][30];
char file_idx;
unsigned int file_seq;
FILE *trace_fp[8];


/*
 * End of modified source -  by parkhk 
 */

#endif //__QEMU_FILE_H

