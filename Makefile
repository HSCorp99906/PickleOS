all:
	gcc -c -m32 src/x86_64/kernel/kmain.c -mgeneral-regs-only -ffreestanding -fno-pie -fstack-protector -o obj/kmain.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/PIC.c -ffreestanding -fno-pie -fstack-protector -o obj/pic.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/VGA.c -ffreestanding -fno-pie -fstack-protector -o obj/vga.o
	gcc -c -m32 src/x86_64/kernel/util/impl/strings.c -ffreestanding -fno-pie -fstack-protector -o obj/strings.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/IO.c -ffreestanding -fno-pie -fstack-protector -o obj/io.o
	gcc -c -m32 src/x86_64/kernel/interrupts/impl/IDT.c -ffreestanding -fno-pie -fstack-protector -o obj/idt.o
	gcc -c -m32 src/x86_64/kernel/drivers/impl/graphics.c -ffreestanding -fno-pie -fstack-protector -o obj/gfx.o
	gcc -c -m32 src/x86_64/kernel/memory/impl/memset.c -ffreestanding -fno-pie -fstack-protector -o obj/memset.o
	nasm -felf32 src/x86_64/kernel/kernel.S -o objres/kernel.o
	nasm -fbin src/x86_64/boot/bootloader.S -o bin/bootloader.bin
	i686-elf-ld -T link.ld objres/*.o obj/*.o --oformat binary -o bin/kernel.bin
	cat bin/bootloader.bin bin/kernel.bin > bin/PickleOS.bin
	sudo dd if=/dev/zero of=PickleOS.img bs=1024 count=1440
	sudo dd if=bin/PickleOS.bin of=PickleOS.img conv=notrunc
	sudo dd if=PickleOS.img of=/dev/sdb
	sudo qemu-system-x86_64 -hdb /dev/sdb -d int -D logfile.txt -M smm=off -monitor stdio 
