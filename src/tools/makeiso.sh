#!/bin/bash

os_image=$1
iso_dir=$2

if [ ! -f $os_image ]; then
  echo "Can't find file $os_image, aborting"
  exit 1
fi

if ! which grub-mkrescue; then
  echo "ERROR: You need grub-mkrescue installed in order to make an ISO"
  exit 1
fi

if ! which xorriso; then
  echo "ERROR: You need xorriso installed in order to make an ISO"
  echo "Using Debian? Try sudo apt-get install xorriso"
  exit 1
fi

mkdir -p $iso_dir/boot/grub
cp $os_image $iso_dir/boot
cat << EOF 1>$iso_dir/boot/grub/grub.cfg
menuentry "osdev" {
  multiboot /boot/$os_image
}
EOF

# First remove existing ISO, it can't handle existing ISOs well
rm -f $iso_dir/cdrom.iso

grub-mkrescue -o $iso_dir/cdrom.iso $iso_dir
