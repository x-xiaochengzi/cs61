	.file	"f17.cc"
	.text
	.globl	_Z12array_accessP2prl
	.type	_Z12array_accessP2prl, @function
_Z12array_accessP2prl:
	endbr64
	movl	(%rdi,%rsi,8), %eax
	ret
	.size	_Z12array_accessP2prl, .-_Z12array_accessP2prl
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
