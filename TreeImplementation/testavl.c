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
   
	T = MakeEmpty( NULL );

	fp = fopen( "data_1000.txt", "r" );
	
		fscanf( fp, "%s", ignore );
		
		fscanf( fp, "%d", &num_records );
		
		printf( "Number of Records: %d\n", num_records );
		
		Record_Arr = ReadRecords( fp, num_records );
	
	fclose(fp);

	QueryPerformanceFrequency(&frequency);
	
	QueryPerformanceCounter(&start_time);
	    for (i = 0; i < num_records; i++)
		{
	        T = Insert( RetrieveID( Record_Arr[i] ), Record_Arr[i], T);
		}
	QueryPerformanceCounter(&end_time);
	
	elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;
	
	printf("Time for Tree Insertion = %f s\n", run_time);
	
    return 0;
}
