#include "List.hpp"
#include <iostream>

int main() {
	List list;
	list.appendElement(1);
	list.appendElement(2);
	list.appendElement(-1);
	list.appendElement(3);
	list.prependElement(0);
	list.deleteFirst();			// delete 0
	list.deleteAt(2);			// delete -1
	// list2 should be 1, 2, 3 now
	
	List list2(list);			
	
	list.deleteAt(2);			// delete 3
	list.appendElement(3);		// append 3 
	list.deleteAt(0);			// delete 1
	list.prependElement(1);		// prepend 1
	list.deleteLast();			// delete 3
	// list should be 2, 3 now
	
	std::cout << "list size = " << list.getSize() << std::endl;
	for (ListIterator iter = list.begin(); iter != list.end(); ++iter) {
		std::cout << *iter << std::endl;
	}
	std::cout << std::endl << "list2 size = " << list2.getSize() << std::endl;
	for (ListIterator iter = list2.begin(); iter != list2.end(); ++iter) {
		std::cout << *iter << std::endl;
	}

	std::cout << list2 << std::endl;
}
