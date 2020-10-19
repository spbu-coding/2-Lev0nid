	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L1
	leal	-1(%rsi), %r10d
	movl	$1, %r9d
	movq	%rdi, %r8
	addq	$1, %r10
	cmpq	%r10, %r9
	je	.L1
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%r9, %rax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	(%r8), %edx
	movl	(%rdi,%rax,4), %ecx
	cmpl	%ecx, %edx
	jle	.L3
	movl	%ecx, (%r8)
	movl	%edx, (%rdi,%rax,4)
.L3:
	addq	$1, %rax
	cmpl	%eax, %esi
	jg	.L4
	addq	$1, %r9
	addq	$4, %r8
	cmpq	%r10, %r9
	jne	.L8
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
