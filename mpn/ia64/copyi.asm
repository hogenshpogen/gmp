dnl  IA-64 mpn_copyi -- copy limb vector, incrementing.

dnl  Copyright (C) 2001 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 2.1 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
dnl  the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
dnl  MA 02111-1307, USA.

include(`../config.m4')

C INPUT PARAMETERS
C rp = r32
C sp = r33
C n = r34

ASM_START()
PROLOGUE(mpn_copyi)
	.prologue
	.body
	mov	r2 = ar.lc
	and	r14 = 3, r34
	cmp.ge	p14, p15 = 4, r34
	add	r34 = -4, r34
	;;
	cmp.eq	p6, p7 = 0, r14
	cmp.eq	p8, p9 = 1, r14
	cmp.eq	p10, p11 = 2, r14
	cmp.eq	p12, p13 = 3, r14;;
  (p6)	br	.Lb00
  (p8)	br	.Lb01
  (p10)	br	.Lb10
  (p12)	br	.Lb11

.Lb00:	C  n = 4, 8, 12, ...
	ld8	r16 = [r33], 8
	shr	r15 = r34, 2
	;;
	ld8	r17 = [r33], 8
	mov	ar.lc = r15
	;;
	ld8	r18 = [r33], 8
	;;
	ld8	r19 = [r33], 8
  (p14)	br	.Ls00
	br.cloop.dptk .Loop
	;;

.Lb01:	C  n = 1, 5, 9, 13, ...
	ld8	r19 = [r33], 8
	shr	r15 = r34, 2
  (p14)	br	.Ls01
	;;
	ld8	r16 = [r33], 8
	mov	ar.lc = r15
	;;
	ld8	r17 = [r33], 8
	;;
	ld8	r18 = [r33], 8
	br	.Li01
	;;

.Lb10:	C  n = 2,6, 10, 14, ...
	ld8	r18 = [r33], 8
	shr	r15 = r34, 2
	;;
	ld8	r19 = [r33], 8
	mov	ar.lc = r15
  (p14)	br	.Ls10
	;;
	ld8	r16 = [r33], 8
	;;
	ld8	r17 = [r33], 8
	br	.Li10
	;;

.Lb11:	C  n = 3, 7, 11, 15, ...
	ld8	r17 = [r33], 8
	shr	r15 = r34, 2
	;;
	ld8	r18 = [r33], 8
	mov	ar.lc = r15
	;;
	ld8	r19 = [r33], 8
  (p14)	br	.Ls11
	;;
	ld8	r16 = [r33], 8
	br	.Li11
	;;

.Loop:
  { .mmb
.Li00:	st8	[r32] = r16, 8
	ld8	r16 = [r33], 8	;;
} { .mmb
.Li11:	st8	[r32] = r17, 8
	ld8	r17 = [r33], 8	;;
} { .mmb
.Li10:	st8	[r32] = r18, 8
	ld8	r18 = [r33], 8	;;
} { .mmb
.Li01:	st8	[r32] = r19, 8
	ld8	r19 = [r33], 8
	br.cloop.dptk .Loop	;;
}
.Ls00:	st8	[r32] = r16, 8	;;
.Ls11:	st8	[r32] = r17, 8	;;
.Ls10:	st8	[r32] = r18, 8	;;
.Ls01:	st8	[r32] = r19, 8

	mov.i	ar.lc = r2
	br.ret.sptk.many rp
EPILOGUE(mpn_copyi)
ASM_END()
