#include "header.h"

int main(void)
{
	Node* pHead, * pStudent;
	pHead = NULL;

	FILE* pFin, * pFout;
	pFin = fopen("InputData.txt", "r");
	if (!pFin)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}

	while (GetStudentInfo(&pStudent, pFin, pHead))
	{
		if (!pHead)
			pHead = pStudent;
		else
			AddStudentToList(pStudent, &pHead);
	}

	if (!Is_File_Empty(pHead))
	{
		printf("The File: InputData.txt  is empty!\n");
		fclose(pFin);
		return 0;
	}

	printf("Do you wanna print the list in Consol or File?\n");
	printf("So, your choise(0 - File,other - Consol):\n");
	int iChoise;
	scanf(" %d", &iChoise);
	if (!iChoise)
	{
		printf("You can see result list in file: OutputData.txt\n");

		 pFout = freopen("OutputData.txt", "w", stdout);
		if (!pFout)
		{
			perror("Error ");
			fclose(pFin);
			DeleteList(pHead);
			exit(EXIT_FAILURE);
		}
	}


	printf("\n\t\tList of all students:\n\n");
	PrintAllStudents(pHead);
	PrintStudentsBornedInAutumn(pHead);

	DeleteStudents(&pHead);

	PrintAllStudents(pHead);

	fclose(pFin);
	if(!iChoise) { fclose(pFout); }
	
	DeleteList(pHead);

	return 0;
}