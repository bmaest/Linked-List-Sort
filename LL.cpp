#include "LL.h"

template <typename type >
LL<type>::iterator::iterator() {
	current = nullptr;				
}

template <typename type>
LL<type>::iterator::iterator(node* ptr) {
	current = ptr;					// constructor sets current to passed pointer
}

template <typename type>
type LL<type>::iterator::operator*() const {
	return current->data;			// dereference overload, returns data in current node
}

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int iterate) {
	current = current->next;		// move to next node, return pointer to this list
	return *this;
}

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int iterate) {
	current = current->prev;		// move to previous node, return pointer to this list
	return *this;
}

template <typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const {
	if (rhs.current == this->current)// return true if both nodes are equal
		return true;
	else
		return false;
}

template <typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const {
	if (rhs.current == this->current)// return false if both nodes are equal
		return false;
	else
		return true;
}

template <typename type>
LL<type>::LL() {
	head = nullptr;			
	tail = nullptr;
}

template <typename type>
LL<type>::LL(const LL<type>& copy) {
	if (copy->head == nullptr)		// return if list is empty
		return;

	node* temp = new node;			// set first item in list
	temp->prev = nullptr;
	this->head = temp;

	node* tempc = copy->head;

	while (tempc != nullptr) {		// create new node and copy contents
		temp->data = tempc->data;

		temp->next = new node;
		temp->next->prev = temp;
		temp = temp->next;
		tempc = temp->next;
	}
}

template <typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs) {
	if (rhs->head == nullptr)		// return if list is empty
		return;

	node* temp = this->head;
	node* tempc = rhs->head;

	while (temp != nullptr && tempc != nullptr) {
		if (temp->data != tempc->data)
			break;					// check if lists are the same

		temp = temp->next;
		tempc = temp->next;
	}

	node* temp = nullptr;

	while (this->head != nullptr) {	// free the list
		temp = this->head;
		this->head = this->head->next;
		free(temp);
	}

	temp = new node;
	temp->prev = nullptr;
	this->head = temp;

	tempc = rhs->head;

	while (tempc != nullptr) {		// copy passed list to this
		temp->data = tempc->data;

		temp->next = new node;
		temp->next->prev = temp;
		temp = temp->next;
		tempc = temp->next;
	}

	return this;
}

template <typename type>
LL<type>::~LL() {
	node* temp = nullptr;
	
	while (this->head != nullptr) {	// free the list, deconstructor
		temp = this->head;
		this->head = this->head->next;
		free(temp);
	}
}

template <typename type>
void LL<type>::tailInsert(const type& item) {
	node* temp = new node;
	temp->data = item;

	if (head != nullptr) {			// if list contains items
		this->tail->next = temp;
		temp->prev = this->tail;
	}
	else {							// edge case, if list is empty
		this->head = temp;
		temp->prev = nullptr;
	}
		
	this->tail = temp;				// set tail
	temp->next = nullptr;
	return;
}

template <typename type>
typename LL<type>::iterator LL<type>::begin() const {
	LL<type>::iterator temp;
	temp.current = this->head;		// return iterator pointing to head of list

	return temp;
}

template <typename type>
typename LL<type>::iterator LL<type>::end() const {
	LL<type>::iterator temp;
	temp.current = this->tail;		// return iterator pointing to tail of list
	return temp;
}

template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2) {
	node* node1 = it1.current;
	node* node2 = it2.current;
									// edge cases, list is less than two items or nodes are the same
	if (this->head == nullptr || this->head->next == nullptr || it1.current == it2.current)
		return;

	if (node1 == this->head)		// edge case, node1 is at head
		this->head = node2;
	else if (node2 == this->head)	// edge case, node2 is at head
		this->head = node1;
	if (node1 == this->tail)		// edge case, node 1 is at tail
		this->tail = node2;
	else if (node2 == this->tail)	// edge case, node 2 is at tail
		this->tail = node1;

	node* temp;
	temp = node1->next;				// swap node 1 and node 2 next pointer
	node1->next = node2->next;
	node2->next = temp;

	if (node1->next != nullptr)		// sets item before node to point to new node
		node1->next->prev = node1;
	if (node2->next != nullptr)
		node2->next->prev = node2;

	temp = node1->prev;				// swap node 1 and node 2 prev pointer
	node1->prev = node2->prev;
	node2->prev = temp;

	if (node1->prev != nullptr)		// sets item after node to point to new nod
		node1->prev->next = node1;
	if (node2->prev != nullptr)
		node2->prev->next = node2;
}