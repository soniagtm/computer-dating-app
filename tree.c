/********************************************************************
 *
 * tree.c
 *
 *      This program implements the tree which will be used
 *   	to partition and access the entire user base according
 *      to the mutually exclusive attributes. Any person will
 *      be associated with a single path through the tree.
 *      At the leaf nodes, there would be a list of all people
 *      who fall into this combination of categories.
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

/* global variables */
NODE_T* pRoot = NULL;       /* Root node of the tree */
int attributeCount = 4;     /* number of exclusive attributes */

/* an array of char* holding names of exclusive attributes */
char* attributes[] = {"GENDER","AGE","ETHNICITY","RELIGION"};


/* private function */
/**************************************************************
 *
 * This function is responsible for recursively creating lower
 * levels' nodes until the level is equal to the number of
 * exclusive attributes.
 *
 * Arguments
 *      pParent         -   The parent node of the child nodes
 *      childCount      -   number of child nodes to be allocated
 *      level           -   level of the tree
 *
 *************************************************************/
void allocateChildren(NODE_T* pParent, int childCount, int level)
    {
    int i = 0;                  /* loop variable */
    NODE_T* pNewNode = NULL;    /* to create the new node */

    level = level + 1;
    if (level < attributeCount)
        {
        /* allocate child nodes */
        for (i = 0; i < childCount; i++)
            {
            pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
            if (pNewNode == NULL)
                {
                printf("\n\tMemory allocation failure - exiting!\n");
                exit(0);
                }
            strcpy(pNewNode->attribute,attributes[level]);
            pParent->children[i] = pNewNode;
            allocateChildren(pNewNode,6,level);
            }
        }
    else
        {
        if (level == attributeCount)
            {
            /* allocate the leaf nodes */
            for (i = 0; i < childCount; i++)
                {
                pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
                if (pNewNode == NULL)
                    {
                    printf("\n\tMemory allocation failure - exiting!\n");
                    exit(0);
                    }
                strcpy(pNewNode->attribute,"LEAF");
                pParent->children[i] = pNewNode;
                pNewNode->head = NULL;
                pNewNode->tail = NULL;
                }
            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for building the tree
 * with empty leaf nodes.
 *
 * No Argument.
 *
 *************************************************************/
void createNewTree()
    {
    NODE_T* pNewNode = NULL;    /* to create the new node */
    NODE_T* pParent = NULL;     /* points to the parent node */
    int level = 0;              /* level of the tree */

    pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
    if (pNewNode == NULL)
        {
        printf("\n\tMemory allocation failure - exiting!\n");
        exit(0);
        }

    strcpy(pNewNode->attribute,attributes[0]);
    pRoot = pNewNode;
    pParent = pRoot;

    /* recursively create lower levels */
    allocateChildren(pParent,2,level);
    }


/* public function */
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
void addNewPerson(PERSON_T* pPerson)
    {
    int i = 0;                      /* loop variable */

    /* an array of integer to store values of exclusive attributes */
    int attributeValue[4] = {0,0,0,0};

    NODE_T* pCurrent = NULL;        /* points to the current node */
    PERSON_REF_T* pEntry = NULL;    /* points to new user's reference */


    /* check if information is filled or not */
    if (checkGender(pPerson->gender) == 1)
        {
        /* get exclusive attributes' value */
        if (strcmp(pPerson->gender,"M") == 0)
            attributeValue[0] = 1;
        else
            attributeValue[0] = 2;

        attributeValue[1] = pPerson->age;
        attributeValue[2] = pPerson->ethnicity;
        attributeValue[3] = pPerson->religion;

        /* traverse the tree to find the right leaf node */
        pCurrent = pRoot;

        for (i = 0; i < attributeCount; i++)
            {
            pCurrent = pCurrent->children[attributeValue[i]-1];
            }

        pEntry = (PERSON_REF_T*) calloc(1,sizeof(PERSON_REF_T));
        if (pEntry == NULL)
            {
            printf("\n\tMemory allocation failure - exiting!\n");
            exit(0);
            }
        pEntry->pPerson = pPerson;

        /* add new person to the list on that leaf node */
        if (pCurrent->head == NULL)
            {
            pCurrent->head = pEntry;
            pCurrent->tail = pEntry;
            }
        else
            {
            pCurrent->tail->pNext = pEntry;
            pCurrent->tail = pEntry;
            }
        }

    }


/* private function */
/**************************************************************
 *
 * This function is responsible for removing the user's
 * from the list in order to change reference list
 * corresponding to the updated exclusive attributes.
 *
 * Arguments
 *      pPerson       -      pointer to PERSON_T structure
 *                           holding logged in user's data
 *      oldAttribute  -      array of integer holding values
 *                           of exclusive attributes before
 *                           modifying the data
 *
 *************************************************************/
void removePerson(PERSON_T* pPerson, int oldAttribute[4])
    {
    int i = 0;                             /* loop variable */
    NODE_T* pCurrent = NULL;               /* points to the current node */
    PERSON_REF_T* currentPerson = NULL;    /* points to the current person */
                                           /* in the list */
    PERSON_REF_T* previousPerson = NULL;   /* points to the previous person */
                                           /* in the list */

    /* check if information is filled or not */
    if (checkGender(pPerson->gender) == 1)
        {
        /* traverse the tree to find the right leaf node */
        pCurrent = pRoot;

        for (i = 0; i < attributeCount; i++)
            {
            pCurrent = pCurrent->children[oldAttribute[i] - 1];
            }

        previousPerson = NULL;
        currentPerson = pCurrent->head;

        /* find the person to be removed */
        while (currentPerson != NULL)
            {
            if (currentPerson->pPerson == pPerson)
                break;

            previousPerson = currentPerson;
            currentPerson = currentPerson->pNext;
            }

        /* remove the person from the list on that leaf node */
        if (currentPerson == pCurrent->head)
            {
            pCurrent->head = currentPerson->pNext;
            }
        else if (currentPerson == pCurrent->tail)
            {
            pCurrent->tail = previousPerson;
            }
        else
            {
            previousPerson->pNext = currentPerson->pNext;
            free(currentPerson);
            }
        }
    }


/* public function */
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
void transferPerson(PERSON_T* pPerson, int oldAttribute[4])
    {
    /* remove the person from the former list */
    removePerson(pPerson,oldAttribute);

    /* add the person to the new list */
    addNewPerson(pPerson);
    }


/* public function */
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
PERSON_REF_T* passList(PERSON_T* pPartner)
    {
    int i = 0;                      /* loop variable */

    /* an array of integer to store values of exclusive attributes */
    int attributeValue[4] = {0,0,0,0};

    NODE_T* pCurrent = NULL;            /* points to the current node */
    PERSON_REF_T* currentPerson = NULL;	/* points to the reference of */
                                        /* current person in the list */

    /* get exclusive attributes' value */
    if (strcmp(pPartner->gender,"M") == 0)
        attributeValue[0] = 1;
    else
        attributeValue[0] = 2;

    attributeValue[1] = pPartner->age;
    attributeValue[2] = pPartner->ethnicity;
    attributeValue[3] = pPartner->religion;

    /* traverse the tree to find the right leaf node */
    pCurrent = pRoot;
    for (i = 0; i < attributeCount; i++)
        {
        pCurrent = pCurrent->children[attributeValue[i]-1];
        }

    currentPerson = pCurrent->head;

    return currentPerson;
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for freeing people in the
 * the list at the leaf node of the tree.
 *
 *      pLeaf      -      pointer to NODE_T structure
 *                        holding leaf node of the tree
 *
 *************************************************************/
void freePeople(NODE_T* pLeaf)
    {
    PERSON_REF_T* pHead = NULL;     /* to store reference to the list's head */
    PERSON_REF_T* pCurrent = NULL;  /* points to the current reference */
    PERSON_REF_T* pDelete = NULL;   /* points to the reference to be freed */

    pHead = pLeaf->head;
    pCurrent = pHead;

    while (pCurrent != NULL)
        {
        pDelete = pCurrent;
        pCurrent = pCurrent->pNext;

        free(pDelete->pPerson);
        free(pDelete);
        }
    }


/* private function */
/**************************************************************
 *
 * This function is responsible for recursively freeing lower
 * levels' nodes and calls other function to free people
 * in the list of each leaf node.
 *
 * Arguments
 *      pParent         -   The parent node of the child nodes
 *      childCount      -   number of child nodes to be freed
 *      level           -   level of the tree
 *
 *************************************************************/
void freeChildren(NODE_T* pParent, int childCount, int level)
    {
    NODE_T* currentNode = NULL;   /* points to the current node */
    int i = 0;                    /* loop variable */

    level = level + 1;
    if (level < attributeCount)
        {
        /* free child nodes */
        for (i = 0; i < childCount; i++)
            {
            currentNode = pParent->children[i];
            freeChildren(currentNode,6,level);
            free(currentNode);
            }
        }
    else
        {
        if (level == attributeCount)
            {
            /* free leaf nodes */
            for (i = 0; i < childCount; i++)
                {
                currentNode = pParent->children[i];
                freePeople(currentNode);
                free(currentNode);
                }
            }
        }
    }


/* public function */
/**************************************************************
 *
 * This function is responsible for freeing items in the
 * tree and linked lists at the leaf nodes.
 *
 * No Argument.
 *
 *************************************************************/
void freeTree()
    {
    int level = 0;      /* level of the tree */

    /* free nodes in the tree and lists at leaf nodes */
    freeChildren(pRoot,2,level);

    /* free root node of the tree */
    free(pRoot);
    }
