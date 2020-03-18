#ifndef ETSE_FUNCTIONS_H
#define ETSE_FUNCTIONS_H

//Max length of name and surname
#define NAME_LENGTH 25

//The total number of marks
#define MARKS_COUNT 5

//Length of table's head without name and surname(they are variable)
#define HEAD_LENGTH 34

//Length of path to the input ir output file
#define PATH_LENGTH 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

typedef struct student
{
    char m_szSurname[NAME_LENGTH];
    char m_szName[NAME_LENGTH];
    int m_iDay;
    int m_iMonth;
    int m_iYear;
    int m_iMarks[MARKS_COUNT];
    float m_fAverageMark;
    struct student* m_pNext;
} SSTUDENT;

typedef struct list
{
    SSTUDENT* m_pHead;
    unsigned short m_usMaxNameLength;
    unsigned short m_usMaxSurnameLength;
    float m_fAverageMark;
} SLIST;

enum {SURNAME, NAME, DAY, MONTH, YEAR, MARK_0, MARK_1, MARK_2, MARK_3, MARK_4};

//Add new student to StudentsList
SLIST* addStudent(SLIST** ppHead);

//Delete student from StudentsList by surname
SLIST* deleteStudentBySurname(SLIST** ppList, char* pszSurname);

//Delete students from StudentsList with average mark less then group's average mark
SLIST* deleteStudentsLessThenAverage(SLIST** ppList);

//Show on screen two student with highest average mark in group
SLIST* displayTwoTheSmartestStudents(SLIST** ppList);

//Sort StudentsList by surnames
SSTUDENT* sortStudentsBySurname(SSTUDENT** ppHead);

//Show StudentsList on Screen
void showStudentsOnScreen(SLIST* pList);

//Save StudentList to file (.txt)
void saveStudentsToFile(SLIST* pList);

//Load StudentList from input.txt
void readStudentsFromFile(SLIST** ppList);

//Free memory allocated for StudentsList
void freeStudentsList(SLIST** ppList);


#endif //ETSE_FUNCTIONS_H