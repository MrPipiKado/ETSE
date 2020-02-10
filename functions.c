#include "functions.h"

static STUDENT* prev_student(STUDENT *head, STUDENT *puk)
{
    if(puk==head)
        return NULL;
    else
    {
        STUDENT *kaka;
        for(kaka = head; kaka->next!=puk; kaka = kaka->next);
        return kaka;
    }
}

static int print_line(char ch, int n)
{
    while(n)
    {
        fprintf(stdout, "%c", ch);
        n--;
    }
    fprintf(stdout, "\n");
    return 0;
}

static int print_head_of_table(int length)
{
    int puk = (length + 7)*2;
    print_line('_', puk);
    fprintf(stdout, "|   NAME   | ");
    fprintf(stdout, "|  SURNAME | ");
    fprintf(stdout, "|DT| ");
    fprintf(stdout, "|MN| ");
    fprintf(stdout, "|YEAR| ");
    fprintf(stdout, "|  MARKS  |\n");
    puk = (length + 7)*2;
    print_line('-', puk);
    return 0;
}

STUDENT* sort_by_surname(STUDENT **head)
{
    STUDENT *p1 ,*p2 , *pp1 , *pp2 , *tmp ;
    int i;
    for(p1=*head; p1->next; p1=p1->next )
    {
        for(p2=p1->next; p2 ; p2=p2->next)
        {
            pp1=prev_student(*head,p1);
            pp2=prev_student(*head,p2);
            i = 0;
            while(p1->surname[i] < p2->surname[i] && p1->surname[i]!='\0' && p2->surname[i]!='\0')
            {
                ++i;
            }
            if(p1->surname[i] < p2->surname[i])
            {
                if(p1->next == p2)
                {
                    tmp = p2->next;
                    p2->next = p1;
                    p1->next = tmp;
                }
                else
                {
                    tmp = p2->next;
                    p2->next = p1->next;
                    p1->next = tmp;
                    pp2->next = p1;
                }
                if(!pp1)
                    *head = p2;
                else
                    pp1->next = p2;
                tmp = p1;
                p1 = p2;
                p2 = tmp;
            }
        }
    }
    return *head;
}

STUDENT* delete_by_surname(STUDENT **head, char *surname)
{
    STUDENT *p = *head, *pp = NULL;
    if(!strcmp((*head)->surname, surname))
    {
        *head = p->next;
        free(p);
        return *head;
    }
    p = *head;
    while(p)
    {
        if(!strcmp((*head)->surname, surname))
        {
            pp = prev_student(*head, p);
            pp->next = p->next;
            free(p);
            return *head;
        }
        p = p->next;
    }
    fprintf(stdout, "Can not find %s", surname);
    return *head;
}

STUDENT* add_student(STUDENT *head)
{
    STUDENT *p_end;
    for(p_end = head; p_end->next!=NULL; p_end = p_end->next);
    p_end->next = (STUDENT*)malloc(sizeof(STUDENT));
    p_end = p_end->next;
    if(!(p_end))
    {
        fprintf(stderr, "Can not allocate so much memory");
        return head;
    }

    int j = 0;
    while (1)
    {
        switch (j)
        {
            case SURNAME:
                fprintf(stdout, "Enter surname:");
                scanf("%s", p_end->surname);
                break;
            case NAME:
                fprintf(stdout, "Enter name:");
                scanf("%s", p_end->name);
                break;
            case DAY:
                fprintf(stdout, "Enter day of birth:");
                scanf("%d", &(p_end->date.day));
                break;
            case MONTH:
                fprintf(stdout, "Enter month of birth:");
                scanf("%d", &(p_end->date.month));
                break;
            case YEAR:
                fprintf(stdout, "Enter year of birth:");
                scanf("%d", &(p_end->date.year));
                break;
            case MARK_0:
                fprintf(stdout, "Enter first mark:");
                scanf("%d", &(p_end->marks[0]));
                break;
            case MARK_1:
                fprintf(stdout, "Enter second mark:");
                scanf("%d", &(p_end->marks[1]));
                break;
            case MARK_2:
                fprintf(stdout, "Enter third mark:");
                scanf("%d", &(p_end->marks[2]));
                break;
            case MARK_3:
                fprintf(stdout, "Enter fourth mark:");
                scanf("%d", &(p_end->marks[3]));
                break;
            case MARK_4:
                fprintf(stdout, "Enter fifth mark:");
                scanf("%d", &(p_end->marks[4]));
                break;
            default:
                fprintf(stdout, "Done.\n");
        }
        j++;
        if(j>MARK_4)break;
    }
    sort_by_surname(&head);

    fprintf(stdout, "Added)\n");
    return head;
}

void print_students(STUDENT *head)
{
    if(!head)
    {
        fprintf(stderr, "List is empty\n");
        return;
    }
    STUDENT *p = head;
    print_head_of_table(NAME_LENGTH*2);
    while (p)
    {
        fprintf(stdout, "|");
        fprintf(stdout, "%-*s",NAME_LENGTH, p->surname);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-*s",NAME_LENGTH, p->name);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", p->date.day);
        fprintf(stdout, "| |");
        fprintf(stdout, "%02d", p->date.month);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-4d", p->date.year);
        fprintf(stdout, "| |");
        for(int k=0; k<MARKS_COUNT; ++k)
        {
            fprintf(stdout, "%1d", p->marks[k]);
            fprintf(stdout, "|");
        }
        fprintf(stdout, "\n");
        p = p->next;
    }
    printf("\n");
}

void free_list(STUDENT *head)
{
    STUDENT *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}