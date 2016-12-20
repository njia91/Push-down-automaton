/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). Till�telse ges f�r anv�ndning p� kurserna
 * i Datastrukturer och algoritmer vid Ume� Universitet. All annan anv�ndning kr�ver f�rfattarens
 * tillst�nd.
 */

/*
Implementation av datatypen riktad lista.

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa dlist_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer listan
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n listan. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n listan.
*/

#ifndef _DLIST_H
#define _DLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __DATA
#define __DATA
typedef void *data;
#endif

#ifndef __MEMFREEDATAFUNC
#define __MEMFREEDATAFUNC
typedef void memFreeFunc(data);
#endif

typedef struct link {
	data data;
	struct link *next;
} element;

typedef element * dlist_position;

struct list {
	element *head;
    memFreeFunc *freeFunc;
};
typedef struct list dlist;

/*
Syfte: Skapa en ny tom lista.
Returv�rde: Pekare till den nyskapade listan.
Kommentarer: D� man anv�nt listan f�rdigt s� m�ste minnet f�r listan
             avallokeras via funktionen dlist_free
*/
dlist *dlist_empty(void);

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
void dlist_setMemHandler(dlist *l, memFreeFunc *f);

/*
Syfte: Returnerar listans f�rsta position
Parametrar: l - listan
Returv�rde: den f�rsta positionen i listan
Kommentarer:
*/
dlist_position dlist_first(dlist *l);

/*
Syfte: H�mta efterf�ljaren till en given position
Parametrar: l - listan
            p - positionen man vill veta efterf�ljaren till
Returv�rde: positionen f�r efterf�ljaren
Kommentarer: Odefinierad f�r end positionen
*/
dlist_position dlist_next(dlist *l,dlist_position p);

/*
Syfte: Kontrollera om listan �r tom.
Parametrar: l - listan
Returv�rde: true om listan �r tom, false annars
Kommentarer:
*/
bool dlist_isEmpty(dlist *l);

/*
Syfte: S�tta in ett v�rde i listan p� en given position
Parametrar: l - listan
            p - positionen
            d v�rdet som ska s�ttas in
Returv�rde: Positionen f�r det nyinsatta v�rdet.
Kommentarer: p b�r ej anv�ndas efter anropet
*/
dlist_position dlist_insert(dlist *l,dlist_position p,data d);

/*
Syfte: Ta bort ett v�rde p� en given position i listan
Parametrar: l - listan
            p - positionen f�r v�rdet som ska tas bort
Returv�rde: positionen d�r v�rdet togs bort
Kommentarer: Returv�rdet b�r anv�ndas ist�llet f�r p efter ett anrop
             till funktionen
*/
dlist_position dlist_remove(dlist *l, dlist_position p);

/*
Syfte: Avallokerar allt inne som anv�nds av listan. Och om en funktion
       f�r att avallokera minnet f�r datav�rdena i listan installerats
       mha dlist_setMemHandler kommer �ven minnet f�r datat i listan avallokeras.
Parametrar: l - listan
Kommentarer: Efter ett anrop till denna funktion s� �r alla funktioner p� listan
             odefinierade.
*/
void dlist_free(dlist *l);

/*
Syfte: H�mta ett v�rde p� en given position fr�n listan
Parametrar: l - listan
            p - positionen i listan
Returv�rde: v�rdet som fanns p� positionen p
Kommentarer:
*/
data dlist_inspect(dlist *l, dlist_position p);

/*
Syfte: Kolla om en given position �r positionen efter det sista v�rdet i listan
Parametrar: l - listan
            p - positionen man vill kontrollera om den �r positionen efter det sista v�rdet.
Returv�rde: true om p �r positionen efter sista v�rdet, false annars.
Kommentarer:
*/
bool dlist_isEnd(dlist *l, dlist_position p);

#endif
