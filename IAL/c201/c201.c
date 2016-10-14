
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
** 
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	
    L->First = NULL;
    L->Act = NULL;
 
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/

// Uložíme si ukazovatel na prvý prvok

    tElemPtr tmp = L->First;

// Pomocný ukazovatel na ďalší prvok
    tElemPtr tmpNext;

// Vynulujeme hodnoty ako pri inicializácií

    L->First = NULL;
    L->Act = NULL;

// Pamäť uvolňujeme postupne

    while( tmp != NULL )
	{
	    tmpNext = tmp->ptr;
	    free(tmp);
	    tmp = tmpNext;
	}  
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    
// Alokovanie pamäte
    tElemPtr item = malloc( sizeof( tElemPtr ) );

// Kontrola alokácie
    if (item == NULL )
	{
	    Error();
	    return;
	}

    item->ptr = L->First;
    item->data = val;
    L->First = item; //prvý prvok
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
    L->Act = L->First;
 
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	
    if ( L->First == NULL )
	{
	    Error();
	    return;
	}	

    *val = L->First->data; 

}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	
    if ( L->First == NULL ) //zoznam je prázdny
	return;

    if ( L->First == L->Act ) //aktuálny prvok bol aj prvým prvkom 
	L->Act = NULL;
  
    tElemPtr tmp = L->First->ptr;  //uložíme si ukazovatel na ďalší prvok
    free( L->First );
    L->First = tmp; //nastavíme ďalší prvok ako prvý 
	
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
	
    if ( L->Act == NULL ) // Zoznam L neaktivny
	return;

    if ( L->Act->ptr == NULL ) // Posledný prvok aktívny
	return;    	

    tElemPtr tmp = L->Act->ptr->ptr; // Uložime ponter na prvok za aktívnym prvkom
    free( L->Act->ptr );
    L->Act->ptr = tmp;

}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
    if ( L->Act == NULL ) // Zoznam L neaktivny
	return;

    tElemPtr newItem = malloc( sizeof(tElemPtr ) ); // Alokujeme pamäť pre nový prvok
    if ( newItem == NULL ) // Kontrola alokácie
	{
	    Error();
	    return;	
 	}    

    newItem->data = val; // Uložíme dáta do nového prvku
    newItem->ptr = L->Act->ptr; // Pridelenie ukazovatela novému prvku
    L->Act->ptr = newItem; // Pridelenie ukazovatela aktívnemu prvku
        	 

}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	
    if ( L->Act == NULL ) // Zoznam L neaktivny
	{
	    Error();
	    return;	
 	}

    *val = L->Act->data;
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
	
    if ( L->Act == NULL ) // Zoznam L neaktivny
	return;

    L->Act->data = val;	
 
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	
    if ( L->Act == NULL ) // Zoznam L neaktivny
	return;

    L->Act = L->Act->ptr;	

}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	
    return L->Act == NULL ? 0 : 1;	

}

/* Konec c201.c */
