	.file	"f06.cc"
	.text
	.globl	_Z1fPi
	.type	_Z1fPi, @function
_Z1fPi:
	endbr64
	movl	(%rdi), %eax
	ret
	.size	_Z1fPi, .-_Z1fPi
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
