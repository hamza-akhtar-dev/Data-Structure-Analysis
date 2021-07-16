#include "list.h"
#include "fileio.h"
#include "fatal.h"
#include <stdlib.h>

struct Node
{
	
    ElementType Element;
    Record 		Data;
    Position    Next;
};

List
MakeEmpty( List L )
{
    if( L != NULL )
        DeleteList( L );
    L = malloc( sizeof( struct Node ) );
    if( L == NULL )
        FatalError( "Out of memory!" );
    L->Next = NULL;
    L->Data = NULL;
    return L;
}

int
IsEmpty( List L )
{
    return L->Next == NULL;
}


int IsLast( Position P, List L )
{
    return P->Next == NULL;
}


Position
Find( ElementType X, List L )
{
    Position P;

    P = L->Next;
    while( P != NULL && P->Element != X )
        P = P->Next;

    return P;
}

/* Delete from a list */
/* Cell pointed to by P->Next is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */

void
Delete( ElementType X, List L )
{
    Position P, TmpCell;

    P = FindPrevious( X, L );

    if( !IsLast( P, L ) )  /* Assumption of header use */
    {                      /* X is found; delete it */
        TmpCell = P->Next;
        P->Next = TmpCell->Next;  /* Bypass deleted cell */
        free( TmpCell );
    }
}


/* If X is not found, then Next field of returned value is NULL */
/* Assumes a header */

Position
FindPrevious( ElementType X, List L )
{
    Position P;

    P = L;
    while( P->Next != NULL && P->Next->Element != X )
        P = P->Next;

    return P;
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */

void
Insert( ElementType X, Record R, List L, Position P )
{
    Position TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    if( TmpCell == NULL )
        FatalError( "Out of space!!!" );

    TmpCell->Element = X;
    TmpCell->Data = R;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}


void
DeleteList( List L )
{
    Position P, Tmp;

    P = L->Next;  /* Header assumed */
    L->Next = NULL;
    while( P != NULL )
    {
        Tmp = P->Next;
        free(P->Data);
        free( P );
        P = Tmp;
    }
}


Position
Header( List L )
{
    return L;
}

Position
First( List L )
{
    return L->Next;
}

Position
Advance( Position P )
{
    return P->Next;
}

ElementType
Retrieve( Position P )
{
    return P->Element;
}

void
PrintList( List L )
{
	Position P = L->Next;
	printf("\nThe List:\n");
	while ( P != NULL )
	{
		Record R = P->Data;
		printf("ID = %d \t Name = %s \t City = %s \t Sevice = %s\n", 
		Retrieve(P), RetrieveName(R), RetrieveCity(R),RetrieveService(R) );
		P = P->Next;
	}
	printf("\n");
}
