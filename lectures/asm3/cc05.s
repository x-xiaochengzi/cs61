	.file	"cc05.cc"
	.text
	.globl	_Z8identityi
	.type	_Z8identityi, @function
_Z8identityi:
	endbr64
	movl	%edi, %eax
	ret
	.size	_Z8identityi, .-_Z8identityi
	.globl	_Z1fj
	.type	_Z1fj, @function
_Z1fj:
	endbr64
	movl	$61, -24(%rsp)
	movl	$42981762, -20(%rsp)
	movl	$391063, -16(%rsp)
	movl	$2164, -12(%rsp)
	andl	$3, %edi
	movl	-24(%rsp,%rdi,4), %eax
	ret
	.size	_Z1fj, .-_Z1fj
	.ident	"GCC: (Ubuntu 11.2.0-17ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
