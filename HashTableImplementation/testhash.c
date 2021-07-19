#include "hashquad.h"   
#include "fileio.h"
#include <windows.h>

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    HashTable H;
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
	
	H = InitializeTable(num_records, &MemoryUsage);

	QueryPerformanceFrequency(&frequency);
	
	//=======INSERTION=======//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], H );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Insert \t\t     Execution Time: \t %f s \t Memory Consuption: \t %d bytes\n", run_time, MemoryUsage);
	//PrintHashTable(H);
	
	//========FIND========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2)
		{
	        P = Find(RetrieveID( Record_Arr[i] ), H);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Find \t\t     Execution Time: \t %f s \t Memory Consuption: \t %d bytes\n", run_time, MemoryUsage);
	
	//========SORTED TRAVERSAL 101========//
	
	QueryPerformanceCounter(&start_time);
	    SortedTraversal101( H, &MemoryUsage );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal 101 Execution Time: \t %f s \t Memory Consuption: \t %d bytes\n", run_time, MemoryUsage);
	
	//========SORTED TRAVERSAL========//
	
	QueryPerformanceCounter(&start_time);
	    SortedTraversal( H );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal     Execution Time: \t %f s \t Memory Consuption: \t %d bytes\n", run_time, MemoryUsage);
	
	//========DELETE========//
	
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2)
		{
	        Delete(RetrieveID( Record_Arr[i] ), H);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Delete \t\t     Execution Time: \t %f s \t Memory Consuption: \t %d bytes\n", run_time, MemoryUsage);
	//PrintHashTable(H);
	DestroyTable(H, &MemoryUsage);
	//printf("After Destroying \t\t     Memory Usage: \t %d bytes\n\n", MemoryUsage);
    return 0;
}
