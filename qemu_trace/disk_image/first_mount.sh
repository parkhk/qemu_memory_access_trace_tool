modprobe nbd max_part=63
qemu-nbd -c /dev/nbd4 centos-5.9.img
qemu-nbd -c /dev/nbd5 home.img
mount /dev/nbd4p1 root_fs
mount /dev/nbd5p1 root_fs/home
