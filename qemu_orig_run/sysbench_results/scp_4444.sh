echo "start 4th"
ssh -p 4444 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_4
echo "end 4th"