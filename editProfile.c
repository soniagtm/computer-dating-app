/********************************************************************
 *
 * editProfile.c
 *
 *      This program is responsible for modifying user's
 *   	information and calling responsible functions to
 *		update the tree, hash table as appropriate and
 *      update modified data in database file.
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

/* Declaration of some functions used in editProfile.c */
void editPreference(PERSON_T* pPerson, int option);
void editPersonalInfo(PERSON_T* pPerson, int option);


/* private function */
/**************************************************************
 *
 * This function asks the user to enter the option he/she
 * wants to modify.
 *
 * type is the category he/she wanted to modify
 *      1   -   Personal information (11 options)
 *      2   -   Preference (5 options)
 *
 * This function returns 'option' which is the option
 * the user wants to modify.
 *
 *************************************************************/
int getOption(int type)
    {
    int option = 0;                 /* to store selected option */
    char stringInput[MAXLEN];       /* to get input from the user */

    while (1)
        {
        option = 0;
        printf("\n  Which option do you want to modify?");
        printf("\n  (press ENTER to back) : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            break;

        sscanf(stringInput,"%d",&option);

        if (type == 1)
            {
            /* category : personal information */
            if ((option > 11) || (option < 1))
                {
                printf("\n\tinvalid option - should be an integer between 1 and 11\n");
                }
            else
                break;
            }
        else
            {
            /* category : preference */
            if ((option > 5) || (option == 0))
                {
                printf("\n\tinvalid option - should be an integer between 1 and 5\n");
                }
            else
                break;
            }

        }
    return option;
    }


/* public function */
/**************************************************************
 *
 * This function asks the user which category he/she wants
 * to modify (Personal information or preference)
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'edit' which is the category
 * that the user wants to modify (3 means back to menu)
 *
 *************************************************************/
int editInfo(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int option = 0;             /* to store selected option */
    int edit = 0;               /* to store category that user wants to modify */

    printf("\033[2J\033[;H");
    while (1)
        {
        printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
        printf("     Which category do you want to modify?\n\n");
        printf("\t  [01]   Personal information\n");
        printf("\t  [02]   Preference\n");
        printf("\t  [03]   Back to main menu\n\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");

        printf("     >> Enter your choice : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&edit);

        if (edit == 1)
            {
            printf("\033[2J\033[;H");

            /* display user's personal information */
            printEditInfo(pPerson,edit);

            /* get option of data to be modified */
            option = getOption(edit);

            /* modify that data */
            editPersonalInfo(pPerson,option);
            }
        else if (edit == 2)
            {
            printf("\033[2J\033[;H");

            /* display user's preference */
            printEditInfo(pPerson,edit);

            /* get option of data to be modified */
            option = getOption(edit);

            /* modify that data*/
            editPreference(pPerson,option);
            }
        else if (edit == 3)
            {
            break;
            }
        else
            {
            printf("\n\tinvalid option - should be an integer between 1 and 3\n");
            }
        }

    return edit;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new name and checks if it is the same with the current
 * name or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the name
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewName(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char name[MAXLEN];          /* to temporary store the new name */
    char demand[16];            /* to track if user wants to modify or not */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        addName(name);
        if (strcmp(name,pPerson->name) != 0)
            {
            strcpy(pPerson->name,name);
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old name\n\n");
            printf("     Do you want to change your name?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new email and checks if it is the same with the current
 * email or not. If not, the functions calls the responsible
 * function to check if the new email already exist or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the email
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewEmail(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char email[MAXLEN];         /* to temporary store the new email */
    char demand[16];            /* to track if user wants to modify or not */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        addEmail(email);
        if (strcmp(email,pPerson->email) != 0)
            {
            /* check if new email is in-use or not */
            if (checkDuplicateEmail(email) == 1)
                {
                strcpy(pPerson->email,email);
                status = 1;
                break;
                }
            else
                printf("\t\tThis username already exist!\n");
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old email\n\n");
            printf("     Do you want to change your email?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new username and checks if it is the same with the current
 * username or not. If not, the functions calls the responsible
 * function to check if the new username already exist or not.
 * Then, remove the old and insert the new username into the
 * hash table.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 2 if the username
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewUsername(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char username[MAXLEN];      /* to temporary store the new username */
    char demand[16];            /* to track if user wants to modify or not */
    int result = 0;             /* to store return value from other function */
    int status = 0;             /* to return if data is modified or not */
    int pCollision = 0;         /* store collision status */

    while (1)
        {
        printf("\n");
        addUsername(username);
        if (strcmp(username,pPerson->username) != 0)
            {
            /* check if new username is in-use or not */
            if (checkDuplicateUsername(username) == 1)
                {
                /* remove old key from the hash table */
                if (hashTableRemove(pPerson->username) != NULL)
                    {
                    strcpy(pPerson->username,username);

                    /* insert data with new username as a key */
                    result = hashTableInsert(pPerson->username,pPerson,&pCollision);
                    if (result == 0)
                        {
                        printf("\n\tError occurred while inserting %s's information \
                               into hash table!\n",pPerson->name);
                        exit(0);
                        }
                    status = 2;
                    break;
                    }
                }
            else
                {
                printf("\t\tThis username already exist!\n");
                }
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old username\n\n");
            printf("     Do you want to change your username?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }

    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new password and checks if it is the same with the current
 * password or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the password
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewPassword(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char password[MAXLEN];      /* to temporary store the new password */
    char demand[16];            /* to track if user wants to modify or not */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        memset(password,0,sizeof(password));
        memset(demand,0,sizeof(demand));
        memset(stringInput,0,sizeof(stringInput));
        printf("\n");

        /* let the user enter his/her current password */
        printf("Enter your current password : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the password\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",password);

            /* check if the password matched with the real one or not */
            if (strcmp(password,pPerson->password) == 0)
                {
                addPassword(password);

                if (strcmp(password,pPerson->password) != 0)
                    {
                    strcpy(pPerson->password,password);
                    status = 1;
                    break;
                    }
                else
                    {
                    printf("\t\tNot valid - cannot use your old password\n\n");
                    printf("     Do you want to change your password?\n");
                    printf("     Y - yes , other alphabet - no : ");
                    fgets(stringInput,sizeof(stringInput),stdin);
                    sscanf(stringInput,"%s",demand);

                    if (strcasecmp(demand,"Y") != 0)
                        {
                        break;
                        }
                    }
                }
            else
                {
                printf("\n\t\tCurrent password incorrect!!\n\n");
                printf("     Do you want to re-enter current password?\n");
                printf("     Y - yes , other alphabet - no : ");
                fgets(stringInput,sizeof(stringInput),stdin);
                sscanf(stringInput,"%s",demand);

                if (strcasecmp(demand,"Y") != 0)
                    {
                    break;
                    }
                }
            }

        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function asks if the user wants to change his/her
 * gender or not. If yes, the gender will be changed.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the gender
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewGender(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    char newGender[16];         /* to temporary store the new gender */
    int status = 0;             /* to return if data is modified or not */

    if (strcmp(pPerson->gender,"M") == 0)
        strcpy(newGender,"F");
    else
        strcpy(newGender,"M");

    printf("\n     Do you want to change your gender from '%s' to '%s' ?\n"
           ,pPerson->gender,newGender);
    printf("     Y - yes , other alphabet - no : ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%s",demand);

    if (strcasecmp(demand,"Y") == 0)
        {
        strcpy(pPerson->gender,newGender);
        status = 1;
        }

    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new location and checks if it is the same with the current
 * location or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the location
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewLocation(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char location[MAXLEN];      /* to temporary store the new location */
    char demand[16];            /* to track if user wants to modify or not */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getLocation(location);
        if (strcmp(location,pPerson->location) != 0)
            {
            strcpy(pPerson->location,location);
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old location\n\n");
            printf("     Do you want to change your location?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new age and checks if it is the same with the current
 * age or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the age
 * is changed, otherwise 0.
 *
 *************************************************************/
int getNewAge(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int status = 0;             /* to return if data is modified or not */
    int age = 0;                /* to temporary store the new age */

    while (1)
        {
        printf("\n");
        getAge(&age);

        if (age != pPerson->age)
            {
            pPerson->age = age;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old age\n\n");
            printf("     Do you want to change your age?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new ethnicity and checks if it is the same with the
 * current ethnicity or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the
 * ethnicity is changed, otherwise 0.
 *
 *************************************************************/
int getNewEthnicity(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int ethnicity = 0;          /* to temporary store the new ethnicity */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getEthnicity(&ethnicity);
        if (ethnicity != pPerson->ethnicity)
            {
            pPerson->ethnicity = ethnicity;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old ethnicity\n\n");
            printf("     Do you want to change your ethnicity?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new religion and checks if it is the same with the
 * current religion or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the
 * religion is changed, otherwise 0.
 *
 *************************************************************/
int getNewReligion(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int religion = 0;           /* to temporary store the new religion */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getReligion(&religion);
        if (religion != pPerson->religion)
            {
            pPerson->religion = religion;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old religion\n\n");
            printf("     Do you want to change your religion?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new education level and checks if it is the same
 * with the current education level or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the
 * education level is changed, otherwise 0.
 *
 *************************************************************/
int getNewEduLev(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int eduLev = 0;             /* to temporary store the new education level */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getEducationLevel(&eduLev);
        if (eduLev != pPerson->eduLevBitstring)
            {
            pPerson->eduLevBitstring = eduLev;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old education level\n\n");
            printf("     Do you want to change your education level?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new occupation and checks if it is the same with the
 * current occupation or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the
 * occupation is changed, otherwise 0.
 *
 *************************************************************/
int getNewOccupation(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int occupation = 0;         /* to temporary store the new occupation */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getOccupation(&occupation);
        if (occupation != pPerson->workBitstring)
            {
            pPerson->workBitstring = occupation;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old occupation\n\n");
            printf("     Do you want to change your occupation?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new favorite cuisine(s) and checks if it is the same with
 * the current favorite cuisine(s) or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the favorite
 * cuisine(s) is changed, otherwise 0.
 *
 *************************************************************/
int getNewFavFood(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int favFood = 0;            /* to temporary store the new favorite cuisine */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getFavCuisine(&favFood);
        if (favFood != pPerson->foodBitstring)
            {
            pPerson->foodBitstring = favFood;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old preference for food\n\n");
            printf("     Do you want to change your preference for food?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new favorite pet(s) and checks if it is the same with
 * the current favorite pet(s) or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the favorite
 * pet(s) is changed, otherwise 0.
 *
 *************************************************************/
int getNewFavPet(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int favPet = 0;             /* to temporary store the new favorite pet */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getFavPet(&favPet);
        if (favPet != pPerson->petBitstring)
            {
            pPerson->petBitstring = favPet;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old preference for pet\n\n");
            printf("     Do you want to change your preference for pet?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new favorite music genre(s) and checks if it is the same
 * with the current favorite music genre(s) or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the favorite
 * music genre(s) is changed, otherwise 0.
 *
 *************************************************************/
int getNewFavMusic(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int favMusic = 0;           /* to temporary store the new favorite music */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getFavMusic(&favMusic);
        if (favMusic != pPerson->musicBitstring)
            {
            pPerson->musicBitstring = favMusic;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old preference for music\n\n");
            printf("     Do you want to change your preference for music?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new favorite hobby/hobbies and checks if it is the same
 * with the current favorite hobby/hobbies or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the favorite
 * hobby/hobbies is changed, otherwise 0.
 *
 *************************************************************/
int getNewFavHobby(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int favHobby = 0;           /* to temporary store the new favorite hobby */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getFavHobby(&favHobby);
        if (favHobby != pPerson->hobbyBitstring)
            {
            pPerson->hobbyBitstring = favHobby;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old preference for hobby\n\n");
            printf("     Do you want to change your preference for hobby?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to get the
 * new favorite film genre(s) and checks if it is the same
 * with the current favorite film genre(s) or not.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 * This function returns 'status' which is 1 if the favorite
 * film genre(s) is changed, otherwise 0.
 *
 *************************************************************/
int getNewFavMovie(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to track if user wants to modify or not */
    int favMovie = 0;           /* to temporary store the new favorite movie */
    int status = 0;             /* to return if data is modified or not */

    while (1)
        {
        printf("\n");
        getFavMovie(&favMovie);
        if (favMovie != pPerson->movieBitstring)
            {
            pPerson->movieBitstring = favMovie;
            status = 1;
            break;
            }
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\t\tNot valid - cannot use your old preference for pet\n\n");
            printf("     Do you want to change your preference for pet?\n");
            printf("     Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            }
        }
    return status;
    }


/* private function */
/**************************************************************
 *
 * This function gets new data from the user to modify
 * selected option from the options below
 *
 *      -   Name
 *      -   Email
 *      -   Username
 *      -   Password
 *      -   Gender
 *      -   Location
 *      -   Age
 *      -   Ethnicity
 *      -   Religion
 *      -   Education level
 *      -   Occupation
 *
 * Arguments
 *      pPerson     -    a pointer to PERSON_T structure
 *                       holding logged in user's data
 *      option      -    the option that user wants
 *                       to modify
 *
 *************************************************************/
void editPersonalInfo(PERSON_T* pPerson, int option)
    {
    int status = 0;                         /* to get return value from other functions */
    int attributeValue[4] = {0,0,0,0};      /* an array of integer to store values */
                                            /* of former exclusive attributes */

    /* store former exclusive attributes value*/
    if (option != 0)
        {
        if (strcmp(pPerson->gender, "M") == 0)
            attributeValue[0] = 1;
        else
            attributeValue[0] = 2;

        attributeValue[1] = pPerson->age;
        attributeValue[2] = pPerson->ethnicity;
        attributeValue[3] = pPerson->religion;

        switch (option)
            {
            case 1:
                status = getNewName(pPerson);
                break;
            case 2:
                status = getNewEmail(pPerson);
                break;
            case 3:
                status = getNewUsername(pPerson);
                break;
            case 4:
                status = getNewPassword(pPerson);
                break;
            case 5:
                status = getNewGender(pPerson);
                break;
            case 6:
                status = getNewLocation(pPerson);
                break;
            case 7:
                status = getNewAge(pPerson);
                break;
            case 8:
                status = getNewEthnicity(pPerson);
                break;
            case 9:
                status = getNewReligion(pPerson);
                break;
            case 10:
                status = getNewEduLev(pPerson);
                break;
            case 11:
                status = getNewOccupation(pPerson);
                break;
            }

        /* check if the data was changed or not */
        if (status > 0)
            {
            /* update the data in the file */
            addPersonalData(pPerson,status);

            /* if one of the exclusive attribute values is changed */
            /* change the list that the user is in */
            if ((option == 5) || (option == 7) || (option == 8) || (option == 9))
                {
                transferPerson(pPerson,attributeValue);
                }
            }
        }
    }


/* private function */
/**************************************************************
 *
 * This function gets new data from the user to modify
 * selected option from the options below
 *
 *      -   Food preference
 *      -   Pet preference
 *      -   Music preference
 *      -   Hobby preference
 *      -   Movie preference
 *
 * Arguments
 * pPerson     is  pointer to PERSON_T structure holding
 *             logged in user's data
 * option      the option that user wants to modify
 *
 *************************************************************/
void editPreference(PERSON_T* pPerson, int option)
    {
    int status = 0;     /* to get return value from other functions */

    if (option != 0)
        {
        switch (option)
            {
            case 1:
                status = getNewFavFood(pPerson);
                break;
            case 2:
                status = getNewFavPet(pPerson);
                break;
            case 3:
                status = getNewFavMusic(pPerson);
                break;
            case 4:
                status = getNewFavHobby(pPerson);
                break;
            case 5:
                status = getNewFavMovie(pPerson);
                break;
            }

        /* check if the data was changed or not */
        if (status > 0)
            {
            /* update the data in the file */
            addPersonalData(pPerson,status);
            }
        }
    }
