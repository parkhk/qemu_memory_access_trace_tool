echo "start 3rd"
ssh -p 3333 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_3
echo "end 3rd"
