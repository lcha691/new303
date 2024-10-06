#ifndef UTIL_H
#define UTIL_H
#include "sccharts.h"

typedef enum
{
	BUTTON,
	UART,
	NOT_A_MODE
} Mode;

typedef enum
{
	SCCHART,
	C,
	NOT_A_IMP
} Implementation;

typedef struct
{
	char VS;
	char AS;
	char VP;
	char AP;
} Heart;

#endif
