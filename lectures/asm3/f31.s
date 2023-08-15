	.file	"f31.cc"
	.text
	.globl	_Z5mod16j
	.type	_Z5mod16j, @function
_Z5mod16j:
	endbr64
	movl	%edi, %eax
	andl	$15, %eax
	ret
	.size	_Z5mod16j, .-_Z5mod16j
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
