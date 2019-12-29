### centos install
#./qemu-system-x86_64_1.6 -hda ./fedora12_disks/fedora_disk_8G_1.img -cdrom ./Fedora-12-x86_64-DVD.iso -boot d -m 4096
date +%H:%M:%S.%2N > booting_time/booting_start
./qemu-system-x86_64_1.6 -hda ./fedora12_disks/fedora_disk_8G_1.img -m 4096 -redir tcp:1111::22 &
./qemu-system-x86_64_1.6 -hda ./fedora12_disks/fedora_disk_8G_2.img -m 4096 -redir tcp:2222::22 &
./qemu-system-x86_64_1.6 -hda ./fedora12_disks/fedora_disk_8G_3.img -m 4096 -redir tcp:3333::22 &
./qemu-system-x86_64_1.6 -hda ./fedora12_disks/fedora_disk_8G_4.img -m 4096 -redir tcp:4444::22 &

### run centos with origina:wql
#./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_1.img -m 1024 -redir tcp:1111::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_2.img -m 1024 -redir tcp:2222::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_3.img -m 1024 -redir tcp:3333::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_4.img -m 1024 -redir tcp:4444::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_5.img -m 1024 -redir tcp:5555::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_6.img -m 1024 -redir tcp:6666::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_7.img -m 1024 -redir tcp:7777::22 & ./qemu-system-x86_64_1.6 -hda ./disk_img/fedora_disk_8G_8.img -m 1024 -redir tcp:8888::22 &
#./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_1.img -m 1024 -redir tcp:1111::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_2.img -m 1024 -redir tcp:2222::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_3.img -m 1024 -redir tcp:3333::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_4.img -m 1024 -redir tcp:4444::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_5.img -m 1024 -redir tcp:5555::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_6.img -m 1024 -redir tcp:6666::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_7.img -m 1024 -redir tcp:7777::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_8.img -m 1024 -redir tcp:8888::22 &
#./qemu-system-x86_64_1.6 -hda ./fedora19_disks/fedora19_1.img -m 2048 -redir tcp:1111::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_2.img -m 2048 -redir tcp:2222::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_3.img -m 2048 -redir tcp:3333::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_4.img -m 2048 -redir tcp:4444::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_5.img -m 2048 -redir tcp:5555::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_6.img -m 2048 -redir tcp:6666::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_7.img -m 2048 -redir tcp:7777::22 & ./qemu-system-x86_64 -hda ./fedora19_disks/fedora19_8.img -m 2048 -redir tcp:8888::22 &
#./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_1.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_2.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_3.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_4.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_5.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_6.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_7.img -m 1024 & ./qemu-system-x86_64 -hda ./disk_img/fedora_disk_8G_8.img -m 1024
#qemu-system-x86_64 -hda ./centos-6.4.qcow -m 4096
#qemu-system-x86_64 -hda /home/parkhk/development/qemu_trace/run_qemu/disk_img/fedora_18.img -m 4096 -smp 4
 

### run centos
#qemu-system-x86_64 -hda ./centos-6.4.qcow -m 1024

