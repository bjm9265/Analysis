// analysis.h
// L. Kiser Nov. 20, 2015

#define MAX_WORD (20)		// maximum length of a legal word_entry

#include "linked_list_functions.h"

// document analysis project functions
extern int process_word ( struct linked_list *p_list, char *word ) ;
extern int read_file( struct linked_list *p_list, char *file_name ) ;
extern struct word_entry get_first_word( struct linked_list *p_list ) ;
extern struct word_entry get_next_word( struct linked_list *p_list ) ;
extern struct word_entry get_prev_word( struct linked_list *p_list ) ;
extern struct word_entry get_last_word( struct linked_list *p_list ) ;
extern int write_unique_word_list_to_csv_file( struct linked_list *p_list, char *file_name ) ;
