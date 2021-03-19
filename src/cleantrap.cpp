#include "../headers/cleanobject.h"
#include "../headers/cleanio.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory>


[[noreturn]] void clean::trap(const char* function, const char* error)
{
	clean::io::print("Called trap on `{0}`: {1}\n", { function, error });
	throw "trap";
}
