/********************************************************************
 *
 * addProfile.c
 *
 *      This program is responsible for adding new user's
 *   	information and calling editing function in
 *		editProfile.c to modify the user's information.
 *
 *      Created by Jiajia      Bai   	   (Jia)   ID 63070503404
 *		           Sonia       Gautam 	   (Sonia) ID 63070503410
 *		           Tamonwan    Boonpa 	   (Nice)  ID 63070503418
 *                 Theeranont  Ruchiyakorn (Peak)  ID 63070503420
 *
 *      22 May 2021
 *
 ********************************************************************
 */

#include "datingApp.h"
#include "abstractHashTable.h"

/* global variables */

/* an array of unsigned int holding bit-strings with different
   position of '1' to represent each choice */
unsigned int bitConstants[6] = {0b000001,0b000010,0b000100,
                                0b001000,0b010000,0b100000};

/* an array of string holding choices for age */
char age[MAXCHOICE][MAXLEN] = {"Between 18 and 22","Between 23 and 27",
                               "Between 28 and 35","Between 36 and 46",
                               "Between 47 and 58","Above 59 years old"};

/* an array of string holding choices for ethnicity */
char ethnicity[MAXCHOICE][MAXLEN] = {"Thai","Chinese","Indian",
                                     "Caucasian","African","Others"};

/* an array of string holding choices for religion */
char religion[MAXCHOICE][MAXLEN] = {"Christianity","Islam","Hinduism",
                                    "Buddhism","No religion","Others"};

/* an array of string holding choices for education level */
char eduLev[MAXCHOICE][MAXLEN] = {"Primary Education","Secondary Education",
                                  "Bachelor's Degree","Master's Degree",
                                  "Doctor of Philosophy","Others"};

/* an array of string holding choices for occupation */
char occupation[MAXCHOICE][MAXLEN] = {"Student","Engineer","Doctor",
                                      "Teacher","Chef","Others"};

/* an array of string holding choices for cuisine */
char cuisine[MAXCHOICE][MAXLEN] = {"Thai cuisine","Chinese cuisine",
                                   "Korean cuisine","Japanese cuisine",
                                   "Italian cuisine","Others"};

/* an array of string holding choices for pet */
char pet[MAXCHOICE][MAXLEN] = {"Dogs","Cats","Rabbits","Birds",
                               "Hamsters","Others"};

/* an array of string holding choices for music */
char music[MAXCHOICE][MAXLEN] = {"Country","Pop","Jazz","R&B",
                                 "Rock","Others"};

/* an array of string holding choices for hobby */
char hobby[MAXCHOICE][MAXLEN] = {"Sports","Music","Cooking",
                                 "Games","Reading","Others"};

/* an array of string holding choices for movie */
char movie[MAXCHOICE][MAXLEN] = {"Romance","Action","Horror",
                                 "Science fiction","Comedy","Others"};


/* Declaration of some functions used in addProfile.c */
int getRegion();
void addInfo(PERSON_T* pPerson);
void passLocation(int location);
void printProfile(PERSON_T* pPerson);
void displayLocation(char location[][MAXLEN], int locationCount);
int compareSimilar(unsigned int personBit, unsigned int partnerBit);


/* public function */
/**************************************************************
 *
 * This function is the major function for adding and editing
 * personal information of the user.
 *
 * If the user hasn't filled his/her information yet, this
 * function will call responsible function to ask his/her data.
 *
 * This function will call responsible function to display
 * current information and call editing function if he/she
 * wants to modify the information.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 *************************************************************/
void addEditProfile(PERSON_T* pPerson)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[MAXLEN];        /* to store reply if user wants to modify or not */

    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("*                                           *\n");
    printf("|                                           |\n");
    printf("*                 ADD/EDIT                  *\n");
    printf("|           PERSONAL INFORMATION            |\n");
    printf("*                                           *\n");
    printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");

    /* check if the user has filled his/her information */
    if (checkGender(pPerson->gender) == 0)
        addInfo(pPerson);

    while (1)
        {
        /* display user's profile */
        printf("\n  *  %s's profile\n",pPerson->name);
        printProfile(pPerson);

        printf("\n* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
        printf("     Do you want to modify your information?\n");
        printf("     Y - yes , other alphabet - no : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%s",demand);
        printf("\n* * * * * * * * * * * * * * * * * * * * * * * * *");

        if (strcasecmp(demand,"Y") == 0)
            {
            /* call modifying function */
            if (editInfo(pPerson) == 3)
                break;
            }
        else
            break;
        }

    }


/* private function */
/**************************************************************
 *
 * This function calls responsible functions to ask the
 * user's data which contains
 *
 *      -   Gender
 *      -   Location
 *      -   Age
 *      -   Ethnicity
 *      -   Religion
 *      -   Education level
 *      -   Occupation
 *      -   Favorite cuisine
 *      -   Favorite pet
 *      -   Favorite music genre
 *      -   Favorite hobby
 *      -   Favorite film genre
 *
 * Then, this function will save the information into the file
 * and add the user into the tree corresponding to the attributes.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 *************************************************************/
void addInfo(PERSON_T* pPerson)
    {
    printf("\n    You haven't fill your information yet!");
    printf("\n      Please fill the information below \n\n\n");

    /* get information */
    getGender(pPerson->gender);
    getLocation(pPerson->location);
    getAge(&pPerson->age);
    getEthnicity(&pPerson->ethnicity);
    getReligion(&pPerson->religion);
    getEducationLevel(&pPerson->eduLevBitstring);
    getOccupation(&pPerson->workBitstring);
    getFavCuisine(&pPerson->foodBitstring);
    getFavPet(&pPerson->petBitstring);
    getFavMusic(&pPerson->musicBitstring);
    getFavHobby(&pPerson->hobbyBitstring);
    getFavMovie(&pPerson->movieBitstring);

    printf("\033[2J\033[;H");

    /* update the data in the file */
    addPersonalData(pPerson,1);

    /* insert the user to the appropriate list */
    addNewPerson(pPerson);
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * gender and checking if it is valid or not by
 * calling 'checkGender' function.
 *
 * pGender is a pointer to get the gender and store the
 * gender to the variable in that address.
 *
 *************************************************************/
void getGender(char* pGender)
    {
    char stringInput[MAXLEN];    /* to get input from the user */

    printf(" Gender -> 'M' for Male, 'F' for Female\n");

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  GENDER            : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the gender\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pGender);

            if (checkGender(pGender) == 1)
                {
                pGender[0] = toupper(pGender[0]);
                break;
                }
            else
                {
                printf("\t\tNot valid - please enter 'M' or 'F'\n");
                }
            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for asking the user's
 * location and checking if it is valid or not by
 * calling 'validateLocation' function.
 *
 * pLocation is a pointer to get the location and store the
 * location to the variable in that address.
 *
 *************************************************************/
void getLocation(char* pLocation)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int location = 0;           /* to store choice selected for the region */
    int i = 0;                  /* loop variable */

    /* display choices for user convenience */
    location = getRegion();

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf(" >>  LOCATION          : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the location\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pLocation);

            if (validateLocation(pLocation,location) == 1)
                {
                for (i = 0; i < strlen(pLocation); i++)
                    pLocation[i] = toupper(pLocation[i]);

                break;
                }
            }
        }
    }


/* private function */
/**************************************************************
 *
 * This function asks the user which part of Thailand he/she
 * lives. Then, calls the responsible function to print
 * location in that area.
 *
 * No argument.
 *
 * This function returns 'choice' which is the choice for
 * region selected by the user.
 *
 *************************************************************/
int getRegion()
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int choice = 0;             /* to store user's selected choice */

    printf("\n -- Please select your location from the choices below\n\n");
    printf("\tChoice 1: Northern Thailand\n");
    printf("\tChoice 2: Northeastern Thailand\n");
    printf("\tChoice 3: Western Thailand\n");
    printf("\tChoice 4: Central Thailand\n");
    printf("\tChoice 5: Eastern Thailand\n");
    printf("\tChoice 6: Southern Thailand\n");
    printf("\tChoice 7: Bangkok (Capital city)\n");

    while (1)
        {
        choice = 0;
        memset(stringInput,0,sizeof(stringInput));
        printf("\n >> Enter your choice : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the choice\n");
            }
        else
            {
            if (strlen(stringInput) > 2)
                {
                printf("\t\tPlease enter only one digit\n");
                }
            else
                {
                sscanf(stringInput,"%d",&choice);
                if ((choice > 0) && (choice < 8))
                    {
                    break;
                    }
                else
                    {
                    printf("\n\tInvalid option - should be an integer between 1 and 6\n");
                    }
                }
            }
        }

    /* display locations in that region */
    passLocation(choice);

    return choice;
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for passing the provinces or
 * districts in the selected part of Thailand to the responsible
 * function to print them.
 *
 * location is the number representing region he/she is living
 *
 *************************************************************/
void passLocation(int location)
    {
    /* an array of string holding provinces in northern Thailand */
    char northern[9][MAXLEN] = {"CHIANGMAI","CHIANGRAI","LAMPANG","LAMPHUN","MAEHONGSON",
                                "NAN","PHAYAO","PHRAE","UTTARADIT"};

    /* an array of string holding provinces in northeastern Thailand */
    char northeastern[20][MAXLEN] = {"KALASIN","KHONKAEN","CHAIYAPHUM","NAKHONPHANOM",
                                     "NAKHONRATCHASIMA","BUENGKAN","BURIRAM","MAHASARAKHAM",
                                     "MUKDAHAN","YASOTHON","ROIET","LOEI","SAKONNAKHON",
                                     "SURIN","SISAKET","NONGBUALAMPHU","UDONTHANI",
                                     "NONGKHAI","UBONRATCHATHANI","AMNATCHAROEN"};

    /* an array of string holding provinces in western Thailand */
    char western[5][MAXLEN] = {"KANCHANABURI","TAK","PRACHUAPKHIRIKHAN",
                               "PHETCHABURI","RATCHABURI"};

    /* an array of string holding provinces in central Thailand */
    char central[21][MAXLEN] = {"KAMPHAENGPHET","CHAINAT","NAKHONNAYOK","NAKHONPATHOM",
                                "NAKHONSAWAN","NONTHABURI","PATHUNTHANI","PHRANAKHONSIAYUTTHAYA",
                                "PHICHIT","PHITSANULOK","PHETCHABUN","LOPBURI","SAMUTPRAKAN",
                                "SAMUTSAKHON","SAMUTSONGKHRAM","SINGBURI","SUKHOTHAI",
                                "SUPHANBURI","SARABURI","ANGTHONG","UTHAITHANI"};

    /* an array of string holding provinces in eastern Thailand */
    char eastern[7][MAXLEN] = {"CHANTHABURI","CHACHOENGSAO","CHANBURI","TRAT","PRACHINBURI",
                               "RAYONG","SAKAEO"};

    /* an array of string holding provinces in southern Thailand */
    char southern[14][MAXLEN] = {"KRABI","CHUMPHON","TRANG","NAKHONSITHAMMARAT","NARATHIWAT",
                                 "PATTANI","PHANGNGA","PHATTHALUNG","PHUKET","RANONG",
                                 "SATUN","SONGKHLA","SURATTHANI","YALA"};

    /* an array of string holding districts in Bangkok */
    char bangkok[50][MAXLEN] = {"BANGBON","BANGKAPI","BANGKHAE","BANGKHEN","BANGKHOLAEM",
                                "BANGKHUNTHIAN","BANGNA","BANGPHLAT","BANGRAK","BANGSUE",
                                "BANGKOKNOI","BANGKOKYAI","BUENGKUM","CHATUCHAK","CHOMTHONG",
                                "DINDAENG","DONMUEANG","DUSIT","HUAIKHWANG","KHANNAYAO",
                                "KHLONGSAMWA","KHLONGSAN","KHLONGTOEI","LAKSI","LATKRABANG",
                                "LATPHRAO","MINBURI","NONGCHOK","NONGKHAEM","PATHUMWAN",
                                "PHASICHAROEN","PHAYATHAI","PHRAKHANONG","PHRANAKHON",
                                "POMPRAPSATTRUPHAI","PRAWET","RATBURANA","RATCHATHEWI",
                                "SAIMAI","SAMPHANTHAWONG","SAPHANSUNG","SATHON","SUANLUANG",
                                "TALINGCHAN","THAWIWATTHANA","THONBURI","THUNGKHRU",
                                "WANGTHONGLANG","WATTHANA","YANNAWA"};
    switch (location)
        {
        case 1:
            displayLocation(northern,9);
            break;
        case 2:
            displayLocation(northeastern,20);
            break;
        case 3:
            displayLocation(western,5);
            break;
        case 4:
            displayLocation(central,21);
            break;
        case 5:
            displayLocation(eastern,7);
            break;
        case 6:
            displayLocation(southern,14);
            break;
        case 7:
            displayLocation(bangkok,50);
            break;
        }

    }


/* private function */
/**************************************************************
 *
 * This function is responsible for printing the locations
 * sent from 'passLocation' function.
 *
 * Arguments
 * location[][MAXLEN]   -   an array of string holding locations
 *                          in specific region of Thailand
 * locationCount        -   number of provinces/districts in
 *                          the array
 *
 *************************************************************/
void displayLocation(char location[][MAXLEN], int locationCount)
    {
    int count = 0;  /* to count number of locations printed */

    if (locationCount == 50)
        printf("\n    Select your location from districts below\n");
    else
        printf("\n    Select your location from provinces below\n");

    while (count < locationCount)
        {
        if (count % 2 == 0)
            printf("\n");

        printf("     %-22s",location[count]);
        count++;
        }
    printf("\n\n");
    }


/* private function */
/**************************************************************
 *
 * This function converts the choice(s) selected by the user
 * into a bitstring.
 *
 * choices[] is the choice(s) selected by the user
 * Example : 1,2,5
 *
 * This function returns 'bitstring' which is the bitstring
 * representing user's preference for each attribute.
 *
 *************************************************************/
unsigned int convertChoices(char choices[])
    {
    int i = 0;          /* loop variable */
    int number = 0;     /* to store choices changed from ASCii value */

    /* to hold final bitstring converted from user's selected option */
    unsigned int bitstring = 0b000000;

    for (i = 0; i < strlen(choices); i++)
        {
        if ((i + 1) % 2 != 0)
            {
            /* convert string to integer (1-6) */
            number = (int)choices[i] - 48;
            bitstring |= bitConstants[number-1];
            }
        }

    return bitstring;
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for printing the choices
 * for each attribute.
 *
 * choices[][MAXLEN]    -   an array of string holding choices
 *                          of specific attribute
 *
 *************************************************************/
void printChoices(char choices[][MAXLEN])
    {
    int i = 0;      /* loop variable */

    for (i = 0; i < MAXCHOICE; i++)
        {
        printf("\tChoice %d: %s\n",i+1,choices[i]);
        }
    }


/* private function */
/**************************************************************
 *
 * This function asks the user to enter his/her choice.
 *
 * No arguments.
 *
 * This function returns 'choice' which is the choice
 * selected by the user.
 *
 *************************************************************/
int getOneChoice()
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int choice = 0;             /* to store user's selected choice */

    while (1)
        {
        choice = 0;
        memset(stringInput,0,sizeof(stringInput));
        printf("\n >> Enter your choice : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the choice\n");
            }
        else
            {
            if (strlen(stringInput) > 2)
                {
                printf("\t\tPlease enter only one digit\n");
                }
            else
                {
                sscanf(stringInput,"%d",&choice);
                if ((choice > 0) && (choice < 7))
                    {
                    break;
                    }
                else
                    {
                    printf("\n\tinvalid option - should be an integer between 1 and 6\n");
                    }
                }

            }
        }

    return choice;
    }


/* private function */
/**************************************************************
 *
 * This function asks the user to enter his/her choice(s)
 * and checks if the choices entered by the user is valid
 * or not by calling 'validateChoices' function. Then,
 * convert the choices into the bitstring.
 *
 * No arguments.
 *
 * This function returns 'bitstring' representing the
 * choice(s) selected by the user.
 *
 *************************************************************/
unsigned int getMultiChoices()
    {
    char choice[32];           /* to store user's selected choice(s) */
    char stringInput[MAXLEN];  /* to get input from the user */

    /* to store bit-string converted from the selected choice(s) */
    unsigned int bitstring = 0b000000;


    while (1)
        {
        memset(choice,0,sizeof(choice));
        memset(stringInput,0,sizeof(stringInput));
        printf("\n >> Enter your choice(s) : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the choice(s)\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",choice);

            if (validateChoices(choice) == 1)
                {
                /* convert choice to bitstring */
                bitstring = convertChoices(choice);
                break;
                }
            }
        }

    return bitstring;
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for age and calls another function to get the
 * user's selection.
 *
 * pAge is a pointer to get the selected option for age
 * and store that in the variable in that address.
 *
 *************************************************************/
void getAge(int* pAge)
    {
    printf("\n -- Please select age from the choices below\n\n");

    printChoices(age);

    *pAge = getOneChoice();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for ethnicity and calls another function to get
 * the user's selection.
 *
 * pEthnicity is a pointer to get the selected option for
 * ethnicity and store that in the variable in that address.
 *
 *************************************************************/
void getEthnicity(int* pEthnicity)
    {
    printf("\n -- Please select ethnicity from the choices below\n\n");

    printChoices(ethnicity);

    *pEthnicity = getOneChoice();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for religion and calls another function to get
 * the user's selection.
 *
 * pReligion is a pointer to get the selected option for
 * religion and store that in the variable in that address.
 *
 *************************************************************/
void getReligion(int* pReligion)
    {
    printf("\n -- Please select religion from the choices below\n\n");

    printChoices(religion);

    *pReligion = getOneChoice();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for education level and calls another function
 * to get the user's selection.
 *
 * pEduLevel is a pointer to get the bitstring representing
 * selected education level and store that in the variable
 * in that address.
 *
 *************************************************************/
void getEducationLevel(unsigned int* pEduLevel)
    {
    int selection = 0;      /* to store selected choice */

    printf("\n -- Please select education level from the choices below\n\n");

    printChoices(eduLev);

    selection = getOneChoice();
    *pEduLevel = bitConstants[selection-1];
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for occupation and calls another function
 * to get the user's selection.
 *
 * pOccupation is a pointer to get the bitstring representing
 * selected occupation and store that in the variable
 * in that address.
 *
 *************************************************************/
void getOccupation(unsigned int* pOccupation)
    {
    int selection = 0;      /* to store selected choice */

    printf("\n -- Please select occupation from the choices below\n\n");

    printChoices(occupation);

    selection = getOneChoice();
    *pOccupation = bitConstants[selection-1];
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for cuisine and calls another function
 * to get the user's selection.
 *
 * pFavCuisine is a pointer to get the bitstring representing
 * selected cuisine(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getFavCuisine(unsigned int* pFavCuisine)
    {
    printf("\n -- Please select favorite cuisine from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I like Chinese and Japanese cuisine -> Enter : 2,4\n\n");

    printChoices(cuisine);

    *pFavCuisine = getMultiChoices();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for pet and calls another function to get
 * the user's selection.
 *
 * pFavPet is a pointer to get the bitstring representing
 * selected pet(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getFavPet(unsigned int* pFavPet)
    {
    printf("\n -- Please select favorite pet from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I like Cats, Rabbits, and Birds -> Enter : 2,3,4\n\n");

    printChoices(pet);

    *pFavPet = getMultiChoices();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for music genre and calls another function to
 * get the user's selection.
 *
 * pFavMusic is a pointer to get the bitstring representing
 * selected music genre(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getFavMusic(unsigned int* pFavMusic)
    {
    printf("\n -- Please select favorite music genre from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I like Jazz and Rock music -> Enter : 3,5\n\n");

    printChoices(music);

    *pFavMusic = getMultiChoices();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for hobby and calls another function to
 * get the user's selection.
 *
 * pFavHobby is a pointer to get the bitstring representing
 * selected hobby/hobbies and store that in the variable
 * in that address.
 *
 *************************************************************/
void getFavHobby(unsigned int* pFavHobby)
    {
    printf("\n -- Please select favorite hobby from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I like Sports and Music -> Enter : 1,2\n\n");

    printChoices(hobby);

    *pFavHobby = getMultiChoices();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for film genre and calls another function to
 * get the user's selection.
 *
 * pFavMovie is a pointer to get the bitstring representing
 * selected film genre(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getFavMovie(unsigned int* pFavMovie)
    {
    printf("\n -- Please select favorite film genre from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I like Action and Comedy stories -> Enter : 2,5\n\n");

    printChoices(movie);

    *pFavMovie = getMultiChoices();
    }


/* private function */
/**************************************************************
 *
 * This function prints the password by replacing each letter
 * as a '*' to be confidential.
 *
 * Arguments
 *      password[]   -  the original password
 *      hiddenPW[]   -  password in confidential form
 *
 *************************************************************/
void printPassword(char password[], char hiddenPW[])
    {
    int i = 0;              /* loop variable */
    char output[MAXLEN];    /* to store password in the * form */

    for (i = 0; i < strlen(password); i++)
        {
        output[i] = '*';
        }
    output[i++] = '\0';

    strcpy(hiddenPW,output);
    }


/* private function */
/**************************************************************
 *
 * This function converts the bitstring into the choice(s)
 * which was selected by the user.
 *
 * Arguments
 *      bitstring    -  the bitstring to be converted
 *      data         -  an array of integer holding
 *                      choice(s) that was selected.
 *
 *************************************************************/
void convertBitstring(unsigned int bitstring, int* data)
    {
    int i = 0;      /* loop variable */

    for (i = 0; i < MAXCHOICE; i++)
        {
        data[i] = bitstring & bitConstants[i];
        }
    }


/* private function */
/**************************************************************
 *
 * This function calls the responsible function to convert
 * the bitstring into the choices(s) that was selected
 * by the user and prints it.
 *
 * Arguments
 * bitstring           -  the bitstring representing
 *                        selected choice(s)
 * choices[][MAXLEN]   -  choices of each attribute
 * type                -  if type is 1, only one choice
 *                        was allowed to be selected
 *                        if type is 2, more than one choice
 *                        were allowed to be selected
 *
 *************************************************************/
void printSelection(unsigned int bitstring, char choices[][MAXLEN], int type)
    {
    int i = 0;       /* loop variable */

    /* an array of int to store selected choices converted from the bit-string */
    int data[MAXCHOICE] = {0,0,0,0,0,0};

    convertBitstring(bitstring,data);

    for (i = 0; i < MAXCHOICE; i++)
        {
        if (data[i] > 0)
            {
            if (type == 1)
                printf("%s",choices[i]);
            else
                printf("\t- %s\n",choices[i]);
            }
        }
    printf("\n");
    }


/* private function */
/**************************************************************
 *
 * This function asks user to enter the page he or she
 * wants to look at.
 *
 * pageNum is the current page number to be updated
 *
 * This function returns 'result' which is 0 when user
 * wants to exit displaying, otherwise 1.
 *
 *************************************************************/
int managePage(int* pageNum)
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to store reply which process
                                /* user wants to do */
    int result = 1;             /* to store return value */
    int page = 0;               /* to temporary store the page number */

    page = *pageNum;
    while (1)
        {
        memset(demand,0,sizeof(demand));
        memset(stringInput,0,sizeof(stringInput));

        printf("     Enter P - previous page\n");
        printf("     Enter E - exit displaying\n");
        printf("     Enter N - next page >> ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%s",demand);

        if (strcasecmp(demand,"E") == 0)
            {
            result = 0;
            break;
            }
        else if (strcasecmp(demand,"P") == 0)
            {
            page--;
            printf("\033[2J\033[;H");
            break;
            }
        else if (strcasecmp(demand,"N") == 0)
            {
            page++;
            printf("\033[2J\033[;H");
            break;
            }
        else
            printf("\n\t\tPlease enter only P , E or N\n\n");
        }

    if (page > 3)
        page = 3;
    if (page < 0)
        page = 0;

    *pageNum = page;

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function displays user's information in 2 pages
 * The first page shows personal information and the second
 * shows the preferences.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 *************************************************************/
void printProfile(PERSON_T* pPerson)
    {
    char hiddenPW[MAXLEN];      /* to store password in the form of '*' */
    int page = 1;               /* to store page number that user */
                                /* wants to look at */

    while (1)
        {
        printf("\n");

        if (page == 1)
            {
            printf("  *  Name             : %s\n",pPerson->name);
            printf("  *  Email            : %s\n",pPerson->email);
            printf("  *  Username         : %s\n",pPerson->username);

            printPassword(pPerson->password,hiddenPW);
            printf("  *  Password         : %s\n",hiddenPW);

            printf("  *  Gender           : %s\n",pPerson->gender);
            printf("  *  Location         : %s\n",pPerson->location);

            printf("  *  Age              : %s\n",age[pPerson->age - 1]);
            printf("  *  Ethnicity        : %s\n",ethnicity[pPerson->ethnicity - 1]);
            printf("  *  Religion         : %s\n",religion[pPerson->religion - 1]);

            printf("  *  Education Level  : ");
            printSelection(pPerson->eduLevBitstring,eduLev,1);

            printf("  *  Occupation       : ");
            printSelection(pPerson->workBitstring,occupation,1);
            printf("\n");
            }
        else if (page == 2)
            {
            printf("  *  Favorite cuisine\n");
            printSelection(pPerson->foodBitstring,cuisine,2);

            printf("  *  Favorite pet\n");
            printSelection(pPerson->petBitstring,pet,2);

            printf("  *  Favorite music\n");
            printSelection(pPerson->musicBitstring,music,2);

            printf("  *  Favorite hobby\n");
            printSelection(pPerson->hobbyBitstring,hobby,2);

            printf("  *  Favorite movie\n");
            printSelection(pPerson->movieBitstring,movie,2);
            }
        else if (page == 0)
            {
            printf("\n\t       No previous page\n\n");
            }
        else
            {
            printf("\n\t       No more pages\n\n");
            }

        if (managePage(&page) == 0)
            break;

        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("*                                           *\n");
        printf("|                                           |\n");
        printf("*                 ADD/EDIT                  *\n");
        printf("|           PERSONAL INFORMATION            |\n");
        printf("*                                           *\n");
        printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
        }

    }


/* public function */
/**************************************************************
 *
 * This function displays user's information depending on
 * the category he/she wants to modify.
 *
 * Arguments
 * pPerson      -   pointer to PERSON_T structure
 *                  holding logged in user's data
 * type         -   if type is 1, personal information
 *                  should be printed. Otherwise, the
 *                  preference should be printed
 *
 *************************************************************/
void printEditInfo(PERSON_T* pPerson, int type)
    {
    char hiddenPW[MAXLEN];      /* to store password in the form of '*' */

    printf("\n");

    if (type == 1)
        {
        printf("  [01]  Name             : %s\n",pPerson->name);
        printf("  [02]  Email            : %s\n",pPerson->email);
        printf("  [03]  Username         : %s\n",pPerson->username);

        printPassword(pPerson->password,hiddenPW);
        printf("  [04]  Password         : %s\n",hiddenPW);

        printf("  [05]  Gender           : %s\n",pPerson->gender);
        printf("  [06]  Location         : %s\n",pPerson->location);

        printf("  [07]  Age              : %s\n",age[pPerson->age - 1]);
        printf("  [08]  Ethnicity        : %s\n",ethnicity[pPerson->ethnicity - 1]);
        printf("  [09]  Religion         : %s\n",religion[pPerson->religion - 1]);

        printf("  [10]  Education Level  : ");
        printSelection(pPerson->eduLevBitstring,eduLev,1);

        printf("  [11]  Occupation       : ");
        printSelection(pPerson->workBitstring,occupation,1);
        }
    else
        {
        printf("  [01]  Favorite cuisine\n");
        printSelection(pPerson->foodBitstring,cuisine,2);

        printf("  [02]  Favorite pet\n");
        printSelection(pPerson->petBitstring,pet,2);

        printf("  [03]  Favorite music\n");
        printSelection(pPerson->musicBitstring,music,2);

        printf("  [04]  Favorite hobby\n");
        printSelection(pPerson->hobbyBitstring,hobby,2);

        printf("  [05]  Favorite movie\n");
        printSelection(pPerson->movieBitstring,movie,2);
        }

    }


/* public function */
/**************************************************************
 *
 * This function displays compatible member's general
 * information.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding compatible member's data
 *
 *************************************************************/
void printGeneral(PERSON_T* pPerson)
	{
    printf("  *  Name             : %s\n",pPerson->name);
    printf("  *  Email            : %s\n",pPerson->email);
	printf("  *  Gender           : %s\n",pPerson->gender);
    printf("  *  Location         : %s\n",pPerson->location);
    printf("  *  Age              : %s\n",age[pPerson->age - 1]);
	printf("  *  Ethnicity        : %s\n",ethnicity[pPerson->ethnicity - 1]);
    printf("  *  Religion         : %s\n",religion[pPerson->religion - 1]);
	}


/* public function */
/**************************************************************
 *
 * This function displays compatible member's properties
 * that matched with the properties the logged in user is
 * looking for.
 *
 * Arguments
 * pPerson      -   pointer to PERSON_T structure
 *                  holding compatible member's data
 * pPartner     -   pointer to PERSON_T structure
 *                  holding desire qualities to be
 *                  matched with logged in user
 *
 *************************************************************/
void printSimilar(PERSON_T* pPerson, PERSON_T* pPartner)
	{
	int printCount = 0;		/* to count number of properties printed */

	if (compareSimilar(pPerson->eduLevBitstring,pPartner->eduLevBitstring) == 1)
		{
		printf("  *  Education Level  : ");
        printSelection(pPerson->eduLevBitstring,eduLev,1);
		printCount++;
		}

	if (compareSimilar(pPerson->workBitstring,pPartner->workBitstring) == 1)
		{
		printf("  *  Occupation       : ");
        printSelection(pPerson->workBitstring,occupation,1);
		printCount++;
		}

	if (compareSimilar(pPerson->foodBitstring,pPartner->foodBitstring) == 1)
		{
		printf("  *  Favorite cuisine\n");
        printSelection(pPerson->foodBitstring,cuisine,2);
		printCount++;
		}

	if (compareSimilar(pPerson->petBitstring,pPartner->petBitstring) == 1)
		{
		printf("  *  Favorite pet\n");
        printSelection(pPerson->petBitstring,pet,2);
		printCount++;
		}

	if (compareSimilar(pPerson->musicBitstring,pPartner->musicBitstring) == 1)
		{
		printf("  *  Favorite music\n");
        printSelection(pPerson->musicBitstring,music,2);
		printCount++;
		}

	if (compareSimilar(pPerson->hobbyBitstring,pPartner->hobbyBitstring) == 1)
		{
		printf("  *  Favorite hobby\n");
        printSelection(pPerson->hobbyBitstring,hobby,2);
		printCount++;
		}

	if (compareSimilar(pPerson->movieBitstring,pPartner->movieBitstring) == 1)
		{
		printf("  *  Favorite movie\n");
        printSelection(pPerson->movieBitstring,movie,2);
		printCount++;
		}

	if (printCount == 0)
        printf("\n\t       No similar properties found\n\n");
	}


/* public function */
/**************************************************************
 *
 * This function displays compatible member's other properties
 * that weren't printed in the 'printSimilar' function.
 *
 * Arguments
 * pPerson      -   pointer to PERSON_T structure
 *                  holding compatible member's data
 * pPartner     -   pointer to PERSON_T structure
 *                  holding desire qualities to be
 *                  matched with logged in user
 *
 *************************************************************/
void printProperties(PERSON_T* pPerson, PERSON_T* pPartner)
	{
	int printCount = 0;		/* to count number of properties printed */

	if (compareSimilar(pPerson->eduLevBitstring,pPartner->eduLevBitstring) == 0)
		{
		printf("  *  Education Level  : ");
        printSelection(pPerson->eduLevBitstring,eduLev,1);
		printCount++;
		}

	if (compareSimilar(pPerson->workBitstring,pPartner->workBitstring) == 0)
		{
		printf("  *  Occupation       : ");
        printSelection(pPerson->workBitstring,occupation,1);
		printCount++;
		}

	if (compareSimilar(pPerson->foodBitstring,pPartner->foodBitstring) == 0)
		{
		printf("  *  Favorite cuisine\n");
        printSelection(pPerson->foodBitstring,cuisine,2);
		printCount++;
		}

	if (compareSimilar(pPerson->petBitstring,pPartner->petBitstring) == 0)
		{
		printf("  *  Favorite pet\n");
        printSelection(pPerson->petBitstring,pet,2);
		printCount++;
		}

	if (compareSimilar(pPerson->musicBitstring,pPartner->musicBitstring) == 0)
		{
		printf("  *  Favorite music\n");
        printSelection(pPerson->musicBitstring,music,2);
		printCount++;
		}

	if (compareSimilar(pPerson->hobbyBitstring,pPartner->hobbyBitstring) == 0)
		{
		printf("  *  Favorite hobby\n");
        printSelection(pPerson->hobbyBitstring,hobby,2);
		printCount++;
		}

	if (compareSimilar(pPerson->movieBitstring,pPartner->movieBitstring) == 0)
		{
		printf("  *  Favorite movie\n");
        printSelection(pPerson->movieBitstring,movie,2);
		printCount++;
		}

	if (printCount == 0)
        printf("\n\t       No more properties to display\n\n");

	}


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for education level and calls another function
 * to get the user's selection.
 *
 * pEduLevel is a pointer to get the bitstring representing
 * selected education level(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getMultiEducationLevel(unsigned int* pEduLevel)
    {
    printf("\n -- Please select educational level from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I prefer person who has at least Bachelor's degree\n");
    printf("           -> Enter : 3,4,5\n\n");

    printChoices(eduLev);

    *pEduLevel = getMultiChoices();
    }


/* public function */
/**************************************************************
 *
 * This function calls the responsible function to print
 * choices for occupation and calls another function
 * to get the user's selection.
 *
 * pOccupation is a pointer to get the bitstring representing
 * selected occupation(s) and store that in the variable
 * in that address.
 *
 *************************************************************/
void getMultiOccupation(unsigned int* pOccupation)
    {
    printf("\n -- Please select occupation from the choices below\n");
    printf(" -- You can select multiple choices\n");
    printf(" Example : I prefer Doctors and Teachers -> Enter : 3,4\n\n");

    printChoices(occupation);

    *pOccupation = getMultiChoices();
    }


/* private function */
/**************************************************************
 *
 * This function converts two bitstrings and checks if the
 * selected options in this two bitstrings have at least
 * one matching selection or not.
 *
 * Arguments
 *      personBit    -  compatible member's atrribute
 *                      bitstring
 *      partnerBit   -  desired selection to be matched
 *                      with logged in user for each
 *                      attribute
 *
 * This function returns 'status' which is 1 when at least
 * one matching selection is found, otherwise 0.
 *
 *************************************************************/
int compareSimilar(unsigned int personBit, unsigned int partnerBit)
    {
    /* an array of int to store selected choices converted from */
    /* the bit-string of the compatible member */
    int personData[MAXCHOICE] = {0,0,0,0,0,0};

    /* an array of int to store selected choices converted from */
    /* the bit-string of the desired properties */
    int partnerData[MAXCHOICE] = {0,0,0,0,0,0};

    int status = 0;		/* to track if the similar attribute is found */
    int i = 0;			/* loop variable */

    convertBitstring(personBit,personData);
    convertBitstring(partnerBit,partnerData);

    for (i = 0; i < MAXCHOICE; i++)
        {
        if ((personData[i] > 0) && (partnerData[i] > 0))
            {
            status = 1;
            break;
            }
        }

    return status;
    }


