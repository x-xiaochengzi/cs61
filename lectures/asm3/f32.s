	.file	"f32.cc"
	.text
	.globl	_Z8is_equalii
	.type	_Z8is_equalii, @function
_Z8is_equalii:
	endbr64
	xorl	%eax, %eax
	cmpl	%esi, %edi
	sete	%al
	ret
	.size	_Z8is_equalii, .-_Z8is_equalii
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
