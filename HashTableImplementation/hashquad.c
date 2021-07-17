#include "fatal.h"
#include "hashquad.h"
#include "fileio.h"
#include <stdlib.h>

#define MinTableSize (10)

enum KindOfEntry { Legitimate, Empty, Deleted, Found };

struct HashEntry
{
    ElementType      Element;
    Record			 Data;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/* Cell *TheCells will be an array of */
/* HashEntry cells, allocated later */
struct HashTbl
{
    int TableSize;
    int Nelts;
    Cell *TheCells;
};

/* Return next prime; assume N >= 10 */

static int
NextPrime( int N )
{
    int i;
	N *= 1.5;
    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 )
    {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto CountOuter;  
        return N;
      CountOuter: ;
    }
}

Index
Hash( ElementType Key, int TableSize )
{
    return Key % TableSize;
}

HashTable
InitializeTable( int TableSize, int* MemoryUsage )
{
    HashTable H;
    int i;

    if( TableSize < MinTableSize )
    {
    Error( "Table size too small" );
    return NULL;
    }

    /* Allocate table */
    H = malloc( sizeof( struct HashTbl ) );
    *MemoryUsage += sizeof( struct HashTbl );
    
    if( H == NULL )
        FatalError( "Out of space!!!" );

    H->TableSize = NextPrime( TableSize );
	H->Nelts = 0;
    /* Allocate array of Cells */
    H->TheCells = malloc( sizeof( Cell ) * H->TableSize );
    *MemoryUsage += sizeof( Cell ) * H->TableSize;
    
    if( H->TheCells == NULL )
        FatalError( "Out of space!!!" );

    for( i = 0; i < H->TableSize; i++ )
        H->TheCells[ i ].Info = Empty;
    return H;
}

Position
Find( ElementType Key, HashTable H )
{
    Position CurrentPos;
    int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash( Key, H->TableSize );
	while( H->TheCells[ CurrentPos ].Info != Empty &&
           H->TheCells[ CurrentPos ].Element != Key )
    {
		CurrentPos += 2 * ++CollisionNum - 1;
		if( CurrentPos >= H->TableSize )
    		CurrentPos -= H->TableSize;
    }
    return CurrentPos;
}

void 
Insert( ElementType Key, Record R, HashTable H  )
{
    Position Pos;

    Pos = Find( Key, H );
    if( H->TheCells[ Pos ].Info != Legitimate )
    {
        H->Nelts += 1;
		H->TheCells[ Pos ].Info = Legitimate;
        H->TheCells[ Pos ].Element = Key;
        H->TheCells[ Pos ].Data = R;
    }
}

ElementType
Retrieve( Position P, HashTable H )
{
    return H->TheCells[ P ].Element;
}

void
DestroyTable( HashTable H, int* MemoryUsage )
{
    int i;
	for ( i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != Empty)
		{
			Record R = H->TheCells[i].Data;
			free( RetrieveName( R ) );
			free( RetrieveCity( R ) );
			free( RetrieveService( R ) );
			free(R);
		}
	}
	free( H->TheCells );
    *MemoryUsage -= sizeof( Cell ) * H->TableSize;
	free(H);
	*MemoryUsage -= sizeof( struct HashTbl );
}

/*
In order to print the hash table u need to
iterate through the TheLists and print the entry at each index
, if the index is legitimate print the entry contained by it, 
if its info is deleted print deleted and if its info is empty
print empty
*/
void 
PrintHashTable( HashTable H )
{
	int i;
	// iterating through the hash table
	for (i = 0; i < H->TableSize; i++)
	{
		printf("Index %d: ",i);
		// printing the entry at cell
		if ( H->TheCells[ i ].Info == Legitimate || H->TheCells[ i ].Info == Found )
			{
				Record R = H->TheCells[i].Data;
				printf("ID = %d \t Name = %s \t City = %s \t Sevice = %s\n", 
				RetrieveID(R), RetrieveName(R), RetrieveCity(R),RetrieveService(R) );
			}
		// printing empty, as the cell is empty
		else if ( H->TheCells[ i ].Info == Empty )
			printf("Empty");
		// printing deleted as the the entry at the cell is deleted
		else if ( H->TheCells[ i ].Info == Deleted )
			printf("Deleted");
		printf("\n");
	}
}

/*
In order to delete a key, first find the postion of the key
using Find() function, then change the info of the cell 
to Deleted
*/
void
Delete( ElementType Key, HashTable H )
{
	// finding the corresponding cell that contains our required key
	Position P = Find( Key, H );
	// if the info of the cell is empty, this means that our key doesnt exist in hash table
	if ( H->TheCells[ P ].Info == Empty )
	{
		Error( "Key not found" );	// exit with error message
	}
	// else, we have found our required cell, simply change the info of the cell to deleted
	H->TheCells[ P ].Info = Deleted;
}

void
Swap( ElementType *Lhs, ElementType *Rhs )
{
    ElementType Tmp = *Lhs;
    *Lhs = *Rhs;
    *Rhs = Tmp;
}
       
void
Qsort( ElementType A[ ], int Left, int Right )
{
    if( Left < Right )
    {
        int i, j;
        ElementType Pivot;

        i = Left; j = Right - 1;
        
		Pivot = A[ Right ];
        
        while (1)
        {
            while( A[ i ] < Pivot ) {++i;}
            while( A[ j ] >= Pivot ) {--j;}    

            if( i < j )
            {
                Swap( &A[ i ], &A[ j ] );
            }
            else
                break;
        }

        Swap( &A[ Right ], &A[ i ] );      // Put pivot at appropriate place

        Qsort( A, Left, j );
        Qsort( A, j + 2, Right );
	}	
}
        
void
Quicksort( ElementType A[ ], int N )
{
    Qsort( A, 0, N - 1 );
}

void
Copy( HashTable H, ElementType Array[] )
{
	int i;
	int t = 0;
	for ( i = 0; i < H->TableSize; i++)
	{
		if ( H->TheCells[ i ].Info == Legitimate )
		{
			Array[ t ] = H->TheCells[ i ].Element;
			t += 1;
		}
	}
}
      
void		
SortedTraversal101( HashTable H, int* MemoryUsage )
{
	int i;
	ElementType Array[ H->Nelts ];
	*MemoryUsage += sizeof(ElementType) * H->Nelts;
	Copy( H, Array );
	Quicksort( Array, H->Nelts );
	for ( i = 0; i < H->Nelts; i++ )
	{
		Position P = Find( Array[i], H);
		Record R = H->TheCells[P].Data;
		//printf("ID = %d \t Name = %s \t City = %s \t Sevice = %s\n", 
		//RetrieveID(R), RetrieveName(R), RetrieveCity(R),RetrieveService(R) );		
	}
}		
		
void
SortedTraversal( HashTable H )	
{
	int i, j;
	int Min, Index;
	
	for ( i = 0; i < H->TableSize; i++ )
	{
		if ( H->TheCells[i].Info == Empty || H->TheCells[i].Info == Deleted )
		{
			continue;
		}
		
		Min = 10000000; //An "Arbitrary Large Number" for which we are sure that ID will be less than this.
		
		for ( j = 0; j < H->TableSize; j++ )
		{
			if ( H->TheCells[j].Element < Min && H->TheCells[j].Info == Legitimate )
			{
				Min = H->TheCells[j].Element;
				
				Index = j;
			}
		}
		H->TheCells[Index].Info = Found;
		Record R = H->TheCells[Index].Data;
		//printf("ID = %d \t Name = %s \t City = %s \t Sevice = %s\n", 
		//RetrieveID(R), RetrieveName(R), RetrieveCity(R),RetrieveService(R) );
	}
}	
