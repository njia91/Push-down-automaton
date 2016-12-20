/*
File Name   : brackets.c

Purpose     : This is the main file for an application that controll if
              a string contains matching parentheses.

Synopsis		:
              automat [INPUT]

              [INPUT] -  Expecting a string of parentheses within
                         quotation marks.




Usage       : Usage in OU5  Extra assigment - Matching  parentheses.

Files used	:	brackets.c
              pda.c
              pda.h
              brackets_transitionFunctions.c
              brackets_transitionFunctions.h
              dlist.c
              dlist.h
              stack_1cell.c
              stack_1cell.h

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "brackets_transitionFunctions.h"
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
  pda_setInitialState(aut, "q0");
  //Creating transitions
  setupTransitions(aut);
  //Runs the PDA
  pda_run(aut,argv[1]);
  //Checking if the automaton accepting the input string
  if(pda_isStateAccepted(aut)){
    printf("Accepted\n");
  }
  else{
    printf("Invalid expression\n");
  }
  //Deallocating memory
  pda_free(aut);
  return 0;
}

//Simple function which controlls that the number of parameters.
void check_parameters(int nrOfParameters){
  if (nrOfParameters != 2){
    errorOutput();
  }
}
//If wrong number parameters was ented this function will print an error output
void errorOutput(void){
  fprintf(stderr,"Usage:\nautomat [INPUT]\n");
  fprintf(stderr,"INPUT - Expects  brackets )( "
                  "within quotation marks \n");

  exit(0);
}
//Function that inserts states to the PDA.
void setupStates(pda *aut){
  pda_setState(aut,"q0",false);
  pda_setState(aut,"q1",true);
  pda_setState(aut,"q2",false);
}
//Function that inserts transitions between states
void setupTransitions(pda *aut){
  pda_setTransitions(aut,"q0",isEpsilonInput,
                    isEpsilonStack, epsilonTransition,"q1");

  pda_setTransitions(aut,"q1",isLeftBracketInput,
                    isEpsilonStack, addLeftBracketToStack,"q2");
  pda_setTransitions(aut, "q1", isEmpty,
                    isEpsilonStack, indexCountUp, "q1");

  pda_setTransitions(aut,"q2",isLeftBracketInput,
                    isLeftBracketOnStack, addLeftBracketToStack,"q2");
  pda_setTransitions(aut,"q2",isRightBracketInput,
                    isLeftBracketOnStack, removeLeftBracketFromStack,"q2");
  pda_setTransitions(aut,"q2",isEpsilonInput,
                    isFinalStackEmpty, epsilonTransition,"q1");

}
