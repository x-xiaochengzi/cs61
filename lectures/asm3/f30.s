	.file	"f30.cc"
	.text
	.globl	_Z1flll
	.type	_Z1flll, @function
_Z1flll:
	endbr64
	salq	$20, %rdi
	imulq	%rdx, %rsi
	leaq	(%rdi,%rsi), %rax
	ret
	.size	_Z1flll, .-_Z1flll
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
