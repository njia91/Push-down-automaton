/*
  Filename    : rpn_transitionFunctions.h

  Usage       : This functions in this file are used as transitions in the
                in the Push Down automata(pda.h).

  Author      : Michael Andersson
  CS-id       : dv15man
*/
#ifndef __rpnFunc
#define __rpnFunc

#include "pda.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*************************Controll for Stack*********************************/

/*
Purpose: Controlls that there is a value on the stack
Returns: Returns true if there is only one value on stack, otherwise false.
Input:   A pointer to the PDA-struct
Description : This function is used to verify that there is a value on the
              stack and not a NULL pointer. The state of the top value on the
              stack is set by controlStackValue() previously
*/
bool isFinalStackEmpty(pda *aut);

/*
Purpose: Controlls if there is two values on stack.
Returns: Returns true if there are two values on the stack, otherwise false.
Input:   A pointer to the PDA-struct
Description: This function is used for to controll that there is two values
             on the stack. It is used to comfirm that it is possible to
             perform an operaton.
*/
bool isTwoValuesOnStack(pda *aut);

/*
Purpose: Controlls if there are less then two values on stack.
Returns: Returns true if there are less then 2 value on stack, otherwise false.
Input:   A pointer to the PDA-struct
Description: This function is used for to controll that there is less than
             two values on the stack. It is used to comfirm that it is
             impossible to perform an operation, and that it is an invalid
             input.
*/
bool isTooFewValuesOnStack(pda *aut);

/*
Purpose: Is an Epsilon transition.
Returns: Will return ture no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonStack(pda *aut);

/*************************Control for Input string***********************/

/*
Purpose: Is an Epsilon transition.
Returns: Will return ture no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonInput(char c);

/*
Purpose: Controlls if the input character is a digit.
Returns: Will return true if the character is NOT a digit, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is a digit.
*/
bool isDigit(char c);

/*
Purpose: Controlls if the input character is NOT adigit.
Returns: Will return true if the character is a digit, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT a digit,
             this is used to escape the q_digit state and return to the
             start state.
*/
bool isNotDigit(char c);

/*
Purpose: Controlls if the input character is an operator.
Returns: Will return true if the character is an operator, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is an operator.
*/
bool isOperator(char c);

/*
Purpose: Controlls if the input character is NOT an operator.
Returns: Will return true if the character is NOT an operator, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT an operator,
             this is used to escape the q_operator state and return to the
             start state.
*/
bool isNotOperator(char c);
/*
Purpose: Controlls if the input character is NULL character.
Returns: Will return true if the character is NULL character, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NULL character and
             and end-of-string.
*/
bool isEmpty(char c);

/*
Purpose: Controlls if the input character is a space .
Returns: Will return true if the character is a space, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is a space.

*/
bool isBlank(char c);

/*
Purpose: Controlls if the input character is a NOT space .
Returns: Will return true if the character is a space, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NOT a space,
             this is used to escape the q_blank state and return to the
             start state.

*/
bool isNotBlank(char c);

/*
Purpose: Controlls if the input character is invalid .
Returns: Will return true if the character is invalid, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is an invalid character.
*/
bool isInvalidInput(char c);


/***********************Transition functions*****************************/

/*
Purpose: Adds a digit to the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will convert the digit from character C into an int and place it
             on the stack.And add the string indexCounter with one.
*/
void addDigitToStack(char c, pda *aut);


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
void mergeDigitToStack(char c, pda *aut);

/*
Purpose: Add the indexCounter with one.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will count the indexCounter with one, this function is used
             when there is an epsilon transition.
*/
void indexCountUp(char c, pda *aut);

/*
Purpose: Use the operator that the input character is representing.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will perfom the operation that the input character C represents
             with two of the top values on the stack. Will store the result
             on the stack. Will also add the string indexCounter with one.
*/
void useOperator(char c, pda *aut);

/*
Purpose: Controlls that there is one value on the stack
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: This function will be used then the input is empty and will
             therefore controll that there is only one value on the stack.
             If there is one value on the stack the function pushes that value
             back on the stack. Otherwise will push a NULL-pointer to the
             stack to indicate that the expression is invalid.
*/
void controlStackValue(char c, pda *aut);

void epsilonTransition(char c, pda *aut);


#endif
