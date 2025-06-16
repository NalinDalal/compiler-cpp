.global main
.text
main:
    mov $5, %t0
    mov $3, %t1
    mov $2, %t2
    mov %t1, %rax
    imul %t2, %rax
    mov %rax, %t3
    mov %t0, %rax
    add %t3, %rax
    mov %rax, %t4
    mov %t4, %a
    mov %a, %rdi
    call print_int
    mov $0, %rax
    ret
