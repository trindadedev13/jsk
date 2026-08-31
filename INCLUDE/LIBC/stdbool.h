#ifndef JSK_LIBC_STDBOOL_H
#define JSK_LIBC_STDBOOL_H

#ifndef __cplusplus

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
/** bool, true and false are keywords */
#else
#define bool  _Bool
#define true  1
#define false 0
#endif

#else
/** C++ doesn't have _Bool */
#define _Bool bool
#endif

#endif
