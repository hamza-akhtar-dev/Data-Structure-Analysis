#include <windows.h>
#include "avltree.h"
#include "fileio.h"

int main( void )
{
	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
	char ignore[MAXNAMELENGTH];
	Record* Record_Arr;
    AvlTree T;
    FILE* fp;
    double run_time;
    int i, num_records;
    int MemoryUsage = 0;
   
	T = MakeEmpty( NULL );

	fp = fopen( "data_10.txt", "r" );
	
		fscanf( fp, "%s", ignore );
		
		fscanf( fp, "%d", &num_records );
		
		printf( "Number of Records: %d\n", num_records );
		
		Record_Arr = ReadRecords( fp, num_records );
	
	fclose(fp);

	QueryPerformanceFrequency(&frequency);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        T = Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], T , &MemoryUsage );
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf( "Time for Tree Insertion = %f sec\n", run_time );
	printf( "Memory Consumed for Tree Insertion = %d bytes\n", MemoryUsage );
	
    return 0;
}
