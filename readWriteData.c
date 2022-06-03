/********************************************************************
 *
 * readWriteData.c
 *
 *      This program is responsible for reading, writing
 *      modifying and creating new computer dating application's
 *      database file. The Database file is created as a binary file.
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

#define BUCKET_COUNT 4993       /* the number of buckets in the hash table */

/* Adapted with permission from function by Aj. Sally
 * in file hashTester.c
 */
/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key)
    {
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;

    for (i = 0; i < strlen(key); i++)
        {
        /* shift up four bits then add in next char */
        result = (result << 4) + key[i];
        if (tmp = (result & 0xf0000000))  /* if high bit is set */
            {
            /* XOR result with down shifted tmp */
            result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
            result = result ^ tmp;
            }
        }
    result = result % size;   /* make it fit in the table size */
    return result;
    }


/* public function */
/**************************************************************
 *
 * This function checks if the database file exists or not.
 * If not, the new database file will be created and number
 * of people in the file (zero at initial) will be written.
 *
 * No argument.
 *
 * This function returns 'status' which is 1 when the
 * database file is found, otherwise 0.
 *
 *************************************************************/
int checkFile()
    {
    FILE* pNew = NULL;      /* File pointer - will be used to access file */
    int status = 0;         /* to store return value */
    int fileStatus = 0;     /* to store return value from access function */
    int peopleCount = 0;    /* to store number of people at the beginning */

    /* check if the database file exists or not*/
    fileStatus = access(FILENAME,F_OK);

    if (fileStatus == 0)
        {
        status = 1;
        }
    else
        {
        printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * ");
        printf("\n\n\t - Database file not found -\n");

        /* create new database file */
        pNew = fopen(FILENAME,"wb");

        if (pNew == NULL)
            {
            printf("\n\tError creating new database file!\n");
            exit(0);
            }

        /* write number of people(0) in the file */
        if (fwrite(&peopleCount,sizeof(int),1,pNew) != 1)
            {
            printf("\n\tError writing number of people in database file!\n");
            exit(4);
            }
        if (fclose(pNew))
            {
            printf("\n\tError occurred while closing the file!\n");
            exit(3);
            }

        printf("\t  Created new database file!!\n");
        printf("\n* * * * * * * * * * * * * * * * * * * * * * * \n\n");
        }

    return status;
    }


/* public function */
/**************************************************************
 *
 * This function reads the number of people in the database
 * file and returns it to the calling function.
 *
 * No argument.
 *
 * This function returns 'peopleCount' which is the number
 * of people in the database file.
 *
 *************************************************************/
int readToCount()
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */
    int peopleCount = 0;        /* to get number of people in the file */

    pDatabase = fopen(FILENAME,"rb");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    /* read number of people in the file */
    if (fread(&peopleCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("\n\tError occurred while reading the file!\n");
        exit(2);
        }

    if (fclose(pDatabase))
        {
        printf("\n\tError occurred while closing the file!\n");
        exit(3);
        }

    return peopleCount;
    }


/* public function */
/**************************************************************
 *
 * This function reads all data from the file and store each
 * users's data in the array of structure.
 *
 * userData is array of pointer PERSON_T structure to
 * store each user's data.
 *
 *************************************************************/
void readData(PERSON_T** userData)
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */
    PERSON_T* pEntry = NULL;    /* pointer to structure for each user */
    int personCount = 0;        /* to get number of people in the file */
    int indexCount = 0;         /* to increment index number */
    int i = 0;                  /* loop variable */

    pDatabase = fopen(FILENAME,"rb");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    /* read number of people in the file */
    if (fread(&personCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("\n\tError occurred while reading the file!\n");
        exit(2);
        }

    /* read each person's information stored in the file */
    for (i = 0; i < personCount; i++)
        {
        pEntry = calloc(1,sizeof(PERSON_T));
        if (pEntry == NULL)
            {
            printf("\n\tMemory allocation failure - exiting!\n");
            exit(0);
            }

        if (fread(pEntry,sizeof(PERSON_T),1,pDatabase))
            {
            userData[indexCount] = pEntry;
            indexCount++;
            }
        else
            {
            printf("\n\tError occurred while reading the file!\n");
            exit(2);
            }
        }

    if (fclose(pDatabase))
        {
        printf("\n\tError occurred while closing the file!\n");
        exit(3);
        }
    }


/* public function */
/**************************************************************
 *
 * This function calls other functions to check the file
 * status. If the file and user's data exist, it calls the
 * responsible function to read the user's data and add user
 * to the tree and insert user's data into the hash table.
 *
 * No argument.
 *
 *************************************************************/
void readFile()
    {
    PERSON_T** userData = NULL; /* array of pointer PERSON_T structure */
                                /* to store each user's data */
    int personCount = 0;        /* to get number of people in the file */
    int fileStatus = 0;         /* to store return value from access function */
    int pCollision = 0;         /* store collision status */
    int result = 0;             /* to store return value from other function */
    int i = 0;                  /* loop variable */

    /* check if the database file exists or not */
    fileStatus = checkFile();

    /* get the number of people in the file */
    personCount = readToCount();

    /* initialize the hash table */
    result = hashTableInit(BUCKET_COUNT,&bitwiseOpHash);
    if (result == 0)
        {
        printf("\n\tError occurred while initializing the hash table!\n");
        exit(0);
        }


    /* check if there's the data in the file or not */
    if ((fileStatus == 1) && (personCount > 0))
        {
        userData = calloc(personCount,sizeof(PERSON_T*));

        if (userData == NULL)
            {
            printf("\n\tMemory allocation failure - exiting!\n");
            exit(0);
            }

        /* read all user's data */
        readData(userData);

        for (i = 0; i < personCount; i++)
            {
            /* add each user to appropriate list */
            addNewPerson(userData[i]);

            /* insert each user's data into hash table */
            /* user's username is the key */
            result = hashTableInsert(userData[i]->username,userData[i],&pCollision);
            if (result == 0)
                {
                printf("\n\tError occurred while inserting %s's information into hash table!\n",userData[i]->name);
                }
            }
        free(userData);
        }
    }


/* public function */
/**************************************************************
 *
 * This function adds new data into the database file and
 * updates number of people in the file at the top of
 * the file. This function also insert new user's data
 * into the hash table.
 *
 * Arguments
 *      pNew         -    a pointer to structure storing
 *                        new user's data
 *      peopleCount  -    the number of people in the file
 *
 *************************************************************/
void addNewData(PERSON_T* pNew, int personCount)
    {
    FILE* pDatabase = NULL;  /* File pointer - will be used to access file */
    int pCollision = 0;      /* to store collision status */
    int result = 0;          /* to store return value from other function */

    pDatabase = fopen(FILENAME,"rb+");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    /* move to the end of the file */
    fseek(pDatabase,0,SEEK_END);

    /* write new user's data */
    if (fwrite(pNew,sizeof(PERSON_T),1,pDatabase) != 1)
        {
        printf("\n\tError occurred while writing new data to the file!\n");
        exit(4);
        }

    /* move to the beginning of the file */
    fseek(pDatabase,0,SEEK_SET);

    /* write number of people in the file */
    if (fwrite(&personCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("\n\tError occurred while writing number of person to the file!\n");
        exit(4);
        }
    else
        {
        if (fclose(pDatabase))
            {
            printf("\n\tError occurred while closing the file!\n");
            exit(3);
            }
        }

    /* insert new user's data into hash table */
    /* user's username is the key */
    result = hashTableInsert(pNew->username,pNew,&pCollision);
    if (result == 0)
        {
        printf("\n\tError occurred while inserting %s's information into hash table!\n",pNew->name);
        }
    }


/* private function */
/**************************************************************
 *
 * This function writes modified version data into the file
 * by using the username to compare people in the file to
 * find the person whose data has been modified.
 *
 * Arguments
 *      data         -   array of pointer PERSON_T structure
 *                       storing each user's data.
 *      pPerson      -   pointer to structure storing currently
 *                       logged in user's updated information
 *      personCount  -   the number of people in the file
 *
 *************************************************************/
void addByUsername(PERSON_T** data, PERSON_T* pPerson, int personCount)
	{
	FILE* pDatabase = NULL;		/* File pointer - will be used to access file */
	int i = 0;					/* loop variable */

	pDatabase = fopen(FILENAME,"rb+");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    for (i = 0; i < personCount; i++)
    	{
  		/* move to the end of the file */
        fseek(pDatabase,0,SEEK_END);

        if (strcmp(pPerson->username,data[i]->username) == 0)
            {
            /* write updated version of current user's data */
            if (fwrite(pPerson,sizeof(PERSON_T),1,pDatabase) != 1)
                {
                printf("\n\tError occurred while writing new data to the file!\n");
                exit(4);
                }
            }
        else
            {
            /* write other user's data */
            if (fwrite(data[i],sizeof(PERSON_T),1,pDatabase) != 1)
                {
                printf("\n\tError occurred while writing new data to the file!\n");
                exit(4);
                }
            }
        }

    if (fclose(pDatabase))
        {
        printf("\n\tError occurred while closing the file!\n");
        exit(3);
        }
    }


/* private function */
/**************************************************************
 *
 * This function writes modified version data into the file
 * by using the email to compare people in the file to find
 * the person whose username has been modified.
 *
 * Arguments
 *      data         -   array of pointer PERSON_T structure
 *                       storing each user's data.
 *      pPerson      -   pointer to structure storing currently
 *                       logged in user's updated information
 *      personCount  -   the number of people in the file
 *
 *************************************************************/
void addByEmail(PERSON_T** data, PERSON_T* pPerson, int personCount)
	{
	FILE* pDatabase = NULL;		/* File pointer - will be used to access file */
	int i = 0;					/* loop variable */

    pDatabase = fopen(FILENAME,"rb+");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    for (i = 0; i < personCount; i++)
        {
  		/* move to the end of the file */
        fseek(pDatabase,0,SEEK_END);

        if (strcmp(pPerson->email,data[i]->email) == 0)
            {
            /* write updated version of current user's data */
            if (fwrite(pPerson,sizeof(PERSON_T),1,pDatabase) != 1)
                {
                printf("\n\tError occurred while writing new data to the file!\n");
                exit(4);
                }
            }
        else
            {
            /* write other user's data */
            if (fwrite(data[i],sizeof(PERSON_T),1,pDatabase) != 1)
                {
                printf("\n\tError occurred while writing new data to the file!\n");
                exit(4);
                }
            }
    	}

	if (fclose(pDatabase))
        {
        printf("\n\tError occurred while closing the file!\n");
        exit(3);
        }
	}


/* public function */
/**************************************************************
 *
 * This function writes the number of people in the database
 * file and call responsible functions to write the modified
 * data into the file.
 *
 * Arguments
 *      pPerson   -   pointer to structure storing currently
 *                    logged in user's updated information
 *      type      -   to indicate how data should be rewritten
 *
 *      if type = 1,  username is not modified, so username
 *                    can be used to find user's old data
 *                    and replace with new data.
 *
 *      if type = 2,  username has been modified, so username
 *                    can't be used to find user's old data
 *                    since the program won't be able to find
 *                    person in the file by new username. Thus,
 *                    the program will use email to find that
 *                    person instead of username.
 *
 *************************************************************/
void addPersonalData(PERSON_T* pPerson, int type)
    {
    PERSON_T** data = NULL;     /* array of pointer PERSON_T structure */
                                /* to store each user's data */
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */
    int personCount = 0;        /* to get number of people in the file */

    /* get the number of people in the file */
    personCount = readToCount();

    data = calloc(personCount,sizeof(PERSON_T*));

    if (data == NULL)
        {
        printf("\n\tMemory allocation failure - exiting!\n");
        exit(0);
        }

    /* read all user's data */
    readData(data);

    pDatabase = fopen(FILENAME,"wb");

    if (pDatabase == NULL)
        {
        printf("\n\tError occurred while opening the file!\n");
        exit(1);
        }

    /* write number of people in the file */
    if (fwrite(&personCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("\n\tError occurred while writing number of person to the file!\n");
        exit(4);
        }

    if (fclose(pDatabase))
        {
        printf("\n\tError occurred while closing the file!\n");
        exit(3);
        }

    /* if username hasn't been modified */
    if (type == 1)
        {
		addByUsername(data,pPerson,personCount);
        }
    else
        {
        /* username has been modified */
        /* email will be used to find person instead */
        addByEmail(data,pPerson,personCount);
        }

    free(data);
    printf("\n\tSuccessfully updated the information\n\n");
    }
