modprobe nbd max_part=16
qemu-nbd -c /dev/nbd0 fedora_18.img
qemu-nbd -c /dev/nbd1 home.img
#partprobe /dev/nbd0