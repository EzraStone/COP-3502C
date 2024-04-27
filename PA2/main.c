/* 
COP 3502C Assignment 2
This program is written by: Ezra Stone
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define QNUM 12 // Max amount of queues
#define MAXLEN 51 // Max length of a customer name

// Customer struct to store the user info
typedef struct customer {
    char name[MAXLEN];
    int line_no;// Line Number
    int time;
    int noOfTicket;// Number of Tickets
}customer;

// Node struct for linked list
typedef struct node {
    customer *custPtr;// Lets us access the information for the customer
    struct node *next;// Goes to next node in the linked list
}node;

// Queue struct used for all the booths 
typedef struct queue {
    node *front;
    node *back;
    int nodeCount;// Keeps count of all the nodes
}queue;

// Creates and adds are new element to end of the queue
void enqueue(queue* qPtr, customer* cPtr) {
    node* newNode = (node*)malloc(sizeof(node));// Allocating memory for a new node
    newNode->custPtr = cPtr;// Has our new nodes customer pointer point to customer in main
    newNode->next = NULL;// Assigns nodes next to NULL

    if(qPtr->front == NULL) {// Checks if it is the first node being added
        //if true both front and back are assigned to the new node
        qPtr->front = newNode;
        qPtr->back = newNode;
    }

    if (qPtr->nodeCount == 0) {// Checks if the node count is equal to 0
        qPtr->front = newNode;// If true front is equal to new node
    } 
    else {// If it is not equal to 0 the next node will equal new node
        qPtr->back->next = newNode;
    }

    qPtr->back = newNode;// Back equals the new node
    qPtr->nodeCount++;// Adds 1 to the nodecount because a new node has been added
}

// Removes the node that is being stored at the front if there is a node
customer* dequeue(queue* qPtr){
    if(qPtr->front ==NULL){// Checks if there is any nodes currently present
        return NULL;// If not just return NULL
    }

    node *temp = qPtr->front;// temp node equal to current queue front
    customer *returnVal = qPtr->front->custPtr;// return value equals queues front customer

    qPtr->front = qPtr->front->next;// goes to next 

    if(qPtr->front == NULL){// Assigns the back to NULL if the front is equal to NULL
        qPtr->back = NULL;
    }

    free(temp);// frees the memory created for temp in enqueue
    qPtr->nodeCount--;// Remove 1 from the node count because node has been removed

    return returnVal;// Returns return value
}

// Peeks at the front of the queue
customer* peek(queue *qPtr){
    if(qPtr->front != NULL){// If queues front not equal to NULL
        return qPtr->front->custPtr;// returns the customer pointer
    }
    else{// if the queues front equals NULL than return NULL
        return NULL;
    }
}

// Checks if the queue is empty
int Empty(queue* qPtr) {
    if (qPtr->front == NULL) {// If front equals NULL than the q is empty so return 1
        return 1;
    }
    else {// Else queue has at least one value so return 1
        return 0;
    }
}

// Initialize the queues
void init(queue* qPtr){
    // Sets front and back equal to NULL
    qPtr->front = NULL;
    qPtr->back = NULL;
    qPtr->nodeCount = 0;// Sets node count equal to 0
}

// Gets the size of the queues
int size(queue* qPtr) {
    return qPtr->nodeCount;// Gets size by returning node count
}

// Calculates the time using the formula given in the pdf
int calculateTime(int numTickets) {
    return 30 + numTickets * 5;
}

// Processes customer and displays the customer info
void displayQueue(queue* qPtr, int booths, int *boothQCount, int nonEmptyQ[]) {
    int currentTime = 0;// Keeps track of time
    int queueIndex = 0; // Index to iterate over all queues
    for (int i = 0; i < booths; i++) {// Iterate through all the booths given to us by user input
        printf("Booth %d\n", i + 1);// Prints the current booth were on
        int endQueueIndex = queueIndex + boothQCount[i]; // Calculate end index for queues in this booth  

        while(1) {
            int minQue = queueIndex;// Minimum queue equals the queue index
            int minCount = 0;
            for (int j = queueIndex; j < endQueueIndex; j++) {// Iterate over queues in the current booth             
                if(Empty(&qPtr[nonEmptyQ[j]])) {// If the queue at j is empty ignore it by using continue
                    continue;
                }
                if(Empty(&qPtr[minQue]) || qPtr[nonEmptyQ[j]].front->custPtr->time < qPtr[minQue].front->custPtr->time) {// Checks if queue is empty at each index or if current time less than the arrival time
                    minQue = nonEmptyQ[j];// Sets mininmum queue equal to non empty queue at j iteration
                    minCount = qPtr[nonEmptyQ[j]].front->custPtr->time;// minimum count equals the time for that queue
                }                
            }

            // If all queues in the booth are empty, exit the loop
            if(peek(&qPtr[minQue])==NULL)
                break;
            
            // Update current time based on the customer's time
            if(currentTime < qPtr[minQue].front->custPtr->time) {
                currentTime = qPtr[minQue].front->custPtr->time;// assigns the arrival time to current time for the first customer of that booth
            }            
            currentTime += calculateTime(qPtr[minQue].front->custPtr->noOfTicket);// Adds the calculated time

            // Prints the customer info
            printf("%s from line %d checks out at time %d.\n", qPtr[minQue].front->custPtr->name, minQue+1, currentTime);
            
            // Frees and dequeue the customer
            free(dequeue(&qPtr[minQue]));
            
            // Move to the next queue index in the current booth
        }
        printf("\n");
        queueIndex = endQueueIndex;// Sets queue index equal to the end queue index
        currentTime = 0; // Resets current time for the next booth
    }
}

// Finds the queue with the lowest arrival time
int lowestQueue(queue* qPtr) {
    int minSize = size(&qPtr[0]);// Stes minimum size equal to the size at first queue
    int minQueueIndex = 0;

    for (int i = 1; i < QNUM; i++) {// Iterate through all the queues by using QNUM
        if (size(&qPtr[i]) > 0 && (size(&qPtr[minQueueIndex]) == 0 || size(&qPtr[i]) < minSize)) {// Checks if the size at queue iteration great than 0 and if the size at the first index is 0 or queue size less than minimum size
            minSize = size(&qPtr[i]);// Sets minimum size equal to the size of queue iteration
            minQueueIndex = i;// Sets minimum queue index equal to i
        }
    }

    return minQueueIndex;// Returns the queue index with lowest arrival time
} 

// Assigns the values given to us by the user into the customer struct
customer* createCustomer(char* name, int time, int noOfTicket, int lineNo) {
    customer* newCustomer = (customer*)malloc(sizeof(customer));// Allocates memory for the customer

    if (newCustomer != NULL) {// Checks if new customer is NULL
        // Copies user info into customer struct
        strcpy(newCustomer->name, name);
        newCustomer->name[MAXLEN - 1] = '\0'; 
        newCustomer->time = time;
        newCustomer->noOfTicket = noOfTicket;
        newCustomer->line_no = lineNo;
    }

    return newCustomer;// Returns the new customer we just made
}

int main(void){
    int customers;
    int booths;
    char cName[MAXLEN];// Customer name
    int noSeats;// Number of seats
    int lineNum;// Line Number
    int time;
    int totalTime = 0;

    queue lines[QNUM];// Declare the 12 queues

    for(int i = 0; i<QNUM; i++) {
        init(&lines[i]);// Initializes the 12 queues
    }

    scanf("%d %d", &customers, &booths);// Retrieves the amount of customer and booths that will be used

    for(int i=0; i<customers; i++) {
        scanf("%s %d %d", cName, &noSeats, &time);// Retrieves custoner name, number of seats, and time 

        lineNum = tolower(cName[0] % 13);// Calculates the seat number by mod 13ing the first character of the name then assigns it to line number

        if (lineNum == 0) {// If the calculations above are A or N this will run 
            lineNum = lowestQueue(lines);// Sets line num equal to lowest queue value
        }else{
            lineNum -= 1;// Subtracts 1 from line number
        }

        customer *oneCustomer = createCustomer(cName, time, noSeats, lineNum);// This is where are cutomer is actually being made in main

        enqueue(&lines[lineNum], oneCustomer);// Adds new customer to end of queue
    }
    int nonEmptyQ[QNUM];// Will store the queues that have at least one customer in it
    int qNums = 0;

    for (int i = 0; i < QNUM; i++) {// Iterate through all the queues
        if (size(&lines[i]) > 0) {// Checks if the size of the queue is greater than 1 which is needed for it to not be empty
            nonEmptyQ[qNums] = i;// Saves that iteration in nonEmptyQ
            qNums++;// Adds one to help us keep track of how many queues are non empty
        }
    }

    int boothNum = qNums/booths;// Determines how many queues each booth will have
    int boothExtra = qNums%booths;// Determines how many booths will have one extra queue
    int *boothQCount = calloc(booths,sizeof(int));// Allocates memory for these booths and sets the value for them to 0

    for(int i=0; i<booths; i++){// Iterate through all the booths
        boothQCount[i] += boothNum;// Sets the booth q count = to the calculations done above
        if(i < boothExtra){// Will run as long as there are still extras
            boothQCount[i]++;// Adds one to booth q count
        }
    }
    
    displayQueue(lines, booths, boothQCount, nonEmptyQ);// Display our queue
    free(boothQCount);// Frees memeory for booth queue count
}