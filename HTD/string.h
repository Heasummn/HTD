#pragma once
#ifndef HTD_STRING_H_
#define HTD_STRING_H_
namespace htd
{
	class string
	{
	private:
		// For size
		size_t m_length;
		// For reallocation
		size_t maxLength = 8;

		char* m_data = new char[maxLength];

		void reallocate();
		void fillData(const char*);

	public:
		const static size_t npos = -1; // Largest possible size_t value, string can't be higher

		// Constructors
		string();
		string(char);
		string(const char*);
		string(const string&);
		string(string&&);

		// Deconstructor
		~string();

		// Size function
		size_t length() const;
		size_t size() const;
		void clear();
		void reserve(size_t n = 0);
		size_t capacity() const;
		bool empty();

		// Element accessors
		char& at(size_t);
		const char& at(size_t) const;
		char& front();
		const char& front() const;
		char& back();
		const char& back() const;

		// String Modifications
		string& operator+=(const string&);
		string& operator+=(char);
		void string::swap(string&);
		void push_back(char);
		void pop_back();

		// String Operations
		const char* data() const;
		const char* c_str() const;
		string substr(size_t pos = 0, size_t len = npos) const;
		size_t find(char c, size_t pos = 0);
		size_t find(const string& str, size_t pos = 0);

		// Operators
		string& operator= (const char*);
		string& operator=(const string& str);
		string& operator=(string&& str);
		char& operator[](size_t);
		const char& operator[](size_t) const;
	};

	// Non-Member Functions
	string operator+ (const string&, const string&);
	string operator+ (const string& rhs, char lhs);
	bool operator== (const string&, const string&);
	bool operator!= (const string&, const string&);
	//std::istream& operator>>(std::istream&, string&);
	//std::ostream& operator<<(std::ostream&, const string&);

} // End namespace htd

#endif