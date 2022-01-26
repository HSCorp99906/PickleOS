all:
	gcc -c -m32 src/x86_64/kernel/kmain.c -ffreestanding -fno-pie -fstack-protector -o obj/kmain.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/VGA.c -ffreestanding -fno-pie -fstack-protector -o obj/vga.o
	gcc -c -m32 src/x86_64/kernel/util/impl/strings.c -ffreestanding -fno-pie -fstack-protector -o obj/strings.o
	nasm -felf32 src/x86_64/kernel/kernel.S -o obj/kernel.o
	i686-elf-ld -T link.ld obj/*.o -o Pickle/boot/kernel.bin
	grub-mkrescue -o PickleOS.iso Pickle/
	sudo dd bs=4M if=PickleOS.iso of=/dev/sdb
	rm PickleOS.iso
	sudo qemu-system-x86_64 -hdb /dev/sdb -d int -D logfile.txt -M smm=off -monitor stdio 
