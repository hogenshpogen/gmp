dnl  AMD64 mpn_rshift -- mpn right shift, optimised for Atom.

dnl  Contributed to the GNU project by Torbjorn Granlund.

dnl  Copyright 2011 Free Software Foundation, Inc.
dnl
dnl  This file is part of the GNU MP Library.
dnl
dnl  The GNU MP Library is free software; you can redistribute it and/or
dnl  modify it under the terms of the GNU Lesser General Public License as
dnl  published by the Free Software Foundation; either version 3 of the
dnl  License, or (at your option) any later version.
dnl
dnl  The GNU MP Library is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl  Lesser General Public License for more details.
dnl
dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.

include(`../config.m4')

C	     cycles/limb
C AMD K8,K9	 ?
C AMD K10	 ?
C Intel P4	 ?
C Intel core2	 ?
C Intel NHM	 ?
C Intel SBR	 ?
C Intel atom	 4.5
C VIA nano	 ?

C TODO
C  * Consider using 4-way unrolling.  We reach 4 c/l, but the code is 2.5 times
C    larger.

C INPUT PARAMETERS
define(`rp',	`%rdi')
define(`up',	`%rsi')
define(`n',	`%rdx')
define(`cnt',	`%rcx')

ABI_SUPPORT(DOS64)
ABI_SUPPORT(STD64)

ASM_START()
	TEXT
	ALIGN(16)
PROLOGUE(mpn_rshift)
	DOS64_ENTRY(4)
	shr	R32(n)
	mov	(up), %rax
	jnc	L(evn)

	mov	%rax, %r11
	shr	R8(cnt), %r11
	neg	R8(cnt)
	shl	R8(cnt), %rax
	test	n, n
	jnz	L(gt1)
	mov	%r11, (rp)
	DOS64_EXIT()
	ret

L(gt1):	mov	8(up), %r8
	mov	%r8, %r10
	shl	R8(cnt), %r8
	jmp	L(lo1)

L(evn):	mov	%rax, %r10
	neg	R8(cnt)
	shl	R8(cnt), %rax
	mov	8(up), %r9
	mov	%r9, %r11
	shl	R8(cnt), %r9
	neg	R8(cnt)
	dec	n
	lea	-8(rp), rp
	lea	8(up), up
	jz	L(end)

	ALIGN(8)
L(top):	shr	R8(cnt), %r10
	or	%r10, %r9
	shr	R8(cnt), %r11
	neg	R8(cnt)
	mov	8(up), %r8
	mov	%r8, %r10
	mov	%r9, 8(rp)
	shl	R8(cnt), %r8
	lea	16(rp), rp
L(lo1):	mov	16(up), %r9
	or	%r11, %r8
	mov	%r9, %r11
	shl	R8(cnt), %r9
	lea	16(up), up
	neg	R8(cnt)
	mov	%r8, (rp)
	dec	n
	jg	L(top)

L(end):	shr	R8(cnt), %r10
	or	%r10, %r9
	shr	R8(cnt), %r11
	mov	%r9, 8(rp)
	mov	%r11, 16(rp)
	DOS64_EXIT()
	ret
EPILOGUE()
