//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

/*
Datatypen Stack enligt definitionen p� sidan 134 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Denna stack �r implementerad med hj�lp av en 1-cell

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa stack_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer stacken
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n stacken. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n stacken.
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack_1cell.h"

/*
Syfte: Skapa en ny stack
Returv�rde: Den nyskapade stacken (stack*)
Kommentarer: D� man anv�nt stacken f�rdigt s� m�ste minnet f�r stacken
             avallokeras via funktionen stack_free
*/
stack *stack_empty(void) {
   stack *s=malloc(sizeof(stack));
   s->top = NULL;
   s->freeFunc=NULL;
   return s;
}

/*
Syfte: Installera en minneshanterare f�r stacken s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i stacken mer.
Parametrar: s - stacken (stack *)
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i stacken).
Kommentarer: B�r anropas direkt efter att stacken skapats om funktionaliteten
             ska anv�ndas. Stacken funkar �ven om denna funktion inte anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i stacken.
*/
void stack_setMemHandler(stack *s, memFreeFunc *f) {
    s->freeFunc=f;
}

/*
Syfte: Kontrollera om stacken �r tom
Parametrar: s (stack *) stack som ska kontrolleras.
Returv�rde: true om stacken �r tom annars false
Kommentarer:
*/
bool stack_isEmpty(stack *s) {
   return s->top==NULL;
}

/*
Syfte: Tar bort �versta v�rdet p� stacken.
Parametrar: s (stack *) stacken vars �versta v�rde ska tas bort.
Kommentarer: Ej definierad f�r en tom stack.
*/
void stack_pop(stack *s) {
   if (stack_isEmpty(s)) {
      fprintf(stderr,"pop on empty stack");
      exit(1);
   }
   else {
      one_cell *temp=s->top;
      s->top=s->top->next;
      if(s->freeFunc!=NULL)
          s->freeFunc(temp->data);
      free(temp);
   }
}

/*
Syfte: H�mta v�rdet �verst p� stacken
Parametrar: l (stack *) vars �versta v�rde man vill h�mta.
Returv�rde: �versta v�rdet p� stacken (data)
Kommentarer: Ej definierad f�r en tom stack
*/
data stack_top(stack *s) {
   return s->top->data;
}

/*
Syfte: L�gger till ett v�rde �versta p� stacken.
Parametrar: l (stack *) stacken.
*/
void stack_push(stack *s, data value) {
   one_cell *new_cell=malloc(sizeof(one_cell));
   new_cell->data = value;
   new_cell->next=s->top;
   s->top=new_cell;
}

/*
Syfte: Avallokera minne som anv�nds av stacken.
Parametrar: s stacken (stack *)
Kommentarer: Minne f�r ev v�rden i stacken avallokeras bara om en funktion
             f�r detta �r satt via stack_setMemHandler. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i stacken.
*/
void stack_free(stack *s) {
    while(!stack_isEmpty(s))
        stack_pop(s);
    free(s);
}
