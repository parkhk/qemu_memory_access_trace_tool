#!/bin/gnuplot
set terminal png size 1248,1024
#set terminal postscript
#set xrange [5300000:8000000]
set yrange [16900000000.0:17200000000.0]
#set format x "0x%x"
#set format y "0x%x"
set pointsize 0.3
#plot  "./trace"
plot "memtrace_inst" using 1:3 ti "Instruction", "memtrace_read" using 1:3 ti "Read", "memtrace_write" using 1:3 ti "Write"
#plot  "bank_conflict" #"trace" using 2
