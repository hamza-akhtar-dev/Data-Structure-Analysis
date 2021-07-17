#include "fileio.h"

typedef int ElementType;

#ifndef _array_h
#define _array_h

typedef unsigned int Index;
typedef Index Position;

struct ArrayRecord;
typedef struct ArrayRecord *Array;

Array CreateArray( int ArraySize, int* MemoryUsage );
void Insert( Array A, Record R, Index I );
void PrintData( Array A );
void SortedTraversal( Array A );
Position Find( Array A, ElementType Element );  
void Delete( Array A, ElementType Element );  
void SortedTraversal( Array A );
void DestroyArray( Array A , int* MemoryUsage );

#endif  
