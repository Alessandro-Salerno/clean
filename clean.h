#pragma once

#include <memory>

#define uint unsigned int
#define var auto

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
	}

	namespace integer
	{
		/// <summary>
		/// converts a int to a string
		/// </summary>
		/// <param name="digit">10 based integer</param>
		/// <returns></returns>
		char* tostring(int digit);
	}

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
	}

	/// <summary>
	/// throws an unmanageable exception
	/// </summary>
	/// <param name="functionName">the caller function name</param>
	/// <param name="errorMessage">a well-explained reason why the program is crashed</param>
	[[noreturn]] void trap(const char* functionName, const char* errorMessage);

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

	/// dynamic array class
	template <typename T>
	class Vector
	{
	private:
		uint m_length;
		uint m_capacity;
		T* m_raw;

	public:
		/// <summary>
		/// initializes a new dynamic array with a specific capacity
		/// </summary>
		/// <param name="initialCapacity">number of embedded array elements to allocate</param>
		Vector(uint initialCapacity)
		{
			this->construct(initialCapacity);
		}

		/// <summary>
		/// initializes a new dynamic array with 1000 embedded elements
		/// </summary>
		Vector()
		{
			this->construct(1000);
		}

		~Vector()
		{
			delete[] this->m_raw;
		}

		/// <summary>
		/// returns the length of the dynamic vector
		/// </summary>
		/// <returns></returns>
		inline int length() const
		{
			return this->m_length;
		}

		/// <summary>
		/// returns the current dyanic array's capacity, it changes when the dynamic array has not more space
		/// </summary>
		/// <returns></returns>
		inline int capacity() const
		{
			return this->m_capacity;
		}

		/// <summary>
		/// returns a dynamic array element from at a specific index, if out of the bounds traps the program
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		inline T elementat(uint index) const
		{
			if (this->isOutOfBounds(index))
				trap("Vector.elementat(unsigned int)", string::format("vector length was `{0}`, but indexed at `{1}`", { integer::tostring(this->m_length), integer::tostring(index) }));

			return this->m_raw[index];
		}

		inline void setelement(uint index, T element)
		{
			if (this->m_length <= index)
				trap("Vector.setelement()", "`index` is greater than the dynamic vector's length");

			this->m_raw[index] = element;
		}

		/// <summary>
		/// adds a new element on the top of the dynamic array
		/// </summary>
		/// <param name="element">the element to add</param>
		inline void add(T element)
		{
			this->reallocIFNeeded();

			this->m_raw[this->m_length++] = element;
		}

		/// <summary>
		/// takes the last element added, removes it from the top and returns the element.
		/// If no elements on the top traps the program
		/// </summary>
		/// <returns></returns>
		inline T pop()
		{
			if (this->m_length == 0)
				trap("Vector.pop()", "Vector length was `0`");

			return this->m_raw[--this->m_length];
		}

		/// <summary>
		/// removes the last element from the top of the array.
		/// If no elements on the top traps the program
		/// </summary>
		inline void poptop()
		{
			if (this->m_length == 0)
				trap("Vector.poptop()", "vector length was `0`");

			this->m_length--;
		}

		/// <summary>
		/// returns true if the dynamic array contains an element equals to `element`
		/// </summary>
		/// <param name="element">element to check</param>
		/// <returns></returns>
		inline bool contains(T element) const
		{
			for (uint i = 0; i < this->m_length; i++) if (this->m_raw[i] == element) return true;

			return false;
		}

		/// <summary>
		/// returns true if the dynamic array contains the element passed and set `i` to its index
		/// </summary>
		/// <param name="element"></param>
		/// <param name="i"></param>
		/// <returns></returns>
		inline bool contains(T element, int& i) const
		{
			for (i = 0; i < this->m_length; i++) if (this->m_raw[i] == element) return true;

			i = 0;
			return false;
		}

		/// <summary>
		/// returns the index of an element in the sequence, if no element equals to `element` traps the program
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		inline uint indexof(T element) const
		{
			for (uint i = 0; i < this->m_length; i++) if (this->m_raw[i] == element) return i;

			trap("Vector.indexof(T)", "vector does not contain element");
		}

		/// <summary>
		/// returns the index `element` starting from the top, if not in the sequence traps the program
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		inline uint lastindexof(T element) const
		{
			for (uint i = this->m_length - 1; i > 0; i--) if (this->m_raw[i] == element) return i;

			trap("Vector.lastindexof(T)", "vector does not contain element");
		}

		/// <summary>
		/// returns the index of an element that satisfies the `predicateFunction` requirements
		/// </summary>
		/// <param name="predicateFunction"></param>
		/// <returns></returns>
		inline uint findindex(bool (*predicateFunction)(T)) const
		{
			for (uint i = 0; i < this->m_length; i++) if (predicateFunction(this->m_raw[i])) return i;
			
			trap("Vector.find(bool (*)(T))", "vector does not contain an element that satisfies the `predicateFunction` requirements");
		}
		
		/// <summary>
		/// returns the element that satisfies the `predicateFunction` requirements
		/// </summary>
		/// <param name="predicateFunction"></param>
		/// <returns></returns>
		inline T find(bool (*predicateFunction)(T)) const
		{
			return this->m_raw[this->findindex(predicateFunction)];
		}

		/// <summary>
		/// returns the array reppresentation in string format, uses `stringize` to convert each element
		/// in the sequence to string
		/// </summary>
		/// <param name="stringize"></param>
		/// <returns></returns>
		char* tostring(char* (*stringize)(T)) const
		{
			uint size = 2 + this->m_length;

			if (this->m_length > 2) size += this->m_length * 2;
			else if (this->m_length > 1) size += 2;
			else size++;

			char* result = new char[size];
			uint result_i = 0;

			result[result_i++] = '[';

			for (uint i = 0; i < this->m_length; i++)
			{
				if (i > 0)
				{
					result[result_i++] = ','; result[result_i++] = ' ';
				}

				var string = stringize(this->m_raw[i]);

				for (uint j = 0; j < strlen(string); j++)
					result[result_i++] = string[j];

				delete[] string;
			}

			result[result_i++] = ']';
			result[result_i] = '\0';

			return result;
		}

		/// <summary>
		/// copies the embedded array of the sequence to a new allocation
		/// </summary>
		/// <returns></returns>
		T* toarray() const
		{
			var result = new T[this->m_length];

			for (uint i = 0; i < this->m_length; i++)
				result[i] = this->m_raw[i];

			return result;
		}

		/// <summary>
		/// like `toarray`, returns the embedded array allocation pointer, but without coping it into a new one
		/// </summary>
		/// <returns></returns>
		inline T* topointer() const
		{
			return this->m_raw;
		}

		/// <summary>
		/// resizes the dynamic array capacity
		/// </summary>
		inline void resize(uint newcapacity)
		{
			if (this->m_length > newcapacity)
				trap("Vector.resize(uint)", "`newcapacity` is less than the dynamic array's length, losing elements is not allowed");

			this->m_capacity = newcapacity;
		}

		/// clears the sequence, the capacity will be the same, the length resetted
		inline void clear()
		{
			this->m_length = 0;
		}

		// inserts an element into a specific index and moves the next data
		void insert(uint index, T element)
		{
			if (this->m_length <= index)
				trap("Vector.insert(uint)", "`index` is greater than the dynamic array's length");

			T* result;
			uint i = 0;

			if (this->m_length++ > this->m_capacity)
				result = new T[this->getNewCapacity()];
			else
				result = new T[this->m_capacity];

			for (; i < index; i++)
				result[i] = this->m_raw[i];

			result[i++] = element;

			for (; i < this->m_length+1-index; i++)
				result[i] = this->m_raw[i-1];
			
			delete[] this->m_raw;
			this->m_raw = result;
		}

		/// returns true whether the sequence contains no elements
		inline bool isempty() const
		{
			return this->m_length == 0;
		}

		T& operator [](uint index)
		{
			if (this->m_length <= index)
				trap("Vector.[]", "`index` is greater than the dynamic vector's length");

			return this->m_raw[index];
		}

		/// <summary>
		/// same of `add`
		/// </summary>
		/// <param name="element"></param>
		void operator <<(T element)
		{
			this->add(element);
		}

		/// <summary>
		/// same of `pop`
		/// </summary>
		/// <param name="element"></param>
		void operator >>(T& element)
		{
			element = this->pop();
		}

	private:
		inline bool isOutOfBounds() const
		{
			return this->m_length >= this->m_capacity;
		}

		inline bool isOutOfBounds(uint index) const
		{
			return index >= this->m_length || index < 0;
		}

		inline void reallocRaw()
		{
			T* buf = this->m_raw;
			this->m_raw = (T*)std::malloc(this->getNewCapacity() * sizeof(T));

			for (uint i = 0; i < this->m_length; i++)
				this->m_raw[i] = buf[i];

			std::free(buf);
		}

		inline uint getNewCapacity()
		{
			return this->m_capacity *= 2; // currently there's no need to make a guard on the capacoty
		}

		inline void reallocIFNeeded()
		{
			if (this->isOutOfBounds())
				this->reallocRaw();
		}

		inline void construct(uint initialCapacity)
		{
			this->m_capacity = initialCapacity;
			this->m_length = 0;
			this->m_raw = (T*)std::malloc(sizeof(T) * initialCapacity);
		}
	};
}