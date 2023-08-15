	.file	"f15.cc"
	.text
	.globl	_Z12array_accessPil
	.type	_Z12array_accessPil, @function
_Z12array_accessPil:
	endbr64
	movl	(%rdi,%rsi,4), %eax
	ret
	.size	_Z12array_accessPil, .-_Z12array_accessPil
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
