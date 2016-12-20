/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). Till�telse ges f�r anv�ndning p� kurserna
 * i Datastrukturer och algoritmer vid Ume� Universitet. All annan anv�ndning kr�ver f�rfattarens
 * tillst�nd.
 */

#include "dlist.h"

/*
Implementation av datatypen riktad lista.

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa dlist_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer listan
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n listan. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n listan.
*/

/*
Syfte: Skapa en ny tom lista.
Returv�rde: Pekare till den nyskapade listan.
Kommentarer: D� man anv�nt listan f�rdigt s� m�ste minnet f�r listan
             avallokeras via funktionen dlist_free
*/
dlist *dlist_empty(void) {
    dlist *theList=malloc(sizeof(struct list));
    theList->head=malloc(sizeof(element)); //huvudet f�r listan
    theList->head->next=NULL;
    theList->freeFunc=NULL;
    return theList;
}

/*
Syfte: Installera en minneshanterare f�r listan s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i listan mer.
Parametrar: l - listan
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i listan).
Kommentarer: Bara minne f�r v�rden som finns i listan vid tidpunkten d� en
             minneshanterare satts eller senare kommer tas bort.
             Listan funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i listan.
*/
void dlist_setMemHandler(dlist *l, memFreeFunc *f) {
   l->freeFunc=f;
}

/*
Syfte: Returnerar listans f�rsta position
Parametrar: l - listan
Returv�rde: den f�rsta positionen i listan
Kommentarer:
*/
dlist_position dlist_first(dlist *l) {
   return l->head;
}

/*
Syfte: H�mta efterf�ljaren till en given position
Parametrar: l - listan
            p - positionen man vill veta efterf�ljaren till
Returv�rde: positionen f�r efterf�ljaren
Kommentarer: Odefinierad f�r end positionen
*/
dlist_position dlist_next(dlist *l, dlist_position p) {
   return p->next;
}

/*
Syfte: Kontrollera om listan �r tom.
Parametrar: l - listan
Returv�rde: true om listan �r tom, false annars
Kommentarer:
*/
bool dlist_isEmpty(dlist *l) {
    return (l->head->next==NULL);
}

/*
Syfte: S�tta in ett v�rde i listan p� en given position
Parametrar: l - listan
            p - positionen
            d v�rdet som ska s�ttas in
Returv�rde: Positionen f�r det nyinsatta v�rdet.
Kommentarer: p b�r ej anv�ndas efter anropet
*/
dlist_position dlist_insert(dlist *l,dlist_position p,data d) {
   dlist_position newPosition=malloc(sizeof(element));
   newPosition->data=d;

   newPosition->next=p->next;

   p->next=newPosition;
   return p;
}

/*
Syfte: H�mta ett v�rde p� en given position fr�n listan
Parametrar: l - listan
            p - positionen i listan
Returv�rde: v�rdet som fanns p� positionen p
Kommentarer:
*/
data dlist_inspect(dlist *l, dlist_position p) {
    return p->next->data;
}

/*
Syfte: Ta bort ett v�rde p� en given position i listan
Parametrar: l - listan
            p - positionen f�r v�rdet som ska tas bort
Returv�rde: positionen d�r v�rdet togs bort
Kommentarer: Returv�rdet b�r anv�ndas ist�llet f�r p efter ett anrop
             till funktionen
*/
dlist_position dlist_remove(dlist *l,dlist_position p) {
   dlist_position temp=p->next;
   p->next=p->next->next;
   if(l->freeFunc!=NULL)
      l->freeFunc(temp->data);
   free(temp);
   return p;
}

/*
Syfte: Kolla om en given position �r positionen efter det sista v�rdet i listan
Parametrar: l - listan
            p - positionen man vill kontrollera om den �r positionen efter det sista v�rdet.
Returv�rde: true om p �r positionen efter sista v�rdet, false annars.
Kommentarer:
*/
bool dlist_isEnd(dlist *l,dlist_position p) {
   return (p->next==NULL);
}

/*
Syfte: Avallokerar allt inne som anv�nds av listan. Och om en funktion
       f�r att avallokera minnet f�r datav�rdena i listan installerats
       mha dlist_setMemHandler kommer �ven minnet f�r datat i listan avallokeras.
Parametrar: l - listan
Kommentarer: Efter ett anrop till denna funktion s� �r alla funktioner p� listan
             odefinierade.
*/
void dlist_free(dlist *l) {
   dlist_position p=dlist_first(l);
   while(!dlist_isEmpty(l)) {
       p=dlist_remove(l,p);
   }
   free (l->head);
   free (l);
}
