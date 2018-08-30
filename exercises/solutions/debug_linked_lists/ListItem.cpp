#include "ListItem.hpp"

ListItem::ListItem(ListItem *prev, ListItem *next, int content):
	previous(prev), next(next), content(content)
{
	if (previous) {
		previous->next = this;
	}
	if (next) {
		next->previous = this;
	}
}

ListItem::~ListItem() {
	if (previous) {
		previous->next = next;
	}
	if (next) {
		next->previous = previous;
	}
}

int& ListItem::getContent() {
	return content;
}

ListItem* ListItem::getNext() {
	return next;
}

ListItem* ListItem::getPrevious() {
	return previous;
}
