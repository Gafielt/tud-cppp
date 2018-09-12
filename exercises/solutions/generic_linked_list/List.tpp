
template<typename T>
List<T>::List():
	first(NULL), last(NULL), currentSize(0)
{}

template<typename T>
List<T>::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0) {
		deleteFirst();
	}
}

template<typename T>
List<T>::List(const List& other):
	first(NULL), last(NULL), currentSize(0)
{
	for (ListItem<T> *item = other.first; item != NULL; item = item->getNext()) {
		appendElement(item->getContent());
	}
}

template<typename T>
void List<T>::appendElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(last, NULL, i);
	last = item;
	// if size WAS 0, set first item to newly created item
	if (currentSize++ == 0) {
		first = item;
	}
}

template<typename T>
void List<T>::prependElement(const T& i) {
	ListItem<T> *item = new ListItem<T>(NULL, first, i);
	first = item;
	// if size WAS 0, set last item to newly created item
	if (currentSize++ == 0) {
		last = item;
	}
}

template<typename T>
void List<T>::insertElementAt(const T& i, size_t pos) {
	if(pos > getSize()) {
		//Will also be true for negative values of pos, because of the wrap-around.
		throw std::out_of_range("List::insertElementAt() out of range");
	} 
	else if (pos == 0) {
		prependElement(i);
	}
	else if (pos >= getSize()) {
		appendElement(i);
	}
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		new ListItem<T>(p->getPrevious(), p, i);
		++currentSize;
	}
}

template<typename T>
size_t List<T>::getSize() const {
	return currentSize;
}

template<typename T>
T& List<T>::getNthElement(size_t n) {
	if (n >= getSize()) {
		throw std::out_of_range("List::getNthElement() out of range");
	}
	
	ListItem<T>* p = first;
	// iterate over elements
	while (n-- > 0) {
		p = p->getNext();
	}
	return p->getContent();
}

template<typename T>
T& List<T>::getFirst() {
	return first->getContent();
}

template<typename T>
T& List<T>::getLast() {
	return last->getContent();
}

template<typename T>
void List<T>::deleteFirst() {
	if (first) {
		ListItem<T> *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		// do not forget to reset last element if list is empty
		if (next == NULL) {
			last = NULL;
		}
		--currentSize;
	}
}

template<typename T>
void List<T>::deleteLast() {
	if (last) {
		ListItem<T> *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		// do not forget to reset first element if list is empty
		if (last == NULL) {
			first = NULL;
		}
		--currentSize;
	}
}

/** delete element at given position. delete first/last if pos outside of range */
template<typename T>
void List<T>::deleteAt(size_t pos) {
	if (pos >= getSize()) {
		throw std::out_of_range("List::deleteAt() out of range");
	} 
	else if (pos <= 0) {
		return deleteFirst();
	}
	else if (pos >= currentSize - 1) {
		return deleteLast();
	}
	else {
		ListItem<T>* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		delete p;
		--currentSize;
	}
}

template<typename T>
ListIterator<T> List<T>::begin() {
	return ListIterator<T>(this, first);
}

template<typename T>
ListIterator<T> List<T>::end() {
	return ListIterator<T>(this, NULL);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, List<T>& list) {
	out << "[";
	ListIterator<T> iter = list.begin();
	if (iter != list.end()) {
		out << *iter++;
		while (iter != list.end()) {
			out << ", " << *iter++;
		}
	}
	out << "]";
	return out;
}
