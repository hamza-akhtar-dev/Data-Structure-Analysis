#include "array.h"   
#include "fileio.h"
#include <windows.h>

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    Array A;
    Position P;
    FILE* fp;
    double run_time;
    int i, num_records;
	int MemoryUsage = 0; 
	
	/*<-----------FILE INPUT----------->*/  

	fp = fopen( "data_10.txt", "r" );
		fscanf( fp, "%s", ignore );
		fscanf( fp, "%d", &num_records );
		printf( "Number of Records: %d\n", num_records );
		Record_Arr = ReadRecords( fp, num_records );
	fclose(fp);
	
	/*<----------OPERATIONS------------>*/
	
	A = CreateArray( num_records, &MemoryUsage );

	QueryPerformanceFrequency(&frequency);
	
	
	//=======INSERTION=======//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        Insert( A, Record_Arr[i], i );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Insert \t\t     Execution Time: %f s ; Memory Usage: %d bytes\n", run_time, MemoryUsage);
    //PrintData( A );

	
	//========FIND========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2)
		{
	        P = Find( A, RetrieveID( Record_Arr[i] ) );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Find \t\t     Execution Time: %f s ; Memory Usage: %d bytes\n", run_time, MemoryUsage);
	
	//========SORTED TRAVERSAL========//
	
	QueryPerformanceCounter(&start_time);
	    SortedTraversal( A );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal     Execution Time: %f s ; Memory Usage: %d bytes\n", run_time, MemoryUsage);
	
	//========DELETE========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2)
		{
	        Delete( A, RetrieveID( Record_Arr[i] ) );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Delete \t\t     Execution Time: %f s ; Memory Usage: %d bytes\n", run_time, MemoryUsage);
	
	//PrintData( A );
	DestroyArray( A, &MemoryUsage );
	
	//printf("After Destroying \t\t     Memory Usage: \t %d bytes\n\n", MemoryUsage);
    return 0;
}
