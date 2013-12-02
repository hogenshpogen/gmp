/* Alpha EV4 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999-2002, 2004, 2005, 2009 Free Software
Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library.  If not, see https://www.gnu.org/licenses/.  */

#define GMP_LIMB_BITS 64
#define BYTES_PER_MP_LIMB 8


/* 175MHz 21064 */

/* Generated by tuneup.c, 2009-01-15, gcc 3.2 */

#define MUL_TOOM22_THRESHOLD             12
#define MUL_TOOM33_THRESHOLD             69
#define MUL_TOOM44_THRESHOLD             88

#define SQR_BASECASE_THRESHOLD            4
#define SQR_TOOM2_THRESHOLD              20
#define SQR_TOOM3_THRESHOLD              62
#define SQR_TOOM4_THRESHOLD             155

#define MULLO_BASECASE_THRESHOLD          0  /* always */
#define MULLO_DC_THRESHOLD               40
#define MULLO_MUL_N_THRESHOLD           202

#define DIV_SB_PREINV_THRESHOLD           0  /* preinv always */
#define DIV_DC_THRESHOLD                 38
#define POWM_THRESHOLD                   60

#define MATRIX22_STRASSEN_THRESHOLD      17
#define HGCD_THRESHOLD                   80
#define GCD_DC_THRESHOLD                237
#define GCDEXT_DC_THRESHOLD             198
#define JACOBI_BASE_METHOD                2

#define DIVREM_1_NORM_THRESHOLD           0  /* preinv always */
#define DIVREM_1_UNNORM_THRESHOLD         0  /* always */
#define MOD_1_NORM_THRESHOLD              0  /* always */
#define MOD_1_UNNORM_THRESHOLD            0  /* always */
#define MOD_1_1_THRESHOLD                 2
#define MOD_1_2_THRESHOLD                 9
#define MOD_1_4_THRESHOLD                20
#define USE_PREINV_DIVREM_1               1  /* preinv always */
#define USE_PREINV_MOD_1                  1  /* preinv always */
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always */

#define GET_STR_DC_THRESHOLD             20
#define GET_STR_PRECOMPUTE_THRESHOLD     37
#define SET_STR_DC_THRESHOLD            746
#define SET_STR_PRECOMPUTE_THRESHOLD   1332

#define MUL_FFT_TABLE  { 240, 480, 1344, 2304, 5120, 20480, 49152, 0 }
#define MUL_FFT_MODF_THRESHOLD          232
#define MUL_FFT_THRESHOLD              1664

#define SQR_FFT_TABLE  { 240, 480, 1216, 2304, 5120, 12288, 49152, 0 }
#define SQR_FFT_MODF_THRESHOLD          232
#define SQR_FFT_THRESHOLD              1408
