//Jacky Huynh
//301305184

#include <iostream>
using namespace std;
#include <cstring> // For declaration of NULL

#include "Deque.h"

// constructor initializes all pointers to NULL, and the current_size to 0 
Deque::Deque() {
	
    left_p = NULL;
    right_p = NULL;
    cursor = NULL;
	current_size = 0;
	
}

// Copy Constructor
Deque::Deque(const Deque& dq) {
	
	current_size = dq.current_size;									// copies the dq.current_siz to current_size
	node *new_node;													// node used to create copies of the nodes in dq
	node *temp = dq.left_p;											// temporary node used to traverse through dq to grab values, starts from the very left of dq
	
	if ( dq.current_size == 0 ) {									// if dq is empty create an empty copy
		left_p = NULL;
		right_p = NULL;
		cursor = NULL;
		current_size = 0;
		return;
	}

	new_node = new node( temp->data, NULL, NULL );					// creates a node for the left pointer
	left_p = new_node;
	
	if (temp == dq.cursor) {										// checks if we should assign cursor
		cursor = new_node;
	}	
	
	if ( temp->next == NULL ) {										// if dq is only size 1 assign right_p to the node that was just created or left_p
		right_p = new_node;
		return;
	}
	
	temp = temp->next;												// temp moves on to the next node
	
	while ( temp->next != NULL ) {									// while to traverse through dq while temp->next != NULL
		new_node->next = new node( temp->data, new_node, NULL );	// creates a new node
		new_node = new_node->next;									// moves the new_node to next to create another node later
		
		if (temp == dq.cursor) {									// checks if we should should assign cursor
			cursor = new_node;
		}
		
		temp = temp->next;											// moves temp to the next node
	}
	
	new_node->next = new node( temp->data, new_node, NULL );		// creates the very last node, which is going to be where right_p is going to point to
	right_p = new_node;
	
	if (temp == dq.cursor) {										// checks if cursor is pointing to right_p
		cursor = new_node;
	}
}

// Destructor
Deque::~Deque() {
	
	if ( current_size == 0 ) {										// checks if deque is empty, if it is just make all pointers NULL
		return;
	}
	
	node *temp_ptr;													// temporary node used to delete nodes in deque
	
	while (left_p != NULL) {										// while loop that traverses through every single node, and deleting them
		temp_ptr = left_p;											// sets the temp_ptr to the very left of deque
		left_p = left_p->next;										// left_p to the next node, as it is about to be deleted
		delete temp_ptr;											// deletes the node
	}
}

void Deque::push_left( int item ) {
	
	if ( current_size == 0 ) {										// checks if the deque is empty, if it is the item about to pushed is going to be the first node
		left_p = new node(item , NULL, NULL);						// creates a new node, for the item
		right_p = left_p;											// right_p is equal to left_p because there is only 1 element in deque
		cursor = left_p;											// cursor points to left_p because that is the only item in deque
	}

	else { 															// if deque not empty
		left_p->prev = new node(item, NULL, left_p);				// creates a new node, for the item
		left_p = left_p->prev;										// moves left_p to the new position 
	}
	
	current_size++;													// increment size
}

void Deque::push_right( int item ) {

	if ( current_size == 0 ) {										// checks if the deque is empty, if it is the item about to pushed is going to be the first node
		right_p = new node(item , NULL, NULL);						// creates a new node, for the item
		left_p = right_p;											// left_p is equal to right_p because there is only 1 element in deque
		cursor = right_p;											// cursor points to right_p because that is the only item in deque
	}
	
	else { 															// if deque not empty
		right_p->next = new node(item, right_p, NULL);				// creates a new node, for the item
		right_p = right_p->next;									// moves right_p to the new position 
	}
	
	current_size++;													// increment size
}

int Deque::pop_left() {

	int temp_val = left_p->data;									// temporary variable to return value that is going to be popped 
	node *temp_ptr = left_p;										// temporary pointer to point to node that is going to be popped to delete
	
	if ( cursor == left_p ) {										// checks if cursor is ontop of left_p if it is we have to move it, cause we don't want to delete cursor
		cursor = cursor->next;
	}
	
	if ( left_p->next != NULL ) {									// if left_p is not the last element that is going to be popped
		left_p = left_p->next;										// move left_p to new position
		left_p -> prev = NULL;										// make the previous position NULL
	}
	
	else {															// if left_p is the last element that is going to be popped
		left_p = NULL;												// all pointers must be NULL now
		right_p = NULL;
		cursor = NULL;
		
	}
	current_size--;													// decrement size
	delete temp_ptr;												// delete the element
	return temp_val;												// return the delete node's value
}

int Deque::pop_right() {

	int temp_val = right_p->data;									// temporary variable to return value that is going to be popped 
	node *temp_ptr = right_p;										// temporary pointer to point to node that is going to be popped to delete
	if ( cursor == right_p ) {										// checks if cursor is ontop of right_p if it is we have to move it, cause we don't want to delete cursor
		cursor = cursor->prev;
	}
	
	if ( right_p->prev != NULL ) {									// if right_p is not the last element that is going to be popped
		right_p = right_p->prev;									// move right_p to new position
		right_p->next = NULL;										// make the previous position NULL
	}
	
	else {															// if right_p is the last element that is going to be popped
		right_p = NULL;												// all pointers must be NULL now
		left_p = NULL;
		cursor = NULL;
	}
	
	current_size--;													// decrement size
	delete temp_ptr;												// delete the element
	return temp_val;												// return the delete node's value
}

bool Deque::empty() {												// checks if deque is empty
	return current_size == 0;
}

int Deque::size() {													// returns the size
	return current_size;
}

bool Deque::cursor_left() {											// moves cursor to the left

	if ( cursor->prev != NULL ) {									// if there is a node to the left of cursor, move it and return true
		cursor = cursor->prev;
		return true;
	}
	
	return false;													// return false if there is no more nodes to the left of cursor

}

bool Deque::cursor_right() {										// moves cursor to the right

	if ( cursor->next != NULL) {									// if there is a node to the right of cursor, move it and return true
		cursor = cursor->next;
		return true;
	}

	return false;													// return false if there is no more nodes to the right of cursor
}

int Deque::peek_left() {											// returns data of left_p
	return left_p->data;
}

int Deque::peek_right() {											// returns data of right_p
	return right_p->data;
}	

int Deque::get_cursor() {											// returns data of cursor
	return cursor->data;
}

void Deque::set_cursor(int i) {										// sets cursor's data
	cursor->data = i;
}

void Deque::display() {												// prints out deque
	
	node * temp = left_p;											// temporary node used to traverse through deque
	
	if ( cursor == NULL ) {											// if deque is empty
		cout << "[] size=0, cursor=NULL." << endl;
		return;
	}
																	// otherwise if deque is not empty print out deque
	cout << "[";
	
	while ( temp != NULL ) {										// while loop that prints out elements till temp is equal to NULL
		cout << temp->data << ";";
		temp = temp->next;
	}
	cout << "] ";
	cout << "size=" << current_size << ", cursor=" << cursor->data << "." << endl;
	
	return;
	
}

void Deque::verbose_display() {
	
	node *temp = left_p;

	if ( cursor == NULL ) {
		cout << "[]" << endl;
		cout << "left_p=NULL; right_p=NULL, cursor=NULL, size=0" << endl;
		cout << endl;
		return;
	}
		
	cout << "[";
	cout << "data="<< temp->data;
	cout << " address: " << temp << ";"<< endl; 
	
	if (temp->next == NULL) {
		cout << "]" << endl;
		cout << "right_p->data=" << right_p->data << " right_p=" << right_p << endl;
		cout << "left_p->data=" << left_p->data << " left_p=" << left_p << endl;
		cout << "cursor->data=" << cursor->data << " cursor" << cursor << endl;
		cout << "size=" << current_size << endl;
		return;
	}
	
	temp = temp->next;

	while ( temp->next != NULL ) {
		cout << "data: "<< temp->data;
		cout << " address: " << temp << ";"<< endl; 
		temp = temp->next;
		
		if ( temp->next == NULL ) {
			cout << "]" << endl;
			cout << "left_p->data=" << left_p->data << ", left_p=" << left_p << "; ";
			cout << "right_p->data=" << right_p->data << ", right_p=" << right_p << "; ";
			cout << "cursor->data=" << cursor->data << ", cursor" << cursor << "; ";
			cout << "size=" << current_size << endl;
		}
	}
	cout << endl;
}
