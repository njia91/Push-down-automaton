/*
File Name   : rpn.c

Purpose     : This is the main file for an application that will interpret a
              string as a reverse polish notation.

Synopsis		:
              automat [INPUT]

              [INPUT] - Expecting a string of characters within quotation markss.




Usage       : Usage in OU5 - Reverse Polish notation

Files used	:	rpn.c
              pda.c
              pda.h
              rpn_transitionFunctions.c
              rpn_transitionFunctions.h
              dlist.c
              dlist.h
              stack_1cell.c
              stack_1cell.h
              
Author:       Michael Andersson
CS-id :       d15man

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rpn_transitionFunctions.h"
#include "pda.h"

void check_parameters( int nr_parameters);
void errorOutput(void);
void setupStates(pda *aut);
void setupTransitions(pda *aut);

int main(int argc, char **argv){
  //Checking the input parameters
  check_parameters(argc);
  //Creating the PDA
  pda *aut = pda_empty();
  //Inserting states in the automaton
  setupStates(aut);
  //Selecting the initial state
  pda_setInitialState(aut, "q_start");
  //Creating transitions
  setupTransitions(aut);
  //Runs the PDA
  pda_run(aut,argv[1]);
  //Checking if the automaton accepting the input string
  if(pda_isStateAccepted(aut)){
    //Print the value from the reverse polish notation
    printf("%d\n",*(int *)pda_getTopStackValue(aut));
  }
  else{
    printf("Invalid expression\n");
  }
  //Deallocating memory
  pda_free(aut);
  return 0;
}

//Simple function which controlls that the number of parameters
void check_parameters(int nrOfParameters){
  if (nrOfParameters != 2){
    errorOutput();
  }
}

//If wrong number parameters was ented this function will print an error output
void errorOutput(void){
  fprintf(stderr,"Usage:\nautomat [INPUT]\n");
  fprintf(stderr,"INPUT - Expects  a Reverse Polish Notation "
                  "within quotation marks \n");

  exit(0);
}

//Function that inserts states to the PDA.
void setupStates(pda *aut){
  pda_setState(aut,"q_start", false);
  pda_setState(aut,"q_accept", true);
  pda_setState(aut,"q_fail", false);
  pda_setState(aut,"q_digit", false);
  pda_setState(aut,"q_blank", false);
  pda_setState(aut,"q_operator", false);

}

//Function that inserts transitions between states
void setupTransitions(pda *aut){
  // Sets up transitions from  q_start
  pda_setTransitions(aut,"q_start", isDigit, isEpsilonStack,
                    addDigitToStack,"q_digit");
  pda_setTransitions(aut,"q_start", isInvalidInput,
                    isEpsilonStack, indexCountUp, "q_fail");
  pda_setTransitions(aut,"q_start", isBlank,
                    isEpsilonStack, indexCountUp, "q_blank");
  pda_setTransitions(aut,"q_start", isOperator,
                    isTwoValuesOnStack, useOperator, "q_operator");
  pda_setTransitions(aut,"q_start", isOperator,
                    isTooFewValuesOnStack, indexCountUp,"q_fail");
  pda_setTransitions(aut,"q_start", isEmpty,
                    isTwoValuesOnStack, indexCountUp, "q_fail");
  pda_setTransitions(aut,"q_start", isEmpty,
                    isFinalStackEmpty, indexCountUp,"q_fail");
  pda_setTransitions(aut,"q_start", isEmpty,
                    isTooFewValuesOnStack, indexCountUp, "q_accept");
  //Set up states from q_digit
  pda_setTransitions(aut,"q_digit", isDigit,
                    isEpsilonStack, mergeDigitToStack, "q_digit");
  pda_setTransitions(aut,"q_digit", isNotDigit,
                    isEpsilonStack, epsilonTransition, "q_start");

  //Set up states from q_blank
  pda_setTransitions(aut,"q_blank", isBlank,
                    isEpsilonStack, indexCountUp, "q_blank");
  pda_setTransitions(aut,"q_blank", isNotBlank,
                    isEpsilonStack, epsilonTransition, "q_start");

  //Set up states from q_operator
  pda_setTransitions(aut,"q_operator", isOperator,
                    isTwoValuesOnStack, useOperator, "q_operator");
  pda_setTransitions(aut,"q_operator", isNotOperator,
                    isEpsilonStack, epsilonTransition, "q_digit");
  pda_setTransitions(aut,"q_operator", isOperator,
                    isTooFewValuesOnStack, indexCountUp,"q_fail");
  //Set up states from q_fail
  pda_setTransitions(aut,"q_fail", isEpsilonInput,
                    isEpsilonStack, indexCountUp, "q_fail");
}
