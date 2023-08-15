	.file	"f09.cc"
	.text
	.globl	_Z3sumv
	.type	_Z3sumv, @function
_Z3sumv:
	endbr64
	movl	b(%rip), %eax
	addl	a(%rip), %eax
	ret
	.size	_Z3sumv, .-_Z3sumv
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
