// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

// Implement this function first to create an initialized linked list node.
// It must allocate space for the passed string in the one_word structure.
// It must copy the passed string into that structure and sets its word count to 1.
// Assume that the passed word points is not NULL and is not an empty string.
// The calling function is responsible for passing a valid string.
// This function returns a pointer to the allocated node.
struct node *create_node( char *word )
{
	struct node *new_node = malloc(sizeof(struct node));

	new_node->one_word.unique_word = malloc(strlen(word) * sizeof(char)); // allocating memory for the specific passed string into the struct
	strlcpy(new_node->one_word.unique_word, word, strlen(word) + 1);
	new_node->one_word.word_count = 1;
	new_node->p_previous = NULL;
	new_node->p_next = NULL;

	return new_node; // allocated node
}

// Inserts a node at the beginning of the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the passed p_head and p_current members of p_list.
// p_head and p_current will always point to the newly added node.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
int add_node_at_head( struct linked_list *p_list, char *word )
{
	if(p_list == NULL){ // check 1
		return 0;
	}
	else if(word == NULL){ // check 2
		return 0;
	}
	else if(strlen(word) == 0){ // check 3
		return 0;
	}

	struct node *new_node = create_node(word); // creating the node

	if(p_list->p_head != NULL){ // on adding when there are already nodes in the list
		new_node->p_next = p_list->p_head;
		p_list->p_head->p_previous = new_node; // sets the previous head node 
		p_list->p_head = new_node;  // head always points to new_node
	}else{ // when the list is empty
		p_list->p_head = new_node; // head always points to new_node
		p_list->p_tail = new_node; // sets tail to new_node since its the only node in the list
	}

	p_list->p_current = new_node; // always points to the new node
	return 1;
}

// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).
int clear_linked_list( struct linked_list *p_list )
{
	int freed = 0; // counter

	while(p_list->p_head != NULL){
		struct node* copy = p_list->p_head; // making a copy of the node
		p_list->p_head = p_list->p_head->p_next; // making the next node the head
		copy = NULL; // freeing the node
		freed++; // incrememnting the counter
	}

	if(p_list->p_current != NULL){ // check 1
		p_list->p_current = NULL;
	}

	if(p_list->p_tail != NULL){ // check 2
		p_list->p_tail = NULL;
	}

	if(p_list->p_head != NULL){ // redundent check 3
		p_list->p_head = NULL;
	}

	return freed ;	// REMOVE THIS and replace with working code
}


// Inserts a node after the current pointer in the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the p_current member of p_list. p_current points to the newly added node.
// p_head is updated only if p_current is NULL (an empty list).
// p_tail is updated only if the new node is at the end of the list.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
// Hint: if this function is called with a p_current that is NULL (meaning the list is empty)
//       use the add_node_at_head function to create the new node.
int add_node_after_current( struct linked_list *p_list, char *word )
{
	if(p_list == NULL){ // check 1
		return 0;
	}
	else if(word == NULL){ // check 2
		return 0;
	}
	else if(strlen(word) == 0){ // check 3
		return 0;
	}

	struct node *new_node = create_node(word); // create the node

	if(p_list->p_current == NULL){ // empty list

		add_node_at_head(p_list, word); // calling previous function to add the node to the head
	
	}else{ // list isn't empty
		new_node->p_previous = p_list->p_current; // sets the previous of the new node as the current node
		new_node->p_next = p_list->p_current->p_next; // sets the next node of the new node to the next node of the current node

		if(p_list->p_current->p_next != NULL){ // if there is node after the current
			p_list->p_current->p_next->p_previous = new_node; // sets the previous node to the current to the new node
		}

		p_list->p_current->p_next = new_node; // set the new node as the current
		p_list->p_current = new_node; // set the new node as the current

		if(p_list->p_current->p_next == NULL){ // if there is no node after the current
			p_list->p_tail = p_list->p_current; // set the tail as the current node
		}
	}

	return 1 ;	// REMOVE THIS and replace with working code
}

// Searches the linked list for the passed word.
// NOTE -- this function REQUIRES that the linked list has been maintained in English language alphabetical order.
// Definition of match: every letter must match exactly including by case.
// e.g. "A" does NOT match "a". "a " does NOT match "a"
//
// If found it sets the current pointer to the matching node.
// If not found it returns a failure and sets the current pointer to the node just before the
// insertion point (by alphabetic order). Note the special case for a new word that goes at the
// beginning of the list. See the examples below.
//
// Hint: use strcmp to determine sorting order.
//
// If it is found the current pointer is set to the node containing the matching word.
// If it is found this function returns a 1 to indicate success.
//
// If it is not found the current pointer is set to the node just before the insertion point.
// If it is not found the function returns a 0 to indicate failure.
// e.g. the list contains the words "apple", "buy", "cat".
//      Searching for "baby" would set current to the node containing "apple".
//      Searching for "acid" would set current to NULL to indicate that "acid" belongs at the head.
//      searching for "zebra" would set current to the node containing "cat".
//
// Tests on p_list and word: p_list, p_list->head, and word must all not be NULL.
// In addition, word must not be an empty string.
// We must have a valid list with at least one node and we must a valid word to match.
// If any of these conditions are violated this function returns a -1 to indicate invalid input.
int find_word( struct linked_list *p_list, char *word )
{
	if(p_list == NULL){ // check 1
		return -1;
	}
	else if(p_list->p_head == NULL){ // check 2
		return -1;
	}
	else if(word == NULL){ // check 3
		return -1;
	}
	else if(strlen(word) == 0){ // check 4
		return -1;
	}
	
	struct node* possible = p_list->p_head; // takes the head of the list to check it for the matching word

	while(possible != NULL){ // loop for comparison
		int compare = strcmp(word, possible->one_word.unique_word); // string compare to compare the possible node to the word
		if(compare < 0){
			p_list->p_current = possible->p_previous; // sets the possible node to the previous node to continue the loop
			return 0;
		}
		if(compare == 0){ // found the matching node and sets the current node to the possible node
			p_list->p_current = possible;
			return 1;
		}
		if(compare > 0){ // sets the possible node to the next node to continue the loop
			possible = possible->p_next;
		}
	}

	 p_list->p_current = p_list->p_tail; // current node is the tail node to accomedate the 1 test I kept failing

	return 0 ;	// REMOVE THS and replace with working code
}
