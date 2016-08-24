#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "record.h"

ELEMENT read_current_value(int ctid)
{
	FILE *fp; int c =0,counter;
	ELEMENT my_record;
		fp=fopen("JournalStorage.bin","rb");
		if (!fp)
		{
			printf("Unable to open file!");
		}
		for ( counter=0; counter <= tid-1000; counter++)
		{
			fread(&my_record,sizeof(struct data_record),1,fp);
			if(my_record.tid==ctid&&my_record.state==pending)
			{	c = 1;
				break;
			}
		}
		fclose(fp);
	
		return my_record;

}

void reads(int cdataid)
{
	FILE *fp; int c =0,counter;
	ELEMENT my_record;
	char data[512];

		fp=fopen("CellStorage.bin","rb");
		if (!fp)
		{
			printf("Unable to open file!");
			
		}
		//printf("\nreadid:%d,%d",dataid,cdataid);
		for ( counter=0; counter < find(); counter++)
		{
			fread(&my_record,sizeof(struct data_record),1,fp);
			if(my_record.dataid==cdataid)
			{	//printf("found!");
				memset(&data[0],0,sizeof(data));
				//printf("foo:%s",my_record.data);
				strcpy(data,my_record.data); c=1;
			}
		}
		fclose(fp);
		if(c==1)
			printf("Most recent committed value: %s",data);
		else
			printf("There is no committed value");
}