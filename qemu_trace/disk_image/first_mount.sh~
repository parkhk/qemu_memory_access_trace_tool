modprobe nbd max_part=63
qemu-nbd -c /dev/nbd0 centos_5.5.img
qemu-nbd -c /dev/nbd1 home.img
mount /dev/nbd0p1 root_fs
mount /dev/nbd1p1 root_fs/home
