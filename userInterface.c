/********************************************************************
 *
 * userInterface.c
 *
 *      This program is a main program for Computer dating
 *      application. This program repeatedly ask the user which
 *      operation he/she wants to do.
 *
 *      The option for menu page contains
 *
 *          [1] - Login
 *          [2] - Create new account
 *          [3] - Exit
 *
 *      The option for main menu contains
 *
 *          [1] - Add/Edit profile
 *          [2] - Find your partner
 *          [3] - Logout
 *
 *      When the user has selected his/her option, the program
 *      will redirect to other program which handles a different
 *      aspect of the program depending on the option.
 *
 *      Created by Jiajia      Bai   	   (Jia)   ID 63070503404
 *		           Sonia       Gautam 	   (Sonia) ID 63070503410
 *		           Tamonwan    Boonpa 	   (Nice)  ID 63070503418
 *                 Theeranont  Ruchiyakorn (Peak)  ID 63070503420
 *
 *      18 April 2021
 *
 ********************************************************************
 */

#include "datingApp.h"
#include "abstractHashTable.h"


/* private function */
/**************************************************************
 *
 * This function shows the main menu of the computer dating
 * application and repeatedly asks the user which operation
 * he or she wants to do, until the user selects logout.
 *
 * Add/Edit profile : Add or Edit user's personal information
 * Find match       : Find compatible partners
 * Logout           : Log out from the application
 *
 *      pUser      -      pointer to PERSON_T structure
 *                        holding logged in user's data
 *
 *************************************************************/
void mainMenu(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int option = 0;             /* to store selected option */

    printf("\033[2J\033[;H");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("*                                           *\n");
    printf("|                                           |\n");
    printf("*         COMPUTER DATING APPLICATION       *\n");
    printf("|               WELCOME BACK!!              |\n");
    printf("*                                           *\n");
    printf("|                                           |\n");

    while (1)
        {
        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("|                                           |\n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("*        [ 1 ]     ADD/EDIT PROFILE         *\n");
        printf("|                                           |\n");
        printf("*        [ 2 ]     FIND YOUR PARTNER        *\n");
        printf("|                                           |\n");
        printf("*        [ 3 ]     LOGOUT                   *\n");
        printf("|                                           |\n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("* _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ *\n");
        printf("\n\n");

        printf("Which option do you want to do : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&option);

        if (option == 1)
            {
            printf("\033[2J\033[;H");
            addEditProfile(pPerson);
            }
        else if (option == 2)
            {
            printf("\033[2J\033[;H");
            findMatch(pPerson);
            }
        else if (option == 3)
            {
            printf("\033[2J\033[;H");
            break;
            }
        else
            {
            printf("\n\tInvalid option - should be an integer between 1 and 3\n");
            }
        option = 0;
        printf("\n");
        }
    }

/**************************************************************
 *
 * This is the main function of computer dating application.
 * This function shows the menu, and repeatedly asks the user
 * which operation he or she wants to do, until the user
 * selects exit. Then the program will exit.
 *
 * Login              : Log into the application
 * Create new account : Create an account in the application
 * Exit               : Exit the application
 *
 *************************************************************/
int main(int argc, char* argv[])
    {
    char stringInput[32];       /* to get input from the user */
    PERSON_T* pUser = NULL;     /* to store and pass logged in user's data */
    int option = 0;             /* to store selected option */

    /* initialize the tree */
    createNewTree();

    /* check if the file exist or not and read user's data from the file */
    readFile();

    while (1)
        {
        pUser = NULL;

        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("*                 WELCOME TO                *\n");
        printf("|         COMPUTER DATING APPLICATION       |\n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("*                                           *\n");
        printf("|        [ 1 ]     LOGIN                    |\n");
        printf("*                                           *\n");
        printf("|        [ 2 ]     CREATE NEW ACCOUNT       |\n");
        printf("*                                           *\n");
        printf("|        [ 3 ]     EXIT                     |\n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("* _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ *\n");
        printf("\n\n");

        printf("Which option do you want to do : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&option);

        switch (option)
            {
            case 1:
                if ((checkFile() == 0) || (readToCount() == 0))
                    {
                    printf("\n\tThe database is currently empty!\n");
                    }
                else
                    {
                    printf("\033[2J\033[;H");
                    pUser = login();
                    if (pUser != NULL)
                        mainMenu(pUser);
                    }
                break;
            case 2:
                printf("\033[2J\033[;H");
                createNewProfile();
                break;
            case 3:
                hashTableFree();
                freeTree();
                printf("\n       Hope you enjoyed our application!");
                printf("\n\t   *  Have a nice day :)  * \n\n");
                exit(0);
            default:
                printf("\n\tInvalid option - should be an integer between 1 and 3\n");
            }
        option = 0;
        printf("\n");
        }
    }
