#pragma once

#include <memory>

#include "general.h"

namespace clean
{
	enum class TypeCode
	{
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
		void* m_raw;

	public:
		Object(int value)
		{
			this->construct(4, TypeCode::Int, new int(value));
		}

		Object(long value)
		{
			this->construct(8, TypeCode::Long, new long(value));
		}

		Object(char value)
		{
			this->construct(1, TypeCode::Char, new char(value));
		}

		~Object()
		{
			free(m_raw);
		}

		TypeCode typecode() const
		{
			return this->m_type;
		}

		inline uint size() const
		{
			return this->m_size;
		}

		template<typename T>
		inline T cast() const
		{
			if (sizeof(T) != this->m_size)
				trap("Object.cast<T>()", "type's sizes are different");

			return *((T*)this->m_raw);
		}

	private:
		inline void construct(uint size, TypeCode typecode, void* value)
		{
			this->m_size = size;
			this->m_type = typecode;
			this->m_raw = value;
		}
	};
}