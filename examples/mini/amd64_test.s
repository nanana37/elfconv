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

.section .text
.globl _start

_start:                  
    jmp test_cmp_al_immb

test_cmp_al_immb:
    mov rbp, rsp
    sub rsp, 8
    .byte 0xB0, 0x42  # mov al, 0x42
    .byte 0x3C, 0x42  # cmp al, 0x42
    jne fail_cmp_al_immb
    jmp test_mov_gpr8_immb_b0

.section .data
cmp_al_immb_error_msg:
    .string "[ERROR] CMP_AL_IMMb\n"
.section .text

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

.section .data
mov_gpr8_immb_b0_error_msg:
    .string "[ERROR] MOV_GPR8_IMMb_B0\n"
.section .text

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
    mov rdx, 25
    syscall
    jmp exit

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