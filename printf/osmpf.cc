/* mpf_out_ostream -- mpf formatted output to an ostream.

Copyright 2001 Free Software Foundation, Inc.

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

#include <iostream.h>
#include <stdarg.h>    /* for va_list and hence doprnt_funs_t */

#include "gmp.h"
#include "gmp-impl.h"


ostream&
mpf_out_ostream (ostream &o, mpf_srcptr f)
{
  struct doprnt_params_t  param;
  mp_exp_t exp;
  int      ndigits;

  __gmp_doprnt_params_from_ios (&param, o);
  ndigits = __gmp_doprnt_float_digits_cxx (&param, f);
  gmp_allocated_string alloc
    = mpf_get_str (NULL, &exp, param.base, ndigits, f);
  ASSERT_DOPRNT_NDIGITS (param, ndigits, exp);
  __gmp_doprnt_float_cxx (&__gmp_ostream_funs, &o, &param, alloc.str, exp);
  return o;
}