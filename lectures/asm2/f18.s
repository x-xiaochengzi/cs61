	.file	"f18.cc"
	.text
	.globl	_Z9ptr_arithPil
	.type	_Z9ptr_arithPil, @function
_Z9ptr_arithPil:
	endbr64
	leaq	(%rdi,%rsi,4), %rax
	ret
	.size	_Z9ptr_arithPil, .-_Z9ptr_arithPil
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
