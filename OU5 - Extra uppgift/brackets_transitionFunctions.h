/*
  Filename    : brakets.h

  Usage       : This functions in this file are used as transitions in the
                in the Push Down automata(pda.h).

                For an automata that checks braket-matching

  Author      : Michael Andersson
  CS-id       : dv15man
*/
#ifndef __bracket_func
#define __bracket_func

#include "pda.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*************************Controll for Stack*********************************/

/*
Purpose: Controlls that the stack is empty
Returns: Returns true if stack is empty, otherwise false.
Input:   A pointer to the PDA-struct
Description : Final test.
*/
bool isFinalStackEmpty(pda *aut);


/*
Purpose: Is an Epsilon transition.
Returns: Will return true no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonStack(pda *aut);

/*
Purpose: Controlls if a left bracket is on the stack.
Returns: Will return true if a left bracket is on the stack.
Input:   A pointer to the PDA-struct
Description: Controll function for left-brackets.
*/
bool isLeftBracketOnStack(pda *aut);

/*************************Control for Input string***********************/

/*
Purpose: Is an Epsilon transition.
Returns: Will return ture no matter what.
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition.
*/
bool isEpsilonInput(char c);

/*
Purpose: Controlls if the input character is a left bracket.
Returns: Will return true if input char if a left bracket.
Input:   A pointer to the PDA-struct
Description: Controll function for left-brackets.
*/
bool isLeftBracketInput(char c);

/*
Purpose: Controlls if the input character is a right bracket.
Returns: Will return true if input char if a right bracket.
Input:   A pointer to the PDA-struct
Description: Controll function for right-brackets.
*/
bool isRightBracketInput(char c);

/*
Purpose: Controlls if the input character is NULL character.
Returns: Will return true if the character is NULL character, false otherwise.
Input:   Current character from the input string.
Description: Will controll if the character is NULL character and
             and end-of-string.
*/
bool isEmpty(char c);


/***********************Transition functions*****************************/

/*
Purpose: Adds a left-bracket to the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will add a left-backet to the stack
*/
void addLeftBracketToStack(char c, pda *aut);

/*
Purpose: Rmoves a left-bracket from the stack.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will remove a left-backet from the stack
*/
void removeLeftBracketFromStack(char c, pda *aut);


/*
Purpose: Add the indexCounter with one.
Returns: Nothing
Input:   Char c - Current character from the input string
         pda *aut - A pointer to the PDA-struct
Description: Will add the indexCounter with one, this function is used
             when there is an epsilon transition.
*/
void indexCountUp(char c, pda *aut);

/*
Purpose: Is an Epsilon transition.
Returns: Nothing
Input:   A pointer to the PDA-struct
Description: Is an Epsilon transition, does nothing...
*/
void epsilonTransition(char c, pda *aut);


#endif
