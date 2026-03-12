#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *my_file = fopen("contacts.csv", "w");
    fprintf(my_file, "#%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(my_file, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(my_file);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *my_file = fopen("contacts.csv", "r");
    fscanf(my_file, "#%d\n", &addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(my_file, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(my_file);
}
