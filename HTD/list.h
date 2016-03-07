#pragma once
#ifndef HTD_LIST_H_
#define HTD_LIST_H_

namespace HTD
{
	template <typename T>
	class list
	{
	private:
		// The struct that holds the node data
		struct DNode
		{
			T data;
			DNode* next;
			DNode* prev;

			DNode(const T& the_data,
				DNode* prev_val = nullptr, DNode* next_val = nullptr) : data(the_data), next(next_val), prev(prev_val) {}
		};
	public:
		// Member variables
		static const size_type size_t;
		static const value_type T;
		static const reference value_type&;
		static const const_reference const value_type&;

		// Constructors
		explicit list();
		explicit list(size_type n);
		list(size_type n, const T&);

		// Destructors
		~list();
	};

}

#endif
