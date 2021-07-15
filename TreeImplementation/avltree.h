#include "fileio.h"

typedef int ElementType;

#ifndef _AvlTree_H
#define _AvlTree_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty( AvlTree T );
Position Find( ElementType X, AvlTree T );
Position FindMin( AvlTree T );
Position FindMax( AvlTree T );
AvlTree Insert( ElementType X, Record R, AvlTree T, int* MemoryUsage);
AvlTree Delete( ElementType X, AvlTree T, int* MemoryUsage );
ElementType Retrieve( Position P );
Position SortedTraversal( AvlTree T );

#endif
