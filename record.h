#include<stdio.h>
#ifndef RECORD_H_  
#define RECORD_H_

typedef enum
	{
	   pending,committed,aborted,marked,unmarked
		
	}rec_state;

struct outcome_record
{
	int tid,dataid;
	rec_state state;
	rec_state markpoint;
};

int cur_tid,tid,dataid,tdataid;
int print_JFS();
int print_CSS();
int find();

struct data_record
{
	int tid,dataid;
	char data[512];
	rec_state state;
};

typedef struct data_record *LINK;
typedef struct data_record ELEMENT;

extern struct outcome_record out_rec[100];
void new_action(int tid,int dataid);

void faulty();
int recover();

int write_new_value(int dataid,char data[512],int tid);
void writes(int tid);
void reads(int dataid);
ELEMENT read_current_value(int tid);
void commit(int utid);
#endif // RECORD_H_

