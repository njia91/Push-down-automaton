/*

  Filename  : pha.c

  Usage     : This datatype can be used to create a Push Down Automata(PDA).
              As long as the user gives the PDA the necessary controll functions
              for the input string and the stack and as well the transition
              function for a specifik edge.


  Author    : Michael Andersson
  CS-id     : dv15man

  Files necessary	: pda.c
                    pda.h
                    dlist.c
                    dlist.h
                    stack_1cell.c
                    stack_1cell.h

*/
#include "pda.h"

/*
Purpose: Creates a PDA
Return:  Returns a pointer to the PDA.
Description: The user have to free the memory for the PDA by using the function
              pda_free().
*/
pda *pda_empty(void){
  pda *aut = calloc(1,sizeof(pda));

  //Create a stack
  aut->pda_stack = stack_empty();

  //Creates a dlist for the states, and sets dlists memory manager.
  aut->s_list = dlist_empty();
  dlist_setMemHandler(aut->s_list,free);

  aut->initial_state = NULL;
  aut->current_state = NULL;
  aut->indexCounter = 0;

  return aut;
}

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
void pda_setState(pda *aut, char state_name[], bool s_accept){
  //Allocate memory for a state struct
  pda_state *state = calloc(1,sizeof(pda_state));
  //Allocate memory for the state name.
  char *name = calloc(strlen(state_name)+1,sizeof(char));
  strcpy(name,state_name);
  //Sets the state name
  state->s_name = name;

  //Checks if the state should be accepting state
  if(s_accept){
    state->s_accept = 1;
  }
  //Create a list for the states transitions
  state->trans_list = dlist_empty();
  dlist_setMemHandler(state->trans_list, free);
  //Insert the state in the PDA
  dlist_insert(aut->s_list, dlist_first(aut->s_list), state);
}

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
bool pda_setInitialState(pda *aut, char state_name[]){
  pda_state *s;
  //Search for the state in the PDA.
  s = pda_stateLookup(aut, state_name);
  //If  no match returns 0, else return 1
  if (s == NULL){
    return 0;
  }
  else{
    aut->initial_state = s;
    return 1;
  }

}

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
transitionTest_input *input_control, transitionTest_stack stack_control,
trans_function *t_function, char dest_state[]){
  //Allocate memory for a transition
  transition *t = calloc(1,sizeof(transition));
  pda_state *s_src;
  pda_state *s_dest;

  //Find the source state
  s_src = pda_stateLookup(aut, state_name);

  //Find the destination state
  s_dest = pda_stateLookup(aut, dest_state);

  //Set the function pointers for the the controll functions
  //and transition function.
  t->t_input = input_control;
  t->t_stack = stack_control;
  t->t_func = t_function;
  t->dest = s_dest;

  //Insert the transition in the state's list of transitions.
  dlist_insert(s_src->trans_list, dlist_first(s_src->trans_list), t);
}

/*
Purpose: Search for a specific state in the PDA.
Returns: Returns a function pointer to a state if it was found, otherwise
         returns a NULL pointer.
Input: *aut: Pointer to PDA.
       stat_name: A string of state name.
Description: This function searches for a state name that is matching with the
             input string. Returns the pointer to the state if found,
             NULL pointer if not found.
*/
pda_state *pda_stateLookup(pda *aut, char state_name[]){
  dlist_position p = dlist_first(aut->s_list);
  pda_state *s;

  //Will search through the PDA for the correct state.
  do{
    s = dlist_inspect(aut->s_list, p);
    if (!strcmp(state_name,s->s_name)){

      return s;
    }
    p = dlist_next(aut->s_list, p);
  }while (!dlist_isEnd(aut->s_list, p));

  return NULL;

}

/*
Purpose: Runs through the PDA with the input string.
Returns: Nothing
Input: *aut: Pointer to PDA.
       input: The string that the PDA will run through the automata.
Description: This function will run the PDA with the input string.
             It will through the whole string including the '\0' sign.
*/
void pda_run(pda *aut, char input[]){
  pda_state *s_current;
  transition *t_struct;
  dlist_position p;

  int validTransition = 1;


  //Set the initial state to current state.
  aut->current_state = aut->initial_state;

  //The loop will continue until at end-of-string or of no possible transitions
  //was found from a state.
  while(strlen(input)+1>aut->indexCounter && validTransition){

    validTransition = 0;

    //Stores pointer to current state in s_current
    s_current = aut->current_state;
    p = dlist_first(s_current->trans_list);

    //Controlls that the transition list in the current state is not empty.
    if(!dlist_isEmpty(s_current->trans_list)){
      //Indicates that list is not empty by setting transitionsListNotEmpty to 1.


      //Loops through list of transitions for current state
      //Will exit loop when a valid transition is found.
      do{
        //Stores one transition in t_struct
        t_struct = dlist_inspect(s_current->trans_list, p);

        //if both input and stack controll == true, set validTransition to True
        if (t_struct->t_input(input[aut->indexCounter]) &&
        t_struct->t_stack(aut)){
              validTransition = 1;
        }
        p = dlist_next(s_current->trans_list, p);
      }while(!dlist_isEnd(s_current->trans_list,p) && !validTransition);

      //If a valid transition was found, perform the transition function.
      //Set current state to the destination state for the transition.
      if (validTransition){
        t_struct->t_func(input[aut->indexCounter], aut);
        aut->current_state = t_struct->dest;
        s_current = aut->current_state;
      }
      //Else sett current_state to NULL.
      else{
        aut->current_state = NULL;
      }
    }
  }
}

/*
Purpose: CHecks if the PDA accepted the string.
Returns: True if accepted, false otherwise.
Input: *aut: Pointer to PDA.
Description: This funcion should be called after the pda_run() has been used.
             User can call this function to see if the input string was
             accepted by PDA.

             Undefined if the pda_run() has not been used.
*/
bool pda_isStateAccepted(pda *aut){
  if (aut->current_state){
    return aut->current_state->s_accept;
  }
  return false;
}

/*
Purpose: See what the top value on stack.
Returns: Returns a pointer of the stack value, if stack is empty returning NULL
Input: *aut: Pointer to PDA.
Description: This function should be called if the user wished to see the
             top value on the stack.

             Will return NULL if the stack is empty, should be used after
             pda_run().
*/
void *pda_getTopStackValue(pda *aut){
  if (!stack_isEmpty(aut->pda_stack)){
    return (stack_top(aut->pda_stack));
  }
  else{
    return NULL;
  }
}

/*
Purpose: Frees all the memory used by the PDA.
Returns: Nothing
Input: *aut: Pointer to PDA.
Description: This function will free all memory used by the PDA.
*/
void pda_free(pda *aut){
  dlist_position p = dlist_first(aut->s_list);
  pda_state *s;
  int *v;
  //Free all memory for each state's transitions.
  do {
    s = dlist_inspect(aut->s_list, p);
    dlist_free(s->trans_list);
    free(s->s_name);
    p = dlist_next(aut->s_list, p);
  } while(!dlist_isEnd(aut->s_list, p));

  //Free all elements on the stack
  while(!stack_isEmpty(aut->pda_stack)){
    v = stack_top(aut->pda_stack);
    stack_pop(aut->pda_stack);
    free(v);
  }
  //Free all states
  dlist_free(aut->s_list);
  //Free the stack
  stack_free(aut->pda_stack);
  //Free the PDA
  free(aut);

}
