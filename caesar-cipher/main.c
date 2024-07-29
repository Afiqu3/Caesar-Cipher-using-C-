#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MSG_LENGTH 500
#include "logo.h"

//user details
struct details
{
    char handle[50];
    char email[100];
    char password[100];
};

//for encoding message
void encode(char msg[], int s)
{
    for(int i = 0; msg[i] != '\0'; i++)
    {
        if(msg[i] >= 'A' && msg[i] <= 'Z')
        {
            if((msg[i] + s) > 'Z')
            {
                msg[i] = 'Z' - msg[i];
                msg[i] = '@' + s - msg[i];
            }
            else
            {
                msg[i] += s;
            }
        }
        if(msg[i] >= 'a' && msg[i] <= 'z')
        {
            if((msg[i] + s) > 'z')
            {
                msg[i] = 'z' - msg[i];
                msg[i] = '`' + s - msg[i];
            }
            else
            {
                msg[i] += s;
            }
        }
    }

    printf("Here's the encoded result: %s\n", msg);
}

//for decoding message
void decode(char msg[], int s)
{
    for(int i = 0; msg[i] != '\0'; i++)
    {
        if(msg[i] >= 'A' && msg[i] <= 'Z')
        {
            if((msg[i] - s) < 'A')
            {
                msg[i] = msg[i] - 'A';
                msg[i] = '[' - (s - msg[i]);
            }
            else
            {
                msg[i] -= s;
            }
        }
        if(msg[i] >= 'a' && msg[i] <= 'z')
        {
            if((msg[i] - s) < 'a')
            {
                msg[i] = msg[i] - 'a';
                msg[i] = '{' - (s - msg[i]);
            }
            else
            {
                msg[i] -= s;
            }
        }
    }

    printf("Here's the decoded result: %s\n", msg);
}

//ceasar-cipher
void ce_ci()
{

    printf("\n\n");

    char choice[10], choice1[5];
    int end = 0;

    //repeating process to do encoding and decoding
    while(end != 1)
    {
        int shift;
        char message[MSG_LENGTH];

        //ask user to encrypt or decrypt
        printf("Type 'encode' to encrypt, type 'decode' to decrypt: ");
        //read user choice
        gets(choice);
        fflush(stdin);

        //when user want to encrypt
        if(strcasecmp(choice, "encode") == 0)
        {
            printf("Type your message(under 500 characters):\n");
            gets(message);
            fflush(stdin);
            printf("Type the shift number: ");
            scanf("%d", &shift);
            //if someone enter above 26
            shift = shift % 26;
            encode(message, shift);
        }
        //when user want to decrypt
        else if(strcasecmp(choice, "decode") == 0)
        {
            printf("Type your message(under 500 characters):\n");
            gets(message);
            fflush(stdin);
            printf("Type the shift number: ");
            scanf("%d", &shift);
            //if someone enter above 26
            shift = shift % 26;
            decode(message, shift);
        }
        //when user enter invalid choice
        else
        {
            printf("Wrong Keyword.\n");
            printf("Good bye.\n");
            break;
        }


        //ask user whether he wanted to encrypt or decrypt again
        printf("Type 'yes' if you want to go again. Otherwise type 'no'.\n");
        //read user choice
        scanf("%s", choice1);
        fflush(stdin);


        if(strcasecmp(choice1, "yes") == 0)
        {
            end = 0;
        }
        //if user do not want go again
        else if(strcasecmp(choice1, "no") == 0)
        {
            end = 1;
            printf("Good bye.\n");
        }
        //if user enter wrong word
        else
        {
            printf("Invalid keyword.\n");
            printf("Good bye.\n");
            end = 1;
        }
    }
}

//when user have no account
void signup(struct details d[], int index)
{
    int cor_han = 0;
    //check for valid handle
    while(cor_han != 1)
    {
        cor_han = 1;
        printf("Enter your handle: ");
        scanf("%s", d[index].handle);
        fflush(stdin);
        for(int j = 0; j < index; j++)
        {
            if(strcmp(d[j].handle, d[index].handle) == 0)
            {
                cor_han = 0;
                printf("Choose another handle.\n");
            }
        }
    }

    int correct_mail = 0;
    //check for email
    while(correct_mail != 2)
    {
        correct_mail = 0;
        printf("Enter your email: ");
        gets(d[index].email);
        fflush(stdin);
        for(int j = 0; d[index].email[j] != '\0'; j++)
        {
            if(d[index].email[j] == '@' || d[index].email[j] == '.')
            {
                correct_mail++;
            }
        }
        if(correct_mail < 2)
        {
            printf("Invalid mail.\n");
        }
    }
    //take password
    printf("Enter your password: ");
    char ch;
    int i = 0;
    //take password
    ch = getch();
    while(ch != '\r')
    {
        d[index].password[i++] = ch;
        //other people can't understand his password
        printf("*");
        ch = getch();
    }
    d[index].password[i] = '\0';
    fflush(stdin);
}

void login(struct details d[], int index)
{
    int correct = 0;
    //check whether user enter both handle and password correct
    while(correct != 1)
    {
        char hdle[50], pass[100];
        printf("Enter handle: ");
        scanf("%s", hdle);
        fflush(stdin);
        printf("Enter password: ");
        char ch;
        int i = 0;
        ch = getch();
        while(ch != '\r')
        {
            pass[i++] = ch;
            printf("*");
            ch = getch();
        }
        pass[i] = '\0';
        fflush(stdin);
        //check both handle and password
        for(int i = 0; i < index; i++)
        {
            if(strcmp(d[i].handle, hdle) == 0)
            {
                if(strcmp(d[i].password, pass) == 0)
                {
                    correct = 1;
                }
            }
        }
        //if user not correct
        if(correct == 0)
        {
            printf("\nIncorrect Handle or password.\n");
        }
        //if user enter wrong
        else
        {
            printf("\nSuccessfully login.\n");
        }
    }
}

int main ()
{
    //print logo
    logo();

    printf("\n\n");
    struct details ud[100];
    int idx = 0, choice, end = 0;

    //start everything
    while(end != 1)
    {
        printf("\t\t\t\t 1.Log in \n"
               "\t\t\t\t 2.Sign up \n"
               "\t\t\t\t 3.Exit \n");
        printf("Enter your choice 1, 2 or 3: ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            login(ud, idx);
            ce_ci();
            break;
        case 2:
            signup(ud, idx++);
            break;
        case 3:
            //end if want to exit
            end = 1;
            printf("Exited successfully.\n");
            break;
        default:
            printf("Invalid keyword.\n");
            break;
        }
        printf("\n");
    }
    return 0;
}
