#include "fileio.h"

typedef int ElementType;

#ifndef _HashQuad_H
#define _HashQuad_H

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable( int TableSize, int* MemoryUsage );
void DestroyTable( HashTable H, int* MemoryUsage );
Position Find( ElementType Key, HashTable H );
void Insert( ElementType Key, Record R, HashTable H );
ElementType Retrieve( Position P, HashTable H );
void PrintHashTable( HashTable H );
void Delete( ElementType Key, HashTable H );
void SortedTraversal101( HashTable H, int* MemoryUsage );
void SortedTraversal( HashTable H );
#endif

