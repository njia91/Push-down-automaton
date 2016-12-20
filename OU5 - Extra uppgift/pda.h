/*

  Filename  : pha.h

  Usage     : This datatype can be used to create a Push Down Automata(PDA).
              Aslong as the user gives the PDA the necessary controll functions
              for the input string and the stack and aswell the transition
              function for a specifik edge.


  Author    : Michael Andersson
  CS-id     : dv15man



*/


#ifndef __pda
#define __pda

#include "dlist.h"
#include "stack_1cell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*A struct for each state, contains name of state, list of edges
  and it is accepting or not.*/
typedef struct{
  char *s_name;
  dlist *trans_list;
  bool s_accept;
} pda_state;


/*A struct for the PDA-datatype. Contains a list with all states,
  pointer to a stack and a pointer to initial state and current state
  It also contains a variabel for the string index*/
typedef struct {
  dlist *s_list;
  stack *pda_stack;
  pda_state *initial_state;
  pda_state *current_state;
  int indexCounter;
} pda;

/*Defining function pointers for the transitions*/
typedef bool transitionTest_input(char c);
typedef bool transitionTest_stack(pda *aut);
typedef void trans_function(char c, pda *aut);

/*A struct for each transition/edge in the PDA.
  It contains a function pointer to input and stack test functions and
  to the transition function. It also contains a pointer to the destination
  state.*/
typedef struct {
  transitionTest_input *t_input;
  transitionTest_stack *t_stack;
  trans_function *t_func;
  pda_state *dest;
} transition;



/*
Purpose: Creates a PDA
Return:  Returns a pointer to the PDA.
Description: The user have to free the memory for the PDA by using the function
              pda_free().
*/
pda *pda_empty(void);

/*
Purpose: Adds one state at a time in the PDA.
Returns: Nothing
Input: *aut: Pointer to PDA.
       stat_name: A string of state's name.
       s_accept : Tells if the state is accepting or not.
                  True for yes, false for no.
Description: The user can in this function add diffrent states to the PDA.
             One state at a time and telling the PDA if it is an accepting.
*/
void pda_setState(pda *aut, char state_name[], bool s_accept);

/*
Purpose: Tells the PDA the initial state.
Returns: Returns true it could setup the initial state.
         Returns false it somethig went wrong, probably the wrong name.
Input: *aut: Pointer to PDA.
       state_name: Name of the state.
Description: The functions allows the user setup the initial state for the PDA.
             It uses function pda_stateLookup to find a matching state name
             in set of states in the PDA.
*/
bool pda_setInitialState(pda *aut, char state_name[]);

/*
Purpose: Sets transitionterms and functions for a state.
Returns: Nothing
Input: *aut: Pointer to PDA.
       stat_name: Name of the state.
       *input_control: Function pointer to input test function.
       *stack_controll: Function pointer to stack test function.
       *t_function: Function pointer to the transition function.
       dest_state: This is the destination state for the transition.
Description: In this function the user can input transitions from one state
             to another. This by giving the PDA two controll functions, one
             for the input string and one for the stack. If both of these are
             OK, the transition will proceed by using the transition function
             and change the current state in the PDA to the destination state
             for the transition.
*/
void pda_setTransitions(pda *aut, char state_name[],
transitionTest_input *input_control,transitionTest_stack stack_control,
trans_function *t_function,char dest_state[]);

/*
Purpose: Search for a specifck state in the PDA.
Returns: Returns a function pointer to a state if one was found, otherwise
         returns a NULL pointer.
Input: *aut: Pointer to PDA.
       stat_name: A string of state name.
Description: This function searches for a state name that is matching with the
             input string. Returns the pointer to the state if found,
             NULL pointer if not found.
*/
pda_state *pda_stateLookup(pda *aut, char state_name[]);

/*
Purpose: Runs through the PDA with the input string.
Returns: Nothing
Input: *aut: Pointer to PDA.
       input:  The string that the PDA will run through the automata.
Description: This function will run the PDA with the input string.
             It will through the whole string including the '\0' sign.
*/
void pda_run(pda *aut, char input[]);

/*
Purpose: Checks if the PDA accepted the string.
Returns: True if accepted, false otherwise.
Input: *aut: Pointer to PDA.
Description: This funcion should be called after the pda_run() has been used.
             User can call this function to see if the input string was
             accepted by PDA.

             Undefined if the pda_run() has not been used.
*/
bool pda_isStateAccepted(pda *aut);

/*
Purpose: See what the top value on stack.
Returns: Returns a pointer of the stack value, if stack is empty returning NULL
Input: *aut: Pointer to PDA.
Description: This function should be called if the user wished to see the
             top value on the stack.

             Will return NULL if the stack is empty, should be used after
             pda_run().
*/
void *pda_getTopStackValue(pda *aut);

/*
Purpose: Frees all the memory used by the PDA.
Returns: Nothing
Input: *aut: Pointer to PDA.
Description: This function will free all memory used by the PDA.
*/
void pda_free(pda *aut);

#endif
