/* gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002, 2004, 2005 Free Software
Foundation, Inc.

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

/* 1000 MHz 21164B */

/* Generated by tuneup.c, 2005-03-18, gcc 3.3 */

#define MUL_KARATSUBA_THRESHOLD          31
#define MUL_TOOM3_THRESHOLD             139

#define SQR_BASECASE_THRESHOLD            4
#define SQR_KARATSUBA_THRESHOLD          66
#define SQR_TOOM3_THRESHOLD             117

#define MULLOW_BASECASE_THRESHOLD         0  /* always */
#define MULLOW_DC_THRESHOLD             126
#define MULLOW_MUL_N_THRESHOLD          602

#define DIV_SB_PREINV_THRESHOLD           0  /* preinv always */
#define DIV_DC_THRESHOLD                183
#define POWM_THRESHOLD                  257

#define HGCD_SCHOENHAGE_THRESHOLD       517
#define GCD_ACCEL_THRESHOLD               3
#define GCD_SCHOENHAGE_THRESHOLD       1102
#define GCDEXT_SCHOENHAGE_THRESHOLD    1212
#define JACOBI_BASE_METHOD                1

#define DIVREM_1_NORM_THRESHOLD           0  /* preinv always */
#define DIVREM_1_UNNORM_THRESHOLD         0  /* always */
#define MOD_1_NORM_THRESHOLD              0  /* always */
#define MOD_1_UNNORM_THRESHOLD            0  /* always */
#define USE_PREINV_DIVREM_1               1  /* preinv always */
#define USE_PREINV_MOD_1                  1  /* preinv always */
#define DIVREM_2_THRESHOLD                0  /* preinv always */
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always */

#define GET_STR_DC_THRESHOLD             22
#define GET_STR_PRECOMPUTE_THRESHOLD     25
#define SET_STR_THRESHOLD             35662

#define MUL_FFT_TABLE  { 496, 1184, 1856, 4352, 11264, 20480, 81920, 196608, 0 }
#define MUL_FFT_MODF_THRESHOLD          360
#define MUL_FFT_THRESHOLD              2944

#define SQR_FFT_TABLE  { 560, 1248, 2624, 5376, 11264, 28672, 81920, 327680, 786432, 0 }
#define SQR_FFT_MODF_THRESHOLD          576
#define SQR_FFT_THRESHOLD              3712
