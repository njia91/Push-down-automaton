
/*
  Filename    : rpn_transitionFunctions.c

  Usage       : This functions in this file are used as transitions in the
                in the Push Down automata(pda.h).

  Author      : Michael Andersson
  CS-id       : dv15man
*/

#include "rpn_transitionFunctions.h"

/*************************Controll for Stack*********************************/

/*
Purpose: Controlls that there is a value on the stack
Returns: Returns true if there is only one value on stack, otherwise false.
Input:   A pointer to the PDA-struct
Description : This function is used to verify that there is a value on the
              stack and not a NULL pointer. The state of the top value on the
              stack is set by controlStackValue() previously
*/
bool isFinalStackEmpty(pda *aut){
  if (stack_isEmpty(aut->pda_stack)){
    return true;
  }
  return false;
}


/*
Purpose: Controlls if there is two values on stack.
Returns: Returns true if there are two values on the stack, otherwise false.
Input:   A pointer to the PDA-struct
Description: This function is used for to controll that there is two values
             on the stack. It is used to comfirm that it is possible to
             perform an operaton.
*/
bool isTwoValuesOnStack(pda *aut){
  int *value;

  //Controlls that Stack is not empty, to avoid segfault.
  //Will return false if stack is empty.
  if (!stack_isEmpty(aut->pda_stack)){
    value = stack_top(aut->pda_stack);
    stack_pop(aut->pda_stack);
    //Pop one value, if it is not empty push back value and return false.
    if (!stack_isEmpty(aut->pda_stack)){
      stack_push(aut->pda_stack, value);

      return true;
    }
    //Else push back value and return false.
    else{
      stack_push(aut->pda_stack, value);
      return false;
    }
  }
  return false;
}

/*
Purpose: Controlls if there are less then two values on stack.
Returns: Returns true if there are less then 2 value on stack, otherwise false.
Input:   A pointer to the PDA-struct
Description: This function is used for to controll that there is less than
             two values on the stack. It is used to comfirm that it is
             impossible to perform an operation, and that it is an invalid
             input.
*/
bool isTooFewValuesOnStack(pda *aut){
  int *value;
  //Controlls that Stack is not empty, to avoid segfault.
  //Will return false if stack is empty.
  if (!stack_isEmpty(aut->pda_stack)){
    value = stack_top(aut->pda_stack);
    stack_pop(aut->pda_stack);
    //Pop one value, if it is empty push back value and return false.
    if (stack_isEmpty(aut->pda_stack)){
      stack_push(aut->pda_stack, value);
      return true;
    }
    //Else push back value and return false
    else{
      stack_push(aut->pda_stack, value);
    }
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
bool isDigit(char c){
  if (c >='0' && c <= '9' ){
    return true;
  }
  return false;
}

/*
Purpose: Controlls if the input character is NOT adigit.
Returns: Will return true if the character is NOT a digit, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT a digit,
             this is used to escape the q_digit state and return to the
             start state.
*/
bool isNotDigit(char c){
  return !(isDigit(c) || (isEmpty(c) && isInvalidInput(c)));
}

/*
Purpose: Controlls if the input character is an operator.
Returns: Will return true if the character is an operator, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is an operator.
*/
bool isOperator(char c){
  if (c == '*' || c == '+' || c == '-' || c == '/' ){
    return true;
  }
  return false;

}

/*
Purpose: Controlls if the input character is NOT an operator.
Returns: Will return true if the character is NOT an operator, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT an operator,
             this is used to escape the q_operator state and return to the
             start state.
*/
bool isNotOperator(char c){
  return !(isOperator(c) || (isEmpty(c) && isInvalidInput(c)));
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

/*
Purpose: Controlls if the input character is a space .
Returns: Will return true if the character is a space, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is a space.

*/
bool isBlank(char c){
  if (c == ' '){
    return true;
  }
  return false;
}

/*
Purpose: Controlls if the input character is a NOT space .
Returns: Will return true if the character is a space, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT a space,
             this is used to escape the q_blank state and return to the
             start state.

*/
bool isNotBlank(char c){
  return !(isBlank(c) || (isEmpty(c) && isInvalidInput(c)));
}
/*
Purpose: Controlls if the input character is invalid .
Returns: Will return true if the character is invalid, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is an invalid character.
*/
bool isInvalidInput(char c){
  // It the input is either a digit, operator, blank or NULL, return true.
  if (!(isDigit(c) || isOperator(c) || isBlank(c) || isEmpty(c))){
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
void addDigitToStack(char c, pda *aut){
  int *digit = malloc(sizeof(int));
  //Calculate the value of input character and add it to stack.
  *digit = c - '0';
  stack_push(aut->pda_stack, digit);
  //Count up input string index by 1.
  aut->indexCounter++;
}

/*
Purpose: Merge the input witht the value on the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will convert the digit representing by character C into an int and
             merge it witht the value on the stack. This is done by
             multiply the stack value by 10 and add the interger representing
             by C. And add the string indexCounter by one.
*/
void mergeDigitToStack(char c, pda *aut){
  int *value;
  value = stack_top(aut->pda_stack);

  *value = *value * 10;
  *value = *value + (c - '0');
  //Count up input string index by 1.
  aut->indexCounter++;
}

/*
Purpose: Use the operator that the input character is representing.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will perfom the operation that the input character C represents
             with two of the top values on the stack. Will store the result
             on the stack. Will also add the string indexCounter with one.
*/
void useOperator(char c, pda *aut){
  int *value1;
  int *value2;

  value1 = stack_top(aut->pda_stack);
  stack_pop(aut->pda_stack);
  value2 = stack_top(aut->pda_stack);


  switch(c){
    case '+':
      *value2 = *value2 + *value1;
      break;
    case '-':
      *value2 = *value2 - *value1;
      break;
    case '/':
      if (*value1){
        *value2 = *value2 / *value1;
      }
      else {
        fprintf(stderr,"Error: Divison by zero!\n");
        free(value1);
        pda_free(aut);
        exit(0);
      }
      break;
    case '*':
      *value2 = *value2 * *value1;
      break;
    default:
      aut->current_state = NULL;
  }
  free(value1);
  //Count up input string index by 1.
  aut->indexCounter++;
}

/*
Purpose: Add the indexCounter with one.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will count the indexCounter with one, this function is used
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
