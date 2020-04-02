#include "header.h"
#include <string.h>

//For count quantity of students
int static iCount = 0;

//--------------------------------------------------------------------------------
int GetStudentInfo(Node** pStudent, FILE* ptr, Node* pHead)
{
	++iCount;
	*pStudent = (Node*)malloc(sizeof(Node));

	if (!(*pStudent))
	{
		DeleteList(pHead);
		perror("Error ");
		exit(EXIT_FAILURE);
	}

	if ((fscanf(ptr, " %s %s", (*pStudent)->Student.szSurname,(*pStudent)->Student.szName)) != 2 )
	{
		free(*pStudent);
		return 0;
	}
	if ((fscanf(ptr, " %d.%d.%d", &((*pStudent)->Student.iDay),
		&((*pStudent)->Student.iMonth),
		&((*pStudent)->Student.iYear)) != 3) || !(Is_Correct_Data((*pStudent)->Student.iDay,
		(*pStudent)->Student.iMonth)))
	{
		printf("Incorect entered data,in %d student,in input data file\n",iCount);
		DeleteList(pHead);
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < SUBJECT; ++i)

		if (fscanf(ptr, " %i", &((*pStudent)->Student.iMarks[i])) != 1 ||
			!(Is_Correct_Mark((*pStudent)->Student.iMarks[i])))
		{
			printf("Incorect entered marks,in %d student,in input data file\n", iCount);
			DeleteList(pHead);
			exit(EXIT_FAILURE);
		}

	(*pStudent)->pNext = NULL;

	return 1;
}

//--------------------------------------------------------------------------------

void AddStudentToList(Node* pStudent, Node** pHead)
{
	Node* pPrevious, * pCurrent;
	pCurrent = pPrevious = *pHead;

	while (pCurrent && (strcmp(pStudent->Student.szSurname,
		pCurrent->Student.szSurname) > 0))
	{
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;

	}

	if (pCurrent == *pHead) // the beggining of list
	{
		pStudent->pNext = *pHead;
		*pHead = pStudent;
	}

	else if (pCurrent)
	{
		pStudent->pNext = pCurrent;
		pPrevious->pNext = pStudent;
	}

	else //end of list
	{
		pPrevious->pNext = pStudent;
		pStudent->pNext = NULL;
	}
}

//--------------------------------------------------------------------------------

int Is_File_Empty(const Node* pHead)
{
	if (pHead)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Is_Correct_Mark(int iMark)
{
	if (iMark < 2 || iMark > 5)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}

int Is_Correct_Data(int iDay, int iMonth)
{
	if (iDay < 0 || iDay > 31 || iMonth < 0 || iMonth > 12)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//--------------------------------------------------------------------------------

void PrintAllStudents(const Node* pStudent)
{
	if (!pStudent)
	{
		printf("The list is empty!!!\n");
		return;
	}

	do
	{
		printf("%-12s %-12s %02i.%02i.%02i",
			pStudent->Student.szSurname,
			pStudent->Student.szName,
			pStudent->Student.iDay,
			pStudent->Student.iMonth,
			pStudent->Student.iYear);

		for (size_t i = 0; i < SUBJECT; ++i)
			printf("%2i", pStudent->Student.iMarks[i]);
		printf("\n");
		pStudent = pStudent->pNext;
	} while (pStudent);
}

//--------------------------------------------------------------------------------

void PrintStudentsBornedInAutumn(const Node* pHead)
{
	Node* pStudent = pHead;

	printf("\n\t\tThe list of students borned in Autumn:\n\n");

	while (pStudent)
	{
		int iResult = pStudent->Student.iMonth;
		if (iResult < 12 && iResult > 8)
		{
			printf("%-12s %-12s %02i.%02i.%02i",
				pStudent->Student.szSurname,
				pStudent->Student.szName,
				pStudent->Student.iDay,
				pStudent->Student.iMonth,
				pStudent->Student.iYear);

			for (int i = 0; i < SUBJECT; ++i)
				printf("%2i", pStudent->Student.iMarks[i]);
			printf("\n");
		}
		pStudent = pStudent->pNext;
	}
}
//--------------------------------------------------------------------------------

int CompareMarks(const int aMarks[])
{
	const int aiAllMark[] = { 2, 3, 4, 5 };
	size_t iSize = sizeof(aiAllMark) / sizeof(int);

	for (size_t i = 0; i < iSize; ++i)
	{
		int iExist = 0;

		for (size_t j = 0; j < SUBJECT; ++j)
		{
			if (aiAllMark[i] == aMarks[j])
			{
				iExist = 1;
				break;
			}
		}

		if (!iExist)
		{
			return 0;
		}
	}
	return 1;
}

//--------------------------------------------------------------------------------

void DeleteList(Node* pHead)
{
	if (!pHead)
	{
		return;
	}

	Node* pTemp = NULL;

	while (pHead)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		free(pTemp);
	}
}

//--------------------------------------------------------------------------------

void DeleteStudents(Node** pHead)
{
	printf("\n\t\tList without students who received 2,3,4,5 after the session:\n\n");

	if (!(*pHead))
	{
		printf("The list is empty!!!\n");
		return;
	}

	Node* pPrivious, * pCurrent, * pTemp = NULL;
	pPrivious = pCurrent = *pHead;

	while (1)
	{
		while (pCurrent && !(CompareMarks(pCurrent->Student.iMarks)))
		{
			pPrivious = pCurrent;
			pCurrent = pCurrent->pNext;
		}

		if (pCurrent == *pHead)
		{
			if (!(*pHead))
			{
				return;
			}

			*pHead = pCurrent->pNext;
			free(pCurrent);
			pCurrent = (*pHead);
		}

		else if (!pCurrent)
		{
			return;
		}

		else
		{
			pPrivious->pNext = pCurrent->pNext;
			pTemp = pCurrent;
			free(pTemp);
			pCurrent = pPrivious->pNext;
		}
	}
}

//--------------------------------------------------------------------------------