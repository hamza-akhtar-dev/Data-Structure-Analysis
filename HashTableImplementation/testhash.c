#include "hashquad.h"   
#include "fileio.h"
#include <windows.h>

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    HashTable H;
    FILE* fp;
    double run_time;
    int i, num_records;   

	fp = fopen( "data_100000.txt", "r" );
	
		fscanf( fp, "%s", ignore );
		
		fscanf( fp, "%d", &num_records );
		
		printf( "Number of Records: %d\n", num_records );
		
		Record_Arr = ReadRecords( fp, num_records );
	
	fclose(fp);
	
	H = InitializeTable(num_records);

	QueryPerformanceFrequency(&frequency);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], H );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Insert \t\t Execution Time: \t %f s\n", run_time);
	//PrintHashTable(H);
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2)
		{
	        Find(RetrieveID( Record_Arr[i] ), H);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Find \t\t Execution Time: \t %f s\n", run_time);
	
	QueryPerformanceCounter(&start_time);
	    SortedTraversal( H );
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal Execution Time: \t %f s\n", run_time);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2)
		{
	        Delete(RetrieveID( Record_Arr[i] ), H);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Delete \t\t Execution Time: \t %f s\n", run_time);
	//PrintHashTable(H);
	DestroyTable(H);
    return 0;
}
