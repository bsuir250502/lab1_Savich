#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct staff {
    char surname[30], name[30], patronymic[30];
    int salary[12];
};
void display(struct staff *person, int records)
{
    int i = 0, j;
    for (i = 0; i < records; i++) {
        printf("\n%s%s%s", person[i].surname, person[i].name,
               person[i].patronymic);
        for (j = 0; j < 12; j++)
            printf("\nmonth[%d]=%d", j + 1, person[i].salary[j]);
    }
}

char *delete_space(char *string)
{
    int i = 0, j, k = 0;
    while (string[i++] == ' ' && string[i]);
    if (i < 30) {
        for (j = i - 1; j < 30; j++)
            string[k++] = string[j];
    }
    return string;
}

char *check_input(struct staff *person, int records)
{
    char *string = (char *) calloc(30, sizeof(char));

    do {
        fgets(string, 30, stdin);
        if (strlen(string) == 29)
            while (getchar() != '\n');
    }
    while (string[0] == '\n');
    return string;
}

void input(struct staff *person, char *string, int records)
{
    int i = 0;
    puts("enter surname ");
    string = check_input(person, records);
    strcpy(person[records].surname, delete_space(string));
    puts("enter name ");
    string = check_input(person, records);
    strcpy(person[records].name, delete_space(string));
    puts("enter patronymic ");
    string = check_input(person, records);
    strcpy(person[records].patronymic, delete_space(string));
    printf
        ("enter salary per month\nATTENCION:maximum length of salary cannot exceed 14 symbols\n");
    for (i = 0; i < 12; i++) {
        printf("\n month[%d]=", i + 1);
        string = check_input(person, records);
        person[records].salary[i] = atoi(string);
    }
}

void sorting(struct staff *person, int records)
{
    int i, j;
    struct staff exchange;
    for (i = 0; i < records - 1; i++) {
        for (j = i + 1; j < records; j++) {
            if (strcmp((person + i)->surname, (person + j)->surname) > 0) {
                exchange = person[i];
                person[i] = person[j];
                person[j] = exchange;
            }
            if ((strcmp((person + i)->surname, (person + j)->surname)) ==
                0) {
                int compare_name =
                    strcmp((person + i)->name, (person + j)->name),
                    compare_patronymic =
                    strcmp((person + i)->patronymic,
                           (person + j)->patronymic);
                if ((compare_name > 0) || (compare_name == 0
                                           && compare_patronymic > 0)) {
                    exchange = person[i];
                    person[i] = person[j];
                    person[j] = exchange;
                }
            }
        }
    }
}

void info(void)
{
    printf("\nEnter fullname and salary per month");
}

int main( int argc, char *argv[])
{
    if(argc>1)
    {
        if(!strcmp(argv[1],"-h"))
            info();
    }
    int records = 0, i;
    char *string;
    struct staff *person;

    do {
        string = (char *) calloc(30, sizeof(char));
        person = (struct staff *) calloc(25, sizeof(struct staff));
    }
    while (!person && !string);
    puts("ATTENCION: maximum length of record cannot exceed 29 symbols");
    while (records < 25) {
        input(person, string, records);
        records++;
        puts("enter stop to quit");
        fgets(string, 5, stdin);
        if (strcmp(string, "stop") == 0)
            break;
    }
    if (records == 24)
        puts("you can enter only 25 persons");

    else
        person = (struct staff *) realloc(person, records);
    sorting(person, records);
    display(person, records);
    return 0;
}

