#ifndef ETSE_FUNCTIONS_H
#define ETSE_FUNCTIONS_H

#define NAME_LENGTH 25
#define MARKS_COUNT 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

typedef struct birthday
{
    int day;
    int month;
    int year;
} BIRTHDAY;

typedef struct student
{
    char m_szSurname[NAME_LENGTH];
    char m_szName[NAME_LENGTH];
    BIRTHDAY date;
    int m_iMarks[MARKS_COUNT];
    float m_fAverageMark;
    struct student *m_pNext;
} SSTUDENT;

typedef struct list
{
    SSTUDENT *m_pHead;
    unsigned short m_usMaxNameLength;
    unsigned short m_usMaxSurnameLength;
    float m_fAverageMark;
}SLIST;

enum {SURNAME, NAME, DAY, MONTH, YEAR, MARK_0, MARK_1, MARK_2, MARK_3, MARK_4};

SLIST* addStudent(SLIST** ppHead);
SLIST* deleteStudentBySurname(SLIST** ppList, char* pszSurname);
SLIST* deleteStudentsLessThenAverage(SLIST** ppList);
SLIST* displayTwoTheSmartestStudents(SLIST** ppList);
SSTUDENT* sortStudentsBySurname(SSTUDENT** ppHead);
void showStudentsOnScreen(SLIST* pList);
void saveStudentsToFile(SLIST* pList);
void readStudentsFromFile(SLIST** ppList);
void freeStudentsList(SLIST** ppList);


#endif //ETSE_FUNCTIONS_H