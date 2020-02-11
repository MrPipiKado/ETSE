#ifndef ETSE_FUNCTIONS_H
#define ETSE_FUNCTIONS_H

#define NAME_LENGTH 10
#define MARKS_COUNT 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct list
{
    STUDENT *head;
    float avg_mark;
}LIST;

enum {SURNAME, NAME, DAY, MONTH, YEAR, MARK_0, MARK_1, MARK_2, MARK_3, MARK_4};

int check_input(char* input);
STUDENT* create_list(char *input);
LIST* add_student(LIST **head);
LIST* delete_by_surname(LIST **list, char *surname);
LIST* delete_less_then_avg(LIST **list);
STUDENT* sort_by_surname(STUDENT **head);
void print_students(LIST *list);
void free_list(LIST **list);


#endif //ETSE_FUNCTIONS_H