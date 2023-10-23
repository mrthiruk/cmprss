#ifndef _CMPRSS_COMMON_H_
#define _CMPRSS_COMMON_H_

#include <stdint.h>

#define uint8					uint8_t
#define uint16					uint16_t
#define uint32					uint32_t
#define uint64					uint64_t
#define bool					_Bool

#define true				    1
#define false					0
#define status_ct				uint8_t
#define CMPRSS_SUCCESS			0
#define CMPRSS_FAILURE			-1
#define CMPRSS_EQ				1
#define CMPRSS_NEQ				0
#define CMPRSS_GREAT			2
#define CMPRSS_LESS				3
#endif
