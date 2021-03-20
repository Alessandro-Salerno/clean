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

		void add(Object right) const
		{
			if (this->m_type != right.m_type)
				trap("Object.add()", "unable to add different types");

			switch (this->m_type)
			{
			case TypeCode::Char: *((char*)this->m_raw) = *((char*)this->m_raw)+*((char*)right.m_raw); break;
			case TypeCode::Int: *((int*)this->m_raw) = *((int*)this->m_raw)+*((int*)right.m_raw); break;
			case TypeCode::Long: *((long*)this->m_raw) = *((long*)this->m_raw)+*((long*)right.m_raw); break;
			default: trap("Object.add()", "unable to add non-int types"); break;
			}
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