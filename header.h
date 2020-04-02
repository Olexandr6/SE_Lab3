#pragma once

#include <stdio.h>
#include <stdlib.h>

//Max length of Name,Surname
#define SIZE 32
//Number of academic subjects
#define SUBJECT 7

typedef struct student
{
	char szName[SIZE];
	char szSurname[SIZE];
	int iDay;
	int iMonth;
	int iYear;
	int iMarks[SUBJECT];
}SStudent;

typedef struct node
{
	SStudent Student;
	struct  node* pNext;
}Node;

//Returns 1 if  students info has been successfully read,else returns 0
int GetStudentInfo(Node** pStudent, FILE* ptr, Node* pHead);

//Add students to the sorted list by Surname
void AddStudentToList(Node* pStudent, Node** pHead);

//Checks is the File empty,returns 1 if it does ,0 if doesn't
int Is_File_Empty(const Node* pHead);

//Checks is the Mark corect,returns 1 if it does ,0 if doesn't
int Is_Correct_Mark(int iMark);

//Checks is the Bithday data corect,returns 1 if it does ,0 if doesn't
int Is_Correct_Data(int iDay,int iMonth);

//Print all students from file 
void PrintAllStudents(const Node* pHead);

void PrintStudentsBornedInAutumn(const Node* pHead);

//Returns 1 if student has such Marks: 2,3,4,5 ,else returns 0
int CompareMarks(const int aMarks[]);

//Delete Students whith such marks: 2,3,4,5
void DeleteStudents(Node** pHead);

//Free a memory allocated to list
void DeleteList(Node* pHead);
