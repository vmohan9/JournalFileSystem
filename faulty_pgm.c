#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "record.h"

void faulty()
{
	
	exit(0);
}

int recover()
{
	FILE *fp, *fp1; int length,c =0,counter;ELEMENT my_record,my_record1;
	fp=fopen("transcount.bin","rb");
	if (!fp)
	{
 		return 0;
	}
	else
	{   
		fread(&length,sizeof(int),1,fp);	
		fclose(fp);
	}
	//printf("\n@@@@@@@-%d",length);
	
	fp=fopen("JournalStorage.bin","r+");
	if (!fp)
	{
		printf("Unable to open file!");
	}
	fseek(fp,(length-1000)*sizeof(ELEMENT),SEEK_SET);		
	fread(&my_record,sizeof(struct data_record),1,fp);
	if(my_record.state==committed)
	{

		fp1=fopen("CellStorage.bin","rb");
		if (!fp1)
		{
			printf("Unable to open file!");
			
		}
		//printf("\n$$$$$$");
		for ( counter=0; counter < find(); counter++)
		{
			fread(&my_record1,sizeof(struct data_record),1,fp1);
			if(my_record1.tid==my_record.tid)
			{	
				printf("\nSystem is functional!!!");
				return 1;
			}
		}
		
		my_record.state=pending;
		fseek(fp,(length-1000)*sizeof(ELEMENT),SEEK_SET);	
		fwrite(&my_record, sizeof(struct data_record), 1, fp);	
		printf("\n***** System Recovered from fault ******");			
				
		fclose(fp1);
		fclose(fp);
		return 0;	
	
	}
	else
	{	printf("\nSystem is functional!!!");
		fclose(fp);		
		return 2;
	}	
	

}