/********************************************************************
 *
 * datingApp.h
 *
 *      This header file defines data structures and declares
 *   	functions that are located in several programs used for
 *		Computer dating application.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLEN 256                  /* Maximum length for stringInput */
#define MAXCHOICE 6                 /* Maximum choices for each attribute */
#define FILENAME "database.dat"     /* Computer dating application
                                    /* Database's file name */

/* structure for the user */
typedef struct _person
    {
    char name[64];		            /* user's name */
    char email[64];		            /* user's email address */
    char username[16];		        /* user's username */
    char password[16];		        /* user's password */
    char gender[2];		            /* user's gender */
    char location[64];		        /* user's location */
    int age;			            /* user's age range */
    int ethnicity;		            /* user's ethnicity */
    int religion;		            /* user's religion */
    unsigned int eduLevBitstring;	/* bitstring of user's education level */
    unsigned int workBitstring;		/* bitstring of user's occupation */
    unsigned int foodBitstring;     /* bitstring of user's food preference */
    unsigned int petBitstring;      /* bitstring of user's pet preference */
    unsigned int musicBitstring;    /* bitstring of user's music preference */
    unsigned int hobbyBitstring;    /* bitstring of user's hobby preference */
    unsigned int movieBitstring;    /* bitstring of user's movie preference */
    int similarCount;               /* to count similar attributes */

    } PERSON_T;

/* structure representing the user in the list */
typedef struct _personRef
    {
    PERSON_T * pPerson;           /* pointer to master record for each user */
    struct _personRef * pNext;    /* pointer to next person of each user */
    } PERSON_REF_T;

/* structure representing a node in the tree */
typedef struct _node
    {
    char attribute[32];         /* Name of the attribute, for debugging */
                                /* Set to "LEAF" for leaf nodes */
    struct _node* children[6];  /* Pointers to children - not used for leaf nodes */
    PERSON_REF_T * head;        /* head of person list - only used for leaf nodes */
    PERSON_REF_T * tail;        /* tail of person list - only used for leaf nodes */
    } NODE_T;


/* Declarations of public functions in validateData.c */


/**************************************************************
 *
 * This function deletes the space after the input and space
 * that user may accidentally entered.
 *
 * input[] is the input data from the user
 *
 *************************************************************/
void deleteSpace(char input[]);


/**************************************************************
 *
 * This function checks the input if the user wrote nothing
 * and pressed enter or not.
 *
 * input[] is the input data from the user
 *
 * This function returns 'result' which is 0 when nothing
 * is written, otherwise 1.
 *
 *************************************************************/
int checkEnter(char input[]);


/**************************************************************
 *
 * This function checks if the name contains only letters,
 * and spaces or not
 *
 * name[] is the input name from the user.
 *
 * This function returns 'result' which is 1 when the input
 * contains only letters and spaces, otherwise 0.
 *
 *************************************************************/
int validateName(char name[]);


/**************************************************************
 *
 * This function checks if the username contains only letters,
 * digits and underscore (_) or not. Username must have 5 - 15
 * characters and space is not allowed.
 *
 * username[] is the input username from the user.
 *
 * This function returns 'validNum' which is 1 when the input
 * is in accurate format, otherwise 0.
 *
 *************************************************************/
int validateUsername(char username[]);


/**************************************************************
 *
 * This function is a major validation function used to
 * validate password.
 * This function calls other functions to check invalid cases.
 *
 * password[] is the input password entered by the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validatePassword(char password[]);


/**************************************************************
 *
 * This function is a major validation function used to
 * validate email.
 * This function calls other functions to check invalid cases.
 *
 * email[] is the input email from the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validateEmail(char email[]);


/**************************************************************
 *
 * This function is a major validation function used to
 * validate location.
 * This function calls other functions to check invalid cases.
 *
 * location[] is the location entered by the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validateLocation(char location[], int region);


/**************************************************************
 *
 * This function is a major validation function used to
 * validate choices selected by the user.
 * This function calls other functions to check invalid cases.
 *
 * selection[] is the choices selected by the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validateChoices(char selection[]);


/**************************************************************
 *
 * This function checks if the gender entered by the user is
 * correct or not.
 *
 * F - Female   M - Male
 *
 * gender[] is the gender sent from other function.
 *
 * This function returns 'result' which is 1 when the input
 * gender is in correct format, otherwise 0.
 *
 *************************************************************/
int checkGender(char gender[]);


/**************************************************************
 *
 * This function checks if the input email already exists in
 * the database or not.
 *
 * email[] is the input email entered by the user.
 *
 * This function returns 'result' which is 1 when the input
 * email is not found in the database, otherwise 0.
 *
 *************************************************************/
int checkDuplicateEmail(char email[]);


/**************************************************************
 *
 * This function checks if the input username is already
 * used by other user or not.
 *
 * username[] is the input username entered by the user.
 *
 * This function returns 'result' which is 0 when the input
 * username is in-use, otherwise 1.
 *
 *************************************************************/
int checkDuplicateUsername(char username[]);


/* public function */
/**************************************************************
 *
 * This function counts bits that are '1' in a bit-string
 * passed to this function.
 *
 * tempBits is the bit-string that will be checked.
 *
 * This function returns 'oneBitsTotal' which is the number
 * of bits that are '1'.
 *
 *************************************************************/
int countSimilar(unsigned int tempBits);


/* Declarations of public functions in tree.c */


/**************************************************************
 *
 * This function is responsible for building the tree
 * with empty leaf nodes.
 *
 * No Argument.
 *
 *************************************************************/
void createNewTree();


/**************************************************************
 *
 * This function is responsible for adding new person into
 * the list at the leaf node according to the exclusive
 * attributes of that person.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding logged in user's data
 *
 *************************************************************/
void addNewPerson(PERSON_T* pPerson);


/**************************************************************
 *
 * This function is responsible for updating the user's
 * reference list after modifying one of the exclusive
 * attributes.
 *
 * Arguments
 *      pPerson       -      pointer to PERSON_T structure
 *                           holding logged in user's data
 *      oldAttribute  -      array of integer holding values
 *                           of exclusive attributes before
 *                           modifying the data
 *
 *************************************************************/
void transferPerson(PERSON_T* pPerson, int oldAttribute[4]);


/**************************************************************
 *
 * This function is responsible for finding appropriate people
 * list at the leaf node according to the selected exclusive
 * attributes for compatible partners.
 *
 *      pPartner     -      pointer to PERSON_T structure
 *                          holding desire qualities to be
 *                          matched with logged in user
 *
 * This function returns 'currentPerson' which is pointer
 * to PERSON_REF_T structure holding reference for the head
 * person of the list. (NULL if no one is in the list)
 *
 *************************************************************/
PERSON_REF_T* passList(PERSON_T* pPartner);


/**************************************************************
 *
 * This function is responsible for freeing items in the
 * tree and linked lists at the leaf nodes.
 *
 * No Argument.
 *
 *************************************************************/
void freeTree();


/* Declarations of public functions in readWriteData.c */


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
void readFile();


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
int readToCount();


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
int checkFile();


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
void addNewData(PERSON_T* pNew, int personCount);


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
void addPersonalData(PERSON_T* pPerson, int type);


/**************************************************************
 *
 * This function reads all data from the file and store each
 * users's data in the array of structure.
 *
 * userData is array of pointer PERSON_T structure to
 * store each user's data.
 *
 *************************************************************/
void readData(PERSON_T** userData);


/* Declarations of public functions in loginRegister.c */


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
PERSON_T* login();


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
void createNewProfile();


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
void addName(char* pName);


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
void addEmail(char* pEmail);


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
void addUsername(char* pUsername);


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
void addPassword(char* pPassword);


/* Declarations of public functions in addProfile.c */



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
void addEditProfile(PERSON_T* pPerson);


/**************************************************************
 *
 * This function displays user's information depending on
 * the category he/she wants to modify.
 * shows preference
 *
 * Arguments
 * pPerson      -   pointer to PERSON_T structure
 *                  holding logged in user's data
 * type         -   if type is 1, personal information
 *                  should be printed. Otherwise, the
 *                  preference should be printed
 *
 *************************************************************/
void printEditInfo(PERSON_T* pPerson, int type);


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
void getGender(char* pGender);


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
void getLocation(char* pLocation);


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
void getAge(int* pAge);


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
void getEthnicity(int* pEthnicity);


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
void getReligion(int* pReligion);


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
void getEducationLevel(unsigned int* pEduLevel);


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
void getOccupation(unsigned int* pOccupation);


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
void getFavCuisine(unsigned int* pFavCuisine);


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
void getFavPet(unsigned int* pFavPet);


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
void getFavMusic(unsigned int* pFavMusic);


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
void getFavHobby(unsigned int* pFavHobby);


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
void getFavMovie(unsigned int* pFavMovie);


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
void getMultiEducationLevel(unsigned int* pEduLevel);


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
void getMultiOccupation(unsigned int* pOccupation);


/**************************************************************
 *
 * This function displays compatible member's general
 * information.
 *
 *      pPerson      -      pointer to PERSON_T structure
 *                          holding compatible member's data
 *
 *************************************************************/
void printGeneral(PERSON_T* pPerson);


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
void printSimilar(PERSON_T* pPerson, PERSON_T* pPartner);


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
void printProperties(PERSON_T* pPerson, PERSON_T* pPartner);


/* Declarations of public function in editProfile.c */


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
int editInfo(PERSON_T* pPerson);


/* Declarations of public function in findMatch.c */


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
void findMatch(PERSON_T* pPerson);

