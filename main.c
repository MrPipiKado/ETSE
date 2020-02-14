#include "functions.h"


int main()
{
    LIST *students_list = (LIST*)malloc(sizeof(LIST));
    students_list->head = NULL;
    students_list->avg_mark = 0.0f;
    students_list->max_name_length = 0;
    students_list->max_surname_length = 0;
    int option = 0, sorted = 1;
    char surname[NAME_LENGTH];
    print_students(students_list);
    do
    {

        printf("Choose option:\n1 - Sort\n2 - Delete student by surname\n"
               "3 - Add student\n0 - Exit\nOption:");
        if(!scanf("%d", &option))break;
        if(!option)break;
        if(option==1)
            if(sorted)
            {
                sort_by_surname(&(students_list->head));
                sorted = 0;
            }
        if(option==2)
        {
            printf("Enter surname:");
            scanf("%s", surname);
            delete_by_surname(&students_list, surname);
        }
        if(option==3)
        {
            add_student(&students_list);
        }
        print_students(students_list);
    }while(1);
    free_list(&students_list);

    return 0;
}