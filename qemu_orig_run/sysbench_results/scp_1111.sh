echo "start 1st" 
ssh -p 1111 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_1
echo "end 1st"