#pragma once

#include <memory>

#define uint unsigned int
#define var auto

namespace clean
{
	namespace io
	{
		/// <summary>
		/// writes a single text on the console and writes a new line
		/// </summary>
		/// <param name="text"></param>
		void println(const char* text);

		/// <summary>
		/// python-like print function
		/// </summary>
		/// <param name="args">arguments</param>
		/// <param name="sep">text to write between each argument</param>
		/// <param name="end">text to write at the end of the arguments</param>
		void print(std::initializer_list<const char*> args, const char* sep = " ", const char* end = "\n");

		/// <summary>
		/// writes a formatted text on the console
		/// </summary>
		/// <param name="fmt">formatted text with mark places</param>
		/// <param name="args">arguments to put in the corrispective mark place</param>
		void print(const char* fmt, std::initializer_list<const char*> args);
		
		/// <summary>
		/// writes a single text on the console
		/// </summary>
		/// <param name="text"></param>
		void print(const char* text);

		/// <summary>
		/// prints a blank line
		/// </summary>
		void blank();

		/// <summary>
		/// prints a question and returns the answer as char*
		/// </summary>
		/// <param name="text"></param>
		char* input(const char* text);

		/// <summary>
		/// freezes the program untill the enter key is pressed
		/// </summary>
		void wait();
	}
}
