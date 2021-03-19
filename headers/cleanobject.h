#pragma once

#include <memory>
#include "../headers/cleantypes.h"

#define uint unsigned int
#define var auto


namespace clean
{
	/// <summary>
	/// throws an unmanageable exception
	/// </summary>
	/// <param name="functionName">the caller function name</param>
	/// <param name="errorMessage">a well-explained reason why the program is crashed</param>
	[[noreturn]] void trap(const char* functionName, const char* errorMessage);

	class Object
	{
	private:
		uint m_size;
		TypeCode m_type;
		std::unique_ptr<void*> m_raw;

	public:
		Object(char value)
		{
			trap("Object.Object()", "not implemented yet");
		}

		Object()
		{
			trap("Object.Object()", "not implemented yet");
		}

		TypeCode typecode() const
		{
			return this->m_type;
		}

		uint size()
		{
			return this->m_size;
		}
	};
}
