### centos install
#qemu-system-x86_64 -hda ./disk_img/fedora_18.img  -hdb ./disk_img/home.img -cdrom ./disk_img/Fedora-10-x86_64-DVD.iso -boot d -m 4096

### run centos with original
#qemu-system-x86_64 -hda ../disk_image/centos_5.5.img -hdb ../disk_image/home.img -m 4096 -smp 4

### run centos
#qemu-mtrace-x86_64 -hda ../disk_image/centos-5.9.img -hdb ../disk_image/home.img -m 4096 
#qemu-system-x86_64 -hda ./disk_img/fedora_18.img -hdb ./disk_img/home.img -m 4096
qemu-unicore_mtrace-x86_64 -hda ./disk_img/fedora_18.img -hdb ./disk_img/home.img -m 4096
#qemu-unicore_mtrace-x86_64 -hda ./disk_img/centos_5.5.img -hdb ./disk_img/home.img -m 4096
#qemu-mtrace-x86_64 -smp 4 -hda ../disk_image/centos_5.5.img -hdb ../disk_image/home.img -m 4096 -clock dynticks -rtc clock=vm #-icount 1 #auto

# handle SIGUSR1 SIGUSR2 SIGTRAP nostop noprint
