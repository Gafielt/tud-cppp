#ifndef LIST_HPP_
#define LIST_HPP_

#include <cstdlib>
#include "ListItem.hpp"
#include "ListIterator.hpp"
#include <iostream>

/**
 * @name List;
 * @brief linked list using template type T
 * @author cppp
 */
template<typename T>
class List {
public:
    /**
     * @name List();
     * @brief constructor of an empty list object
     * @author cppp
     */
	List();						// create an empty list
    /**
     * @name ~List();
     * @brief destructor of a list object
     * @author cppp
     */
	~List();					// delete the list and all of its elements
    /**
     * @name List(const List &other);
     * @brief copy constructor
     * @author cppp
     * @param other the list object which will be copied
     */
	List(const List &other);	// create a copy of another list
    /**
     * @name appendElement(const T &i);
     * @brief append content i to list object
     * @sa ListItem();
     * @author cppp
     * @param i content which will be appended
     */
	void appendElement(const T &i);				// append an element to the end of the list
    /**
     * @name prependElement(const T &i);
     * @brief prepend content i to list object
     * @author cppp
     * @param i content which will be prepended
     */
	void prependElement(const T &i);			// prepend an element to the beginning of the list
    /**
     * @name insertElementAt(const T &i, size_t pos);
     * @brief insert an element at a specific position in the list
     * @author cppp
     * @param i content which will interted
     * @param pos the position
     */
	void insertElementAt(const T &i, size_t pos);	// insert an element i at position pos
    /**
     * @name getSize() const;
     * @brief get the current size of the list
     * @author cppp
     */
	size_t getSize() const;		// get the number of elements in list
    /**
     * @name getNthElement(size_t n);
     * @brief get the content of the n-th list item
     * @author cppp
     * @param n the position of the n-th item
     * @return the content of the n-th listitem as T reference
     */
	T& getNthElement(size_t n);	// get content of the n-th element.
    /**
     * @name getFirst();
     * @brief get the content of the first list item
     * @author cppp
     * @return the content of the first listitem as T reference
     */
	T& getFirst();				// get content of the first element
    /**
     * @name getLast();
     * @brief get the content of the last list item
     * @author cppp
     * @return the content of the last listitem as T reference
     */
	T& getLast();				// get content of the last element
    /**
     * @name deleteFirst();
     * @brief deletes the first listitem out of the list object
     * @author cppp
     */
	void deleteFirst();			// delete first element
    /**
     * @name deleteLast();
     * @brief deletes the last listitem out of the list object
     * @author cppp
     */
	void deleteLast();			// delete last element
    /**
     * @name deleteAt(size_t pos);
     * @brief deleting the n-th element out of the list
     * @author cppp
     * @param pos the position at which the listitem will be deleted
     */
	void deleteAt(size_t pos);		// delete element at position pos
    /**
     * @name begin();
     * @brief returns a list iteration pointing to the first listitem
     * @author cppp
     * @return a listiteration
     */
	ListIterator<T> begin();	// return an iterator pointing to the first element
    /**
     * @name end();
     * @brief returns a list iteration pointing to the last listitem
     * @author cppp
     * @return a listiteration
     */
	ListIterator<T> end();		// return an iterator pointing to the element after the last one
private:
	ListItem<T> *first, *last;	// first and last item pointers (NULL if list is empty)
	size_t currentSize;			// current size of the list
	friend class ListIterator<T>;
};

#include "List.tpp"

int dummy();

#endif /* LIST_HPP_ */
