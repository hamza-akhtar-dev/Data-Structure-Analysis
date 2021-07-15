#include <windows.h>
#include "avltree.h"
#include "fileio.h"

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    AvlTree T;
    Position P;
    FILE* fp;
    
    double runtime_insrt, runtime_sort, runtime_find, runtime_delete;
    int i, num_records;
    int MemoryUsage = 0;
   
	T = MakeEmpty( NULL );

	fp = fopen( "data_100.txt", "r" );
		fscanf( fp, "%s", ignore );
		fscanf( fp, "%d", &num_records );
		printf( "Number of Records: %d\n", num_records );
		Record_Arr = ReadRecords( fp, num_records );
	fclose(fp);

	QueryPerformanceFrequency(&frequency);
	
	
	printf("Inserting Records ...\n");
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        T = Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], T , &MemoryUsage );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	runtime_insrt = ( (double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf( "Memory Consumed for Tree Insertion = %d bytes\n", MemoryUsage );
	printf( "Time for Tree Insertion = %f sec\n\n", runtime_insrt );
	
	
	printf("Starting Sorted Traversal ...\n");
	QueryPerformanceCounter(&start_time);
		SortedTraversal( T );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	runtime_sort = ( (double) elapsed_time.QuadPart ) / frequency.QuadPart;
	
	printf( "Time for Tree Sorted Traversal = %f sec\n", runtime_sort );
	printf( "Memory Consumed for Tree Sorted Traversal = %d bytes\n\n", MemoryUsage );
	
	
	printf("Finding Records ...\n");
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2 )
		{
	        P = Find( RetrieveID( Record_Arr[i] ), T );
	        if( P != NULL )
	        {
	        	printf("Found\n");   //Comment this for larger data files
			}
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	runtime_find = ( (double) elapsed_time.QuadPart ) / frequency.QuadPart;
	
	printf( "Time for Tree Finding = %f sec\n", runtime_find );
	printf( "Memory Consumed for Tree Finding = %d bytes\n\n", MemoryUsage );
	
	
	printf("Deleting Records ...\n");
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2 )
		{
	        Delete( RetrieveID( Record_Arr[i] ), T, &MemoryUsage );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	runtime_delete = ( (double) elapsed_time.QuadPart ) / frequency.QuadPart;
	
	printf( "Time for Tree Deletion = %f sec\n", runtime_delete );
	printf( "Memory Consumed after Deletion = %d bytes\n\n", MemoryUsage );
	
    return 0;
}
