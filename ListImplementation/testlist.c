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
	
	L = MakeEmpty( NULL );
	
	fp = fopen( "data_1000000.txt", "r" );
	
		fscanf( fp, "%s", ignore );
		
		fscanf( fp, "%d", &num_records );
		
		printf( "Number of Records: %d\n", num_records );
		
		Record_Arr = ReadRecords( fp, num_records );
	
	fclose(fp);

	QueryPerformanceFrequency(&frequency);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], L, L );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Insert \t\t Execution Time: \t %f s\n", run_time);
	//PrintList(L);
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i+=2)
		{
	        P = Find(RetrieveID( Record_Arr[i] ), L);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Find \t\t Execution Time: \t %f s\n", run_time);
	
	QueryPerformanceCounter(&start_time);
	    
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Sorted Traversal Execution Time: \t %f s\n", run_time);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 1; i < num_records; i+=2)
		{
	        Delete(RetrieveID( Record_Arr[i] ), L);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Delete \t\t Execution Time: \t %f s\n", run_time);
	//PrintList(L);
	DeleteList(L);
    return 0;
}
