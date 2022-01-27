global _gdt_flush
extern gdt


_gdt_flush:
    lgdt  [gdt]
    cli
    hlt
