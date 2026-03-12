#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the chosen criteria
    for (int i = 0; i < addressBook->contactCount; i++) // adressbook pointing to conatctcount so we give address -> contactcount
    {
        printf("%d %s %s %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); //%d for sl/no all others are in string format we are acessing from addressbook name,phone number,email where i+1 is the count incrementing first as 1 then 2 ...
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// int validname(AddressBook *addressBook, char *name)
// {
//     for (int i = 0; i < addressBook->contactCount; i++)
//     {
//         if ((strcmp(addressBook->contacts[i].name, name)) == 0)
//         {
//             return 0;
//         }
//     }
//     return 1;
// }
int validphone(AddressBook *addressBook, char *phone, int index)
{
    if (strlen(phone) != 10)
    {
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == index)
        {
            continue; // to skip current contact being edited
        }
        if ((strcmp(addressBook->contacts[i].phone, phone)) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int validemail(AddressBook *addressBook, char *email)
{
    int count = 0;
    int len=strlen(email);
    if (len<5||strcmp(&email[len-4],".com")!=0)
    {
        return 0;
    }
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] >= 'A' && email[i] <= 'Z')
        {
            return 0;
        }
        if (email[i] == '@')
        {
            count++;
        }
    }
    if (count != 1)
    {
        return 0;
    }
    if (strstr(email, ".com") == NULL)
    {
        return 0;
    }
    char *atSign = strchr(email, '@');
    // if (atSign == email || *(atSign + 1) == '\0')
    // {
    //     return 0;
    // }
    char *dot = strrchr(email, '.');
    // if (dot < atSign || *(dot + 1) == '\0')
    // {
    //     return 0;
    // }   
    if(dot<=atSign+1)
    {
        return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((strcmp(addressBook->contacts[i].email, email)) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    Contact new_contact;
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("--------Address book is full---------\n");
        return;
    }

    // do
    //  {
    printf("Enter name:");
    scanf(" %[^\n]", new_contact.name);
    // if (!validname(addressBook, new_contact.name))
    // {
    //     printf("Name already exists   TRY AGAIN\n");
    // }
    // } while (!validname(addressBook, new_contact.name));

    do
    {
        printf("Enter phone number: ");
        scanf(" %[^\n]", new_contact.phone);
        if (!validphone(addressBook, new_contact.phone, -1))
        {
            printf("--------INVALID NUMBER--------    TRY AGAIN\n");
        }
    } while (!validphone(addressBook, new_contact.phone, -1));

    do
    {
        printf("Enter email ID: ");
        scanf(" %[^\n]", new_contact.email);
        if (!validemail(addressBook, new_contact.email))
        {
            printf("------INVALID EMAIL-------    TRY AGAIN\n");
        }
    } while (!validemail(addressBook, new_contact.email));

    addressBook->contacts[addressBook->contactCount] = new_contact;
    addressBook->contactCount++;
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    printf("-------Contact saved successfully--------\n");
}

int search_name(AddressBook *addressBook)
{
    char input[100];
    // int flag = 0;
    printf("Enter the name : ");
    scanf(" %[^\n]", input);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, input) == 0)
        {
            // printf("------contact found------\n");
            printf("%d  ", i + 1);
            printf("%s  ", addressBook->contacts[i].name);
            printf("%s  ", addressBook->contacts[i].phone);
            printf("%s\n ", addressBook->contacts[i].email);
            // flag = 1;
            return i;
        }
    }
    printf("-------Contact not found--------\n");
    return -1;
    // if (flag == 0)
    // {
    //     printf("-------Contact not found--------\n");
    //     return 0;
    // }
    // else
    // {
    //     return 1;
    // }
}
int search_phone(AddressBook *addressBook)
{
    char input[100];
    // int flag = 0;
    printf("Enter the phone: ");
    scanf(" %[^\n]", input);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, input) == 0)
        {
            printf("------contact found-------\n");
            printf("%d  ", i + 1);
            printf("%s  ", addressBook->contacts[i].name);
            printf("%s  ", addressBook->contacts[i].phone);
            printf("%s\n ", addressBook->contacts[i].email);
            // flag = 1;
            return i;
            break;
        }
    }
    printf("-------Contact not found--------\n");
    return -1;
    // if (flag == 0)
    // {
    //     printf("-------Contact not found--------\n");
    //     return 0;
    // }
    // else
    // {
    //     return 1;
    // }
}
int search_mail(AddressBook *addressBook)
{
    char input[100];
    // int flag = 0;

    printf("Enter the email: ");
    scanf(" %[^\n]", input);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, input) == 0)
        {
            printf("-----contact found-----\n");
            printf("%d  ", i + 1);
            printf("%s  ", addressBook->contacts[i].name);
            printf("%s  ", addressBook->contacts[i].phone);
            printf("%s\n", addressBook->contacts[i].email);
            // flag = 1;
            return i;
            break;
        }
    }
    printf("-------Contact not found--------\n");
    return -1;
    // if (flag == 0)
    // {
    //     printf("-------Contact not found--------\n");
    //     return 0;
    // }
    // else
    // {
    //     return 1;
    // }
}

int searchContact(AddressBook *addressBook)
{
    int sort, ret;
    char input[100];
    int flag = 0;

    printf("1.Search by name:\n");
    printf("2.search by phone number:\n");
    printf("3.seach by email:\n");
    printf("4.Exit search\n");
    printf("Enter your choice:\n");
    scanf("%d", &sort);
    // switch (sort)
    // {
    // case 1:
    //     search_name(addressBook);
    //     // printf("Enter the name :");
    //     // scanf(" %[^\n]", input);
    //     // for (int i = 0; i < addressBook->contactCount; i++)
    //     // {
    //     //     if (strcmp(addressBook->contacts[i].name, input) == 0)
    //     //     {
    //     //         printf("contact found\n");
    //     //         printf("%s\n", addressBook->contacts[i].name);
    //     //         printf("%s\n", addressBook->contacts[i].phone);
    //     //         printf("%s\n", addressBook->contacts[i].email);
    //     //         flag = 1;
    //     //         break;
    //     //     }
    //     // }
    //     // if (flag == 0)
    //     // {
    //     //     printf("Contact not found\n");
    //     // }
    //     break;
    // case 2:
    //     // printf("Enter the phone");
    //     // scanf(" %[^\n]", input);
    //     // for (int i = 0; i < addressBook->contactCount; i++)
    //     // {
    //     //     if (strcmp(addressBook->contacts[i].phone, input) == 0)
    //     //     {
    //     //         printf("contact found\n");
    //     //         printf("%s\n", addressBook->contacts[i].name);
    //     //         printf("%s\n", addressBook->contacts[i].phone);
    //     //         printf("%s\n", addressBook->contacts[i].email);
    //     //         flag = 1;
    //     //         break;
    //     //     }
    //     // }
    //     // if (flag == 0)
    //     // {
    //     //     printf("Contact not found\n");
    //     // }
    //     search_phone(addressBook);
    //     break;
    // case 3:
    //     // printf("Enter the email");
    //     // scanf(" %[^\n]", input);
    //     // for (int i = 0; i < addressBook->contactCount; i++)
    //     // {
    //     //     if (strcmp(addressBook->contacts[i].email, input) == 0)
    //     //     {
    //     //         printf("contact found\n");
    //     //         printf("%s\n", addressBook->contacts[i].name);
    //     //         printf("%s\n", addressBook->contacts[i].phone);
    //     //         printf("%s\n", addressBook->contacts[i].email);
    //     //         flag = 1;
    //     //         break;
    //     //     }
    //     // }
    //     // if (flag == 0)
    //     // {
    //     //     printf("Contact not found\n");
    //     // }
    //     search_mail(addressBook);
    //     break;
    // default:
    //     printf("Invalid choice. Please try again.\n");
    //     break;
    // }
    if (sort == 1)
    {
        ret = search_name(addressBook);
    }
    else if (sort == 2)
    {
        ret = search_phone(addressBook);
    }
    else if (sort == 3)
    {
        ret = search_mail(addressBook);
    }
    else if (sort == 4)
    {
        printf("Exiting search\n");
        return 2;
    }
    else
    {
        printf("Enter valid number");
    }
    return ret;
}

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("The contact is empty.\n");
        return;
    }
    int num = searchContact(addressBook);
    if (num == -1)
    {
        printf("Cannot edit non-existing contact.\n");
        return;
    }
    if (num == 2)
    {
        return;
    }
    // printf("Contact list\n");
    // for (int i = 0; i < addressBook->contactCount; i++)
    // {
    //     printf("%d %s %s %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    // }
    // int num;
    // printf("Enter the serial number you want to edit:");
    // scanf("%d", &num);
    // if (num < 1 || num > addressBook->contactCount)
    // {
    //     printf("---INVALID NUMBER---\n");
    //     return;
    // }
    int i = num;
    int choice;
    do
    {
        printf("Editing contact:%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        printf("What would you like to edit:\n1.Name\n2.Phone number\n3.mail\n4.Exit editing\n");
        printf("Enter the choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the new name:\n");
            scanf(" %[^\n]s", addressBook->contacts[i].name);
            printf("UPDATED SUCCESFULLY\n");
            break;
        case 2:
            do
            {
                printf("Enter new phone number:");
                scanf(" %[^\n]", addressBook->contacts[i].phone);
                if (!validphone(addressBook, addressBook->contacts[i].phone, i))
                {
                    printf("INVALID PHONE NUMBER\n");
                }
            } while (!validphone(addressBook, addressBook->contacts[i].phone, i));
            printf("UPDATED SUCESSFULLY\n");
            break;
        case 3:
            do
            {
                printf("Enter new email:");
                scanf(" %[^\n]", addressBook->contacts[i].email);
                if (!validphone(addressBook, addressBook->contacts[i].email, i))
                {
                    printf("INVALID EMAIL\n");
                }
            } while (!validphone(addressBook, addressBook->contacts[i].email, i));
            printf("UPDATED SUCESSFULLY\n");
            break;
        case 4:
            printf("Exiting editing\n");
            break;
        default:
        {
            printf("Invalid choice\n");
        }
        }
    } while (choice != 4);
    printf("CONTACT EDITED SUCCESSFULLY\n");
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("The contact is empty.\n");
        return;
    }
    int num = searchContact(addressBook);
    if (num == -1)
    {
        printf("Cannot delete non-existing contact.\n");
        return;
    }
    // printf("Contact list\n");
    // for (int i = 0; i < addressBook->contactCount; i++)
    // {
    //     printf("%d %s %s %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    // }
    // printf("Enter the serial number which you want to delete:\n");
    // int num;
    // scanf("%d", &num);
    // if (num > addressBook->contactCount || num < 1)
    // {
    //     printf("--INVALID INPUT--\nplease try again\n");
    //     return;
    // }
    int sure;
    printf("Are you sure to delete %s?(yes=1/no=0)\n", addressBook->contacts[num].name);
    scanf("%d", &sure);
    if (sure == 1)
    {
        for (int i = num; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("SUCCESSFULLY DELETED");
        return;
    }
    else
    {
        printf("CANCELLED");
        return;
    }
}
