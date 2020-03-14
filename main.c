#include "functions.h"


int main()
{
    SLIST *pStudentsList = (SLIST*)malloc(sizeof(SLIST));
    pStudentsList->m_pHead = NULL;
    pStudentsList->m_fAverageMark = 0.0f;
    pStudentsList->m_usMaxNameLength = 0;
    pStudentsList->m_usMaxSurnameLength = 0;
    int iOption = 0, iSorted = 1;
    char surname[NAME_LENGTH];
    showStudentsOnScreen(pStudentsList);
    do
    {

        printf("Choose option:\n"
               "1 - Sort\n"
               "2 - Delete student by surname\n"
               "3 - Delete students with  less then avarage mark\n"
               "4 - Add student\n"
               "5 - Display two the smartest\n"
               "6 - Read from file\n"
               "7 - Write to file\n"
               "0 - Exit\n");
        iOption = get_int("Option:");
        if(!iOption)break;
        if(iOption == 1)
            if(iSorted)
            {
                sortStudentsBySurname(&(pStudentsList->m_pHead));
                iSorted = 0;
            }
        if(iOption == 2)
        {
            printf("Enter surname:");
            scanf("%s", surname);
            deleteStudentBySurname(&pStudentsList, surname);
        }
        if(iOption == 3)
        {
            deleteStudentsLessThenAverage(&pStudentsList);
        }
        if(iOption == 4)
        {
            addStudent(&pStudentsList);
        }
        if(iOption == 5)
        {
            displayTwoTheSmartestStudents(&pStudentsList);
        }
        if(iOption == 6)
        {
            readStudentsFromFile(&pStudentsList);
        }
        if(iOption == 7)
        {
            saveStudentsToFile(pStudentsList);
        }
        showStudentsOnScreen(pStudentsList);
    }while(1);
    freeStudentsList(&pStudentsList);

    return 0;
}