#include "functions.h"


int main()
{
    STUDENT *head = NULL;
    int option = 0, sorted = 1;
    char surname[NAME_LENGTH];
    print_students(head);
    do
    {

        printf("Choose option:\n1 - Sort\n2 - Delete student by surname\n"
               "3 - Add student\n0 - Exit\nOption:");
        if(!scanf("%d", &option))break;
        if(!option)break;
        if(option==1)
            if(sorted)
            {
                head = sort_by_surname(&head);
                sorted = 0;
            }
        if(option==2)
        {
            printf("Enter surname:");
            scanf("%s", surname);
            head = delete_by_surname(&head, surname);
        }
        if(option==3)
        {
            head = add_student(head);
        }
        print_students(head);
    }while(1);
    free_list(head);

    return 0;
}