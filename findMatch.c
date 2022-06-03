/********************************************************************
 *
 * findMatch.c
 *
 *      This program is responsible for finding compatible
 *   	partners for the user by asking the user to enter
 *      personalities he/she is looking for in his/her
 *      partner. Then, the system will compute 3 most
 *      similar members and display with the highest matching
 *      score. Then, the user will be able to look at each
 *      compatible member's similar and other properties.
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

/* Declaration of some functions used in findMatch.c */
PERSON_REF_T* getPreference(PERSON_T* pPartner);
void countMatch(PERSON_T* pPerson, PERSON_T* pPartner);
void displayProperties(PERSON_T* pPerson, PERSON_T* pPartner);
int getMostSimilar(PERSON_REF_T* listHead, PERSON_T** partnerList, PERSON_T* pPerson);
void displayMatch(PERSON_T* pPartner, PERSON_T** partnerList, int matchCount);


/* public function */
/**************************************************************
 *
 * This function is the major function for finding
 * compatible members for logged in user.
 *
 * This function will call responsible function to get
 * the characteristics logged in user wants in his/her
 * partner. Then, other functions will be called to
 * count the number of similarities found to get 3
 * members with highest score and to display 3 most
 * compatible members for the user.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 *************************************************************/
void findMatch(PERSON_T* pPerson)
    {
    int personCount = 0;              /* to store number of users in the file */
    int matchCount = 0;			      /* to count number of compatible members found */
    PERSON_T* pPartner = NULL;        /* pointer to PERSON_T structure */
                                      /* to hold desire qualities to be matched */
    PERSON_T** partnerList = NULL;	  /* an array of pointer to PERSON_T structure */
                                      /* to store 3 most compatible members */
    PERSON_REF_T* headPerson = NULL;  /* reference to the head of the list */

    printf("\033[2J\033[;H");
    printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
    printf("|                                           |\n");
    printf("*                FIND A MATCH               *\n");
    printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
    printf("\n\n");

    if (checkGender(pPerson->gender) != 1)
        printf("\n You must enter your personal information first\n\n");
    else
        {
        /* get the number of people in the file */
        personCount = readToCount();

        if (personCount < 2)
            {
            printf("\n Sorry, you're the only member in our system ;_;\n");
            printf("               Come back Later!!\n\n");
            }
        else
            {
            pPartner = (PERSON_T*) calloc(1,sizeof(PERSON_T));
            if (pPartner == NULL)
                {
                printf("Memory allocation error \n");
                exit(0);
                }

            partnerList = calloc(3,sizeof(PERSON_T*));
            if (partnerList == NULL)
            	{
            	printf("\n\tMemory allocation failure - exiting!\n");
            	exit(0);
            	}

            printf("    Please enter attributes that you are \n");
            printf("        looking for in your partner\n");
            printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n\n");

            /* get the list head according to the exclusive attribute values */
            /* count similar properties of each member in the list */
            headPerson = getPreference(pPartner);
            if (headPerson != NULL)
                {
                /* get 3 most compatible members */
                matchCount = getMostSimilar(headPerson,partnerList,pPerson);

                /* display compatible members with matching score */
                displayMatch(pPartner,partnerList,matchCount);
                }
            }
        }
    }


/* private function */
/**************************************************************
 *
 * This function asks for the exclusive attributes first,
 * then if there exist members in the list according to the
 * selected exclusive attributes, other preferences will be
 * asked and other function will be called to count number
 * of similarities for each person in the list.
 *
 *      pPartner     -   pointer to PERSON_T structure
 *                       to hold desire qualities to be
 *                       matched with logged in user
 *
 * This function returns 'headPerson' which is pointer to
 * PERSON_REF_T structure to pass the list's head according
 * to the selected attributes (NULL if no one is in the list).
 *
 *************************************************************/
PERSON_REF_T* getPreference(PERSON_T* pPartner)
    {
    char stringInput[MAXLEN];             /* to get input from the user */
    char demand[16];                      /* to track if user wants to modify or not */
    PERSON_REF_T* currentPerson = NULL;   /* reference to the current person in the list */
    PERSON_REF_T* headPerson = NULL;      /* reference to the head of the list */

    while (1)
        {
        printf("     Enter 4 exclusive attributes first\n");
        printf("  (you can select only 1 choice/atrribute)\n\n");
        getGender(pPartner->gender);
        getAge(&pPartner->age);
        getEthnicity(&pPartner->ethnicity);
        getReligion(&pPartner->religion);

        /* find people list by exclusive attributes */
        currentPerson = passList(pPartner);

        if (currentPerson != NULL)
            break;
        else
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));
            printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
            printf("No one found with entered exclusive attributes!\n\n");
            printf("* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
            printf("    Do you want to reselect the attributes?\n");
            printf("    Y - yes , other alphabet - no : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"Y") != 0)
                {
                break;
                }
            printf("\033[2J\033[;H");
            }
        }

    if (currentPerson != NULL)
        {
        printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * *\n\n");
        printf("     Now, select the remaining atrributes to\n");
        printf("     find 3 most compatible partners for you\n");
        printf("        (multiple selections are allowed)\n");
        printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\n\n");

        /* get other attributes */
        getMultiEducationLevel(&pPartner->eduLevBitstring);
        getMultiOccupation(&pPartner->workBitstring);
        getFavCuisine(&pPartner->foodBitstring);
        getFavPet(&pPartner->petBitstring);
        getFavMusic(&pPartner->musicBitstring);
        getFavHobby(&pPartner->hobbyBitstring);
        getFavMovie(&pPartner->movieBitstring);

        /* traverse the list to count similarities */
        headPerson = currentPerson;
        while (currentPerson != NULL)
            {
            countMatch(currentPerson->pPerson,pPartner);
            currentPerson = currentPerson->pNext;
            }
        }

    return headPerson;
    }


/**************************************************************
 *
 * This function count number of similarities of member and
 * desired qualities to be matched with logged in user. Then,
 * store the similarity score into member's structure.
 *
 * Arguments
 * pPerson      -   pointer to PERSON_T structure holding
 *                  data of the member in the list
 * pPartner     -   pointer to PERSON_T structure holding
 *                  desire qualities to be matched
 *                  with logged in user
 *
 *************************************************************/
void countMatch(PERSON_T* pPerson, PERSON_T* pPartner)
    {
    unsigned int bitstring = 0b000000;	/* to store the resulting bitstring
                                         * after the comparison */
    int similarCount = 0;			    /* to count similar attributes found */

    /* reset the similar attributes count to zero*/
    pPerson->similarCount = 0;

    /* do the bitwise AND operation between member's bitstring and */
    /* bitstring representing desired properties, then pass to */
    /* another function to get number of similarities from it */

    bitstring = pPerson->eduLevBitstring & pPartner->eduLevBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->workBitstring & pPartner->workBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->foodBitstring & pPartner->foodBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->petBitstring & pPartner->petBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->musicBitstring & pPartner->musicBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->hobbyBitstring & pPartner->hobbyBitstring;
    similarCount += countSimilar(bitstring);

    bitstring = pPerson->movieBitstring & pPartner->movieBitstring;
    similarCount += countSimilar(bitstring);

    /* copy to the person's structure variable */
    pPerson->similarCount = similarCount;

    }


/**************************************************************
 *
 * This function find first 3 members with the highest score
 * and store it in partnerList array
 *
 * Arguments
 * listHead       -   pointer to PERSON_REF_T structure
 *                    holding reference to the list's head
 * partnerList    -   an array of pointer to PERSON_T structure
 *                    to store 3 most compatible members
 * pPerson        -   pointer to PERSON_T structure
 *                    holding logged in user's data
 *
 * This function returns 'matchCount' which is the number
 * of compatible members found (maximum 3 members).
 *
 *************************************************************/
int getMostSimilar(PERSON_REF_T* listHead, PERSON_T** partnerList, PERSON_T* pPerson)
    {
    int matchCount = 0;	    /* to count number of compatible members found */
    int i = 0;		        /* loop variable */
    int score = -1;	        /* to store the number of similar */
                            /* properties of the person */

    PERSON_REF_T* currentPerson = NULL;  /* reference to the current person */
                                         /* in the list */

    /* an array of integer to store 3 maximum scores found so far */
    int maxScore[3] = {-1,-1,-1};

    /* traverse the list to find 3 members with the highest score */
    currentPerson = listHead;

    while (currentPerson != NULL)
        {
        if (currentPerson->pPerson != pPerson)
            {
            score = currentPerson->pPerson->similarCount;
            if (score > maxScore[2])
                {
                if (score > maxScore[1])
                    {
                    if (score > maxScore[0])
                        {
                        maxScore[2] = maxScore[1];
                        partnerList[2] = partnerList[1];

                        maxScore[1] = maxScore[0];
                        partnerList[1] = partnerList[0];

                        maxScore[0] = score;
                        partnerList[0] = currentPerson->pPerson;
                        }
                    else
                        {
                        maxScore[2] = maxScore[1];
                        partnerList[2] = partnerList[1];

                        maxScore[1] = score;
                        partnerList[1] = currentPerson->pPerson;
                        }
                    }
                else
                    {
                    maxScore[2] = score;
                    partnerList[2] = currentPerson->pPerson;
                    }
                }
            }
        currentPerson = currentPerson->pNext;
        }

    /* count number of compatible members in the array */
    for (i = 0; i < 3; i++)
        {
        if (partnerList[i] != NULL)
            matchCount++;
        }

    return matchCount;
    }


/**************************************************************
 *
 * This function displays 3 members with the highest score
 * and calls other function to display selected member's
 * similar and different properties.
 *
 * Arguments
 * pPartner       -   pointer to PERSON_T structure holding
 *                    desire qualities to be matched
 *                    with logged in user
 * partnerList    -   an array of pointer to PERSON_T structure
 *                    storing 3 most compatible members'
 *                    structure
 * matchCount     -   number of compatible members found
 *
 *************************************************************/
void displayMatch(PERSON_T* pPartner, PERSON_T** partnerList, int matchCount)
	{
	char stringInput[MAXLEN];   /* to get input from the user */
    int demand = 0;             /* to track if user wants to modify or not */
	int i = 0;					/* loop variable */

	printf("\033[2J\033[;H");
	while (1)
		{
        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("|                                           |\n");
        printf("*                FIND A MATCH               *\n");
        printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");

		printf("\n\n %d most compatible member to be your partner\n\n",matchCount);

		for (i = 0; i < matchCount; i++)
			{
			if (partnerList[i]->similarCount > 0)
                {
                printf("   [%d]   %-16s  ~  %d similarities found\n"
                        ,i+1,partnerList[i]->name,partnerList[i]->similarCount);
                }
			else
                {
                printf("   [%d]   %-16s  ~  only exclusive attributes are matched\n"
                        ,i+1,partnerList[i]->name);
                }

			}

		printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
		printf(" Which member's properties do you want to see\n");
		printf(" press ENTER to go back to main menu : ");
        fgets(stringInput,sizeof(stringInput),stdin);

		if (checkEnter(stringInput) == 0)
            break;

        sscanf(stringInput,"%d",&demand);

		if ((demand < 1) || (demand > matchCount))
			{
			printf("\n   Invalid option - should be a positive integer not exceeding %d\n\n",matchCount);
			}
		else
			{
            printf("\033[2J\033[;H");
			displayProperties(partnerList[demand-1],pPartner);
			printf("\033[2J\033[;H");
			}
		}
	}


/**************************************************************
 *
 * This function displays 3 members with the highest score
 * and calls other function to display selected member's
 * similar and different properties.
 *
 * Arguments
 * pPerson        -   pointer to PERSON_T structure holding
 *                    data of the compatible member
 * pPartner       -   pointer to PERSON_T structure holding
 *                    desire qualities to be matched
 *                    with logged in user
 *
 *************************************************************/
void displayProperties(PERSON_T* pPerson, PERSON_T* pPartner)
	{
    char stringInput[MAXLEN];   /* to get input from the user */
    char demand[16];            /* to store reply which process user wants to do */
    int page = 1;               /* to store page number that user wants to look at*/

    while (1)
        {
        printf("\033[2J\033[;H");
        printf(" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
        printf("|                                           |\n");
        printf("*                FIND A MATCH               *\n");
        printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n\n\n");

        if (page > 4)
            page = 4;
        if (page < 0)
            page = 0;

        if (page == 1)
            {
            printf("  *  %s's information\n\n",pPerson->name);
            printGeneral(pPerson);
            }
        else if (page == 2)
            {
            printf("  *  Similar properties\n\n");
            printSimilar(pPerson,pPartner);
            }
        else if (page == 3)
            {
            printf("  *  Other properties\n\n");
            printProperties(pPerson,pPartner);
            }
        else if (page == 0)
            {
            printf("\n\t       No previous page\n\n");
            }
        else
            {
            printf("\n\t       No more pages\n\n");
            }

        while (1)
            {
            memset(demand,0,sizeof(demand));
            memset(stringInput,0,sizeof(stringInput));

			printf("\n");
            printf("     Enter P - previous page\n");
            printf("     Enter E - exit displaying\n");
            printf("     Enter N - next page >> ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",demand);

            if (strcasecmp(demand,"E") == 0)
                {
                break;
                }
            else if (strcasecmp(demand,"P") == 0)
                {
                page--;
                break;
                }
            else if (strcasecmp(demand,"N") == 0)
                {
                page++;
                break;
                }
            else
                printf("\n\t\tPlease enter only P , E or N\n\n");
            }

        if (strcasecmp(demand,"E") == 0)
            break;
        }
	}


