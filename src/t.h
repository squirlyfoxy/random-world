#ifndef __T_H__
#define __T_H__

#define FAIL -1
#define SUCCESS 0

#define ARR_LEN(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#endif
