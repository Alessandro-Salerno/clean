#pragma once

#include <memory>

#include "general.h"

namespace clean
{
   enum class TypeCode
	{
		String,
		Char,
		Int,
		Long,
		Float,
		Array
	};

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