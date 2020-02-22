#include "functions.h"

static int list_size(LIST *list)
{
    int count = 0;
    if(!list)
    {
        fprintf(stderr, "List is empty\n");
        return -1;
    }
    STUDENT *p = list->head;
    while(p)
    {
        ++count;
        p = p->next;
    }
    return count;
}

static void change_fields_length(LIST **list, STUDENT *student)
{
    if(strlen(student->name)>(*list)->max_name_length)
        (*list)->max_name_length = strlen(student->name);
    if(strlen(student->surname)>(*list)->max_surname_length)
        (*list)->max_surname_length = strlen(student->surname);
}


static LIST* calculate_avg_list(LIST **list)
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
        ++count;
        sum+=p->avg;
        p = p->next;
    }
    (*list)->avg_mark = sum / (float)count;
    return *list;
}

static STUDENT* calculate_avg_student(STUDENT **student)
{
    float sum = 0.0f;
    for (int i = 0; i<MARKS_COUNT; ++i)
    {
        sum+=(float)((*student)->marks[i]);
    }
    (*student)->avg = sum / MARKS_COUNT;
    return *student;
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

static int print_head_of_table(int surname, int name)
{
    print_line('_', surname+name+3+3+5+5+7+11);

    fprintf(stdout, "|SURNAME");
    for(int i=7;i<surname;++i)
        fprintf(stdout, " ");
    fprintf(stdout, "| ");
    fprintf(stdout, "|NAME");
    for(int i=4;i<name;++i)
        fprintf(stdout, " ");
    fprintf(stdout, "| ");
    fprintf(stdout, "|DT| ");
    fprintf(stdout, "|MN| ");
    fprintf(stdout, "|YEAR| ");
    fprintf(stdout, "|  MARKS  |\n");
    print_line('_', surname+name+3+3+5+5+7+11);
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
        calculate_avg_list(list);
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
            calculate_avg_list(list);
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
                    fprintf(stdout, "Enter surname:");
                    scanf("%s", p_end->surname);
                    for(int i = 0;p_end->surname[i]!='\0';++i)
                    {
                        if(!isalpha(p_end->surname[i]))
                            ok = 0;
                    }
                }
                ok = 0;
                break;
            case NAME:
                while(!ok)
                {
                    ok = 1;
                    fprintf(stdout, "Enter name:");
                    scanf("%s", p_end->name);
                    for(int i = 0;p_end->name[i]!='\0';++i)
                    {
                        if(!isalpha(p_end->name[i]))
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
                    p_end->marks[0] = get_int("Enter first mark:");
                }while(p_end->marks[0]<0 || p_end->marks[0]>5);
                break;
            case MARK_1:
                do
                {
                    p_end->marks[1] = get_int("Enter second mark:");
                }while(p_end->marks[1]<0 || p_end->marks[1]>5);
                break;
            case MARK_2:
                do
                {
                    p_end->marks[2] = get_int("Enter third mark:");
                }while(p_end->marks[2]<0 || p_end->marks[2]>5);
                break;
            case MARK_3:
                do
                {
                    p_end->marks[3] = get_int("Enter fourth mark:");
                }while(p_end->marks[3]<0 || p_end->marks[3]>5);
                break;
            case MARK_4:
                do
                {
                    p_end->marks[4] = get_int("Enter fifth mark:");
                }while(p_end->marks[4]<0 || p_end->marks[4]>5);
                break;
            default:
                fprintf(stdout, "Done.\n");
        }
        j++;
        if(j>MARK_4)break;
    }
    calculate_avg_student(&p_end);
    sort_by_surname(&((*list)->head));
    calculate_avg_list(list);
    change_fields_length(list, p_end);
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
    print_head_of_table(list->max_surname_length, list->max_name_length);
    while (p)
    {
        fprintf(stdout, "|");
        fprintf(stdout, "%-*s",list->max_surname_length, p->surname);
        fprintf(stdout, "| |");
        fprintf(stdout, "%-*s",list->max_name_length, p->name);
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

void print_students_to_file(LIST *list)
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
        STUDENT *p = list->head;
        int n =list->max_surname_length+list->max_name_length+3+3+5+5+7+11;
        while(n)
        {
            fprintf(file, "%c", '_');
            n--;
        }
        fprintf(file, "\n");

        fprintf(file, "|SURNAME");
        for(int i=7;i<list->max_surname_length;++i)
            fprintf(file, " ");
        fprintf(file, "| ");
        fprintf(file, "|NAME");
        for(int i=4;i<list->max_name_length;++i)
            fprintf(file, " ");
        fprintf(file, "| ");
        fprintf(file, "|DT| ");
        fprintf(file, "|MN| ");
        fprintf(file, "|YEAR| ");
        fprintf(file, "|  MARKS  |\n");

        n =list->max_surname_length+list->max_name_length+3+3+5+5+7+11;
        while(n)
        {
            fprintf(file, "%c", '_');
            n--;
        }
        fprintf(file, "\n");
        while (p)
        {
            fprintf(file, "|");
            fprintf(file, "%-*s",list->max_surname_length, p->surname);
            fprintf(file, "| |");
            fprintf(file, "%-*s",list->max_name_length, p->name);
            fprintf(file, "| |");
            fprintf(file, "%02d", p->date.day);
            fprintf(file, "| |");
            fprintf(file, "%02d", p->date.month);
            fprintf(file, "| |");
            fprintf(file, "%-4d", p->date.year);
            fprintf(file, "| |");
            for(int k=0; k<MARKS_COUNT; ++k)
            {
                fprintf(file, "%1d", p->marks[k]);
                fprintf(file, "|");
            }
            fprintf(file, "\n");
            p = p->next;
        }
    }
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
        sum/=MARKS_COUNT;
        if(sum<(*list)->avg_mark)
        {
            pp = prev_student((*list)->head, p);
            pp->next = p->next;
            free(p);
            p=pp;
        }
        p = p->next;
    }
    calculate_avg_list(list);
    return *list;
}

LIST* display_two_the_smartest(LIST ** list)
{

    if(list_size(*list)<3)
    {
        print_students(*list);
        return *list;
    }
    STUDENT *max_avg_1 = (*list)->head, *max_avg_2 = max_avg_1->next;
    STUDENT *p = max_avg_2->next;

    while(p)
    {
        if(p->avg > max_avg_1->avg)
        {
            max_avg_1 = p;
        }
        p = p->next;
    }
    p = (*list)->head;
    while(p)
    {
        if(p->avg > max_avg_2->avg && p!=max_avg_1)
        {
            max_avg_2 = p;
        }
        p = p->next;
    }
    STUDENT *pp1 = (STUDENT*)malloc(sizeof(STUDENT));
    STUDENT *pp2 = (STUDENT*)malloc(sizeof(STUDENT));
    *pp1 = *max_avg_1;
    *pp2 = *max_avg_2;
    pp1->next = pp2;
    pp2->next = NULL;
    LIST *list1 = (LIST*)malloc(sizeof(LIST));
    list1->head=pp1;
    list1->max_name_length = 0;
    list1->max_surname_length = 0;
    change_fields_length(&list1, pp1);
    change_fields_length(&list1, pp2);
    print_students(list1);
    free_list(&list1);
    return *list;
}

void read_from_file(LIST **list)
{
    char ch;
    char path[100];
    STUDENT*p;

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

    LIST *temp = NULL;

    while (!feof(input))
    {
        STUDENT *new_st = (STUDENT *) malloc(sizeof(STUDENT));
        if (!new_st) {
            fprintf(stderr, "can not allocate \n");
            return;
        }
        fscanf(input, "%s %s", new_st->surname, new_st->name);
        fscanf(input, "%d.%d.%d", &(new_st->date.day), &(new_st->date.month), &(new_st->date.year));
        fscanf(input, "%d %d %d %d %d", new_st->marks, new_st->marks + 1,
                new_st->marks + 2, new_st->marks + 3,new_st->marks + 4);
        new_st->next = NULL;
        calculate_avg_student(&new_st);
        if(!((*list)->head))
        {
            (*list)->head = new_st;
        }
        else
        {
            p = (*list)->head;
            for(;p->next;p=p->next);
            p->next = new_st;
        }
        change_fields_length(list, new_st);
    }
    calculate_avg_list(list);
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