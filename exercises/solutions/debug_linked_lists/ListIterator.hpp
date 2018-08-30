#ifndef LISTITERATOR_HPP_
#define LISTITERATOR_HPP_

class ListItem;
class List;

/**
 * @name ListIterator
 * @author cppp
 * @brief Iterator to iterate through a list
 * @sa List;
 */
class ListIterator {
public:
    /**
     * @name ListIterator(List *list, ListItem* item);
     * @author cppp
     * @brief constructor of a listiterator using a consisting list pointing to a certain list item
     * @param list the list which should be iterated
     * @param item the list item at which the iterator is initialized
     */
	ListIterator(List *list, ListItem *item);			// create a new list iterator pointing to an item in a list
    /**
     * @name operator*();
     * @author cppp
     * @brief operator * used to get the content the listitem at which the iterator points
     */
	int& operator*();									// get the content of the current element
    /**
     * @name operator!=(const ListIterator& other);
     * @author cppp
     * @brief operator != used to check if two listiterators are equal
     * @param other a constant listiterator reference which will be used for the equality check
     * @return true iff the iterators are equal, otherwise false
     */
	bool operator!=(const ListIterator& other) const;	// check whether this iterator is not equal to another one
	
    /**
     * @name operator++();
     * @author cppp
     * @brief operator ++ used to increment the iterator and return itself (prefix ++)
     * @return the increased listiterator
     */
	ListIterator& operator++();		// increment this iterator and return itself (prefix ++)
    /**
     * @name operator++(int);
     * @author cppp
     * @brief operator ++ used to increment the iterator and return itself (postfix ++)
     * @return the increased listiterator
     */
	ListIterator operator++(int);	// increment this iterator and return the previous (postfix ++)
    /**
     * @name operator--();
     * @author cppp
     * @brief operator -- used to decrease the iterator and return itself (prefix --)
     * @return the increased listiterator
     */
	ListIterator& operator--();		// decrement this iterator and return itself (prefix --)
    /**
     * @name operator--(int);
     * @author cppp
     * @brief operator -- used to decrement the iterator and return itself (postfix --)
     * @return the increased listiterator
     */
	ListIterator operator--(int);	// decrement this iterator and return the previous (postfix --)
private:
	List *list;
	ListItem *item;
};

#endif /* LISTITERATOR_HPP_ */
