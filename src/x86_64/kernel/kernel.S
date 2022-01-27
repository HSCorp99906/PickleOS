bits 32
global _kentry
extern _start

_kentry:
    call _start

post_exec:
    hlt
    jmp post_exec
