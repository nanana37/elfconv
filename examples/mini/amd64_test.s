.intel_syntax noprefix
.section .data

success_msg: 
    .string "success.\n"

mov_gprv_immz_error_msg:
    .string "[ERROR]: MOV_GPRv_IMMz\n"

add_gprv_immb_error_msg:
    .string "[ERROR] ADD_GPRv_IMMb\n"

mov_memv_gprv_error_msg:
    .string "[ERROR] MOV_MEMv_GPRv\n"

call_procedure_error_msg:
    .string "[ERROR] CALL_NEAR_RELBRd\n"

push_pop_error_msg:
    .string "[ERROR] PUSH_POP\n"

mov_gpr8_immb_b0_error_msg:
    .string "[ERROR] MOV_GPR8_IMMb_B0\n"

cmp_al_immb_error_msg:
    .string "[ERROR] CMP_AL_IMMb\n"

mov_memb_gpr8_error_msg:
    .string "[ERROR] MOV_MEMb_GPR8\n"

setl_gpr8_error_msg:
    .string "[ERROR] SETL_GPR8\n"

mov_gpr8_memb_error_msg:
    .string "[ERROR] MOV_GPR8_MEMb\n"

test_al_immb_error_msg:
    .string "[ERROR] TEST_AL_IMMb\n"

mov_memb_immb_error_msg:
    .string "[ERROR] MOV_MEMb_IMMb\n"

cdq_error_msg:
    .string "[ERROR] CDQ\n"

cdqe_error_msg:
    .string "[ERROR] CDQE\n"

jle_relbrd_error_msg:
    .string "[ERROR] JLE_RELBRd\n"

mov_gprv_immv_error_msg:
    .string "[ERROR] MOV_GPRv_IMMv\n"

add_gprv_immz_error_msg:
    .string "[ERROR] ADD_GPRv_IMMz\n"

.section .text
.global _start

_start:
    jmp test_add_gprv_immz

test_add_gprv_immz:
    xor eax, eax
    .byte 0x81, 0xC0  # ADD EAX, IMM32
    .long 0x12345678  # IMM32
    cmp rax, 0x12345678
    jne fail_add_gprv_immz
    jmp test_mov_gprv_immv

fail_add_gprv_immz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + add_gprv_immz_error_msg]
    mov rdx, 22
    syscall
    jmp exit

test_mov_gprv_immv:
    xor rax, rax
    .byte 0xB8  # MOV RAX, IMM32
    .long 0x12345678  # IMM32
    cmp rax, 0x12345678
    jne fail_mov_gprv_immv
    jmp test_jle_relbrd  # Jump to the next test

fail_mov_gprv_immv:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_gprv_immv_error_msg]
    mov rdx, 22
    syscall
    jmp exit

test_jle_relbrd:
    mov eax, 0
    sub eax, 1
    jle force_jle_relbrd
    jmp fail_jle_relbrd

fail_jle_relbrd:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + jle_relbrd_error_msg]
    mov rdx, 20
    syscall
    jmp exit

test_cdqe:
    mov rbp, rsp
    sub rsp, 8

    # Test with a negative value
    mov eax, -1  # EAX = 0xFFFFFFFF
    .byte 0x48, 0x98  # CDQE
    cmp rax, 0xFFFFFFFFFFFFFFFF
    jne fail_cdqe

    # Test with a positive value
    mov eax, 1  # EAX = 0x00000001
    .byte 0x48, 0x98  # CDQE
    cmp rax, 0x0000000000000001
    jne fail_cdqe
    jmp test_cdq

fail_cdqe:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + cdqe_error_msg]
    mov rdx, 14
    syscall
    jmp exit

test_cdq:
    mov rbp, rsp
    sub rsp, 8

    # Test with a negative value
    mov eax, -1
    .byte 0x99  # CDQ
    cmp edx, 0xFFFFFFFF
    jne fail_cdq

    # Test with a positive value
    mov eax, 1
    .byte 0x99  # CDQ
    cmp edx, 0x00000000
    jne fail_cdq
    jmp test_mov_memb_immb

fail_cdq:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + cdq_error_msg]
    mov rdx, 17
    syscall
    jmp exit

test_mov_memb_immb:
    mov rbp, rsp
    sub rsp, 8
    .byte 0xC6, 0x45, 0xFF, 0x40  # mov byte ptr [rbp - 1], 0x40
    cmp byte ptr [rbp - 1], 0x40
    jne fail_mov_memb_immb
    jmp test_test_al_immb

fail_mov_memb_immb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_memb_immb_error_msg]
    mov rdx, 22
    syscall
    jmp exit

test_test_al_immb:
    mov rbp, rsp
    sub rsp, 8
    mov al, 0x41
    .byte 0xA8, 0x41  # test al, 0x41
    cmp al, 0x41
    jne fail_test_al_immb
    # Check if ZF (Zero Flag) is set correctly
    jnz fail_test_al_immb
    jmp test_mov_gpr8_memb

fail_test_al_immb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + test_al_immb_error_msg]
    mov rdx, 21
    syscall
    jmp exit

test_mov_gpr8_memb:
    mov rbp, rsp
    sub rsp, 8
    mov byte ptr [rbp - 1], 0x42
    .byte 0x8A, 0x45, 0xFF  # mov al, byte ptr [rbp - 1]
    cmp al, 0x42
    jne fail_mov_gpr8_memb
    jmp test_setl_gpr8

fail_mov_gpr8_memb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_gpr8_memb_error_msg]
    mov rdx, 23
    syscall
    jmp exit

test_setl_gpr8:
    mov rbp, rsp
    sub rsp, 8
    mov al, -1
    sub al, 1
    .byte 0x0F, 0x9C, 0xC0  # setl al
    cmp al, 1
    jne fail_setl_gpr8
    jmp test_mov_memb_gpr8

fail_setl_gpr8:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + setl_gpr8_error_msg]
    mov rdx, 22
    syscall
    jmp exit

test_mov_memb_gpr8:
    mov rbp, rsp
    sub rsp, 8
    mov al, 0x40
    .byte 0x88, 0x45, 0xFF # mov byte ptr [rbp - 1], al
    cmp byte ptr [rbp - 1], 0x40
    jne fail_mov_memb_gpr8
    jmp test_cmp_al_immb

fail_mov_memb_gpr8:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_memb_gpr8_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_cmp_al_immb:
    mov rbp, rsp
    sub rsp, 8
    .byte 0xB0, 0x41  # mov al, 0x41
    .byte 0x3C, 0x41  # cmp al, 0x41
    jne fail_cmp_al_immb
    jmp test_mov_gpr8_immb_b0

fail_cmp_al_immb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + cmp_al_immb_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_mov_gpr8_immb_b0:
    mov rbp, rsp
    sub rsp, 8
    .byte 0xB0, 0x42 # mov al, 0x42
    cmp al, 0x42
    jne fail_mov_gpr8_immb_b0
    jmp test_mov_gprv_immz

fail_mov_gpr8_immb_b0:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_gpr8_immb_b0_error_msg]
    mov rdx, 25
    syscall
    jmp exit

.globl func1
.type  func1, @function

func1:
    push rbp
    mov rbp, rsp
    mov qword ptr [rbp - 8], rdi
    mov qword ptr [rbp - 16], rsi
    mov rax, qword ptr [rbp - 8]
    add rax, qword ptr [rbp - 16]
    pop rbp
    ret

test_mov_gprv_immz:
    mov rbx, 50   
    cmp rbx, 50
    jne fail_mov_gprv_immz
    jmp test_add_gprv_immb

fail_mov_gprv_immz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_gprv_immz_error_msg]
    mov rdx, 24
    syscall
    jmp exit

test_add_gprv_immb:
    mov rbx, 10
    add rbx, 20
    cmp rbx, 30
    jne fail_add_gprv_immb
    jmp test_mov_memv_gprv

fail_add_gprv_immb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + add_gprv_immb_error_msg]
    mov rdx, 23
    syscall
    jmp exit

test_mov_memv_gprv:
    mov rbp, rsp
    sub rsp, 8
    mov qword ptr [rbp - 4], 20
    mov rbx, qword ptr [rbp - 4]
    cmp rbx, 20
    jne fail_mov_memv_gprv
    jmp test_push_pop
    
fail_mov_memv_gprv:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + mov_memv_gprv_error_msg]
    mov rdx, 23
    syscall
    jmp exit

test_push_pop:
    mov rax, 15
    push rax
    pop rbx
    cmp rbx, 15
    jne fail_push_pop
    jmp test_call_procedure

fail_push_pop:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + push_pop_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_call_procedure:
    mov rdi, 30
    mov rsi, 30
    call func1
    cmp rax, 60
    jne fail_call_procedure
    jmp test_jnl_relbrd

fail_call_procedure:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + call_procedure_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_jnl_relbrd:
    mov rax, 20
    cmp rax, 20
    jge test_cmp_memv_immz
    jmp fail_jnl_relbrd

.section .data
jnl_relbrd_error_msg:
    .string "[ERROR] JNL_RELBRd\n"
.section .text

fail_jnl_relbrd:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + jnl_relbrd_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_cmp_memv_immz:
    mov rbp, rsp
    sub rsp, 8
    mov dword ptr [rbp - 4], 100
    cmp dword ptr [rbp - 4], 100
    jne fail_cmp_memv_immz
    jmp test_sub_gprv_immz

.section .data
cmp_memv_immz_error_msg:
    .string "[ERROR] CMP_MEMv_IMMz\n"
.section .text

fail_cmp_memv_immz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + cmp_memv_immz_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_sub_gprv_immz:
    mov rax, 20
    sub rax, 10
    cmp rax, 10
    jne fail_sub_gprv_immz
    jmp test_cmp_memv_immb

.section .data
sub_gprv_immz_error_msg:
    .string "[ERROR] SUB_GPRv_IMMz\n"
.section .text

fail_sub_gprv_immz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + sub_gprv_immz_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_cmp_memv_immb:
    mov rbp, rsp
    sub rsp, 8
    mov dword ptr [rbp - 4], 0
    cmp dword ptr [rbp - 4], 0
    jne fail_cmp_memv_immb
    jmp test_jnz_relbrd

.section .data
cmp_memv_immb_error_msg:
    .string "[ERROR] CMP_MEMv_IMMb\n"
.section .text

fail_cmp_memv_immb:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + cmp_memv_immb_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_jnz_relbrd:
    mov rax, 15
    cmp rax, 15
    jne fail_jnz_relbrd
    jmp test_movsxd_gprv_memz

.section .data
jnz_relbrd_error_msg:
    .string "[ERROR] JNZ_RELBRd\n"
.section .text

fail_jnz_relbrd:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + jnz_relbrd_error_msg]
    mov rdx, 25
    syscall
    jmp exit

.section .data
movsxd_gprv_memz_error_msg:
    .string "[ERROR] MOVSXD_GPRv_MEMz\n"
.section .text

test_movsxd_gprv_memz:
    mov rbp, rsp
    sub rsp, 8
    mov dword ptr [rbp - 4], 5
    movsxd rax, dword ptr [rbp - 4]
    cmp rax, 5
    jne fail_movsxd_gprv_memz
    jmp test_shl_gprv_immb_c1r4

fail_movsxd_gprv_memz:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + movsxd_gprv_memz_error_msg]
    mov rdx, 25
    syscall
    jmp exit

test_shl_gprv_immb_c1r4:
    mov rbp, rsp
    sub rsp, 8
    mov rax, 0x1
    .byte 0x48, 0xC1, 0xE0, 0x02  # shl rax, 2 (C1 /4)
    cmp rax, 4
    jne fail_shl_gprv_immb_c1r4
    jmp success

.section .data
shl_gprv_immb_c1r4_error_msg:
    .string "[ERROR] SHL_GPRv_IMMb_C1r4\n"
.section .text

fail_shl_gprv_immb_c1r4:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + shl_gprv_immb_c1r4_error_msg]
    mov rdx, 26
    syscall
    jmp exit

force_jle_relbrd:
    jmp test_cdqe

success:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rip + success_msg]
    mov rdx, 9
    syscall
    jmp exit

exit:
    mov rax, 60
    xor rdi, rdi
    syscall