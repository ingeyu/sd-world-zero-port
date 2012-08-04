/*
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 * This source code was modified by Emergent Game Technologies, Calabasas, CA 91302
 * http://www.emergent.net
 *
 *
 */

#ifndef _STLP_INTERNAL_MBSTATE_T
#define _STLP_INTERNAL_MBSTATE_T

#if (defined (__OpenBSD__) || defined (__FreeBSD__)) && defined (__GNUC__) && !defined (_GLIBCPP_HAVE_MBSTATE_T)
#  define __mbstate_t_defined /* mbstate_t defined in native <cwchar>, so not defined in C! */
#endif

#if defined (_STLP_NO_NATIVE_MBSTATE_T) && !defined (_STLP_NO_MBSTATE_T) && !defined (_MBSTATE_T) && !defined (__mbstate_t_defined)
#  define _STLP_USE_OWN_MBSTATE_T
#  define _MBSTATE_T
#endif

#if defined (_STLP_USE_OWN_MBSTATE_T)
typedef int mbstate_t;

#  if defined (__cplusplus)
_STLP_BEGIN_NAMESPACE
using ::mbstate_t;
_STLP_END_NAMESPACE
#  endif

#endif /* _STLP_USE_OWN_MBSTATE_T */

#endif /* _STLP_INTERNAL_MBSTATE_T */
