echo "start 2nd" 
ssh -p 2222 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_2
echo "end 2nd"
