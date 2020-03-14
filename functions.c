#include "functions.h"

static int getListSize(SLIST* pList)
{
    int count = 0;
    if(!pList)
    {
        fprintf(stderr, "List is empty\n");
        return -1;
    }
    SSTUDENT *p = pList->m_pHead;
    while(p)
    {
        ++count;
        p = p->m_pNext;
    }
    return count;
}

static void changeFieldsLength(SLIST** pList, SSTUDENT* pStudent)
{
    if(strlen(pStudent->m_szName) > (*pList)->m_usMaxNameLength)
        (*pList)->m_usMaxNameLength = strlen(pStudent->m_szName);
    if(strlen(pStudent->m_szSurname) > (*pList)->m_usMaxSurnameLength)
        (*pList)->m_usMaxSurnameLength = strlen(pStudent->m_szSurname);
}


static SLIST* calculateAverageMarkInList(SLIST** pList)
{
    SSTUDENT *p = (*pList)->m_pHead;
    int count = 0;
    float sum = 0.0f;
    if(!p)
    {
        fprintf(stderr, "List is empty\n");
        return *pList;
    }
    while(p)
    {
        ++count;
        sum+=p->m_fAverageMark;
        p = p->m_pNext;
    }
    (*pList)->m_fAverageMark = sum / (float)count;
    return *pList;
}

static SSTUDENT* calculateAverageMarkOfStudent(SSTUDENT** ppStudent)
{
    float sum = 0.0f;
    for (int i = 0; i<MARKS_COUNT; ++i)
    {
        sum+=(float)((*ppStudent)->m_iMarks[i]);
    }
    (*ppStudent)->m_fAverageMark = sum / MARKS_COUNT;
    return *ppStudent;
}

static SSTUDENT* getPreviousStudent(SSTUDENT* pHead, SSTUDENT* pCurrent)
{
    if(pCurrent == pHead)
        return NULL;
    else
    {
        SSTUDENT *p;
        for(p = pHead; p->m_pNext != pCurrent; p = p->m_pNext);
        return p;
    }
}

static int printLineOnScreen(char ch, int iCount)
{
    while(iCount)
    {
        fprintf(stdout, "%c", ch);
        iCount--;
    }
    fprintf(stdout, "\n");
    return 0;
}

static int printHeadOfTableOnScreen(int iSurnameLength, int iNameLength)
{
    printLineOnScreen('_', iSurnameLength + iNameLength
                           + 3 + 3 + 5 + 5 + 7 + 11);

    fprintf(stdout, "|SURNAME");
    for(int i=7; i < iSurnameLength; ++i)
        fprintf(stdout, " ");
    fprintf(stdout, "| ");
    fprintf(stdout, "|NAME");
    for(int i=4; i < iNameLength; ++i)
        fprintf(stdout, " ");
    fprintf(stdout, "| ");
    fprintf(stdout, "|DT| ");
    fprintf(stdout, "|MN| ");
    fprintf(stdout, "|YEAR| ");
    fprintf(stdout, "|  MARKS  |\n");
    printLineOnScreen('_', iSurnameLength + iNameLength
                           + 3 + 3 + 5 + 5 + 7 + 11);
    return 0;
}

SSTUDENT* sortStudentsBySurname(SSTUDENT** ppHead)
{
    if(!(*ppHead))
    {
        fprintf(stderr, "List is empty\n");
        return *ppHead;
    }
    SSTUDENT *p1 ,*p2 , *pp1 , *pp2 , *tmp ;
    for(p1=*ppHead; p1->m_pNext; p1=p1->m_pNext )
    {
        for(p2=p1->m_pNext; p2 ; p2=p2->m_pNext)
        {
            pp1= getPreviousStudent(*ppHead, p1);
            pp2= getPreviousStudent(*ppHead, p2);
            if(strcmp(p1->m_szSurname, p2->m_szSurname) > 0)
            {
                if(p1->m_pNext == p2)
                {
                    tmp = p2->m_pNext;
                    p2->m_pNext = p1;
                    p1->m_pNext = tmp;
                }
                else
                {
                    tmp = p2->m_pNext;
                    p2->m_pNext = p1->m_pNext;
                    p1->m_pNext = tmp;
                    pp2->m_pNext = p1;
                }
                if(!pp1)
                    *ppHead = p2;
                else
                    pp1->m_pNext = p2;
                tmp = p1;
                p1 = p2;
                p2 = tmp;
            }
        }
    }
    return *ppHead;
}

SLIST* deleteStudentBySurname(SLIST** ppList, char* pszSurname)
{
    SSTUDENT *p = (*ppList)->m_pHead, *pp = NULL;
    if(!(p))
    {
        fprintf(stderr, "List is empty\n");
        return *ppList;
    }
    if(!strcmp(((*ppList)->m_pHead)->m_szSurname, pszSurname))
    {
        (*ppList)->m_pHead = p->m_pNext;
        free(p);
        calculateAverageMarkInList(ppList);
        return *ppList;
    }
    p = (*ppList)->m_pHead;
    while(p)
    {
        if(!strcmp(((*ppList)->m_pHead)->m_szSurname, pszSurname))
        {
            pp = getPreviousStudent((*ppList)->m_pHead, p);
            pp->m_pNext = p->m_pNext;
            free(p);
            calculateAverageMarkInList(ppList);
            return *ppList;
        }
        p = p->m_pNext;
    }
    fprintf(stdout, "Can not find %s", pszSurname);
    return *ppList;
}

SLIST* addStudent(SLIST** ppHead)
{
    SSTUDENT *p_end;
    if(!((*ppHead)->m_pHead))
    {
        p_end = (SSTUDENT*)malloc(sizeof(SSTUDENT));
        (*ppHead)->m_pHead = p_end;
    }
    else
    {
        for (p_end = (*ppHead)->m_pHead; p_end->m_pNext != NULL; p_end = p_end->m_pNext);
        p_end->m_pNext = (SSTUDENT *) malloc(sizeof(SSTUDENT));
        p_end = p_end->m_pNext;
    }
    if(!(p_end))
    {
        fprintf(stderr, "Can not allocate so much memory");
        return *ppHead;
    }
    int ok = 0;
    int j = 0;
    while (1)
    {
        switch (j)
        {
            case SURNAME:
                while(!ok)
                {
                    ok = 1;
                    fprintf(stdout, "Enter m_szSurname:");
                    scanf("%s", p_end->m_szSurname);
                    for(int i = 0; p_end->m_szSurname[i] != '\0'; ++i)
                    {
                        if(!isalpha(p_end->m_szSurname[i]))
                            ok = 0;
                    }
                }
                ok = 0;
                break;
            case NAME:
                while(!ok)
                {
                    ok = 1;
                    fprintf(stdout, "Enter m_szName:");
                    scanf("%s", p_end->m_szName);
                    for(int i = 0; p_end->m_szName[i] != '\0'; ++i)
                    {
                        if(!isalpha(p_end->m_szName[i]))
                            ok = 0;
                    }
                }
                getchar();
                break;
            case DAY:
                do
                {
                    p_end->date.day = get_int("Enter day of birth:");
                }while(p_end->date.day <0 || p_end->date.day>31);
                break;
            case MONTH:
                do
                {
                    p_end->date.month = get_int("Enter month of birth:");
                }while(p_end->date.month <0 || p_end->date.month>12);
                break;
            case YEAR:
                do
                {
                    p_end->date.year = get_int("Enter year of birth:");
                }while(p_end->date.year <1900 || p_end->date.year>2020);
                break;
            case MARK_0:
                do
                {
                    p_end->m_iMarks[0] = get_int("Enter first mark:");
                }while(p_end->m_iMarks[0] < 0 || p_end->m_iMarks[0] > 5);
                break;
            case MARK_1:
                do
                {
                    p_end->m_iMarks[1] = get_int("Enter second mark:");
                }while(p_end->m_iMarks[1] < 0 || p_end->m_iMarks[1] > 5);
                break;
            case MARK_2:
                do
                {
                    p_end->m_iMarks[2] = get_int("Enter third mark:");
                }while(p_end->m_iMarks[2] < 0 || p_end->m_iMarks[2] > 5);
                break;
            case MARK_3:
                do
                {
                    p_end->m_iMarks[3] = get_int("Enter fourth mark:");
                }while(p_end->m_iMarks[3] < 0 || p_end->m_iMarks[3] > 5);
                break;
            case MARK_4:
                do
                {
                    p_end->m_iMarks[4] = get_int("Enter fifth mark:");
                }while(p_end->m_iMarks[4] < 0 || p_end->m_iMarks[4] > 5);
                break;
            default:
                fprintf(stdout, "Done.\n");
        }
        j++;
        if(j>MARK_4)break;
    }
    calculateAverageMarkOfStudent(&p_end);
    sortStudentsBySurname(&((*ppHead)->m_pHead));
    calculateAverageMarkInList(ppHead);
    changeFieldsLength(ppHead, p_end);
    fprintf(stdout, "Added)\n");
    return *ppHead;
}

void showStudentsOnScreen(SLIST* pList)
{
    if(!(pList->m_pHead))
    {
        fprintf(stderr, "List is empty\n");
        return;
    }
    SSTUDENT *p = pList->m_pHead;
    printHeadOfTableOnScreen(pList->m_usMaxSurnameLength, pList->m_usMaxNameLength);
    while (p)
    {
        fprintf(stdout, "|");
        fprintf(stdout, "%-*s", pList->m_usMaxSurnameLength, p->m_szSurname);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-*s", pList->m_usMaxNameLength, p->m_szName);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", p->date.day);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", p->date.month);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-4d", p->date.year);
        fprintf(stdout, "| |");
        for(int k=0; k<MARKS_COUNT; ++k)
        {
            fprintf(stdout, "%1d", p->m_iMarks[k]);
            fprintf(stdout, "|");
        }
        fprintf(stdout, "\n");
        p = p->m_pNext;
    }
    printf("\n");
}

void saveStudentsToFile(SLIST* pList)
{
    fprintf(stdout, "Enter full path to file");
    char file_name[100];
    scanf("%s", file_name);
    FILE *file = fopen(file_name, "wt");
    if(!file)
    {
        fprintf(stderr, "Can not open file\n");
        return;
    }
    else
    {
        SSTUDENT *p = pList->m_pHead;
        int n = pList->m_usMaxSurnameLength + pList->m_usMaxNameLength + 3 + 3 + 5 + 5 + 7 + 11;
        while(n)
        {
            fprintf(file, "%c", '_');
            n--;
        }
        fprintf(file, "\n");

        fprintf(file, "|SURNAME");
        for(int i=7; i < pList->m_usMaxSurnameLength; ++i)
            fprintf(file, " ");
        fprintf(file, "| ");
        fprintf(file, "|NAME");
        for(int i=4; i < pList->m_usMaxNameLength; ++i)
            fprintf(file, " ");
        fprintf(file, "| ");
        fprintf(file, "|DT| ");
        fprintf(file, "|MN| ");
        fprintf(file, "|YEAR| ");
        fprintf(file, "|  MARKS  |\n");

        n = pList->m_usMaxSurnameLength + pList->m_usMaxNameLength + 3 + 3 + 5 + 5 + 7 + 11;
        while(n)
        {
            fprintf(file, "%c", '_');
            n--;
        }
        fprintf(file, "\n");
        while (p)
        {
            fprintf(file, "|");
            fprintf(file, "%-*s", pList->m_usMaxSurnameLength, p->m_szSurname);
            fprintf(file, "| |");
            fprintf(file, "%-*s", pList->m_usMaxNameLength, p->m_szName);
            fprintf(file, "| |");
            fprintf(file, "%02d", p->date.day);
            fprintf(file, "| |");
            fprintf(file, "%02d", p->date.month);
            fprintf(file, "| |");
            fprintf(file, "%-4d", p->date.year);
            fprintf(file, "| |");
            for(int k=0; k<MARKS_COUNT; ++k)
            {
                fprintf(file, "%1d", p->m_iMarks[k]);
                fprintf(file, "|");
            }
            fprintf(file, "\n");
            p = p->m_pNext;
        }
    }
}

SLIST* deleteStudentsLessThenAverage(SLIST** ppList)
{
    if(!((*ppList)->m_pHead))
    {
        fprintf(stderr, "List is empty\n");
        return *ppList;
    }
    SSTUDENT *p = (*ppList)->m_pHead, *pp = NULL;
    float sum;
    while(p)
    {
        sum = 0.0f;
        for(int i = 0; i<MARKS_COUNT; ++i)
        {
            sum += (float)p->m_iMarks[i];
        }
        sum/=MARKS_COUNT;
        if(sum<(*ppList)->m_fAverageMark)
        {
            pp = getPreviousStudent((*ppList)->m_pHead, p);
            pp->m_pNext = p->m_pNext;
            free(p);
            p=pp;
        }
        p = p->m_pNext;
    }
    calculateAverageMarkInList(ppList);
    return *ppList;
}

SLIST* displayTwoTheSmartestStudents(SLIST** ppList)
{

    if(getListSize(*ppList) < 3)
    {
        showStudentsOnScreen(*ppList);
        return *ppList;
    }
    SSTUDENT *max_avg_1 = (*ppList)->m_pHead, *max_avg_2 = max_avg_1->m_pNext;
    SSTUDENT *p = max_avg_2->m_pNext;

    while(p)
    {
        if(p->m_fAverageMark > max_avg_1->m_fAverageMark)
        {
            max_avg_1 = p;
        }
        p = p->m_pNext;
    }
    p = (*ppList)->m_pHead;
    while(p)
    {
        if(p->m_fAverageMark > max_avg_2->m_fAverageMark && p != max_avg_1)
        {
            max_avg_2 = p;
        }
        p = p->m_pNext;
    }
    SSTUDENT *pp1 = (SSTUDENT*)malloc(sizeof(SSTUDENT));
    SSTUDENT *pp2 = (SSTUDENT*)malloc(sizeof(SSTUDENT));
    *pp1 = *max_avg_1;
    *pp2 = *max_avg_2;
    pp1->m_pNext = pp2;
    pp2->m_pNext = NULL;
    SLIST *list1 = (SLIST*)malloc(sizeof(SLIST));
    list1->m_pHead=pp1;
    list1->m_usMaxNameLength = 0;
    list1->m_usMaxSurnameLength = 0;
    changeFieldsLength(&list1, pp1);
    changeFieldsLength(&list1, pp2);
    showStudentsOnScreen(list1);
    freeStudentsList(&list1);
    return *ppList;
}

void readStudentsFromFile(SLIST** ppList)
{
    char ch;
    char path[100];
    SSTUDENT*p;

    fprintf(stdout, "Do you want to read from default file?(y/n):\n");
    fscanf(stdin,"%c", &ch);
    if (ch == 'n')
    {
        fprintf(stdout, "Enter full path to file:");
        scanf("%s", path);
    }
    else
    {
        strcpy(path, "/home/user/Desktop/ETSE/input.txt");
    }
    FILE *input = fopen(path, "rt");
    if (input == NULL)
    {
        fprintf(stderr, "Cant open file\n");
        return;
    }

    SLIST *temp = NULL;

    while (!feof(input))
    {
        SSTUDENT *new_st = (SSTUDENT *) malloc(sizeof(SSTUDENT));
        if (!new_st) {
            fprintf(stderr, "can not allocate \n");
            return;
        }
        fscanf(input, "%s %s", new_st->m_szSurname, new_st->m_szName);
        fscanf(input, "%d.%d.%d", &(new_st->date.day), &(new_st->date.month), &(new_st->date.year));
        fscanf(input, "%d %d %d %d %d", new_st->m_iMarks, new_st->m_iMarks + 1,
               new_st->m_iMarks + 2, new_st->m_iMarks + 3, new_st->m_iMarks + 4);
        new_st->m_pNext = NULL;
        calculateAverageMarkOfStudent(&new_st);
        if(!((*ppList)->m_pHead))
        {
            (*ppList)->m_pHead = new_st;
        }
        else
        {
            p = (*ppList)->m_pHead;
            for(; p->m_pNext; p=p->m_pNext);
            p->m_pNext = new_st;
        }
        changeFieldsLength(ppList, new_st);
    }
    calculateAverageMarkInList(ppList);
}

void freeStudentsList(SLIST** ppList)
{
    SSTUDENT *tmp;
    while ((*ppList)->m_pHead)
    {
        tmp = (*ppList)->m_pHead;
        (*ppList)->m_pHead = (*ppList)->m_pHead->m_pNext;
        free(tmp);
    }
    free(*ppList);
    *ppList = NULL;
}