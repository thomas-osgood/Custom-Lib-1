/*
 * Created By : Thomas Osgood
 * Date Created : 2015 11 18 
 *
 * Thomas Osgood's Custom Library C File.
 *
 * Note :
 * Must attempt to organize functions in both
 * this file and the H file.
 * The most user-friendly method would be 
 * organizing them by alphabet.
 * Can also organize them by their return types.
 */

#include "ozlib.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * Display User Information Function
 *
 * Function to display user information.
 * Prints information to standard output.
 *
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * To Call : DispUserInfo();
 */
void DispUserInfo(void) {
	/* Initialize Local Variables */
	char uname[40];
	int retVal = 0;
	char c = '-';
	int amt = 20;

	/* Get Name Of User Logged In */
	retVal = getlogin_r(uname,40);

	/* Display User Information */
	printf("\n\tUser Information :\n\t");
	PrintChar(c,amt);
	printf("\n\tUsername = %s\n\n",uname);
}


/*
 * Print Character Function
 *
 * Function that prints a specified amount
 * of a designated character to stdout.
 *
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * To Call : PrintChar(_charVar, _intVar);
 */
void PrintChar(const char c, const int amt) {
	int i = 0;
	for (i=0;i<amt;i++)
		printf("%c",c);
}


/*
 * Write To File Function
 * 
 * Writes information to a specified file.
 * Uses the system calls 'open' and 'write'.
 * 
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * To Call : _var = Write2File(filename);
 *
 */
int Write2File(const char *f) {
	/* Initialize Local Variables */
	char input[] = "This is the input to the testfile.";
	//int ssize = (sizeof(input) / sizeof(char)) - sizeof(char);
	int ssize = NUMELEMS(input) - sizeof(input[0]);

	/* Attempt To Open. Return Error If Unsuccessful */
	int fd = open(f, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0) {
		printf("\n\t[!] There was an error opening the file ( %s )\n\n",f);
		return 1;
	}

	/* Attempt To Write. Return Error If Not All Bytes Written */
	if (write(fd,input,ssize) != ssize) {
		close(fd);
		printf("\n\t\a[!] There was an error writing to the file ( %s )\n\n",f);
		return 1;
	}

	/* Report Successful Write To User */
	printf("\n\t>>> Information Written To %s <<<\n",f);


	/* Close File, Return Success */
	close(fd);
	return 0;
}


/*
 * Display File Information Function
 *
 * This function takes a file and displays
 * the file size, number of links, and inodes.
 *
 * Also works with directories.
 *
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * To Call : _var = DispFileInfo(filename);
 */
int DispFileInfo(const char *f) {
	/* Initialize Local Variables */
	struct stat filestat;
	int fsize = 0;
	int nlinks = 0;
	int inodes = 0;

	/* Error Checking */
	if (stat(f,&filestat) < 0) {
		printf("\n[!] Error Getting File Information ( %s )\n\n",f);
		return 1;
	}

	/* Set Variables */
	fsize = filestat.st_size;
	nlinks = filestat.st_nlink;
	inodes = filestat.st_ino;

	/* Display Information */
	printf("\n\tFile Name : %s",f);
	printf("\n\tFile Size : %d bytes [ %d bits ]\n",fsize,BYTE2BIT(fsize));
	printf("\tNumber Of Links : %d links\n",nlinks);
	printf("\tFile Inode : %d\n",inodes);

	/* Return Success */
	return 0;
}


/*
 * Log Variables Function
 *
 * Function to log current state of variables.
 *
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * To Call :
 *	_var = LogVars(variableArray, numberOfElements);
 */
int LogVars(const int *varArr, const int numElems) {
	/* Initialize Local Variables */
	const char logname[] = "variables.txt";
	int buffsize = sizeof(varArr)/sizeof(varArr[0]);
	char logtxt[buffsize];
	int i = 0;

	/* Attempt To Open. Return Error If Unsuccessful */
	int fd = open(logname, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0) {
		printf("\n\t[!] There was an error opening the file ( %s )\n\n",logname);
		return 1;
	}

	/* Loop Over Variable Array, Print Values To Log */
	for (i=0;i<numElems;i++) {

		/* Format Data, Store In Variable */
		sprintf(logtxt,"%d\n",varArr[i]);

		/* Attempt To Write. Return Error If Not All Bytes Written */
		if (write(fd,logtxt,sizeof(logtxt)) != sizeof(logtxt)) {
			close(fd);
			printf("\n\t\a[!] There was an error writing to the file ( %s )\n\n",logname);
			return 1;
		}

		/* Report Successful Write To User */
		printf("\n\t>>> Variable %d Information Written To %s <<<",i+1,logname);
	}
	printf("\n");


	/* Close File. Return Success. */
	close(fd);	
	return 0;
}


/*
 * System Message Function
 *
 * Function that displays a message in a 
 * specific format ("\n>>> MSG <<<\n")
 *
 * Not an actual system message.
 *
 * Used by Thomas Osgood to display important
 * information while debugging.
 *
 * Known Bugs :
 *	(1) None
 *
 * Fixes :
 *	(1) None
 *
 * Improvement Ideas :
 *	(1) Add Argument To Allow For Feeding To File
 *	(2) Change 'printf' to 'write' 
 * 
 * To Call : SysMsg(stringMessage);
 */
void SysMsg(const char *str) {
	printf("\n>>> %s <<<\n",str);
}
