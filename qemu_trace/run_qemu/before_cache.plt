#!/bin/gnuplot
set terminal png truecolor size 1248,1024
#set yrange [0:50.0]
set grid
#set xtic rotate by 90
#set style data histograms
#set style fill solid 1.00 border -1
#plot "cpu_read_cnt" using 2:xtic(1) title "read request count"
set pointsize 0.3
set output "all_requests.png"
plot "mem_trace_inst" using 1:2 ti "Instruction", "mem_trace_read" using 1:2 ti "Read", "mem_trace_write" using 1:2 ti "Write"
set output "inst_requests.png"
plot "mem_trace_inst" using 1:2 ti "Instruction"
set output "read_requests.png"
plot "mem_trace_read" using 1:2 ti "Read"
set output "write_requests.png"
plot "mem_trace_write" using 1:2 ti "Write"
