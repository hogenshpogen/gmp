/* gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1995, 1999, 2000 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#define BITS_PER_MP_LIMB 64
#define BYTES_PER_MP_LIMB 8
#define BITS_PER_LONGINT 64
#define BITS_PER_INT 32
#define BITS_PER_SHORTINT 16
#define BITS_PER_CHAR 8

/* Generated by tuneup.c, 2000-10-24. */

#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD   10
#endif
#ifndef TOOM3_MUL_THRESHOLD
#define TOOM3_MUL_THRESHOLD       57
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD   16
#endif
#ifndef TOOM3_SQR_THRESHOLD
#define TOOM3_SQR_THRESHOLD       89
#endif

#ifndef DC_THRESHOLD
#define DC_THRESHOLD              28
#endif

#ifndef FIB_THRESHOLD
#define FIB_THRESHOLD            216
#endif

#ifndef POWM_THRESHOLD
#define POWM_THRESHOLD            46
#endif

#ifndef GCD_ACCEL_THRESHOLD
#define GCD_ACCEL_THRESHOLD        3
#endif
#ifndef GCDEXT_THRESHOLD
#define GCDEXT_THRESHOLD         156
#endif

#ifndef FFT_MUL_TABLE
#define FFT_MUL_TABLE  { 336, 800, 1600, 3328, 9216, 20480, 0 }
#endif
#ifndef FFT_MODF_MUL_THRESHOLD
#define FFT_MODF_MUL_THRESHOLD     296
#endif
#ifndef FFT_MUL_THRESHOLD
#define FFT_MUL_THRESHOLD         2176
#endif

#ifndef FFT_SQR_TABLE
#define FFT_SQR_TABLE  { 368, 736, 1856, 3328, 7168, 20480, 49152, 0 }
#endif
#ifndef FFT_MODF_SQR_THRESHOLD
#define FFT_MODF_SQR_THRESHOLD     280
#endif
#ifndef FFT_SQR_THRESHOLD
#define FFT_SQR_THRESHOLD         1920
#endif
