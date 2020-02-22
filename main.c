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

        printf("Choose option:\n"
               "1 - Sort\n"
               "2 - Delete student by surname\n"
               "3 - Delete students with  less then avarage mark\n"
               "4 - Add student\n"
               "5 - Display two the smartest\n"
               "6 - Read from file\n"
               "7 - Write to file\n"
               "0 - Exit\n");
        option = get_int("Option:");
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
            delete_less_then_avg(&students_list);
        }
        if(option==4)
        {
            add_student(&students_list);
        }
        if(option==5)
        {
            display_two_the_smartest(&students_list);
        }
        if(option==6)
        {
            read_from_file(&students_list);
        }
        if(option==7)
        {
            print_students_to_file(students_list);
        }
        print_students(students_list);
    }while(1);
    free_list(&students_list);

    return 0;
}