#include "functions.h"

static int getListSize(SLIST* pList)
{
    int iCount = 0;
    if(!pList)
    {
        fprintf(stderr, "List is empty\n");
        return -1;
    }
    SSTUDENT *pTmp = pList->m_pHead;
    while(pTmp)
    {
        ++iCount;
        pTmp = pTmp->m_pNext;
    }
    return iCount;
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
    SSTUDENT *pTmp = (*pList)->m_pHead;
    int iCount = 0;
    float fSum = 0.0f;
    if(!pTmp)
    {
        fprintf(stderr, "List is empty\n");
        return *pList;
    }
    while(pTmp)
    {
        ++iCount;
        fSum+=pTmp->m_fAverageMark;
        pTmp = pTmp->m_pNext;
    }
    (*pList)->m_fAverageMark = fSum / (float)iCount;
    return *pList;
}

static SSTUDENT* calculateAverageMarkOfStudent(SSTUDENT** ppStudent)
{
    float fSum = 0.0f;
    for (int i = 0; i<MARKS_COUNT; ++i)
    {
        fSum+=(float)((*ppStudent)->m_iMarks[i]);
    }
    (*ppStudent)->m_fAverageMark = fSum / MARKS_COUNT;
    return *ppStudent;
}

static SSTUDENT* getPreviousStudent(SSTUDENT* pHead, SSTUDENT* pCurrent)
{
    if(pCurrent == pHead)
        return NULL;
    else
    {
        SSTUDENT *pTmp;
        for(pTmp = pHead; pTmp->m_pNext != pCurrent; pTmp = pTmp->m_pNext);
        return pTmp;
    }
}

static int printLineOnScreen(char cCh, int iCount)
{
    while(iCount)
    {
        fprintf(stdout, "%c", cCh);
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
    SSTUDENT *pCurrent1, *pCurrent2, *pPrevious1, *pPrevious2, *pTmp;
    for(pCurrent1=*ppHead; pCurrent1->m_pNext; pCurrent1=pCurrent1->m_pNext )
    {
        for(pCurrent2=pCurrent1->m_pNext; pCurrent2 ; pCurrent2=pCurrent2->m_pNext)
        {
            pPrevious1= getPreviousStudent(*ppHead, pCurrent1);
            pPrevious2= getPreviousStudent(*ppHead, pCurrent2);
            if(strcmp(pCurrent1->m_szSurname, pCurrent2->m_szSurname) > 0)
            {
                if(pCurrent1->m_pNext == pCurrent2)
                {
                    pTmp = pCurrent2->m_pNext;
                    pCurrent2->m_pNext = pCurrent1;
                    pCurrent1->m_pNext = pTmp;
                }
                else
                {
                    pTmp = pCurrent2->m_pNext;
                    pCurrent2->m_pNext = pCurrent1->m_pNext;
                    pCurrent1->m_pNext = pTmp;
                    pPrevious2->m_pNext = pCurrent1;
                }
                if(!pPrevious1)
                    *ppHead = pCurrent2;
                else
                    pPrevious1->m_pNext = pCurrent2;
                pTmp = pCurrent1;
                pCurrent1 = pCurrent2;
                pCurrent2 = pTmp;
            }
        }
    }
    return *ppHead;
}

SLIST* deleteStudentBySurname(SLIST** ppList, char* pszSurname)
{
    SSTUDENT *pTmp1 = (*ppList)->m_pHead, *pTmp2 = NULL;
    if(!(pTmp1))
    {
        fprintf(stderr, "List is empty\n");
        return *ppList;
    }
    if(!strcmp(((*ppList)->m_pHead)->m_szSurname, pszSurname))
    {
        (*ppList)->m_pHead = pTmp1->m_pNext;
        free(pTmp1);
        calculateAverageMarkInList(ppList);
        return *ppList;
    }
    pTmp1 = (*ppList)->m_pHead;
    while(pTmp1)
    {
        if(!strcmp(((*ppList)->m_pHead)->m_szSurname, pszSurname))
        {
            pTmp2 = getPreviousStudent((*ppList)->m_pHead, pTmp1);
            pTmp2->m_pNext = pTmp1->m_pNext;
            free(pTmp1);
            calculateAverageMarkInList(ppList);
            return *ppList;
        }
        pTmp1 = pTmp1->m_pNext;
    }
    fprintf(stdout, "Can not find %s", pszSurname);
    return *ppList;
}

SLIST* addStudent(SLIST** ppHead)
{
    SSTUDENT *pEnd;
    if(!((*ppHead)->m_pHead))
    {
        pEnd = (SSTUDENT*)malloc(sizeof(SSTUDENT));
        (*ppHead)->m_pHead = pEnd;
    }
    else
    {
        for (pEnd = (*ppHead)->m_pHead; pEnd->m_pNext != NULL; pEnd = pEnd->m_pNext);
        pEnd->m_pNext = (SSTUDENT *) malloc(sizeof(SSTUDENT));
        pEnd = pEnd->m_pNext;
    }
    if(!(pEnd))
    {
        fprintf(stderr, "Can not allocate so much memory");
        return *ppHead;
    }
    int iOk = 0;
    int j = 0;
    while (1)
    {
        switch (j)
        {
            case SURNAME:
                while(!iOk)
                {
                    iOk = 1;
                    fprintf(stdout, "Enter m_szSurname:");
                    scanf("%s", pEnd->m_szSurname);
                    for(int i = 0; pEnd->m_szSurname[i] != '\0'; ++i)
                    {
                        if(!isalpha(pEnd->m_szSurname[i]))
                            iOk = 0;
                    }
                }
                iOk = 0;
                break;
            case NAME:
                while(!iOk)
                {
                    iOk = 1;
                    fprintf(stdout, "Enter m_szName:");
                    scanf("%s", pEnd->m_szName);
                    for(int i = 0; pEnd->m_szName[i] != '\0'; ++i)
                    {
                        if(!isalpha(pEnd->m_szName[i]))
                            iOk = 0;
                    }
                }
                getchar();
                break;
            case DAY:
                do
                {
                    pEnd->date.day = get_int("Enter day of birth:");
                }while(pEnd->date.day < 0 || pEnd->date.day > 31);
                break;
            case MONTH:
                do
                {
                    pEnd->date.month = get_int("Enter month of birth:");
                }while(pEnd->date.month < 0 || pEnd->date.month > 12);
                break;
            case YEAR:
                do
                {
                    pEnd->date.year = get_int("Enter year of birth:");
                }while(pEnd->date.year < 1900 || pEnd->date.year > 2020);
                break;
            case MARK_0:
                do
                {
                    pEnd->m_iMarks[0] = get_int("Enter first mark:");
                }while(pEnd->m_iMarks[0] < 0 || pEnd->m_iMarks[0] > 5);
                break;
            case MARK_1:
                do
                {
                    pEnd->m_iMarks[1] = get_int("Enter second mark:");
                }while(pEnd->m_iMarks[1] < 0 || pEnd->m_iMarks[1] > 5);
                break;
            case MARK_2:
                do
                {
                    pEnd->m_iMarks[2] = get_int("Enter third mark:");
                }while(pEnd->m_iMarks[2] < 0 || pEnd->m_iMarks[2] > 5);
                break;
            case MARK_3:
                do
                {
                    pEnd->m_iMarks[3] = get_int("Enter fourth mark:");
                }while(pEnd->m_iMarks[3] < 0 || pEnd->m_iMarks[3] > 5);
                break;
            case MARK_4:
                do
                {
                    pEnd->m_iMarks[4] = get_int("Enter fifth mark:");
                }while(pEnd->m_iMarks[4] < 0 || pEnd->m_iMarks[4] > 5);
                break;
            default:
                fprintf(stdout, "Done.\n");
        }
        j++;
        if(j>MARK_4)break;
    }
    calculateAverageMarkOfStudent(&pEnd);
    sortStudentsBySurname(&((*ppHead)->m_pHead));
    calculateAverageMarkInList(ppHead);
    changeFieldsLength(ppHead, pEnd);
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
    SSTUDENT *pTmp = pList->m_pHead;
    printHeadOfTableOnScreen(pList->m_usMaxSurnameLength, pList->m_usMaxNameLength);
    while (pTmp)
    {
        fprintf(stdout, "|");
        fprintf(stdout, "%-*s", pList->m_usMaxSurnameLength, pTmp->m_szSurname);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-*s", pList->m_usMaxNameLength, pTmp->m_szName);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", pTmp->date.day);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", pTmp->date.month);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-4d", pTmp->date.year);
        fprintf(stdout, "| |");
        for(int k=0; k<MARKS_COUNT; ++k)
        {
            fprintf(stdout, "%1d", pTmp->m_iMarks[k]);
            fprintf(stdout, "|");
        }
        fprintf(stdout, "\n");
        pTmp = pTmp->m_pNext;
    }
    printf("\n");
}

void saveStudentsToFile(SLIST* pList)
{
    fprintf(stdout, "Enter full path to file");
    char szFileName[100];
    scanf("%s", szFileName);
    FILE* pFile = fopen(szFileName, "wt");
    if(!pFile)
    {
        fprintf(stderr, "Can not open file\n");
        return;
    }
    else
    {
        SSTUDENT *pTmp = pList->m_pHead;
        int n = pList->m_usMaxSurnameLength + pList->m_usMaxNameLength + 3 + 3 + 5 + 5 + 7 + 11;
        while(n)
        {
            fprintf(pFile, "%c", '_');
            n--;
        }
        fprintf(pFile, "\n");

        fprintf(pFile, "|SURNAME");
        for(int i=7; i < pList->m_usMaxSurnameLength; ++i)
            fprintf(pFile, " ");
        fprintf(pFile, "| ");
        fprintf(pFile, "|NAME");
        for(int i=4; i < pList->m_usMaxNameLength; ++i)
            fprintf(pFile, " ");
        fprintf(pFile, "| ");
        fprintf(pFile, "|DT| ");
        fprintf(pFile, "|MN| ");
        fprintf(pFile, "|YEAR| ");
        fprintf(pFile, "|  MARKS  |\n");

        n = pList->m_usMaxSurnameLength + pList->m_usMaxNameLength + 3 + 3 + 5 + 5 + 7 + 11;
        while(n)
        {
            fprintf(pFile, "%c", '_');
            n--;
        }
        fprintf(pFile, "\n");
        while (pTmp)
        {
            fprintf(pFile, "|");
            fprintf(pFile, "%-*s", pList->m_usMaxSurnameLength, pTmp->m_szSurname);
            fprintf(pFile, "| |");
            fprintf(pFile, "%-*s", pList->m_usMaxNameLength, pTmp->m_szName);
            fprintf(pFile, "| |");
            fprintf(pFile, "%02d", pTmp->date.day);
            fprintf(pFile, "| |");
            fprintf(pFile, "%02d", pTmp->date.month);
            fprintf(pFile, "| |");
            fprintf(pFile, "%-4d", pTmp->date.year);
            fprintf(pFile, "| |");
            for(int k=0; k<MARKS_COUNT; ++k)
            {
                fprintf(pFile, "%1d", pTmp->m_iMarks[k]);
                fprintf(pFile, "|");
            }
            fprintf(pFile, "\n");
            pTmp = pTmp->m_pNext;
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
    SSTUDENT *pTmp1 = (*ppList)->m_pHead, *pTmp2 = NULL;
    float fSum;
    while(pTmp1)
    {
        fSum = 0.0f;
        for(int i = 0; i<MARKS_COUNT; ++i)
        {
            fSum += (float)pTmp1->m_iMarks[i];
        }
        fSum/=MARKS_COUNT;
        if(fSum < (*ppList)->m_fAverageMark)
        {
            pTmp2 = getPreviousStudent((*ppList)->m_pHead, pTmp1);
            pTmp2->m_pNext = pTmp1->m_pNext;
            free(pTmp1);
            pTmp1=pTmp2;
        }
        pTmp1 = pTmp1->m_pNext;
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
    SSTUDENT *pMaxAverageMark1 = (*ppList)->m_pHead, *pMaxAverage2 = pMaxAverageMark1->m_pNext;
    SSTUDENT *pTmp = pMaxAverage2->m_pNext;

    while(pTmp)
    {
        if(pTmp->m_fAverageMark > pMaxAverageMark1->m_fAverageMark)
        {
            pMaxAverageMark1 = pTmp;
        }
        pTmp = pTmp->m_pNext;
    }
    pTmp = (*ppList)->m_pHead;
    while(pTmp)
    {
        if(pTmp->m_fAverageMark > pMaxAverage2->m_fAverageMark && pTmp != pMaxAverageMark1)
        {
            pMaxAverage2 = pTmp;
        }
        pTmp = pTmp->m_pNext;
    }
    SSTUDENT *pTmp1 = (SSTUDENT*)malloc(sizeof(SSTUDENT));
    SSTUDENT *pTmp2 = (SSTUDENT*)malloc(sizeof(SSTUDENT));
    *pTmp1 = *pMaxAverageMark1;
    *pTmp2 = *pMaxAverage2;
    pTmp1->m_pNext = pTmp2;
    pTmp2->m_pNext = NULL;
    SLIST *list1 = (SLIST*)malloc(sizeof(SLIST));
    list1->m_pHead=pTmp1;
    list1->m_usMaxNameLength = 0;
    list1->m_usMaxSurnameLength = 0;
    changeFieldsLength(&list1, pTmp1);
    changeFieldsLength(&list1, pTmp2);
    showStudentsOnScreen(list1);
    freeStudentsList(&list1);
    return *ppList;
}

void readStudentsFromFile(SLIST** ppList)
{
    char cCh;
    char szPath[100];
    SSTUDENT* pTmp1;

    fprintf(stdout, "Do you want to read from default file?(y/n):\n");
    fscanf(stdin,"%c", &cCh);
    if (cCh == 'n')
    {
        fprintf(stdout, "Enter full szPath to file:");
        scanf("%s", szPath);
    }
    else
    {
        strcpy(szPath, "/home/user/Desktop/ETSE/input.txt");
    }
    FILE* pFile = fopen(szPath, "rt");
    if (pFile == NULL)
    {
        fprintf(stderr, "Cant open file\n");
        return;
    }

    while (!feof(pFile))
    {
        SSTUDENT *pNewStudent = (SSTUDENT *) malloc(sizeof(SSTUDENT));
        if (!pNewStudent) {
            fprintf(stderr, "can not allocate \n");
            return;
        }
        fscanf(pFile, "%s %s", pNewStudent->m_szSurname, pNewStudent->m_szName);
        fscanf(pFile, "%d.%d.%d", &(pNewStudent->date.day), &(pNewStudent->date.month), &(pNewStudent->date.year));
        fscanf(pFile, "%d %d %d %d %d", pNewStudent->m_iMarks, pNewStudent->m_iMarks + 1,
               pNewStudent->m_iMarks + 2, pNewStudent->m_iMarks + 3, pNewStudent->m_iMarks + 4);
        pNewStudent->m_pNext = NULL;
        calculateAverageMarkOfStudent(&pNewStudent);
        if(!((*ppList)->m_pHead))
        {
            (*ppList)->m_pHead = pNewStudent;
        }
        else
        {
            pTmp1 = (*ppList)->m_pHead;
            for(; pTmp1->m_pNext; pTmp1=pTmp1->m_pNext);
            pTmp1->m_pNext = pNewStudent;
        }
        changeFieldsLength(ppList, pNewStudent);
    }
    calculateAverageMarkInList(ppList);
}

void freeStudentsList(SLIST** ppList)
{
    SSTUDENT *pTmp;
    while ((*ppList)->m_pHead)
    {
        pTmp = (*ppList)->m_pHead;
        (*ppList)->m_pHead = (*ppList)->m_pHead->m_pNext;
        free(pTmp);
    }
    free(*ppList);
    *ppList = NULL;
}