#include "fileio.h"

typedef int ElementType;

#ifndef _HashQuad_H
#define _HashQuad_H

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable( int TableSize );
void DestroyTable( HashTable H );
Position Find( ElementType Key, HashTable H );
void Insert( ElementType Key, Record R, HashTable H );
ElementType Retrieve( Position P, HashTable H );
void PrintHashTable( HashTable H );
void Delete( ElementType Key, HashTable H );
void SortedTraversal( HashTable H );
void SortedTraversal101( HashTable H );
#endif

