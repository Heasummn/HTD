#include "list.h"
using namespace HTD;

template <typename T>
list<T>::list()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

template <typename T>
list<T>::~list()
{
	delete m_head;
	delete m_tail;
}

template <typename T>
typename list<T>::reference
list<T>::iterator::operator*() const
{
	if (current == nullptr)
		throw std::invalid_argument("Attemp to access null value");
	return curent->data;
}

template <typename T>
typename list<T>::pointer
list<T>::iterator::operator->() const
{
	if(current == nullptr)
		throw std::invalid_argument("Attemp to access null value");
	&(current->data);
}

template <typename T>
typename list<T>::iterator&
list<T>::iterator::operator++()
{
	if (current == nullptr)
		throw std::invalid_argument("Attempt to iterator in null");
	curent = current->next;
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
HTD::list<T>::iterator::operator++(int)
{
	iterator old_value = *this; // Store the old value
	++(*this); // Advance self
	return old_value;
}

template<typename T>
typename list<T>::iterator
HTD::list<T>::iterator::operator--(int)
{
	iterator old_value = *this; // Store old
	--(*this); // Decrement
	return old_value;
}

template<typename T>
bool HTD::list<T>::iterator::operator==(const iterator & other)
{
	return current == other.current;
}

template<typename T>
bool HTD::list<T>::iterator::operator!=(const iterator &)
{
	return !operator==(other);
}

// This functions makes sure that no linker errors happen
// No need to ever use it
void HTD_temp()
{
	list<int> tempObj;
}