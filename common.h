#ifndef _COMMON_
#define _COMMON_

#include <stdlib.h>
#include <string.h>

#define RET_TYPE_OK	1
#define RET_TYPE_ERROR	0
#define RET_TYPE_WRONG_HEADER	2

/*hours*/
#define GMT_TIME_DIFF 6

extern float NMEAStrToDegree(char *str);

#endif
