#include "fileio.h"
typedef int ElementType;

#ifndef _List_H
#define _List_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L, int* MemoryUsage );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( ElementType X, List L );
void Delete( ElementType X, List L, int* MemoryUsage );
Position FindPrevious( ElementType X, List L );
void Insert( ElementType X, Record R, Position P, int* MemoryUsage );
void DeleteList( List L, int* MemoryUsage );
Position Header( List L );
Position First( List L );
Position Advance( Position P );
ElementType Retrieve( Position P );
void SortedTraversal ( List L );


#endif
