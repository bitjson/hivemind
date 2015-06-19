
/* @(#)s_ldexp.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
	double FDLIBM_ldexp(double value, int exp)
#else
	double FDLIBM_ldexp(value, exp)
	double value; int exp;
#endif
{
	if(!FDLIBM_finite(value)||value==0.0) return value;
	value = FDLIBM_scalbn(value,exp);
	if(!FDLIBM_finite(value)||value==0.0) errno = ERANGE;
	return value;
}
