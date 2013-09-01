/*
 * List.h
 */

#ifndef LIST_H_
#define LIST_H_

#include <cstdlib>
#include "ListItem.h"
#include "ListIterator.h"

#include <iostream>

template<class T>
class List {
public:
	/** Create an empty list */
	List();

	/** Delete the list and all elements */
	~List();

	/** Create List as copy of other list */
	List(const List<T>& other);

	/** append an element to end of the list */
	void appendElement(const T& i);

	/** prepend an element to beginning of the list */
	void prependElement(const T& i);

	/** insert element at position pos. append/prepend element if pos outside of range*/
	void insertElementAt(const T& i, int pos);

	/** number of elements in list */
	int getSize() const;

	/* return n-th element. No range checks. slow! */
	T& getNthElement(int n);

	/** return first element */
	T& getFirst();

	/** return last element */
	T& getLast();

	/** delete first element */
	void deleteFirst();

	/** delete last element */
	void deleteLast();

	/** delete element at given position. delete first/last if pos outside of range */
	void deleteAt(int pos);

	/** iterator to first element */
	ListIterator<T> begin();

	/** iterator to element after the last one*/
	ListIterator<T> end();

private:
	/** first and last item pointers. NULL if list is empty */
	ListItem<T> *first, *last;

	/** current size of the list */
	int currentSize;

	/** declare ListIterator as friend to allow access on list items */
	friend class ListIterator<T> ;
};

template<class T>
List<T>::List() :
		first(NULL), last(NULL), currentSize(0) {
}

template<class T>
List<T>::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0)
		deleteFirst();
}

template<class T>
List<T>::List(const List<T>& other) :
		first(NULL), last(NULL), currentSize(0) {
	for (ListItem<T> *item = other.first; item != NULL; item = item->getNext())
		appendElement(item->getContent());
}

template<class T>
void List<T>::appendElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(last, NULL, i);
	last = item;
	
	// if size WAS 0, set first item to newly created item
	if (currentSize++ == 0)
		first = item;
}

template<class T>
void List<T>::prependElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(NULL, first, i);
	first = item;
	
	// if size WAS 0, set last item to newly created item
	if (currentSize++ == 0)
		last = item;
}

template<class T>
void List<T>::insertElementAt(const T& i, int pos) {
	if (pos <= 0)
		prependElement(i);
	if (pos >= getSize())
		appendElement(i);
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0)
			p = p->getNext();
		
		new ListItem<T>(p->getPrevious(), p, i);
		currentSize++;
	}
}

template<class T>
int List<T>::getSize() const {
	return currentSize;
}

template<class T>
T& List<T>::getNthElement(int n) {
	ListItem<T>* p = first;
	// iterate over elements
	while (n-- > 0)
		p = p->getNext();
	
	return p->getContent();
}

template<class T>
T& List<T>::getFirst() {
	return first->getContent();
}

template<class T>
T& List<T>::getLast() {
	return last->getContent();
}

template<class T>
void List<T>::deleteFirst() {
	if (first) {
		ListItem<T> *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		        
		if (next == NULL
		) // do not forget to reset last element if list is empty
			last = NULL;
		
		currentSize--;
	}
}

template<class T>
void List<T>::deleteLast() {
	if (last) {
		ListItem<T> *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		        
		if (last == NULL
		) // do not forget to reset first element if list is empty
			first = NULL;
		
		currentSize--;
	}
}

/** delete element at given position. delete first/last if pos outside of range */
template<class T>
void List<T>::deleteAt(int pos) {
	if (pos <= 0)
		return deleteFirst();
	else if (pos >= currentSize - 1)
		return deleteLast();
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0)
			p = p->getNext();
		
		delete p;
		currentSize--;
	}
}

template<class T>
ListIterator<T> List<T>::begin() {
	return ListIterator<T>(this, first);
}

template<class T>
ListIterator<T> List<T>::end() {
	return ListIterator<T>(this, NULL);
}

template<class T>
std::ostream& operator<<(ostream& out, List<T>& list) {
	out << "[";
	ListIterator<T> iter = list.begin();
	if (iter != list.end()) {
		out << *iter++;
		while (iter != list.end())
			out << ", " << *iter++;
	}
	out << "]";
	return out;
}

#endif /* LIST_H_ */
