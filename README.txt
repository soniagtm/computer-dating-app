/********************************************************************
 *
 * README.txt
 *
 *      This text file explains how to run the program 
 *      as well as brief explanation of the process of
 *      the program. Some test cases for finding the 
 *      match is provided as well. This text file also 
 *      list files written by Aj. Sally Goldin which 
 *      are used in Computer dating application.
 *
 *      Created by Jiajia      Bai   	   (Jia)   ID 63070503404
 *		   Sonia       Gautam 	   (Sonia) ID 63070503410
 *		   Tamonwan    Boonpa 	   (Nice)  ID 63070503418
 *                 Theeranont  Ruchiyakorn (Peak)  ID 63070503420
 *
 *	24 May 2021
 *
 ********************************************************************


 User manual
 ------------

 To run the program, follow the instruction
 - - - - - - - - - - - - - - - - - - - - - - 

 1) Run Makefile on the terminal.
 2) Type ./datingApp to execute the program.
 3) The system will display options for the user to select
    which are  

	[1]     LOGIN               
	[2]     CREATE NEW ACCOUNT
        [3]     EXIT    


 (menu page)
 To create new account, the user has to type 2 and enter the following information
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

 1) Name     : Any combination of alphabets and spaces
 2) Email    : Must follow the rules below

	• No embedded spaces or special characters anywhere in 
	  the email address, except period (.), at­sign (@), 
	  underscore (_) and/or dash (­)

	• Must begin with an alphanumeric (letter or digit) character 

	• Exactly one occurrence of the at­sign (@)

	• At least one alphabetic or numeric character before the at­sign

	• Address must end in one of: .com, .net, .ac.th, or .co.th 
	  (top­level domains or TLD)

	• At least one alphabet between the at­sign and the TLD.

	• No underscores and digits after the at­sign.

	• At least one alphabet between any periods that occur 
	  after the at­sign.

 3) Username : Must follow the rules below

	• Any combination of alphabets, digits, and underscore (_)

	• The length should be 5 -15 and no space is allowed.

	• Username is case-sensitive.

 4) Password : Must follow the rules below

	• At least 8 characters long and no longer than 12 characters

	• Must contain at least one upper case letter

	• Must contain at least one lower case letter

	• Must contain at least two digits

	• Must contain at least one of the following special characters: ? @ % $ #

	• Must not contain any other special characters not in the list above.

 5) The system will ask if the user is sure that the user wants to create an account
    with the information that has been typed. 
    - If the user is sure, type 'Y'.
    - If the user is not, type any alphabets other than 'Y' to go back to menu page.

 6) If the user typed 'Y', the user's information will be saved in the system and the 
    system will redirect the user to the menu page. 

 (menu page)
 To login, the user has to type 1 and enter the following information
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

 1) Username : type your username
 2) Password : type your password

 Note that the user can press "ENTER" if he/she wants to go back to menu page

 3) The system will display the main menu of computer dating application

	
 Main menu of the computer dating application
 - - - - - - - - - - - - - - - - - - - - - - -
 
 The system will display 3 options which are

	[1]     ADD/EDIT PROFILE              
	[2]     FIND YOUR PARTNER
        [3]     LOGOUT

 (main menu)
 To add or edit data, the user has to type 1 
 - - - - - - - - - - - - - - - - - - - - - -

 1) If the user hasn't filled his/her information yet, the system will let
    the user fill neccessary information which are

	-   Gender		 : M - Male , F - Female 

	-   Location		 : Select region your living from the choices
				   provided, then the system will display
				   districts/provinces in that region.
				   Type the province you're living 
				   (district if you're in Bangkok)

       	-   Age			 : Select your age from choices provided (1-6)

	Note that our application only allows user with age between 18 and 47

       	-   Ethnicity		 : Select your ethnicity from choices provided (1-6)

      	-   Religion		 : Select your religion from choices provided (1-6)

      	-   Education level	 : Select your education level from choices provided (1-6)

       	-   Occupation		 : Select your occupation from choices provided (1-6)

       	-   Favorite cuisine	 : Select your preference for food from choices provided (1-6)
				   You can select more than one choice (ex. 1,2)

       	-   Favorite pet	 : Select your preference for pet from choices provided (1-6)
				   You can select more than one choice (ex. 3,4,5)

       	-   Favorite music genre : Select your preference for music from choices provided (1-6)
				   You can select more than one choice (ex. 1,3)

       	-   Favorite hobby	 : Select your preference for hobby from choices provided (1-6)
				   You can select more than one choice (ex. 2,4,6)

       	-   Favorite film genre	 : Select your preference for movie from choices provided (1-6)
				   You can select more than one choice (ex. 3,5)

    If the information has already been filled, the system will skip this step

 2) The system will display current information and ask if the user wants to modify
    his/her information or not. If the user want to, type 'Y'. Otherwise, type any 
    alphabets other than 'Y' to go back to main menu.

 3) If the user typed 'Y', the system will let the user select the category of information
    that the user wants to modify which are

	[1]     Personal information             
	[2]     Preference
        [3]     Back to main menu

    The user has to select the category  and then the system will display choices of 
    information which the user has to choose one of them to modify. The system will 
    ask for new information of the choice the user wanted to modify.

    Note that the system will not allow the user to enter his/her current data

    This will be repeated until the user type 3 (Back to main menu)


 (main menu)
 To find the match, the user has to type 2
 - - - - - - - - - - - - - - - - - - - - - 

    First of all, the system will check if the logged in user has already filled 
    his/her information or not. If not, the system will display error message
    and go back to main menu of computer dating application.


    If the logged in user has already added the information, the system will 
    do the following process
    
 1) The system will ask the user to enter exclusive attributes which are gender, 
    age, ethnicity, and religion that the user desired for his/her partner.

 2) The system will find list of people according to entered exclusive attributes.
    If no one found with entered properties, the system will display error message
    and ask the user if he/she wants to re-enter the exclusive attributes.

 3) When the list is found and there exist at least one member in that list,
    the system will ask the user to enter remaining attributes for desired partner
    with the allowance of multiple selections. The remaining attributes are  
    education level, occupation, preference for food, pet, music, hobby and movie.

 4) The system will compute the number of similarities of each person in the list
    with the properties other than exclusive one (since everyone in the list have
    same combination of exclusive attributes).

 5) The system will display 3 people with highest similarity score and will allow
    the user to look at each matching person's general information, matching 
    properties, and other properties.


 Some test cases for finding the match
 - - - - - - - - - - - - - - - - - - - 

    If you already has an account and your information has been entered, you can
    test the find match feature by entering the following exclusive attributes

    * No one with the following combination of exclusive attributes

	-   Gender		 : M   	[Male] 
        -   Age  		 : 6	[Above 59 years old]
	-   Ethnicity		 : 6	[Others] 
	-   Religion		 : 6	[Others]
   
    =============================================================

	-   Gender		 : F   	[Female] 
        -   Age  		 : 4	[Between 36 and 46]
	-   Ethnicity		 : 5	[African] 
	-   Religion		 : 5	[No religion]
   
    =============================================================


    * One or two people with the following combination of exclusive attributes

	-   Gender		 : M   	[Male] 
        -   Age  		 : 3	[Between 28 and 35]
	-   Ethnicity		 : 6	[Others] 
	-   Religion		 : 2	[Islam]
   
    =============================================================

	-   Gender		 : F   	[Female] 
        -   Age  		 : 5	[Between 47 and 58]
	-   Ethnicity		 : 1	[Thai] 
	-   Religion		 : 4	[Buddhism] 
   
    =============================================================


    * Three or more people with the following combination of exclusive attributes

	-   Gender		 : M   	[Male] 
        -   Age  		 : 2	[Between 23 and 27]
	-   Ethnicity		 : 4	[Caucasian] 
	-   Religion		 : 1	[Christianity]
   
    =============================================================

	-   Gender		 : F   	[Female] 
        -   Age  		 : 1	[Between 18 and 22]
	-   Ethnicity		 : 1	[Thai] 
	-   Religion		 : 4	[Buddhism]
   
    =============================================================
    

 (main menu)
 To logout of the application , the user has to type 3
 - - - - - - - - - - - - - - - - - - - - - - - - - - - 

 The system will redirect the user to the menu page.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


 # List of files/functions written by Aj. Sally Goldin  
   which are used in computer daping application.

 - chainedHashTable.c

	We have commented line 168 - 169 which prints hash function
        index in hashTableInsert function.
	The file name is changed to chainedHashTableMod.c
	abstractHashTable.h is still the same.
		
 - unsigned int bitwiseOpHash(char* key)

	This robust hash function from hashTester.c is added 
	in readWriteData.c to modify string values.

	
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
