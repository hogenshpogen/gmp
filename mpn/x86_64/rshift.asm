dnl  AMD64 mpn_rshift -- mpn left shift.

dnl  Copyright 2003, 2005 Free Software Foundation, Inc.
dnl
dnl  This file is part of the GNU MP Library.
dnl
dnl  The GNU MP Library is free software; you can redistribute it and/or
dnl  modify it under the terms of the GNU Lesser General Public License as
dnl  published by the Free Software Foundation; either version 2.1 of the
dnl  License, or (at your option) any later version.
dnl
dnl  The GNU MP Library is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl  Lesser General Public License for more details.
dnl
dnl  You should have received a copy of the GNU Lesser General Public
dnl  License along with the GNU MP Library; see the file COPYING.LIB.  If
dnl  not, write to the Free Software Foundation, Inc., 51 Franklin Street,
dnl  Fifth Floor, Boston, MA 02110-1301, USA.

include(`../config.m4')


C		    cycles/limb
C Hammer:		2.375
C Prescott/Nocona:	8


C INPUT PARAMETERS
C rp	rdi
C up	rsi
C n	rdx
C cnt	rcx

define(`rp',`%rdi')
define(`up',`%rsi')
define(`n',`%rdx')

ASM_START()
	TEXT
	ALIGN(32)
PROLOGUE(mpn_rshift)
	negl	%ecx			C put rsh count in cl
	movq	(up), %rax
	shlq	%cl, %rax		C function return value
	negl	%ecx			C put lsh count in cl

	leal	1(n), %r8d

	leaq	-8(up,n,8), up
	leaq	-8(rp,n,8), rp
	negq	n

	andl	$3, %r8d
	je	.Lrolx			C jump for n = 3, 7, 11, ...

	decl	%r8d
	jne	.L1
C	n = 4, 8, 12, ...
	movq	8(up,n,8), %r10
	shrq	%cl, %r10
	negl	%ecx			C put rsh count in cl
	movq	16(up,n,8), %r8
	shlq	%cl, %r8
	orq	%r8, %r10
	movq	%r10, 8(rp,n,8)
	incq	n
	jmp	.Lroll

.L1:	decl	%r8d
	je	.L1x			C jump for n = 1, 5, 9, 13, ...
C	n = 2, 6, 10, 16, ...
	movq	8(up,n,8), %r10
	shrq	%cl, %r10
	negl	%ecx			C put rsh count in cl
	movq	16(up,n,8), %r8
	shlq	%cl, %r8
	orq	%r8, %r10
	movq	%r10, 8(rp,n,8)
	incq	n
	negl	%ecx			C put lsh count in cl
.L1x:
	cmpq	$-1, n
	je	.Last
	movq	8(up,n,8), %r10
	shrq	%cl, %r10
	movq	16(up,n,8), %r11
	shrq	%cl, %r11
	negl	%ecx			C put rsh count in cl
	movq	16(up,n,8), %r8
	movq	24(up,n,8), %r9
	shlq	%cl, %r8
	orq	%r8, %r10
	shlq	%cl, %r9
	orq	%r9, %r11
	movq	%r10, 8(rp,n,8)
	movq	%r11, 16(rp,n,8)
	addq	$2, n

.Lroll:	negl	%ecx			C put lsh count in cl
.Lrolx:	movq	8(up,n,8), %r10
	shrq	%cl, %r10
	movq	16(up,n,8), %r11
	shrq	%cl, %r11

	addq	$4, n			C				      4
	jb	.Lend			C				      2
	ALIGN(16)
.Loop:
	C finish stuff from lsh block
	negl	%ecx			C put rsh count in cl
	movq	-16(up,n,8), %r8
	movq	-8(up,n,8), %r9
	shlq	%cl, %r8
	orq	%r8, %r10
	shlq	%cl, %r9
	orq	%r9, %r11
	movq	%r10, -24(rp,n,8)
	movq	%r11, -16(rp,n,8)
	C start two new rsh
	movq	0(up,n,8), %r8
	movq	8(up,n,8), %r9
	shlq	%cl, %r8
	shlq	%cl, %r9

	C finish stuff from rsh block
	negl	%ecx			C put lsh count in cl
	movq	-8(up,n,8), %r10
	movq	0(up,n,8), %r11
	shrq	%cl, %r10
	orq	%r10, %r8
	shrq	%cl, %r11
	orq	%r11, %r9
	movq	%r8, -8(rp,n,8)
	movq	%r9, 0(rp,n,8)
	C start two new lsh
	movq	8(up,n,8), %r10
	movq	16(up,n,8), %r11
	shrq	%cl, %r10
	shrq	%cl, %r11

	addq	$4, n
	jae	.Loop			C				      2
.Lend:
	negl	%ecx			C put rsh count in cl
	movq	-16(up,n,8), %r8
	shlq	%cl, %r8
	orq	%r8, %r10
	movq	-8(up,n,8), %r9
	shlq	%cl, %r9
	orq	%r9, %r11
	movq	%r10, -24(rp,n,8)
	movq	%r11, -16(rp,n,8)

	negl	%ecx			C put lsh count in cl
.Last:	movq	(up), %r10
	shrq	%cl, %r10
	movq	%r10, (rp)
	ret
EPILOGUE()
