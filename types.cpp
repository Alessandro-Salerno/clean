#include "types.h"
#include "general.h"

#include <malloc.h>
#include <initializer_list>

const char* clean::boolean::tostring(bool value)
{
	return value ? "true" : "false";
}

bool clean::character::isdigit(char chr)
{
	return chr >= '0' && chr <= '9';
}

char* clean::character::tostring(char chr)
{
	var result = new char[2];
	result[0] = chr;
	result[1] = '\0';
	return result;
}

int clean::integer::absolute(int number)
{
	return number < 0 ? -number : number;
}

char* clean::integer::tostring(int digit)
{
	if (digit == 0)
		return (char*)"0";

	var isnegative = digit < 0;
	var result = new char[100];
	var i = 0;
	digit = clean::integer::absolute(digit);

	while (digit != 0)
	{
		result[i++] = '0' + digit % 10;
		digit /= 10;
	}

	if (isnegative)
		result[i++] = '-';

	result[i++] = '\0';

	result = static_cast<char*>(realloc(static_cast<void*>(result), i-1));

	var r = string::reverse(result, i - 1);

	delete[] result;

	return r;
}

const char* clean::string::concat(const char* left, const char* right)
{
	const uint size = clean::string::lengthof(left)+clean::string::lengthof(right)+1;
	var result = new char[size];
	uint i = 0;
	
	for (; left[i] != '\0'; i++)
		result[i] = left[i];
	
	var left_length = i;

	for (i = 0; right[i] != '\0'; i++)
		result[left_length+i] = right[i];

	result[size-1] = '\0';
	return result;
}

uint clean::string::realsizeof(const char* text)
{
	return clean::string::lengthof(text)+1;
}

uint clean::string::lengthof(const char* text)
{
	uint i = 0; while (text[i] != '\0') i++;
	
	return i;
}

int clean::string::toint(const char* text)
{
	var res = 0;
	char prefixop = '\0';

	for (int i = 0; text[i] != '\0'; ++i)
	{
		const char cur = text[i];

		if (cur == '-' || cur == '+')
		{
			if (prefixop != '\0')
				trap("toint(const char*)", "unexpected double prefix operator");

			prefixop = cur;
			continue;
		}

		if (!character::isdigit(cur))
			trap("toint(const char*)", "text contained a character that is not a number");

		res = res * 10 + cur - '0';
	}

	return prefixop == '-' ? -res : res;
}

char* clean::string::format(const char* fmt, std::initializer_list<const char*> args)
{
	char* result = new char[1000];
	uint i = 0;

	for (uint fmt_i = 0; fmt[fmt_i] != '\0'; i++, fmt_i++)
	{
		if (fmt[fmt_i] == '\\' && fmt[fmt_i + 1] == '{')
			result[i] = fmt[++fmt_i];
		else if (fmt[fmt_i] == '{')
		{
			char* index = new char[50];
			uint j = 0;

			do
			{
				fmt_i++;

				const char cur = fmt[fmt_i];

				if (cur == '\0')
					trap("format(const char*, std::initializer_list<char*>)", "fmt was in a bad format: expected `}`, found `eof`");
				else if (character::isdigit(cur))
					index[j++] = cur;
				else
					trap("format(const char*, std::initializer_list<char*>)", "fmt was in a bad format: expected a number");
			} while (fmt[fmt_i + 1] != '}');

			index[j++] = '\0';

			var index_int = string::toint(index = static_cast<char*>(realloc(index, j)));

			delete[] index;
			var k = 0;

			if (index_int >= args.size())
				trap("format(const char*, std::initializer_list<char*>)", "index was out of bounds of the std::initializer_list");

			for (var arg : args)
			{
				if (index_int == k)
				{
					k = 0;
					var len = lengthof(arg);

					while (k < len)
					{
						result[i++] = arg[k];
						k++;
					}

					i--;

					break;
				}

				k++;
			}

			fmt_i++;
		}
		else
			result[i] = fmt[fmt_i];
	}

	result[i++] = '\0';

	return static_cast<char*>(realloc(result, i));
}

char* clean::string::reverse(const char* text, uint len)
{
	var result = new char[len + 1];
	uint i = 0;

	for (; i < len; i++)
		result[i] = text[len - i - 1];

	result[i] = '\0';

	return result;
}