/* __gmp_extract_double -- convert from double to array of mp_limb_t.

Copyright 1996, 1999, 2000, 2001 Free Software Foundation, Inc.

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

#include "gmp.h"
#include "gmp-impl.h"

#ifdef XDEBUG
#undef _GMP_IEEE_FLOATS
#endif

#ifndef _GMP_IEEE_FLOATS
#define _GMP_IEEE_FLOATS 0
#endif

#define BITS_IN_MANTISSA 53

/* Extract a non-negative double in d.  */

int
__gmp_extract_double (mp_ptr rp, double d)
{
  long exp;
  unsigned sc;
#ifdef _LONG_LONG_LIMB
#define BITS_PER_PART 64	/* somewhat bogus */
  unsigned long long int manh, manl;
#else
#define BITS_PER_PART BITS_PER_MP_LIMB
  unsigned long int manh, manl;
#endif

  /* BUGS

     1. Should handle Inf and NaN in IEEE specific code.
     2. Handle Inf and NaN also in default code, to avoid hangs.
     3. Generalize to handle all BITS_PER_MP_LIMB >= 32.
     4. This lits is incomplete and misspelled.
   */

  ASSERT (d >= 0.0);

  if (d == 0.0)
    {
      MPN_ZERO (rp, LIMBS_PER_DOUBLE);
      return 0;
    }

#if _GMP_IEEE_FLOATS
  {
#if defined (__alpha) && __GNUC__ == 2 && __GNUC_MINOR__ == 8
    /* Work around alpha-specific bug in GCC 2.8.x.  */
    volatile
#endif
    union ieee_double_extract x;
    x.d = d;
    exp = x.s.exp;
#if BITS_PER_PART == 64		/* generalize this to BITS_PER_PART > BITS_IN_MANTISSA */
    manl = (((mp_limb_t) 1 << 63)
	    | ((mp_limb_t) x.s.manh << 43) | ((mp_limb_t) x.s.manl << 11));
    if (exp == 0)
      {
	/* Denormalized number.  Don't try to be clever about this,
	   since it is not an important case to make fast.  */
	exp = 1;
	do
	  {
	    manl = manl << 1;
	    exp--;
	  }
	while ((mp_limb_signed_t) manl >= 0);
      }
#endif
#if BITS_PER_PART == 32
    manh = ((mp_limb_t) 1 << 31) | (x.s.manh << 11) | (x.s.manl >> 21);
    manl = x.s.manl << 11;
    if (exp == 0)
      {
	/* Denormalized number.  Don't try to be clever about this,
	   since it is not an important case to make fast.  */
	exp = 1;
	do
	  {
	    manh = (manh << 1) | (manl >> 31);
	    manl = manl << 1;
	    exp--;
	  }
	while ((mp_limb_signed_t) manh >= 0);
      }
#endif
#if BITS_PER_PART != 32 && BITS_PER_PART != 64
  You need to generalize the code above to handle this.
#endif
    exp -= 1022;		/* Remove IEEE bias.  */
  }
#else
  {
    /* Unknown (or known to be non-IEEE) double format.  */
    exp = 0;
    if (d >= 1.0)
      {
	if (d * 0.5 == d)
	  abort ();

	while (d >= 32768.0)
	  {
	    d *= (1.0 / 65536.0);
	    exp += 16;
	  }
	while (d >= 1.0)
	  {
	    d *= 0.5;
	    exp += 1;
	  }
      }
    else if (d < 0.5)
      {
	while (d < (1.0 / 65536.0))
	  {
	    d *=  65536.0;
	    exp -= 16;
	  }
	while (d < 0.5)
	  {
	    d *= 2.0;
	    exp -= 1;
	  }
      }

    d *= (4.0 * ((unsigned long int) 1 << (BITS_PER_PART - 2)));
#if BITS_PER_PART == 64
    manl = d;
#else
    manh = d;
    manl = (d - manh) * (4.0 * ((unsigned long int) 1 << (BITS_PER_PART - 2)));
#endif
  }
#endif /* IEEE */

  /* Up until here, we have ignored the actual limb size.  Remains
     to split manh,,manl into an array of LIMBS_PER_DOUBLE limbs.
  */

  sc = (unsigned) exp % BITS_PER_MP_LIMB;

  /* We add something here to get rounding right.  */
  exp = (exp + 2048) / BITS_PER_MP_LIMB - 2048 / BITS_PER_MP_LIMB + 1;

#if LIMBS_PER_DOUBLE == 2
  if (sc != 0)
    {
      rp[1] = manl >> (BITS_PER_MP_LIMB - sc);
      rp[0] = manl << sc;
    }
  else
    {
      rp[1] = manl;
      rp[0] = 0;
      exp--;
    }
#endif
#if LIMBS_PER_DOUBLE == 3
  if (sc != 0)
    {
      rp[2] = manh >> (BITS_PER_MP_LIMB - sc);
      rp[1] = (manl >> (BITS_PER_MP_LIMB - sc)) | (manh << sc);
      rp[0] = manl << sc;
    }
  else
    {
      rp[2] = manh;
      rp[1] = manl;
      rp[0] = 0;
      exp--;
    }
#endif
#if LIMBS_PER_DOUBLE > 3
  /* Insert code for splitting manh,,manl into LIMBS_PER_DOUBLE
     mp_limb_t's at rp.  */
  if (sc != 0)
    {
      /* This is not perfect, and would fail for BITS_PER_MP_LIMB == 16.
	 The ASSERT_ALWAYS should catch the problematic cases.  */
      ASSERT_ALWAYS ((manl << sc) == 0);
      manl = (manh << sc) | (manl >> (BITS_PER_MP_LIMB - sc));
      manh = manh >> (BITS_PER_MP_LIMB - sc);
    }
  {
    int i;
    for (i = LIMBS_PER_DOUBLE - 1; i >= 0; i--)
      {
	rp[i] = manh >> (BITS_PER_LONGINT - BITS_PER_MP_LIMB);
	manh = ((manh << BITS_PER_MP_LIMB)
		| (manl >> (BITS_PER_LONGINT - BITS_PER_MP_LIMB)));
	manl = manl << BITS_PER_MP_LIMB;
      }
  }
#endif

  return exp;
}
