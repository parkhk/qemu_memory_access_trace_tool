modprobe nbd max_part=16
qemu-nbd -c /dev/nbd0 fedora_18.img
qemu-nbd -c /dev/nbd1 home.img
vgscan 
vgchange -ay VolGroup00 
lvs
mount /dev/VolGroup00/LogVol00 home
