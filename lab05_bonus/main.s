	.file	"main.c"
	.text
	.globl	my_write
	.type	my_write, @function
my_write:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	$1, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %r8
	movq	-32(%rbp), %r9
	movq	-40(%rbp), %r10
#APP
# 8 "main.c" 1
	mov %rcx, %rax 
mov %r8, %rdi 
mov %r9, %rsi 
mov %r10, %rdx 
syscall 
mov %rax, %rcx
# 0 "" 2
#NO_APP
	movq	%rcx, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	my_write, .-my_write
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -28(%rbp)
	movabsq	$2338328219631577204, %rax
	movq	%rax, -19(%rbp)
	movl	$6647072, -12(%rbp)
	movl	$11, -24(%rbp)
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movl	-28(%rbp), %eax
	cltq
	leaq	-19(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	my_write
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
