/********************************************************************
 *
 * validateData.c
 *
 *      This program is responsible for validating the information
 *      that the user entered if it is valid or not.
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


/* public function */
/**************************************************************
 *
 * This function deletes the space after the input and space
 * that user may accidentally entered.
 *
 * input[] is the input data from the user
 *
 *************************************************************/
void deleteSpace(char input[])
    {
    int i = strlen(input) - 1;      /* i is a length of the variable - 1 */

    while ((i >= 0) && (isspace(input[i])))
        {
        input[i] = '\0';
        i--;
        }
    }


/* public function */
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
int checkEnter(char input[])
    {
    int result = 0;     /* to store return value */

    if ((input[0] != '\n') && (input[0] != '\r'))
        {
        result = 1;
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input contains a space or not.
 *
 * input[] is the input data from the user
 *
 * This function returns 'result' which is 0 when space is
 * found in the string, otherwise 1.
 *
 *************************************************************/
int checkSpace(char input[])
    {
    int i = 0;        /* loop variable*/
    int result = 1;   /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if (isspace(input[i]))
            {
            result = 0;
            break;
            }
        }

    return result;
    }


/* public function */
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
int validateName(char name[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(name); i++)
        {
        if ((isalpha(name[i]) == 0) && (isspace(name[i]) == 0))
            {
            printf("\t\tNot valid - must be only any combination of letters and spaces\n");
            result = 0;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input follows the rules
 * below or not.
 *
 * Arguments
 *      input[]          -    the input data from the user
 *      checkSpecial     -    to store status if invalid
 *                            special character is found
 *      checkDot         -    to store status if dot is
 *                            found aside '@' sign
 *      checkAt          -    to count number of '@' sign
 *                            found in the input
 *
 *************************************************************/
void checkString(char input[], int* checkSpecial, int* checkDot, int* checkAt)
    {
    int i = 0;          /* loop variable */

    for (i = 0; i < strlen(input); i++)
        {
        if(!isupper(input[i]) && !islower(input[i]) && !isdigit(input[i])&& !(input[i] == '@')
            && !(input[i] == '.') && !(input[i] == '_') && !(input[i] == '-'))
            {
            *checkSpecial = 0;
            }
        }

    for (i = 1; i < strlen(input); i++)
        {
        if ((input[i] == '.') && (input[i-1] == '@'))
            {
            *checkDot = 0;
            }
        else
            {
            if ((input[i-1] == '.') && (input[i] == '@'))
                {
                *checkDot = 0;
                }
            }
        }

    for ( i = 0; i < strlen(input); i++)
        {
        if(input[i] == '@')
            {
            (*checkAt)++;
            }
        }
    }


/* private function */
/**************************************************************
 *
 * This function locates the index where the '@' exists.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'index' which is the index number
 * where the at-sign is.
 *
 *************************************************************/
int checkSign(char input[])
    {
    int i = 0;           /* loop variable */
    int index = 0;       /* index number where the '@' is */

    for (i = 0; i < strlen(input); i++)
        {
        if(input[i] == '@')
            index = i;
        }
    return index;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input contains the valid
 * top-level domain or not.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'result' which is 1 when the input
 * contains valid TLD, otherwise 0.
 *
 *************************************************************/
int checkTLD(char input[])
    {
    int i = 0;                  /* loop variable */
    int j = 0;                  /* loop variable */
    int result = 0;             /* to store return value */
    char checkString[MAXLEN];   /* store the TLD from the input */

    memset(checkString,'\0',sizeof(checkString));

    for (i = 0; i < strlen(input); i++)
        {
        if (input[i] == '.')
            {
            memset(checkString,'\0',sizeof(checkString));

            for (j = i; j < strlen(input); j++)
                {
                checkString[j-i] = input[j];
                }
            if ((strcmp(checkString,".com") == 0) || (strcmp(checkString,".net") == 0) ||
                (strcmp(checkString,".ac.th") == 0) || (strcmp(checkString,".co.th") == 0))
                result = 1;
            }
        }
    return result;
    }


/* private function */
/**************************************************************
 *
 * This function locates the position of the TLD.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'index' which is the number
 * where the TLD is.
 *
 *************************************************************/
int locateTLD(char input[])
    {
    int i = 0;                  /* loop variable */
    int j = 0;                  /* loop variable */
    int index = -1;             /* index number where the '@' is */
    char checkString[MAXLEN];   /* store the TLD from the input */

    memset(checkString,'\0',sizeof(checkString));

    for (i = 0; i < strlen(input); i++)
        {
        if(input[i] == '.')
            {
            memset(checkString,'\0',sizeof(checkString));
            for(j = i; j < strlen(input); j++)
                {
                checkString[j-i] = input[j];
                }
            if ((strcmp(checkString,".com") == 0) || (strcmp(checkString,".net") == 0) ||
                (strcmp(checkString,".ac.th") == 0) || (strcmp(checkString,".co.th") == 0))
                index = i;
            }
        }
    return index;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input email contains
 * digits or alphabets before TLD or not.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'result' which is 1 when the input
 * contains digits or alphabets before TLD, otherwise 0.
 *
 *************************************************************/
int alphaNumeric(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 0;     /* to store return value */

    for (i = checkSign(input) + 1; i < locateTLD(input); i++)
        {
        if (isupper(input[i]) || islower(input[i]) || isdigit(input[i]))
            result = 1;
        }
    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input email contains
 * underscore(_) after the at-sign or not.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'result' which is 1 when underscore
 * is not found after the at-sign, otherwise 0.
 *
 *************************************************************/
int checkUnder(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = checkSign(input) + 1; i < strlen(input); i++)
        {
        if (input[i] == '_')
            result = 0;
        }
    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input email contains
 * only one dot after the at-sign or not.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'result' which is 1 when underscore
 * is not found after the at-sign, otherwise 0.
 *
 *************************************************************/
int checkDot(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if (ispunct(input[i]))
            {
            if ((input[i] == '.') && (input[i+1] == '.'))
                {
                result = 0;
                }
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input email contains
 * digits after the at-sign or not.
 *
 * input[] is the input email from the user.
 *
 * This function returns 'result' which is 1 when digits
 * are not found after the at-sign, otherwise 0.
 *
 *************************************************************/
int checkNumAfterAt(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */
    int atSign = 0;		/* to locate the position of '@' */

    for (i = 0 ; i < strlen(input) ; i++)
        {
        if (input[i] == '@')
            {
            atSign = 1;
            continue;
            }
				if ((isdigit(input[i])) && (atSign))
        		{
            result = 0;
            break;
        		}
        }
    return result;
    }


/* public function */
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
int validateEmail(char email[])
    {
    int checkAt = 0;        /* get number of at-signs in the email */
    int validNum = 0;       /* to store return value */
    int checkSpeci = 1;     /* get status if invalid special character is found */
    int checkPeriod = 1;    /* get status if dot is found aside '@' */

    checkString(email,&checkSpeci,&checkPeriod,&checkAt);

    if (!isupper(email[0]) && !islower(email[0]) && !isdigit(email[0]))
        {
        printf("\t\tNot valid - must begin with alphabet or digit\n");
        }
    else if (checkSpace(email) == 0)
        {
        printf("\t\tNot valid - embedded space\n");
        }
    else if (checkAt != 1)
        {
        printf("\t\tNot valid - only one '@' sign is allowed\n");
        }
    else if (checkPeriod == 0)
        {
        printf("\t\tNot valid - periods are not allowed beside the '@'\n");
        }
    else if (checkTLD(email) == 0)
        {
        printf("\t\tNot valid - TLD does not meet the conditions\n");
        }
    else if (alphaNumeric(email) == 0)
        {
        printf("\t\tNot valid - must enter only alphanumeric character between @ and the TLD\n");
        }
    else if (checkUnder(email) == 0)
        {
        printf("\t\tNot valid - no underscore allowed after the '@'\n");
        }
    else if (checkDot(email) == 0)
        {
        printf("\t\tNot valid - must have only 1 dot after the '@' \n");
        }
    else if (checkNumAfterAt(email) == 0)
        {
        printf("\t\tNot valid - digits are not allowed after use '@'\n");
        }
    else if (checkSpeci == 0)
        {
        printf("\t\tNot valid - no special characters allowed\n");
        printf("\t\texcept : '.' , '@' , '_' , '-'\n");
        }
    else
        {
        if (checkSpeci != 0)
            {
            validNum = 1;
            }
        }

    return validNum;
    }


/* public function */
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
int validateUsername(char username[])
    {
    int i = 0;           /* loop variable */
    int validNum = 1;    /* return value */

    if (checkSpace(username) == 0)
        {
        printf("\t\tNot valid - space is not allowed\n");
        validNum = 0;
        }
    else if ((strlen(username) < 5) || (strlen(username) > 15))
        {
        printf("\t\tNot valid - must have 5 - 15 characters\n");
        validNum = 0;
        }
    else
        {
        for (i = 0; i < strlen(username); i++)
            {
            if ((!isdigit(username[i])) && (!isalpha(username[i])) && (username[i] != '_'))
                {
                printf("\t\tNot valid - must be only any combination of letters, numbers and underscore(_)\n");
                validNum = 0;
                break;
                }
            }
        }

    return validNum;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input password is 8-12
 * characters long or not.
 *
 * input[] is the input password from the user.
 *
 * This function returns 'result' which is 1 when the
 * password is 8-12 characters long, -1 if the password
 * is less than 8 characters and 0 if the password is
 * longer than 12.
 *
 *************************************************************/
int checkLength(char input[])
    {
    int result = 0;     /* to store return value */
    int length = 0;     /* to store password length */

    length = strlen(input);

    if ((length >= 8) && (length <= 12))
        {
        result = 1;
        }
    else if ((length > 0) && (length < 8))
        {
        result = -1;
        }
    else
        {
        if (length > 12)
            {
            result = 0;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input password contains
 * at least one uppercase alphabet or not.
 *
 * input[] is the input password from the user.
 *
 * This function returns 'result' which is 1 when the
 * password contains at least one uppercase letter,
 * otherwise 0.
 *
 *************************************************************/
int checkUpper(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 0;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if (isupper(input[i]))
            {
            result = 1;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input password contains
 * at least one lowercase alphabet or not.
 *
 * input[] is the input password from the user.
 *
 * This function returns 'result' which is 1 when the
 * password contains at least one lowercase letter,
 * otherwise 0.
 *
 *************************************************************/
int checkLower(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 0;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if (islower(input[i]))
            {
            result = 1;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input password contains
 * at least two digits or not.
 *
 * input[] is the input password from the user.
 *
 * This function returns 'result' which is 1 when the
 * password contains at least two digits, otherwise 0.
 *
 *************************************************************/
int checkPWDigit(char input[])
    {
    int result = 0;    /* to store return value */
    int count = 0;     /* to count number of digits found */
    int i = 0;         /* loop variable */

    for (i = 0; i < strlen(input); i++)
        {
        if (isdigit(input[i]))
            {
            count++;
            }
        }

    if (count >= 2)
        {
        result = 1;
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input password contains
 * at least one valid special character or not.
 *
 * valid special characters : ? , @ , % , $ , #
 *
 * input[] is the input password from the user.
 *
 * This function returns 'result' which is 0 when no
 * special character is found, -1 if the password contains
 * invalid special character, otherwise 1.
 *
 *************************************************************/
int checkSpecial(char input[])
    {
    int result = 1;     /* store return value */
    int check = 0;      /* track if that letter is punctuation mark */
    int count = 0;      /* count invalid special character */
    int punct = 0;      /* count valid special character */
    int i = 0;          /* loop variable */

    for (i = 0; i < strlen(input); i++)
        {
        check = ispunct(input[i]);
        if (check != 0)
            {
            if ((input[i] != '?') && (input[i] != '@') && (input[i] != '%')
                && (input[i] != '$') && (input[i] != '#'))
                {
                count++;
                }
            else
                {
                punct++;
                }
            }
        }

    if (punct == 0)
        {
        result = 0;
        }
    else
        {
        if (count > 0)
            {
            result = -1;
            }
        }

    return result;
    }


/* public function */
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
int validatePassword(char password[])
    {
    int validNum = 1;       /* to track errors */

    if (checkLength(password) == 0)
        {
        printf("\t\tNot valid - must not be longer than 12 characters\n");
        validNum = 0;
        }
    if (validNum && checkLength(password) < 0)
        {
        printf("\t\tNot valid - must be at least 8 characters\n");
        validNum = 0;
        }
    if (validNum && checkSpace(password) == 0)
        {
        printf("\t\tNot valid - embedded space\n");
        validNum = 0;
        }
    if (validNum && checkUpper(password) == 0)
        {
        printf("\t\tNot valid - must contain at least one upper case letter\n");
        validNum = 0;
        }
    if (validNum && checkLower(password) == 0)
        {
        printf("\t\tNot valid - must contain at least one lower case letter\n");
        validNum = 0;
        }
    if (validNum && checkPWDigit(password) == 0)
        {
        printf("\t\tNot valid - must contain at least two digit\n");
        validNum = 0;
        }
    if (validNum && checkSpecial(password) == 0)
        {
        printf("\t\tNot valid - must contain at least 1 valid special characters (?,@ ,%%,$,#)\n");
        validNum = 0;
        }
    if (validNum && checkSpecial(password) == -1)
        {
        printf("\t\tNot valid - unknown punctuation mark found (only ?,@,%%,$,# are allowed)\n");
        validNum = 0;
        }

    return validNum;
    }


/* public function */
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
int checkGender(char gender[])
    {
    int result = 0;     /* to store return value */

    if ((!strcasecmp(gender,"M")) || (!strcasecmp(gender,"F")))
        {
        result = 1;
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input location exists or not.
 *
 * Arguments
 *      input[]          -    the input location from the user
 *      location         -    provinces/districts in the
 *                            selected region
 *      locationCount    -    number of provinces/districts
 *                            in the region
 *
 * This function returns 'result' which is 1 when input
 * location found in selected region, otherwise 0.
 *
 *************************************************************/
int checkLocation(char input[], char location[][MAXLEN], int locationCount)
    {
    int i = 0;                /* loop variable */
    int result = 0;           /* to store return value */

    for (i = 0; i < locationCount; i++)
        {
        if (strcasecmp(input,location[i]) == 0)
            {
            result = 1;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function passes the provinces/districts in the
 * selected region to another function to check if the
 * entered location exist or not.
 *
 * Arguments
 *      input[]          -    the input location from the user
 *      region           -    selected choice for region
 *
 * This function returns 'result' which is 1 when input
 * location exists, otherwise 0.
 *
 *************************************************************/
int checkRegion(char input[], int region)
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

    int result = 0;     /* to store return value */

    switch (region)
        {
        case 1:
            result = checkLocation(input,northern,9);
            break;
        case 2:
            result = checkLocation(input,northeastern,20);
            break;
        case 3:
            result = checkLocation(input,western,5);
            break;
        case 4:
            result = checkLocation(input,central,21);
            break;
        case 5:
            result = checkLocation(input,eastern,7);
            break;
        case 6:
            result = checkLocation(input,southern,14);
            break;
        case 7:
            result = checkLocation(input,bangkok,50);
            break;
        }

	return result;
	}


/* private function */
/**************************************************************
 *
 * This function checks if the input contains only alphabets
 * or not.
 *
 * input[] is the input data from the user
 *
 * This function returns 'result' which is 1 when input
 * contains only alphabets, otherwise 0.
 *
 *************************************************************/
int checkAlpha(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if (isalpha(input[i]) == 0)
            {
            result = 0;
            break;
            }
        }
    return result;
    }


/* public function */
/**************************************************************
 *
 * This function is a major validation function used to
 * validate location.
 * This function calls other functions to check invalid cases.
 *
 * Arguments
 *      location[]       -    the input location from the user
 *      region           -    selected choice for region
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validateLocation(char location[], int region)
    {
    int validNum = 1;       /* to track errors */

    if (checkSpace(location) == 0)
        {
        printf("\t\tNot valid - no space allowed\n");
        validNum = 0;
        }
    if (validNum && (checkAlpha(location) == 0))
        {
        printf("\t\tNot valid - only alphabets are allowed\n");
        validNum = 0;
        }
    if (validNum && (checkRegion(location,region) == 0))
        {
        printf("\t\tNot valid - unknown province/district in this region\n");
        validNum = 0;
        }

    return validNum;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the choice(s) entered by the user
 * contains only digits and commas or not.
 *
 * input[] is the choice(s) selected by the user.
 *
 * This function returns 'result' which is 1 when the entered
 * choice(s) is in correct format, otherwise 0.
 *
 *************************************************************/
int checkFormat(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if ((isdigit(input[i]) == 0) && (input[i] != ','))
            {
            result = 0;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input contains 2 commas next
 * to each other or not.
 *
 * input[] is the input choice(s) selected by the user.
 *
 * This function returns 'result' which is 1 when no double
 * commas found in the input, otherwise 0.
 *
 *************************************************************/
int checkComma(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if ((input[i] == ',') && (input[i+1] == ','))
            {
            result = 0;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the input contains 2 digits next
 * to each other or not.
 *
 * input[] is the input choice(s) selected by the user.
 *
 * This function returns 'result' which is 1 when no 2 digits
 * next to each other is found, otherwise 0.
 *
 *************************************************************/
int checkDigit(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */

    for (i = 0; i < strlen(input); i++)
        {
        if ((isdigit(input[i]) != 0) && (isdigit(input[i+1]) != 0))
            {
            result = 0;
            break;
            }
        }

    return result;
    }


/* private function */
/**************************************************************
 *
 * This function checks if the choice(s) selected by the user
 * is between 1 and 6 without any duplicate or not
 *
 * input[] is the input choice(s) selected by the user.
 *
 * This function returns 'result' which is 0 when invalid
 * choice is found, -1 if duplicate selection is found,
 * otherwise 1.
 *
 *************************************************************/
int checkChoice(char input[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* to store return value */
    int number = 0;     /* to store choices changed from ASCii value */

    /* an array of integer to count each choices */
    int choice[6] = {0,0,0,0,0,0};

    for (i = 0; i < strlen(input); i++)
        {
        if (isdigit(input[i]) != 0)
            {
            number = (int)input[i] - 48;
            if ((number > 0) && (number < 7))
                {
                choice[number-1]++;
                }
            else
                {
                result = 0;
                break;
                }
            }
        }

    if (result != 0)
        {
        for (i = 0; i < 6; i++)
            {
            if (choice[i] > 1)
                {
                result = -1;
                break;
                }
            }
        }

    return result;
    }


/* public function */
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
int validateChoices(char selection[])
    {
    int validNum = 1;       /* to track errors */

    if (checkSpace(selection) == 0)
        {
        printf("\t\tNot valid - no space allowed\n");
        validNum = 0;
        }
    if (validNum && (checkFormat(selection) == 0))
        {
        printf("\t\tNot valid - wrong format (should be only integers with commas)\n");
        validNum = 0;
        }
    if (validNum && ((selection[0] == ',') || (selection[strlen(selection)-1] == ',')))
        {
        printf("\t\tNot valid - comma cannot be at the first and last position\n");
        validNum = 0;
        }
    if (validNum && (checkComma(selection) == 0))
        {
        printf("\t\tNot valid - double commas are not allowed\n");
        validNum = 0;
        }
    if (validNum && (checkDigit(selection) == 0))
        {
         printf("\t\tNot valid - integers must be separated by commas\n");
        validNum = 0;
        }
    if (validNum && (checkChoice(selection) == 0))
        {
        printf("\t\tNot valid - unknown choice (must be integer between 1 and 6)\n");
        validNum = 0;
        }
    if (validNum && (checkChoice(selection) == -1))
        {
        printf("\t\tNot valid - duplicate choices are not allowed\n");
        validNum = 0;
        }

    return validNum;
    }


/* public function */
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
int checkDuplicateEmail(char email[])
    {
    PERSON_T** userData = NULL;   /* an array of pointer to PERSON_T structure */
                                  /* to hold users's data read from the file */
    int personCount = 0;          /* to store number of user in the file */
    int result = 1;               /* to store return value */
    int i = 0;                    /* loop variable */

    personCount = readToCount();

    userData = calloc(personCount,sizeof(PERSON_T*));

    if (userData == NULL)
        {
        printf("\n\tMemory allocation failure - exiting!\n");
        exit(0);
        }
    readData(userData);

    for (i = 0; i < personCount; i++)
        {
        if (strcmp(userData[i]->email,email) == 0)
            {
            result = 0;
            break;
            }
        }

    return result;
    }


/* public function */
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
int checkDuplicateUsername(char username[])
    {
    PERSON_T* pUser = NULL;     /* to store user that has the same
                                 * username with the given one (if any) */
    int result = 1;             /* to store return value */

    pUser = hashTableLookup(username);

    if (pUser != NULL)
        {
        result = 0;
        }

    return result;
    }


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
int countSimilar(unsigned int tempBits)
    {
    int i = 0;              /* loop variable */
    int oneBitsTotal = 0;   /* to count bits that are '1' */

    /* length of the bit-string */
    int maxbits = sizeof(unsigned int) * 8;

    for (i = 0; i < maxbits; i++)
        {
        oneBitsTotal += tempBits & 0b000001;
        tempBits = tempBits >> 1;
        }

    return oneBitsTotal;
    }
