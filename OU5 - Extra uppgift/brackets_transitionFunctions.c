
/*
  Filename    : rpn_transitionFunctions.c

  Usage       : This functions in this file are used as transitions in the
                in the Push Down automata(pda.h).

  Author      : Michael Andersson
  CS-id       : dv15man
*/

#include "brackets_transitionFunctions.h"

/*************************Controll for Stack*********************************/

/*
Purpose: Controlls that the stack is empty
Returns: Returns true if stack is empty, otherwise false.
Input:   A pointer to the PDA-struct
Description : Final test.
*/
bool isFinalStackEmpty(pda *aut){
  if (stack_isEmpty(aut->pda_stack)){
    return true;
  }

  return false;
}


/*
Purpose: Is an Epsilon transition.
Returns: Will return ture no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonStack(pda *aut){
  return true;
}

/*
Purpose: Controlls if a left bracket is on the stack.
Returns: Will return true if a left bracket is on the stack.
Input:   A pointer to the PDA-struct
Description: Controll function for left-brackets.
*/
bool isLeftBracketOnStack(pda *aut){
  char *c;
  c = stack_top(aut->pda_stack);
  if (*c == '('){
    return true;
  }
  return false;
}

/*************************Control for Input string***********************/

/*
Purpose: Is an Epsilon transition.
Returns: Will return ture no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonInput(char c){
  return true;
}

/*
Purpose: Controlls if the input character is a digit.
Returns: Will return true if the character is a digit, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is a digit.
*/
bool isLeftBracketInput(char c){
  if (c == '(' ){
    return true;
  }
  return false;
}

/*
Purpose: Controlls if the input character is a digit.
Returns: Will return true if the character is a digit, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is a digit.
*/
bool isRightBracketInput(char c){
  if (c == ')' ){
    return true;
  }
  return false;
}
/*
Purpose: Controlls if the input character is NULL character.
Returns: Will return true if the character is NULL character, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NULL character and
             and end-of-string.
*/
bool isEmpty(char c){

  if (c == '\0'){
    return true;
  }
  return false;
}


/***********************Transition functions*****************************/

/*
Purpose: Adds a digit to the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will convert the digit from character C into an int and place it
             on the stack.And add the string indexCounter with one.
*/
void addLeftBracketToStack(char c, pda *aut){
  char *temp = malloc(sizeof(char));
  //Calculate the value of input character and add it to stack.
  *temp = c;
  stack_push(aut->pda_stack, temp);
  //Count up input string index by 1.
  aut->indexCounter++;
}

/*
Purpose: Rmoves a left-bracket from the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will remove a left-backet from the stack
*/
void removeLeftBracketFromStack(char c, pda *aut){

  char *temp;
  temp = stack_top(aut->pda_stack);
  stack_pop(aut->pda_stack);
  free(temp);
  //Count up input string index by 1.
  aut->indexCounter++;
}


/*
Purpose: Add the indexCounter with one.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will add the indexCounter with one, this function is used
             when there is an epsilon transition.
*/
void indexCountUp(char c, pda *aut){
  aut->indexCounter++;
}


/*
Purpose: An epsilon transtiotn function.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Is used when the input string or the stack shouln't be change.
             As in a Epsilon transition.
*/
void epsilonTransition(char c, pda *aut){
  return;
}
