dnl  AMD64 mpn_sub_n -- Subtract two limb vectors of the same length > 0 and
dnl  store difference in a third limb vector.

dnl  Copyright 2003, 2004, 2005, 2007 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 3 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.

include(`../config.m4')


C	    cycles/limb
C K8:		1.69
C P4:		11
C P6-15:	5.0

MULFUNC_PROLOGUE(mpn_sub_n mpn_sub_nc)

C INPUT PARAMETERS
C rp	rdi
C up	rsi
C vp	rdx
C n	rcx
C cy	r8		(only for mpn_sub_nc)

	TEXT
	ALIGN(16)
ASM_START()
PROLOGUE(mpn_sub_nc)
	movq	%rcx, %r10		C				3
	andl	$3, %r10d		C				4
	shrq	$2, %rcx		C				4
	bt	$0, %r8			C cy flag <- carry parameter	5
	je	L(0)			C				2
	jmp	L(oop)			C				2
EPILOGUE()
PROLOGUE(mpn_sub_n)
	movq	%rcx, %r10		C				3
	shrq	$2, %rcx		C				4
	je	L(end)			C				2
	andl	$3, %r10d		C				4

C Main loop.  1 mod 16 aligned.  Blocks between blank lines take one cycle.
L(oop):	movq	(%rsi), %rax		C				3
	movq	8(%rsi), %r9		C				4
	leaq	32(%rsi), %rsi		C				4

	sbbq	(%rdx), %rax		C				3
	movq	%rax, (%rdi)		C				3

	sbbq	8(%rdx), %r9		C				4
	movq	%r9, 8(%rdi)		C				4

	movq	-16(%rsi), %rax		C				4
	movq	-8(%rsi), %r9		C				4

	sbbq	16(%rdx), %rax		C				4
	movq	%rax, 16(%rdi)		C				4

	sbbq	24(%rdx), %r9		C				4
	movq	%r9, 24(%rdi)		C				4
	decq	%rcx			C				3

	leaq	32(%rdx), %rdx		C				4
	leaq	32(%rdi), %rdi		C				4
	jne	L(oop)			C				2


	incl	%r10d			C				3
	decl	%r10d			C				3
	jne	L(0)			C				2

	sbbl	%eax,%eax		C				2
	negl	%eax			C				2
	ret				C				1

L(end):	testl	%eax, %eax		C clear cy			2
L(0):	decl	%r10d			C				3
	jne	L(1)			C				2

	movq	(%rsi), %rax		C				3
	sbbq	(%rdx), %rax		C				3
	movq	%rax, (%rdi)		C				3
	sbbl	%eax,%eax		C				2
	negl	%eax			C				2
	ret				C				1

L(1):	decl	%r10d			C				3
	jne	L(2)			C				2

	movq	(%rsi), %rax		C				3
	movq	8(%rsi), %r9		C				4
	sbbq	(%rdx), %rax		C				3
	movq	%rax, (%rdi)		C				3
	sbbq	8(%rdx), %r9		C				4
	movq	%r9, 8(%rdi)		C				4
	sbbl	%eax,%eax		C				2
	negl	%eax			C				2
	ret				C				1

L(2):
	movq	(%rsi), %rax		C				3
	movq	8(%rsi), %r9		C				4
	sbbq	(%rdx), %rax		C				3
	movq	%rax, (%rdi)		C				3
	sbbq	8(%rdx), %r9		C				4
	movq	%r9, 8(%rdi)		C				4
	movq	16(%rsi), %rax		C				4
	sbbq	16(%rdx), %rax		C				4
	movq	%rax, 16(%rdi)		C				4
	sbbl	%eax,%eax		C				2
	negl	%eax			C				2
	ret				C				1
EPILOGUE()
