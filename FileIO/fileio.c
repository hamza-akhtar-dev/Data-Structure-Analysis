
#include "fileio.h"
#include "fatal.h"

struct CompanyRecord
{
	int id;
	char *name;
	char *city;
	char *service;	
};

Record CreateRecord(int id, char *name, char *city, char* service )
{
    Record CR;

    CR = (Record)malloc( sizeof(struct CompanyRecord) );
    
    if( CR == NULL )
        FatalError( "Out of space!!!" );

    CR->id = id;
    CR->name = name;
    CR->city = city;
    CR->service = service;

    return CR;
}

Record* ReadRecords( FILE *fp, int RecordCount )
{
	int i;
	int id;
	char *N;
	char *C;
	char *S;
	
	Record* Record_Arr;
	
	Record_Arr = (Record*)malloc( RecordCount * sizeof(Record) );
	
	 if( Record_Arr == NULL )
        FatalError( "Out of space!!!" );

	for ( i = 0; i < RecordCount; i++ )
	{
		N = (char *)malloc(sizeof(char) * MAXNAMELENGTH);
        C = (char *)malloc(sizeof(char) * MAXNAMELENGTH);
		S = (char *)malloc(sizeof(char) * MAXNAMELENGTH);

		fscanf( fp, "%d %s %s %s", &id, N, C, S);

		Record_Arr[i] = CreateRecord(id, N, C, S);
	}
	
	return Record_Arr;
}

int RetrieveID ( Record R )
{
	return R->id;
}

char* RetrieveName ( Record R )
{
	return R->name;
}

char* RetrieveCity ( Record R )
{
	return R->city;
}

char* RetrieveService ( Record R )
{
	return R->service;
}
