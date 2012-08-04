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

# if !defined (_STLP_OUTERMOST_HEADER_ID)
#  define _STLP_OUTERMOST_HEADER_ID 0x280
#  include <stlport/stl/_prolog.h>
# elif (_STLP_OUTERMOST_HEADER_ID == 0x280) && ! defined (_STLP_DONT_POP_HEADER_ID)
#  define _STLP_DONT_POP_HEADER_ID
# endif

# if defined (__SUNPRO_CC) || defined (__HP_aCC)
# include "/usr/include/pthread.h"
# else
# include _STLP_NATIVE_C_HEADER(pthread.h)
# endif

# if (_STLP_OUTERMOST_HEADER_ID == 0x280)
#  if ! defined (_STLP_DONT_POP_HEADER_ID)
#   include <stlport/stl/_epilog.h>
#   undef  _STLP_OUTERMOST_HEADER_ID
#  else
#   undef  _STLP_DONT_POP_HEADER_ID
#  endif
# endif

/*
 Local Variables:
 mode:C++
 End:
*/
