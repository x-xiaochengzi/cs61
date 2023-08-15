	.file	"f16.cc"
	.text
	.globl	_Z12array_accessPll
	.type	_Z12array_accessPll, @function
_Z12array_accessPll:
	endbr64
	movl	(%rdi,%rsi,8), %eax
	ret
	.size	_Z12array_accessPll, .-_Z12array_accessPll
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
