/* __gmp_doprnt_integer -- integer style formatted output.

   THE FUNCTIONS IN THIS FILE ARE FOR INTERNAL USE ONLY.  THEY'RE ALMOST
   CERTAIN TO BE SUBJECT TO INCOMPATIBLE CHANGES OR DISAPPEAR COMPLETELY IN
   FUTURE GNU MP RELEASES.

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

#include "config.h"

#if HAVE_STDARG
#include <stdarg.h>    /* for va_list and hence doprnt_funs_t */
#else
#include <varargs.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"
#include "gmp-impl.h"


int
__gmp_doprnt_integer (const struct doprnt_funs_t *funs,
                      void *data,
                      const struct doprnt_params_t *p,
                      const char *s)
{
  int         retval = 0;
  int         justlen, showbaselen, sign, signlen, justify;
  const char  *slash, *showbase;
  
  /* '+' or ' ' if wanted, and don't already have '-' */
  sign = p->sign;
  if (s[0] == '-')
    {
      sign = s[0];
      s++;
    }
  signlen = (sign != '\0');
  
  slash = strchr (s, '/');
  
  showbase = NULL;
  showbaselen = 0;
  switch (p->showbase) {
  default:
    ASSERT (0);
    /*FALLTHRU*/
  case DOPRNT_SHOWBASE_NO:
    break;
  case DOPRNT_SHOWBASE_NONZERO:
    if (s[0] == '0')
      break;
    /*FALLTHRU*/
  case DOPRNT_SHOWBASE_YES:
    switch (p->base) {
    case 16:  showbase = "0x"; showbaselen = 2; break;
    case -16: showbase = "0X"; showbaselen = 2; break;
    case 8:   showbase = "0";  showbaselen = 1; break;
    }
    break;
  }

  /* space left over after actual output length */
  justlen = p->width - (strlen(s) + signlen + showbaselen);
  if (slash != NULL)
    justlen -= showbaselen;

  justify = p->justify;
  if (justlen <= 0) /* no justifying if exceed width */
    justify = DOPRNT_JUSTIFY_NONE;

  if (justify == DOPRNT_JUSTIFY_RIGHT)             /* pad right */
    DOPRNT_REPS (p->fill, justlen);

  DOPRNT_REPS_MAYBE (sign, signlen);               /* sign */

  DOPRNT_MEMORY_MAYBE (showbase, showbaselen);     /* base */

  if (justify == DOPRNT_JUSTIFY_INTERNAL)          /* pad internal */
    DOPRNT_REPS (p->fill, justlen);

  if (slash != NULL && showbaselen != 0)
    {
      DOPRNT_MEMORY (s, slash+1-s);                /* possible numerator */
      s = slash+1;
      DOPRNT_MEMORY_MAYBE (showbase, showbaselen); /* possible extra base */
    }

  DOPRNT_STRING (s);                               /* number or denominator */

  if (justify == DOPRNT_JUSTIFY_LEFT)              /* pad left */
    DOPRNT_REPS (p->fill, justlen);

 done:
  return retval;

 error:
  retval = -1;
  goto done;
}