#include <cstring>
#include <stdexcept>
#include "string.h"

namespace htd {

	// Constructors
	string::string()
	{
		// Set the length conditions
		m_length = 0;

		// Null Terminate the empty string
		*m_data = '\0';
	}

	string::string(const char* string)
	{
		// TODO: if the string isn't a cstring, IE, not null-terminated, we are screwed
		// TODO: Ignore newlines and other weird whitespace characters for the length
		fillData(string);

	}

	string::string(char c)
	{
		m_length = 1;
		m_data[0] = c;
		m_data[1] = '\0';
	}

	string::string(const string& str) : string(str.data()) {}

	string::string(string&& str) : string(str.data())
	{
		str.m_length = 0;
		str.maxLength = 0;
		str.m_data = nullptr;

	}


	// Destructor
	string::~string()
	{
		delete[] m_data;
	}


	// Size functions
	size_t string::length() const
	{
		return sizeof(char) * m_length;
	}

	size_t string::size() const
	{
		
		return sizeof(char) * m_length; // Size in bytes
	}

	void string::clear()
	{
		delete[] m_data; // Clean up
		maxLength = 8; // Reset length
		m_data = new char[maxLength];
		m_length = 0;
		*m_data = '\0'; // Null Terminate
	}

	void string::reserve(size_t n)
	{
		if (n <= 0) // The user is trying to screw with himself
			return;
		char* temp = m_data;
		m_data = new char[n];
		memcpy(m_data, temp, m_length);
		maxLength = n;
		delete[] temp;
	}

	size_t string::capacity() const
	{
		return maxLength - 1;
	}

	bool string::empty()
	{
		return m_length == 0;
	}


	// Element Access functions
	char& string::at(size_t pos)
	{
		if (pos > m_length - 1)
			throw std::out_of_range("Index out of bounds");
		// O(1) Time complexity cause arrays are cool
		return *(m_data + pos);
	}

	const char& string::at(size_t pos) const
	{
		if (pos > m_length - 1)
			throw std::out_of_range("Index out of bounds");

			// O(1) Time complexity cause arrays are cool
			return *(m_data + pos);
	}

	char& string::front()
	{
		return *m_data;
	}

	const char& string::front() const
	{
		return *m_data;
	}

	char& string::back()
	{
		return *(m_data + m_length - 1);
	}

	const char& string::back() const
	{
		return *(m_data + m_length - 1);
	}


	// Element Access operators
	char& string::operator[](size_t pos)
	{
		return *(m_data + pos); // Throws no exceptions
	}

	const char& string::operator[](size_t pos) const
	{
		return *(m_data + pos); // Throws no exceptions
	}


	string& string::operator=(const char* str) 
	{
		clear();
		fillData(str);
		return *this;
	}

	string& string::operator=(const string& str)
	{
		clear();
		fillData(str.data());
		return *this;
	}

	string& string::operator=(string&& str)
	{
		clear();
		fillData(str.data());
		str.m_data = nullptr;
		str.m_length = 0;
		str.maxLength = 0;
		return *this;
	}

	
	// String Modifications
	string& string::operator+=(const string& str)
	{
		*this = *this + str;
		return *this;
	}

	string& string::operator+=(char c)
	{
		*this = *this + c;
		return *this;
	}

	// String Operations
	const char* string::data() const
	{
		return m_data;
	}

	const char* string::c_str() const
	{
		return m_data;
	}

	string string::substr(size_t pos, size_t len) const
	{
		string output = string(); // Create our starting string
		char* tempData = m_data;
		size_t index = 0;
		tempData += pos; // Set the starting position
		while (*tempData && index < len)
		{
			output += *tempData;
			index++;
			tempData++;
		} // End while
		return output;
	}

	size_t string::find(char c, size_t pos)
	{
		if (pos > m_length)
			return npos;

		char* tempData = m_data + pos;
		size_t index = 0;
		
		while (*tempData && *tempData != c)
		{
			tempData++;
			index++;
		}
		if (*tempData)
			return index;
		return npos;
	}

	size_t string::find(const string& str, size_t pos)
	{

		if(pos < 0 || pos >= m_length)
			return npos;

		size_t index = 0, counter = 0;
		char* tempData = m_data + pos;

		if (*tempData == *str.data())
			return 0;

		while (*tempData && (*tempData != *str.data())) // While we aren't on the first char
		{
			tempData++; // Keep moving
			index++;

			while (*tempData && (*tempData == *(str.data() + counter))) // Are we equal to the next chars?
			{ // If we're in here, we are equal to the first char
				tempData++; // Continue to move
				counter++;
				if (counter == str.length()) // If we're equal to all the chars
					return index;
			} // end while

		} // end while
		return npos;
	}

	void string::swap(string& str)
	{
		string temp = str;
		str = *this;
		*this = temp;
	}

	void string::push_back(char c)
	{
		*this += c;
	}

	void string::pop_back()
	{
		*this = (*this).substr(0, m_length - 1);
	}



	// Privates
	void string::reallocate()
	{
		// TODO: Make my own copy function
		/* PsuedoCode
		Double max length
		Make a temporary copy of str
		Reallocate str
		Copy the temporary back into str
		Delete the temporary
		*/

		maxLength *= 2;
		char* temp = m_data;
		m_data = new char[maxLength]();
		memcpy(m_data, temp, maxLength / 2);
		delete[] temp;
	}

	void string::fillData(const char* string)
	{
		m_length = 0;
		while (*string)
		{
			if (m_length == (maxLength - 1))
				reallocate();
			m_data[m_length] = *string;
			string++;
			m_length++;
		} // end while
		m_data[m_length] = '\0'; // Null terminate
	}


	// Non-Member Functions
	string operator+ (const string& rhs, const string& lhs)
	{
		char* result = new char[rhs.length() + lhs.length() + 1]();
		int index = 0; // Counter
		memcpy(result, rhs.data(), rhs.length()); // Copy rhs into bigger sized array
		//std::cout << result << std::endl;
		while (lhs[index])
		{
			result[rhs.length() + index] = lhs[index];
			index++;
		} // endwhile
		result[rhs.length() + lhs.length()] = '\0'; // Null terminate

		string output = string(result);
		delete[] result;
		return output;
	}

	string operator+ (const string& rhs, char lhs)
	{
		char* result = new char[rhs.length() + 2];
		memcpy(result, rhs.data(), rhs.length());
		result[rhs.length()] = lhs;
		result[rhs.length() + 1] = '\0';

		string output = string(result);
		delete[] result;
		return output;
	}

	bool operator== (const string& rhs, const string& lhs)
	{
		// Saving time and double checking later on
		if (rhs.length() != lhs.length())
			return false;

		// Initialize comparison boolean
		bool equal = true;
		size_t counter = 0; // counter

		// Data never changes, make it a var to save writing time
		const char* rhsData = rhs.data();
		const char* lhsData = lhs.data();
		while (equal && counter < rhs.length())
		{
			equal = (*(rhsData + counter) == *(lhsData + counter));
			counter++;
		} // End While

		return equal;
	}
	bool operator!= (const string& rhs, const string& lhs)
	{
		if (rhs.length() != lhs.length())
			return true;
		bool equal = true;
		size_t counter = 0;

		// Data never changes, make it a var to save time
		const char* rhsData = rhs.data();
		const char* lhsData = lhs.data();

		while (equal && counter < rhs.length())
		{
			equal = *(rhsData + counter) == *(lhsData + counter);
			counter++;
		} // end while

		return !equal;
	}
} // End of namespace htd


  /*std::istream& operator>>(std::istream& is, string& str)
  {
  char c;
  while (is.get(c) && !iswspace(c))
  str += c;
  return is;
  }


  //std::ostream& operator<<(std::ostream& os, const string& str)
  {
  os << str.data();
  return os;
  }
  */