#include "functions.h"

static LIST* calculate_avg(LIST **list)
{
    STUDENT *p = (*list)->head;
    int count = 0;
    float sum = 0.0f;
    if(!p)
    {
        fprintf(stderr, "List is empty\n");
        return *list;
    }
    while(p)
    {
        for(int i = 0; i<MARKS_COUNT; ++i)
        {
            sum +=(float)(p->marks[i]);
            ++count;
        }
        p = p->next;
    }
    (*list)->avg_mark = sum / (float)count;
    return *list;
}


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
    if(!(*head))
    {
        fprintf(stderr, "List is empty\n");
        return *head;
    }
    STUDENT *p1 ,*p2 , *pp1 , *pp2 , *tmp ;
    int i;
    for(p1=*head; p1->next; p1=p1->next )
    {
        for(p2=p1->next; p2 ; p2=p2->next)
        {
            pp1=prev_student(*head,p1);
            pp2=prev_student(*head,p2);
            if(strcmp(p1->surname, p2->surname)>0)
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

LIST* delete_by_surname(LIST **list, char *surname)
{
    STUDENT *p = (*list)->head, *pp = NULL;
    if(!(p))
    {
        fprintf(stderr, "List is empty\n");
        return *list;
    }
    if(!strcmp(((*list)->head)->surname, surname))
    {
        (*list)->head = p->next;
        free(p);
        calculate_avg(list);
        return *list;
    }
    p = (*list)->head;
    while(p)
    {
        if(!strcmp(((*list)->head)->surname, surname))
        {
            pp = prev_student((*list)->head, p);
            pp->next = p->next;
            free(p);
            calculate_avg(list);
            return *list;
        }
        p = p->next;
    }
    fprintf(stdout, "Can not find %s", surname);
    return *list;
}

LIST* add_student(LIST **list)
{
    STUDENT *p_end;
    if(!((*list)->head))
    {
        p_end = (STUDENT*)malloc(sizeof(STUDENT));
        (*list)->head = p_end;
    }
    else
    {
        for (p_end = (*list)->head; p_end->next != NULL; p_end = p_end->next);
        p_end->next = (STUDENT *) malloc(sizeof(STUDENT));
        p_end = p_end->next;
    }
    if(!(p_end))
    {
        fprintf(stderr, "Can not allocate so much memory");
        return *list;
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
    sort_by_surname(&((*list)->head));
    calculate_avg(list);
    fprintf(stdout, "Added)\n");
    return *list;
}

void print_students(LIST *list)
{
    if(!(list->head))
    {
        fprintf(stderr, "List is empty\n");
        return;
    }
    STUDENT *p = list->head;
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

LIST* delete_less_then_avg(LIST **list)
{
    if(!((*list)->head))
    {
        fprintf(stderr, "List is empty\n");
        return *list;
    }
    STUDENT *p = (*list)->head, *pp = NULL;
    float sum;
    while(p)
    {
        sum = 0.0f;
        for(int i = 0; i<MARKS_COUNT; ++i)
        {
            sum += (float)p->marks[i];
        }
        if(sum<(*list)->avg_mark)
        {
            pp = prev_student((*list)->head, p);
            pp->next = p->next;
            free(p);
            p=pp;
        }
        p = p->next;
    }
    calculate_avg(list);
    return *list;
}

void free_list(LIST **list)
{
    STUDENT *tmp;
    while ((*list)->head)
    {
        tmp = (*list)->head;
        (*list)->head = (*list)->head->next;
        free(tmp);
    }
    free(*list);
    *list = NULL;
}