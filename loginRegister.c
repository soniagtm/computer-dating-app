/********************************************************************
 *
 * loginRegister.c
 *
 *      This program is responsible for creating new account
 *   	for new user and for logging into the system. Necessary
 *		information will be asked and checked. New user's
 *      information will be saved into the database file.
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

/* Declaration of some functions used in loginRegister.c */
void getInfo(PERSON_T* pNew);
int getUsername(char* pUsername);
int getPassword(char* pPassword);


/* public function */
/**************************************************************
 *
 * This function is the major function for logging into
 * computer dating application.
 *
 * This function will call responsible functions to get
 * and check the username and password. If the information
 * entered is found in the database file, the user will
 * be logged into the computer dating application.
 *
 * No argument.
 *
 * This function returns 'pUser' which is pointer to PERSON_T
 * structure to pass the logged in user's information.
 *
 *************************************************************/
PERSON_T* login()
    {
    PERSON_T* pUser = NULL;     /* pointer to PERSON_T structure */
                                /* to return logged in person's data */
    char username[MAXLEN];      /* to store the entered username */
    char password[MAXLEN];      /* to store the entered password */
    int status = 0;             /* to store return value from other function */

    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("*                                           *\n");
    printf("|                                           |\n");
    printf("*                 LOG INTO                  *\n");
    printf("|         COMPUTER DATING APPLICATION       |\n");
    printf("*                                           *\n");
    printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
    printf("\n\n");

    /* get the username */
    status = getUsername(username);

    if (status != 0)
        {
        /* check if the username exists in the memory or not */
        pUser = hashTableLookup(username);

        if (pUser == NULL)
            printf("\n\tError - No user found with this username!\n");
        else
            {
            while (1)
                {
                /* get the password */
                status = getPassword(password);
                if (status == 0)
                    {
                    pUser = NULL;
                    break;
                    }

                /* compare entered password with the real one */
                if (strcasecmp(password,pUser->password) == 0)
                    {
                    break;
                    }
                else
                    {
                    printf("\t\tIncorrect password - Try again!!\n");
                    }

                }
            }
        }

    return pUser;
    }


/* public function */
/**************************************************************
 *
 * This function is the major function for creating new
 * account in computer dating application.
 *
 * This function will call responsible functions to get
 * and validate some information. Then, this function
 * will call responsible function to save new member's
 * data into the file.
 *
 * No argument.
 *
 *************************************************************/
void createNewProfile()
    {
    PERSON_T* pNew = NULL;      /* pointer to PERSON_T structure */
                                /* to add new person's data */
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[MAXLEN];        /* to track if user wants to
                                /* create an account or not */
    int personCount = 0;        /* to get number of people in the file */

    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("*                                           *\n");
    printf("|                                           |\n");
    printf("*            CREATE AN ACCOUNT IN           *\n");
    printf("|         COMPUTER DATING APPLICATION       |\n");
    printf("*                                           *\n");
    printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");

    printf("\n\n        Please fill in all information!\n\n");

    pNew = (PERSON_T*) calloc(1,sizeof(PERSON_T));
    if (pNew == NULL)
        {
        printf("Memory allocation error \n");
        exit(0);
        }

    getInfo(pNew);

    printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("\n  Are you sure you want to create an account with given information?\n");
    printf("  Y - yes , other alphabet - no : ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%s",demand);

    if (strcasecmp(demand,"Y") != 0)
        {
        printf("\n\t * Denied account creation *\n");
        }
    else
        {
        /* get the number of people in the file
         * and add 1 for the new user */
        personCount = readToCount();
        personCount++;

        /* add new user's information to the file */
        addNewData(pNew,personCount);
        printf("\n\t* Successfully created an account for %s! *\n",pNew->name);
        }

    }


/* private function */
/**************************************************************
 *
 * This function calls responsible functions to get and
 * validate name, email, username, and password of new user.
 *
 * pNew is a pointer to PERSON_T structure to store new
 * user's data.
 *
 *************************************************************/
void getInfo(PERSON_T* pNew)
    {
    /* get the name */
    addName(pNew->name);

    while (1)
        {
        /* get the email */
        addEmail(pNew->email);

        /* check if the entered email already exist or not */
        if (checkDuplicateEmail(pNew->email) == 1)
            break;
        else
            printf("\t\tThis email already exist!\n");
        }

    while (1)
        {
        /* get the username */
        addUsername(pNew->username);

        /* check if the entered username already exist or not */
        if (checkDuplicateUsername(pNew->username) == 1)
            break;
        else
            printf("\t\tThis username already exist!\n");
        }

    /* get the password */
    addPassword(pNew->password);
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * username and checking if it is valid or not by
 * calling 'validateUsername' function.
 *
 * pUsername is a pointer to get the username and store the
 * username to the variable in that address.
 *
 * This function returns 'status' which is 0 when the user
 * didn't enter the username, otherwise 1.
 *
 *************************************************************/
int getUsername(char* pUsername)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char username[MAXLEN];      /* to temporary store the username */
    int status = 1;             /* to return if data is entered or not */

    printf("(Press ENTER if you want to go back to menu)\n\n");
    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Enter username : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            status = 0;
            break;
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",username);
            if (validateUsername(username) == 1)
                {
                strcpy(pUsername,username);
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * password and checking if it is valid or not by
 * calling 'validatePassword' function.
 *
 * pPassword is a pointer to get the password and store the
 * password to the variable in that address.
 *
 * This function returns 'status' which is 0 when the user
 * didn't enter the password, otherwise 1.
 *
 *************************************************************/
int getPassword(char* pPassword)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char password[MAXLEN];      /* to temporary store the password */
    char demand[16];            /* to track if user wants to go back or not */
    int status = 1;             /* to return if data is entered or not */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Enter password : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\n  Are you sure you want to go back to menu?\n");
            printf("  Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") == 0)
                {
                status = 0;
                break;
                }
            printf("\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",password);
            if (validatePassword(password) == 1)
                {
                strcpy(pPassword,password);
                break;
                }

            }
        }
    return status;
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * name and checking if it is valid or not by calling
 * 'validateName' function.
 *
 * pName is a pointer to get the address and store the
 * name to the variable in that address.
 *
 *************************************************************/
void addName(char* pName)
    {
    char stringInput[MAXLEN];    /* to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Name              : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the name\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pName);

            if (validateName(pName) == 1)
                {
                break;
                }
            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * email and checking if it is valid or not by calling
 * 'validateEmail' function.
 *
 * pEmail is a pointer to get the address and store the
 * email to the variable in that address.
 *
 *************************************************************/
void addEmail(char* pEmail)
    {
    char stringInput[MAXLEN];    /* to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Email             : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the email\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pEmail);

            if (validateEmail(pEmail) == 1)
                {
                break;
                }
            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * username and checking if it is valid or not by calling
 * 'validateUsername' function.
 *
 * pUsername is a pointer to get the address and store the
 * username to the variable in that address.
 *
 *************************************************************/
void addUsername(char* pUsername)
    {
    char stringInput[MAXLEN];    /* to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Username          : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the username\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pUsername);

            if (validateUsername(pUsername) == 1)
                {
                break;
                }

            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * password and checking if it is valid or not by calling
 * 'validatePassword' function.
 *
 * pPassword is a pointer to get the address and store the
 * password to the variable in that address.
 *
 *************************************************************/
void addPassword(char* pPassword)
    {
    char stringInput[MAXLEN];    /* to get input from the user */

    printf("\n\n Password rules\n");
    printf(" - - - - - - - - \n");
    printf("  *  8-12 characters long\n");
    printf("  *  At least two digits\n");
    printf("  *  At least one uppercase and one lowercase letter\n");
    printf("  *  At least one of the following special characters\n");
    printf("  *  ? @ %% $ # (others are not allowed)\n\n");

    while(1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  Password          : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the password\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pPassword);

            if (validatePassword(pPassword) == 1)
                {
                break;
                }

            }
        }
    }


