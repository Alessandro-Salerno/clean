#pragma once

#include "general.h"
#include <initializer_list>

namespace clean
{
   namespace boolean
	{
		/// <summary>
		/// converts a bool value to the corrispective string
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		const char* tostring(bool value);
	}

	namespace character
	{
		/// <summary>
		/// returns true whether the passed character is a ascii digit
		/// </summary>
		/// <param name="chr"></param>
		/// <returns></returns>
		bool isdigit(char chr);

		/// <summary>
		/// converts a char to a string
		/// </summary>
		/// <param name="chr"></param>
		/// <returns></returns>
		char* tostring(char chr);
	}

	namespace string
	{
		/// <summary>
		/// converts a string to int, traps if the text contains a damaged number
		/// </summary>
		/// <param name="text">number in text format</param>
		/// <returns></returns>
		int toint(const char* text);

		/// <summary>
		/// returns a string reppresenting the `fmt` with mark places replaced by the corrispective arguments
		/// </summary>
		/// <param name="fmt">the formatted string with mark places</param>
		/// <param name="args">the arguments</param>
		/// <returns></returns>
		char* format(const char* fmt, std::initializer_list<const char*> args);

		/// <summary>
		/// reverses the passed string
		/// </summary>
		char* reverse(const char* text, uint len);

		/// returns a null terminated string's length
		uint lengthof(const char* text);

		/// returns a null terminated string's length taking count also of the null character
		uint realsizeof(const char* text);

		/// returns a string reppresenting `right` concatenated to `left`
		const char* concat(const char* left, const char* right);
	}

	namespace integer
	{
		/// <summary>
		/// converts a int to a string
		/// </summary>
		/// <param name="digit">10 based integer</param>
		/// <returns></returns>
		char* tostring(int digit);

		/// returns the absolute number of a number
		int absolute(int number);
	}
}