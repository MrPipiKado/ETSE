#ifndef ETSE_FUNCTIONS_H
#define ETSE_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 10
#define MARKS_COUNT 5

typedef struct birthday
{
    int day;
    int month;
    int year;
} BIRTHDAY;

typedef struct student
{
    char surname[NAME_LENGTH];
    char name[NAME_LENGTH];
    BIRTHDAY date;
    int marks[MARKS_COUNT];
    struct student *next;
} STUDENT;

enum {SURNAME, NAME, DAY, MONTH, YEAR, MARK_0, MARK_1, MARK_2, MARK_3, MARK_4};

int check_input(char* input);
STUDENT* create_list(char *input);
STUDENT* add_student(STUDENT *head);
STUDENT* delete_by_surname(STUDENT *head, char *surname);
STUDENT* sort_by_surname(STUDENT **head);
void print_students(STUDENT *head);
void free_list(STUDENT *head);


#endif //ETSE_FUNCTIONS_H
