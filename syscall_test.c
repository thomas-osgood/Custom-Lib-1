/*
 * Created By : Thomas Osgood
 * Date Created : 2015 11 16
 *
 * Purpose :
 *	- Practice C Programming
 *	- Practice Kernel Calls In C
 *	- Practice Creating Custom Header Files
 *
 * Requirements :
 *	(1) ozlib.h
 *
 * To Compile :
 *	gcc -o program_name syscall_test.c ozlib.c
 *
 * Known Bugs :
 *	(1) Must Run As SuperUser
 *
 * Fixes :
 *	(1) Call Using 'sudo ./compiledName' Or Call From SuperUser Terminal
 */

#include <stdio.h>
#include <string.h>
#include "ozlib.h"

/* Defines */

/* Global Variables */
const char testfile[] = "file1.txt";

/* Function Prototypes */

/* Main Function */
int main(void) {
	/* Initialize Local Variables */
	int bytes = 0;
	int bits = 0;
	int flags[3] = {5,5,5};
	int allgood[3] = {0,0,0};
	int i = 0;
	int arrsize = 0;
	int varArr[] = {flags[0], flags[1], bytes,bits,i};
	int memcmpSize = 0;
	int badFncs = 0;

	bytes = 1;
	bits = BYTE2BIT(bytes); /* BYTE2BIT() Test */

	printf("\n\t%d bytes = %d bits\n\n",bytes,bits); /* BYTE2BIT() Test Display */
	flags[0] = Write2File(testfile); /* Assign Write2File Return As Flag 0 */
	flags[1] = DispFileInfo(testfile); /* Assign DispFileInfo Return As Flag 1 */

	/* Assign Values To VarArr Indexes */
	varArr[0] = flags[0];
	varArr[1] = flags[1];
	varArr[2] = bytes;
	varArr[3] = bits;
	varArr[4] = i;

	/* Assign LogVars Return As Flag 2 */
	flags[2] = LogVars(varArr,NUMELEMS(varArr)); 

	/* Display User Information (Call Function) */
	DispUserInfo();

	/* Display Final Flag Values (Aids Debug) */
	printf("\tFlags : ");
	arrsize = sizeof(flags) / sizeof(int);
	for (i=0;i<arrsize;i++)
		printf("%d",flags[i]);
	printf("\n\n");

	/* Check Flag Values And Report To User */
	memcmpSize = NUMELEMS(flags);
	if (!memcmp(flags,allgood,memcmpSize))
		printf("\t\t[+] All Functions Successful\n");
	else {
		if (flags[0] != 0) {
			printf("\t\t[!] Error Occurred In Write2File Function\n");
			badFncs++;
		}

		if (flags[1] != 0) {
			printf("\t\t[!] Error Occurred In DispFileInfo Function\n");
			badFncs++;
		}

		if (flags[2] != 0) {
			printf("\t\t[!] Error Occurred In LogVars Function\n");
			badFncs++;
		}
	}
	printf("\n\t>>> %d Functions Returned An Error <<<\n",badFncs);
	printf("\n");

	/* SysMsg Function Call */
	SysMsg("This Is A Test Of SysMsg");

	printf("\n");

	/* Exit Cleanly */
	return 0;
}

/* Sub-Functions */




