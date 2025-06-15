// Mert Hamza Yılmaz / e2649119
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define initial_capacity 10
typedef struct {
    int regID;
    char name[60];
    char surname[60];
    char status[30];
    int year;
    char deviceMACAddress[30];
} Registration;

Registration* Load_RegistrationData(char *fileName, int *recordSize);
void Display_RegistrationData(Registration *, int recordSize);
Registration* Add_Registration(Registration *, int *recordSize);
void Sort(Registration *data, int recordSize);
void Statistics(Registration *data, int recordSize);
void Menu();
int main(int argc, char *argv[]) {
    int choice,recordSize = 0;
    char OutputFileName[150];
    Registration *registrationData = NULL;
    FILE *RegistrationFile = NULL;
    printf("Please enter the file name: ");
    fgets(OutputFileName, sizeof(OutputFileName),stdin);
    OutputFileName[strcspn(OutputFileName, "\n")] = 0;
    while ((RegistrationFile = fopen(OutputFileName, "r")) == NULL) {
        printf("This file does not exist. Please enter again: ");
        fgets(OutputFileName, sizeof(OutputFileName), stdin);
        OutputFileName[strcspn(OutputFileName, "\n")] = 0;
    }
    registrationData = Load_RegistrationData(OutputFileName, &recordSize);
    fclose(RegistrationFile);
    Display_RegistrationData(registrationData,recordSize);
    printf("What would you like to do?\n");
    do{
        Menu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        while(choice<=0 || choice >=5){
            printf("Wrong input!\n\n");
            Menu();
            printf("Enter your choice: ");
            scanf("%d",&choice);
        }
    } while (choice != 4);
    if(choice == 1)
        registrationData = Add_Registration(registrationData, &recordSize);
    else if(choice == 2){
        Sort(registrationData, recordSize);
        Display_RegistrationData(registrationData, recordSize);
    }
    else if(choice == 3)
        Statistics(registrationData, recordSize);
    else if(choice == 4){
        printf("Bye");
        exit(1);
    }
    free(registrationData);
    printf("Bye\n");
    return 0;
}
void Menu() {
    printf("What would you like to do?\n");
    printf("1 – add\n");
    printf("2 – sort\n");
    printf("3 – statistics\n");
    printf("4 - exit\n");
}

Registration* Add_Registration(Registration *data, int *recordSize) {
    Registration newRegistration;
    newRegistration.regID = data[*recordSize - 1].regID + 1;
    printf("Please enter the name: ");
    fgets(newRegistration.name, sizeof(newRegistration.name),stdin);
    newRegistration.name[strcspn(newRegistration.name, "\n")] = 0;
    printf("Please enter the surname: ");
    fgets(newRegistration.surname, sizeof(newRegistration.surname),stdin);
    printf("Please enter the status: ");
    fgets(newRegistration.status, sizeof(newRegistration.status),stdin);
    while(strcmp(newRegistration.status, "Declined") != 0 &&
          strcmp(newRegistration.status, "Blocked") != 0 &&
          strcmp(newRegistration.status, "Approved") != 0){
        printf("This is not valid!\n");
        printf("Please enter the status: ");
        fgets(newRegistration.status, sizeof(newRegistration.status),stdin);
    }
    printf("Please enter the year: ");
    scanf("%d", &newRegistration.year);
    while (getchar() != '\n');
    while (newRegistration.year <= 0){
        printf("Wrong input\n");
        printf("Please enter the year: ");
        scanf("%d", &newRegistration.year);
    }
    int valid = 0;
    while (getchar() != '\n');
    while (!valid){
        printf("Please enter the mac address: ");
        fgets(newRegistration.deviceMACAddress, sizeof(newRegistration.deviceMACAddress),stdin);
        valid = 1;
        if(strlen(newRegistration.deviceMACAddress) != 18){
            printf("This is not valid!\n");
            valid = 0;
        }
        for (int i = 0; i < strlen(newRegistration.deviceMACAddress); ++i) {
            if ((i + 1) % 3 == 0)
            {
                if (newRegistration.deviceMACAddress[i] != ':') {
                    printf("This is not valid!\n");
                    valid = 0;
                }
            }
        }
    }
    data = realloc(data, (*recordSize + 1) * sizeof(Registration));
    data[*recordSize] = newRegistration;
    (*recordSize)++;
    printf("It is recorded successfully!\n");
    return data;
}
Registration* Load_RegistrationData(char *RegistrationFile, int *recordSize){
    char Skip_the_line[260];
    int round=0;
    fgets(Skip_the_line, sizeof(Skip_the_line), RegistrationFile);
    Registration *registration = malloc(initial_capacity * sizeof(Registration));
    while (fscanf(RegistrationFile, "%d %s %s %s %d %s",
                  &registration[round].regID,
                  registration[round].name,
                  registration[round].surname,
                  registration[round].status,
                  &registration[round].year,
                  registration[round].deviceMACAddress) == 6){
        round++;
    }
    fclose(RegistrationFile);
    return registration;
}
void Display_RegistrationData(Registration *data, int recordSize){
    printf("REGID NAME       SURNAME    STATUS     YEAR   DEVICEMACADDRESS\n");
    for (int i = 0; i < recordSize; ++i) {
        printf("%-5d %-10s %-10s %-10s %-6d %-20s\n",
               data[i].regID,
               data[i].name,
               data[i].surname,
               data[i].status,
               data[i].year,
               data[i].deviceMACAddress);
    }
}
void Sort(Registration *registration, int recordSize){
    int Sort_Choice;
    printf("Which column (1: year, 2: surname)?:");
    scanf("%d",&Sort_Choice);
    while (Sort_Choice<=0 || Sort_Choice >=3)
    {
        printf("Invalid choice!\n"
               "Which column (1: year, 2: surname)?:");
        scanf("%d",&Sort_Choice);
    }
    for (int i = 0; i < recordSize - 1; i++) {
        for (int j = 0; j < recordSize - i - 1; j++) {
            int change = 0;
            if (Sort_Choice == 1) {
                if (registration[j].year > registration[j + 1].year) {
                    change = 1;
                }
            }
            else if (Sort_Choice == 2) {
                if (strcmp(registration[j].surname, registration[j + 1].surname) > 0) {
                    change = 1;
                }

            }
            if (change) {
                Registration Sort_temp = registration[j];
                registration[j] = registration[j + 1];
                registration[j + 1] = Sort_temp;
            }
        }
    }
}