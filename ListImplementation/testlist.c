#include "list.h"   
#include "fileio.h"
#include <windows.h>

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    List L;
    Position P;
    FILE* fp;
    double run_time;
    int i, num_records;  
    int MemoryUsage = 0;
	
	
	/*<-----------FILE INPUT----------->*/  

	fp = fopen( "data_10000.txt", "r" );
		fscanf( fp, "%s", ignore );
		fscanf( fp, "%d", &num_records );
		printf( "Number of Records: %d\n", num_records );
		Record_Arr = ReadRecords( fp, num_records );
	fclose(fp);
	
	/*<----------OPERATIONS------------>*/
	
	L = MakeEmpty( NULL, &MemoryUsage );

	QueryPerformanceFrequency(&frequency);
	
	
	//=======INSERTION=======//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], L, &MemoryUsage );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Insert \t\t     Execution Time: %f s \t Memory Usage: %d bytes\n", run_time, MemoryUsage);
    //PrintList( L );

	
	//========FIND========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2)
		{
	        P = Find( RetrieveID( Record_Arr[i] ), L );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Find \t\t     Execution Time: %f s \t Memory Usage: %d bytes\n", run_time, MemoryUsage);
	
	
	//========SORTED TRAVERSAL========//
	
	QueryPerformanceCounter(&start_time);
		SortedTraversal( L );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal     Execution Time: %f s \t Memory Usage: %d bytes\n", run_time, MemoryUsage);
	
	
	//========DELETE========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2)
		{
	        Delete( RetrieveID( Record_Arr[i] ), L, &MemoryUsage );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Delete \t\t     Execution Time: %f s \t Memory Usage: %d bytes\n", run_time, MemoryUsage);
		
	//PrintList(L);
	DeleteList(L, &MemoryUsage);
	
    //printf("After Destroying \t    Memory Usage: %d bytes\n\n", MemoryUsage);
    
    return 0;
}
