#pragma once
#ifndef HTD_LIST_H_
#define HTD_LIST_H_

#include <exception>

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
		class iterator
		{
			friend class list<T>;
		private:
			list<T>* parent;
			typename list<T>::DNode* current;
			// Private, only list class can create
			iterator(list<T>* my_parent, DNode* position) :
				parent(my_parent), current(position) {}
		public:
			T&			operator*() const;
			T*			operator->() const;
			iterator&	operator++();
			iterator&	operator--();
			iterator	operator++(int);
			iterator	operator--(int);
			bool		operator==(const iterator&);
			bool		operator!=(const iterator&);

		}; // End Class Iterator
		friend class iterator;

		// Member types
		typedef size_t				size_type;
		typedef T					value_type;
		typedef	value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

		// Constructors
		list();
		explicit list(size_type n);
		list(size_type n, const T&);

		// Destructors
		~list();
	private:
		// Our way to circumnavigate the list
		DNode* m_head;
		DNode* m_tail;

		// For size
		size_type m_length;
	};

}

#endif
