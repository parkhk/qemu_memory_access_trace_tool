./scp_1111.sh &
./scp_2222.sh &
./scp_3333.sh &
./scp_4444.sh &
#ssh -p 1111 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_1 &
#ssh -p 2222 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_2 &
#ssh -p 3333 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_3 &
#ssh -p 4444 root@localhost "sysbench --test=memory --memory-block-size=2G --memory-total-size=20G run" | grep "execution time"> /home/parkhk/development/qemu_orig_run/sysbench_results/sysbench_result_4 &
