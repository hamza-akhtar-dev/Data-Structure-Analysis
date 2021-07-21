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
MakeEmpty( List L, int* MemoryUsage )
{
    if( L != NULL )
        DeleteList( L, MemoryUsage );
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
Delete( ElementType X, List L, int* MemoryUsage )
{
    Position P, TmpCell;

    P = FindPrevious( X, L );

    if( !IsLast( P, L ) )  /* Assumption of header use */
    {                      /* X is found; delete it */
        TmpCell = P->Next;
        P->Next = TmpCell->Next;  /* Bypass deleted cell */
        free( TmpCell );
        *MemoryUsage -= sizeof( struct Node );
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
Insert( ElementType X, Record R, Position P, int* MemoryUsage )
{
    Position TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    *MemoryUsage += sizeof( struct Node );
    
    if( TmpCell == NULL )
        FatalError( "Out of space!!!" );

    TmpCell->Element = X;
    TmpCell->Data = R;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}


void
DeleteList( List L, int* MemoryUsage )
{
    Position P, Tmp;

    P = L->Next;  /* Header assumed */
    L->Next = NULL;
    while( P != NULL )
    {
        Tmp = P->Next;
        free(P->Data);
        free( P );
		*MemoryUsage -= sizeof( struct Node );
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

Position 
GetTail( Position P )
{
    while ( P->Next != NULL )
        P = P->Next;
    return P;
}

// Partitions the list taking the last element as the pivot
Position 
Partition( Position head, Position end, Position* newHead, Position* newEnd )
{
    Position pivot = end;
    Position prev = NULL, cur = head, tail = pivot;
    Position tmp;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) 
	{
        if (cur->Element < pivot->Element) 
		{
            // First node that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;
            cur = cur->Next;
        }
        
        else // If cur node is greater than pivot
        {
            // Move cur node to Next of tail, and change tail
            if (prev != NULL )
            {
            	prev->Next = cur->Next;
			}
			
            tmp = cur->Next;
            cur->Next = NULL;
            tail->Next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot Element is the smallest element in the
    // current list, pivot becomes the head
    if ( (*newHead) == NULL )
    {
    	(*newHead) = pivot;
	}
       
    // Update newEnd to the current last node
    (*newEnd) = tail;
 
    // Return the pivot node
    return pivot;
}
 
// here the sorting happens exclusive of the end node
Position 
Qsort( Position head, Position end )
{
	Position tmp;
	
    // base condition
    if (!head || head == end)
    {
    	return head;
	}
 
    Position newHead = NULL, newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    Position pivot = Partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur for the left part.
    if (newHead != pivot) 
	{
        // Set the node before the pivot node as NULL
        tmp = newHead;
        
        while (tmp->Next != pivot)
        {
        	tmp = tmp->Next;
		}
        tmp->Next = NULL;
        
        // Recur for the list before pivot
        newHead = Qsort(newHead, tmp);
 
        // Change Next of last node of the left half to pivot
        tmp = GetTail(newHead);
        tmp->Next = pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->Next = Qsort(pivot->Next, newEnd);
 
    return newHead;
}
 
 
void QuickSort( Position *L )
{
    (*L) = Qsort( *L, GetTail(*L) );
}

void SortedTraversal( List L )
{
	Position P;
	QuickSort( &L );
	P = L->Next;
	while ( P != NULL )
	{
		//printf("Id: %d\n", RetrieveID( P->Data ) );  //Comment this print statment for larger data files
		P = P->Next;
	}
}
