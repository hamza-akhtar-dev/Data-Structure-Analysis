#include "avltree.h"
#include "fileio.h"
#include "fatal.h"

struct AvlNode
{
    ElementType Element;
    Record Data;
    AvlTree  Left;
    AvlTree  Right;
    int      Height;
};

AvlTree
MakeEmpty( AvlTree T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

Position
Find( ElementType X, AvlTree T )
{
    if( T == NULL )
        return NULL;
    if( X < T->Element )
        return Find( X, T->Left );
    else
    if( X > T->Element )
        return Find( X, T->Right );
    else
        return T;
}

Position
FindMin( AvlTree T )
{
    if( T == NULL )
        return NULL;
    else
    if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

Position
FindMax( AvlTree T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

static int
Height( Position P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

static int
Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

static Position
SingleRotateWithLeft( Position K2 )
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

static Position
SingleRotateWithRight( Position K1 )
{
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

static Position
DoubleRotateWithLeft( Position K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

static Position
DoubleRotateWithRight( Position K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}

AvlTree
Insert( ElementType X, Record R, AvlTree T, int* MemoryUsage)
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct AvlNode ) );
        
        *MemoryUsage += sizeof( struct AvlNode );
        
        if( T == NULL )
            FatalError( "Out of space!!!" );
        else
        {
            T->Element = X; 
            T->Data = R;
			T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else
    if( X < T->Element )
    {
        T->Left = Insert( X, R, T->Left, MemoryUsage );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( X < T->Left->Element )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
    }
    else
    if( X > T->Element )
    {
        T->Right = Insert( X, R, T->Right, MemoryUsage );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}

AvlTree
Delete( ElementType X, AvlTree T )
{
    printf( "Sorry; Delete is unimplemented; %d remains\n", X );
    return T;
}

ElementType
Retrieve( Position P )
{
    return P->Element;
}

Position
SortedTraversal( AvlTree T )
{
	if( T == NULL)
	{
		return NULL;
	}
	else
	{
		SortedTraversal( T -> Left );
		printf(
			"Id: %d\t Name: %s\t City: %s\t Service: %s \n", 
			RetrieveID( T->Data ), 
			RetrieveName( T->Data ), 
			RetrieveCity( T->Data ), 
			RetrieveService( T->Data ) 
		);
		SortedTraversal( T -> Right );
	}
}
