#include "general.h"
#include <stdio.h>

[[noreturn]] void trap(const char* function, const char* error)
{
   printf("Called trap on `%s`: %s\n", function, error);
	throw "trap";
}