#pragma once
#ifndef HTD_LIST_H_
#define HTD_LIST_H_

#include <exception>

namespace htd
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
		}; // End struct DNode
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
		typedef		size_t				size_type;
		typedef		T					value_type;
		typedef		value_type&			reference;
		typedef		const value_type&	const_reference;
		typedef		value_type*			pointer;
		typedef		const value_type*	const_pointer;

		// Constructors
		list();
		list(size_type n, const T&);

		// Destructors
		~list();

		// Insertion
		void push_front(const value_type&);
		void push_back(const value_type&);

		// Iterator methods
		iterator begin();
		iterator end();
	private:
		// Our way to circumnavigate the list
		DNode* m_head;
		DNode* m_tail;

		// For size
		size_type m_length;

	}; // End class list

} // End namespace HTD

#endif // HTD_LIST_H_

namespace htd
{
	// Constructors
	template <typename T>
	list<T>::list()
	{
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}

	template<typename T>
	list<T>::list(size_type n, const T& item)
	{
		size_type counter = 0;
		while (counter < n)
		{
			push_back(item);
			counter++;
		}
	}

	// Destructor
	template <typename T>
	list<T>::~list()
	{
		while (m_head != nullptr)
		{
			DNode* currNode = m_head; // Set the current node to the head
			m_head = m_head->next; // Shift head over one
			delete currNode; // Get rid of the current Node
		} // end while

		m_tail = nullptr;
		m_length = 0;
	}

	// Insertion
	template<typename T>
	void list<T>::push_front(const value_type& item)
	{
		m_head = new DNode(item, nullptr, m_head); // Make new node at front
		if (m_head->next != nullptr) // If next node not empty
			m_head->next->prev = m_head; // Modify second elements prev
		if (m_tail == nullptr) // the end is empty, meaning the list was empty
			m_tail = m_head; // Make the head also the last element
		m_length++;

	}

	template<typename T>
	void list<T>::push_back(const value_type& item)
	{
		if (m_tail != nullptr) // Not empty
		{
			m_tail = new DNode(item, m_tail, nullptr);
			m_tail->prev->next = m_tail;
			m_length++;

		}
		else // Is empty
		{
			push_front(item);
		}
	}

	template<typename T>
	typename list<T>::iterator 
	list<T>::begin()
	{
		list<T>::iterator output(&*this, m_head);
		return output;
	}

	template<typename T>
	typename list<T>::iterator 
	list<T>::end()
	{
		list<T>::iterator output(&*this, m_tail->next);
		return output;
	}

	// Iterator Operators
	template <typename T>
	typename list<T>::reference
		list<T>::iterator::operator*() const
	{
		if (current == nullptr)
			throw std::invalid_argument("Attemp to access null value");
		return current->data;
	}

	template <typename T>
	typename list<T>::pointer
		list<T>::iterator::operator->() const
	{
		if (current == nullptr)
			throw std::invalid_argument("Attemp to access null value");
		&(current->data);
	}

	template <typename T>
	typename list<T>::iterator&
		list<T>::iterator::operator++()
	{
		if (current == nullptr)
			throw std::invalid_argument("Attempt to iterate into null");
		current = current->next;
		return *this;
	}

	template <typename T>
	typename list<T>::iterator&
		list<T>::iterator::operator--()
	{
		if (current == parent->head)
			throw std::invalid_argument("Attempt to iterate into null");
		if (current == nullptr) // Past the last element
			current = parent->tail;
		else
			current = current->prev;
		return *this;
	}

	template<typename T>
	typename list<T>::iterator
		list<T>::iterator::operator++(int)
	{
		iterator old_value = *this; // Store the old value
		++(*this); // Advance self
		return old_value;
	}

	template<typename T>
	typename list<T>::iterator
		list<T>::iterator::operator--(int)
	{
		iterator old_value = *this; // Store old
		--(*this); // Decrement
		return old_value;
	}

	template<typename T>
	bool list<T>::iterator::operator==(const iterator & other)
	{
		return current == other.current;
	}

	template<typename T>
	bool list<T>::iterator::operator!=(const iterator& other)
	{
		return !operator==(other);
	}
}