	.file	"f28.cc"
	.text
	.globl	_Z7times13j
	.type	_Z7times13j, @function
_Z7times13j:
	endbr64
	leal	(%rdi,%rdi,2), %eax
	leal	(%rdi,%rax,4), %eax
	ret
	.size	_Z7times13j, .-_Z7times13j
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
