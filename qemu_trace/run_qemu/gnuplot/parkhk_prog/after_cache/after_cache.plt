#!/bin/gnuplot
set terminal png truecolor size 1248,1024
#set yrange [0:50.0]
set grid
#set xtic rotate by 90
#set style data histograms
#set style fill solid 1.00 border -1
#plot "cpu_read_cnt" using 2:xtic(1) title "read request count"
set pointsize 0.3
set output "read_cnt.png"
plot "mem_read_cnt" using 1:2 ti "Read Request Count"
set output "write_cnt.png"
plot "mem_write_cnt" using 1:2 ti "Write Request Count"
set output "inst_cnt.png"
plot "mem_inst_cnt" using 1:2 ti "Instruction Request Count"
set output "all_mem_access.png"
plot "cache_trace_inst" using 1:2 ti "Instruction", "cache_trace_read" using 1:2 ti "Read", "cache_trace_write" using 1:2 ti "Write"
set output "inst_mem_access.png"
plot "cache_trace_inst" using 1:2 ti "Instruction"
set output "read_mem_access.png"
plot "cache_trace_read" using 1:2 ti "Read"
set output "write_mem_access.png"
plot "cache_trace_write" using 1:2 ti "Write"
