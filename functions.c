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
            while(p1->surname[i] == p2->surname[i] && p1->surname[i]!='\0' && p1->surname[i]!='\0')
                ++i;
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