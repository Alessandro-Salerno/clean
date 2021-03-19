#include "io.h"
#include "types.h"

#include <stdlib.h>
#include <stdio.h>

void clean::io::println(const char* text)
{
	printf("%s\n", text);
}

void clean::io::print(std::initializer_list<const char*> args, const char* sep, const char* end)
{
	uint i = 0;
	for (var arg : args)
		printf("%s%s", arg, i++ < args.size()-1 ? sep : end);
}

void clean::io::print(const char* fmt, std::initializer_list<const char*> args)
{
	printf("%s", clean::string::format(fmt, args));
}

void clean::io::print(const char* text)
{
	printf("%s", text);
}