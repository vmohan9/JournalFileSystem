------------
Command Line
------------

gcc Journal.c writes.c reads.c faulty_pgm.c
./a.out

files:
1. Record.h
2. Journal.c
3. reads.c
4. writes.c
5. faulty_pgm.c

Procedures:

1.	New_action(int tid) – creates a new action record for each new action with a unique transaction id.
2.	Commit(int tid) - checks if the transaction is in pending state in Journal Storage and if yes, writes the value into the corresponding sector of the cell storage by calling write() and changed the state of the version to committed in journal storage.
3.	Abort(int tid) – checks if the transaction is in pending state in Journal storage and changes the state of the record to aborted.
4.	print_JFS() – enables the user to view the current state of the Journal storage system
5.	print_CSS() – enables the user to view the current state of the Cell storage system.
6.	Find() – returns the total number of cells in the Cell storage system
7.	Write_new_value (int dataid,char data[512],int tid) – writes the record into the Journal storage system with pending state.
8.	Write(int tid) – retrieves the pending record associated with the transaction from the journal storage and writes the record into its respective cell in cell storage.
9.	Read_current_value(int tid) – returns the data corresponding to particular transaction tid stored in the journal storage system.
10.	Read(int dataid) – returns the most recently committed value for the corresponding data object identified using dataid.
11.     fault() – exits the application thereby causing a fault while trying to commit a particular transaction.
12.	recover() – recovers the system to its previously functional state. 
13.	void* threadexecute() – entry method for the threads to start their execution
14.	void markpoint_announce(int ctid) – announces the markpoint for the particular transaction
15.	int check_marked(int ctid,int cdataid) - checks if a transaction is marked or not


		
		
	
