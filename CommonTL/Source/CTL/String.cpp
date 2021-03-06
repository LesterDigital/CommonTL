#include "ctlpch.h"
#include "ctl/String.h"

namespace CTL
{
	size_t String::s_MaxSize = 4294967295u;

	String::String(char* string)
	{
		PushString(string);
	}

	String::String(const String& other)
	{
		m_Buffer = new char[other.m_Size];
		m_Size = other.m_Size;
		m_Capacity = m_Size;
		memcpy(m_Buffer, other.m_Buffer, other.m_Size);
	}

	String::String(String&& other)
	{
		m_Buffer = other.m_Buffer;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;

		other.m_Buffer = nullptr;
		other.m_Size = 0;
		other.m_Capacity = 0;
	}

	String::String(size_t size)
	{
		Reserve(size);
	}

	String::String(const char string[])
	{
		PushString(string);
	}

	void String::Copy(char* string)
	{
		Clear();
		PushString(string);
	}

	void String::Copy(const char* string)
	{
		Clear();
		PushString(string);
	}

	void String::PushBack(const char& c)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(ComputeSize(m_Size + 1));

		m_Buffer[m_Size] = c;
		m_Size++;
	}

	void String::PushString(const char* string)
	{
		for (size_t i = 0u; i < s_MaxSize && string[i] != '\0'; i++)
			PushBack(string[i]);
	}

	void String::PushString(char*& string)
	{
		for (size_t i = 0u; i < s_MaxSize && string[i] != '\0'; i++)
			PushBack(string[i]);
	}

	void String::PushString(const String& string)
	{
		for (size_t i = 0u; i < string.Size(); i++)
			PushBack(string[i]);
	}

	String String::operator+(const String& string) const
	{
		String newString = *this;
		newString.PushString(string);

		return newString;
	}	

	void String::operator+=(const String& string)
	{
		PushString(string);
	}

	void String::operator+=(const char* string)
	{
		PushString(string);
	}

	String String::Cut(const size_t& rLeft, const size_t& rRight)
	{
		if (rRight - rLeft < 0)
			return *this;

		String newstr(ComputeSize(rRight - rLeft));

		for (size_t i = rLeft; i <= rRight; i++)
			PushBack((*this)[i]);

		return newstr;
	}

	char* String::Cstr() const
	{
		char* cstr = new char[m_Size + 1]{};

		for (size_t i = 0; i < m_Size; i++)
			cstr[i] = m_Buffer[i];

		return cstr;
	}

	void String::operator=(const char* string)
	{
		Copy(string);
	}

	size_t String::ComputeSize(size_t size) const
	{
		size_t i = 16u;
		for (; i - 1u < size; i *= 2u) {}

		return i - 1u;
	}

	bool String::operator==(const String& string) const
	{
		if (m_Size != string.Size())
			return false;

		for (size_t i = 0; i < m_Size; i++)
			if (m_Buffer[i] != string[i])
				return false;

		return true;
	}

	bool String::operator!=(const String& string) const
	{
		return !(*this == string);
	}

	void String::operator=(char* string)
	{
		Copy(string);
	}

	std::ostream& operator << (std::ostream& stream, const String& string)
	{
		for (size_t i = 0u; i < string.Size(); i++)
			stream << string[i];

		return stream;
	}
}