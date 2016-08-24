#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "record.h"


void writes(int ctid)
{
	FILE *fp1;ELEMENT ob;
	fp1 = fopen("CellStorage.bin","ab");
	if (!fp1)
		{
			printf("Unable to open file!");
		}
		
		ob = read_current_value(ctid);	
		if(ob.state==pending)
		{
			ob.state=committed;	
			fwrite(&ob, sizeof(struct data_record), 1,fp1);
			printf("Committed Successfully!!!");
		}
		else
			printf("Commit Failed! Please retry.....");
		fclose(fp1);
}

 int write_new_value(int cdataid,char data[512],int ctid)
{
	FILE *fp;
	ELEMENT ob;
	ob.tid = ctid; ob.dataid = cdataid; strcpy(ob.data,data);
	ob.state = pending;
	fp = fopen("JournalStorage.bin","ab");
	if (!fp)
		{
			printf("Unable to open file!");
			return -1;
		}
		
		fwrite(&ob, sizeof(struct data_record), 1, fp);
		printf("\nLogged in version history with pending state. Press commit to write into cell storage.....");
		fclose(fp);
		return 0;
	
}  	
	
