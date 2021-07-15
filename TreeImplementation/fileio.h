#include <stdio.h>

#ifndef _FileIo_H
#define _FileIo_H

#define MAXNAMELENGTH 10

struct CompanyRecord;
typedef struct CompanyRecord* Record;

Record CreateRecord( int id, char *name, char *city, char* service );
Record* ReadRecords( FILE *fp, int RecordCount );
int RetrieveID ( Record R );
char* RetrieveName ( Record R );
char* RetrieveCity ( Record R );
char* RetrieveService ( Record R );


#endif
