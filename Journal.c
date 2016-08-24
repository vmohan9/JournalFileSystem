#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include "record.h"


struct outcome_record out_rec[100];
pthread_t threadid[2];
int coun;
pthread_mutex_t lock;
int i,cdataid;
void aborts(int utid);
void new_action(int ctid,int cdataid)
{
        FILE *fp; struct outcome_record ob;char oc;
	out_rec[i].tid=ctid;
	out_rec[i].state=pending;
        again:
        fp = fopen("outcomerecord.bin","ab");	
        if (!fp)
		{
			printf("file already opened by another thread ");
                        sleep(5);
                        goto again;
		}
		
		ob.tid = ctid;
                ob.state = pending;
		ob.dataid = cdataid;
		printf("\nWould you like to mark the record(Y/N):");
		scanf(" %c", &oc);
		if(oc == 'Y' || oc == 'y')
                	{ob.markpoint = marked;printf("Marked Successfully!!!");}
		else 
			{
         			ob.markpoint = unmarked;}
			
		fwrite(&ob, sizeof(struct outcome_record), 1,fp);
		fclose(fp);
        
}

void commit(int utid)
{
	int j;	
	j = tid_search(utid);
	out_rec[j].state = committed;
	writes(utid);
	FILE *fp; int counter;
	ELEMENT my_record;
		fp=fopen("JournalStorage.bin","r+");
		if (!fp)
		{
			printf("Unable to open file!");
		}
		
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);		
		fread(&my_record,sizeof(struct data_record),1,fp);
		//printf("reading for aborting.. %d %s",my_record.dataid,my_record.data);
		my_record.state=committed;
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);	
		fwrite(&my_record, sizeof(struct data_record), 1, fp);
		fclose(fp);
}

int print_JFS()
{
	FILE *fp; int counter;
	ELEMENT my_record;
	fp=fopen("JournalStorage.bin","rb");
	if (!fp)
	{
			printf("Unable to open file!");
			return -1;
	}
		printf("\n****JournalStorage****\n");
		for ( counter=0; counter <= tid-1000; counter++)
		{
			fread(&my_record,sizeof(struct data_record),1,fp);
			printf("\ndataid: %d	transactionid: %d	data: %s   ",my_record.dataid,my_record.tid,my_record.data);
			switch(my_record.state)
			{
			  case 0 : printf("	state: Pending");
				   break;
		          case 1 : printf("	state: Committed");
				   break;
			  case 2 : printf("	state: Aborted");
			}
		}
		fclose(fp);
		return 0;

}

int print_CSS()
{
	FILE *fp; int counter;
	ELEMENT my_record;
	fp=fopen("CellStorage.bin","rb");
	if (!fp)
	{
			printf("Unable to open file!");
			return -1;
	}
		printf("\n****CellStorage****\n");
		for ( counter=0; counter < find(); counter++)
		{
			fread(&my_record,sizeof(struct data_record),1,fp);
			printf("\ndataid: %d	transactionid: %d	data: %s",my_record.dataid,my_record.tid,my_record.data);
		}
		fclose(fp);
		return 0;
}


int tid_search(int ctid)
{
	int j;
	for(j=0;j<i;j++)
	{
		if(out_rec[j].tid==ctid)
			return j;
	}
	return -1;
}

int findtlen()
{	FILE *fp; int length;
	fp=fopen("transcount.bin","rb");
	if (!fp)
	{
		//printf("Unable to open file!"); 
		return 0;
	}
	else
	{   
		fread(&length,sizeof(int),1,fp);	
		fclose(fp); return length;
	}
}

int finddlen()
{	FILE *fp; int length;
	fp=fopen("datacount.bin","rb");
	if (!fp)
	{
		//printf("Unable to open file!"); 
		return 0;
	}
	else
	{   
		fread(&length,sizeof(int),1,fp);	
		fclose(fp); return length;
	}
}

int find()
{	FILE *fp; int length;
	fp=fopen("CellStorage.bin","rb");
	if (!fp)
	{
		//printf("Unable to open file!"); 
		return 0;
	}
	else
	{   
		fseek(fp,0,SEEK_END);
		length = ftell(fp)/sizeof(ELEMENT);
		//printf("\ndataid:%d length: %d",dataid,length);
		//dataid = dataid+length;	
		fclose(fp); return length;
	}
}

int check_marked(int ctid,int cdataid)
{

	FILE *fp; int c =0,counter;
	struct outcome_record my_record;
		fp=fopen("outcomerecord.bin","rb");
		if (!fp)
		{
			printf("Unable to open file!");
		} 
		for ( counter=0; counter <= tid-1000; counter++)
		{       
			fread(&my_record,sizeof(struct outcome_record),1,fp);
			if(my_record.dataid==cdataid && my_record.markpoint == 3)			     {   c = 1; fclose(fp);
				return 1;}
			else
				c = 0;
			
		}
		fclose(fp);
		return c;

}

void markpoint_announce(int ctid)
{
	FILE *fp; int c =0,counter;
	struct outcome_record my_record;
		fp=fopen("outcomerecord.bin","r+");
		if (!fp)
		{
			printf("Unable to open file!");
		} 
		     

		fseek(fp,(ctid-1000)*sizeof(struct outcome_record),SEEK_SET);		
		fread(&my_record,sizeof(struct outcome_record),1,fp);
		my_record.markpoint=marked;
		fseek(fp,(ctid-1000)*sizeof(struct outcome_record),SEEK_SET);	
		fwrite(&my_record, sizeof(struct outcome_record), 1, fp);
		printf("Marked!");	
		fclose(fp);

}

void faulty_commit(int utid)
{
	FILE *fp; int counter;
	ELEMENT my_record;
		fp=fopen("JournalStorage.bin","r+");
		if (!fp)
		{
			printf("Unable to open file!");
		}
		
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);		
		fread(&my_record,sizeof(struct data_record),1,fp);
		my_record.state=committed;
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);	
		fwrite(&my_record, sizeof(struct data_record), 1, fp);
		fclose(fp);
		print_JFS();
		print_CSS();
		printf("Crashing!!!!!!!!!!!!!!!!!!\n");
		faulty();
	
}


void* threadexecute()
{
        int ch,utid,did,length,k;
	FILE *fp,*fp1; char data[512];
        
        dataid = finddlen();
        tid = findtlen();
	
        if(tid==0)
               tid = 999;
        if(dataid==0)
               dataid = 99;
	recover();	
	do
	{
		printf("\n\n1.Create\n2.Mark\n3.Read\n4.Write\n5.Commit\n6.Faulty commit\n7.Abort\n8.View\n9.Exit\nEnter your choice:");
		scanf("%d",&ch);	
		if(ch==1)
		{
                        dataid++;                        
                        fp1 = fopen("datacount.bin","wb");
                        fwrite(&dataid, sizeof(int), 1,fp1);
                        fclose(fp1);						
			printf("\nCreating a new file..... ");
			printf("Your dataid: %d",dataid);
					
		}
		else if(ch==2) 
		{
			printf("Enter transaction id to be marked:");
			scanf("%d",&utid);
			markpoint_announce(utid);
		}
		else if(ch==3)
		{
			printf("Enter data id:");
			scanf("%d",&did);
			reads(did);
		}	
		else if(ch==4)
		{
			
			fp1 = fopen("transcount.bin","wb");			
			printf("Enter dataid:");
			scanf("%d",&dataid);				
			printf("Enter data:");
			scanf("%s",data);//printf("t%d",tid);
		    	if(tid != 999) 
				if(check_marked(tid,dataid)==0)
					{ printf("Previous transaction has not reached its markpoint");continue;}
				else
				 {
					pthread_mutex_lock(&lock); 
					tid++;//printf("hello");
				  	new_action(tid,dataid);
                         		pthread_mutex_unlock(&lock);
					printf("Your transaction id: %d",tid);
					write_new_value(dataid,data,tid);
                        		fwrite(&tid, sizeof(int), 1,fp1);
				 }
			else
                        {	pthread_mutex_lock(&lock); 
					tid++;
				  	new_action(tid,dataid);
                         		pthread_mutex_unlock(&lock);
					printf("Your transaction id: %d",tid);
					write_new_value(dataid,data,tid);
                        		fwrite(&tid, sizeof(int), 1,fp1);
			}
                        fclose(fp1);
			
		}
		else if(ch==5)
		{
			printf("Enter transaction id to be committed:");
			scanf("%d",&utid);
			commit(utid);
		}
		else if(ch==6)
		{
			printf("Enter transaction id to be committed:");
			scanf("%d",&utid);
			faulty_commit(utid);
		}
		
		else if(ch==7)
		{
			printf("Enter transaction id to be aborted:");
			scanf("%d",&utid);	
			aborts(utid);
		}
		else if(ch==8)
		{
			print_JFS();
			print_CSS();	
		}		
	}while(ch!=9);

        

}

int main()
{	//int ch,utid,did,length,k;
	//FILE *fp,*fp1; char data[512];
        int k,err;
        if (pthread_mutex_init(&lock, NULL) != 0)
        {
            printf("\n mutex init failed\n");
            return 1;
         }
	printf("\n\n*****************************************");
	printf("\n Welcome to Journal Storage File System");
	printf("\n*****************************************");

        while(k < 2)
        {
        printf("\n\nNew Thread executing!!!\n");
        err = pthread_create(&(threadid[k]), NULL, &threadexecute, NULL);
        pthread_join(threadid[0], NULL);
        if (err != 0)
            printf("\ncan't create thread :[%d]", err); //strerror(err));
        k++;
        }
    pthread_join(threadid[1], NULL);
    pthread_mutex_destroy(&lock);

	return 0;
}



void aborts(int utid)
{
	int j; j = tid_search(utid);
	out_rec[j].state = aborted;
	FILE *fp; int counter;
	ELEMENT my_record;
		fp=fopen("JournalStorage.bin","r+");
		if (!fp)
		{
			printf("Unable to open file!");
		}
		
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);		
		fread(&my_record,sizeof(struct data_record),1,fp);
		//printf("reading for aborting.. %d %s",my_record.dataid,my_record.data);
		my_record.state=aborted;
		fseek(fp,(utid-1000)*sizeof(ELEMENT),SEEK_SET);	
		fwrite(&my_record, sizeof(struct data_record), 1, fp);
		printf("\nAborted!!!");
		fclose(fp);
}


