#include "List.hpp"
#include "ListItem.hpp"

List::List():
	first(nullptr), last(nullptr), currentSize(0)
{}

List::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0) {
		deleteFirst();
	}
}

List::List(const List& other):
	first(nullptr), last(nullptr), currentSize(0)
{
	// Copy list item-wise to avoid having two lists pointing at the same list items
	for (ListItem *item = other.first; item != nullptr; item = item->getNext()) {
		appendElement(item->getContent());
	}
}

void List::appendElement(int i) {
	ListItem *item = new ListItem(last, nullptr, i);
	last = item;
	if (first == nullptr) {
		first = item;
	}
	++currentSize;
}

void List::prependElement(int i) {
	ListItem *item = new ListItem(nullptr, first, i);
	first = item;
	if (last == nullptr) {
		last = item;
	}
	++currentSize;
}

void List::insertElementAt(int i, size_t pos) {
	if (pos == 0) {
		prependElement(i);
	}
	else if (pos >= getSize()) {
		appendElement(i);
	}
	else {
		ListItem* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		new ListItem(p->getPrevious(), p, i);
		++currentSize;
	}
}

size_t List::getSize() const {
	return currentSize;
}

int& List::getNthElement(size_t n) {
	size_t index = n;
	ListItem* p = first;
	// iterate over elements
	while (index-- > 0) {
		p = p->getNext();
	}
	return p->getContent();
}

int& List::getFirst() {
	return first->getContent();
}

int& List::getLast() {
	return last->getContent();
}

int List::deleteFirst() {
	if (first) {
		int content = first->getContent(); // save content
		ListItem *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		if (next == nullptr) {// do not forget to reset last element if list is empty
			last = nullptr;
		}
		--currentSize;
		return content;
	}
	return 0;
}

int List::deleteLast() {
	if (last) {
		int content = last->getContent();
		ListItem *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		if (prev == nullptr) {// do not forget to reset first element if list is empty
			first = nullptr;
		}
		--currentSize;
		return content;
	}
	return 0;
}

int List::deleteAt(size_t pos) {
	if (pos == 0) {
		return deleteFirst();
	}
	else if (pos >= currentSize - 1) {
		return deleteLast();
	}
	else {
		size_t index = pos;
		ListItem* p = first;
		// iterate over elements
		while (index-- > 0) {
			p = p->getNext();
		}
		int content = p->getContent();
		delete p;
		--currentSize;
		return content;
	}
}

ListIterator List::begin() {
	return ListIterator(this, first);
}
ListIterator List::end() {
	return ListIterator(this, nullptr);
}

/*
 * This solution uses the begin and end iterators.
 * Instead, we could also List::first and ListItem::next to navigate along
 * the items of the list.
 */
std::ostream &operator<<(std::ostream &stream,  List &list){
	for (ListIterator iter = list.begin(); iter != list.end(); ++iter)
	{
		stream << *iter << ", ";
	}
	return stream;
}
