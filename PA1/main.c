/*
COP 3502C Assignment 1
This program is written by: Ezra Stone
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSIZE 10 // Initial size of any row
#define MAXLEN 50 // Maximum length of a name
#define MAXROWS 100000 //Maximum number of rows in the theatre

/*
Theater seat order
*/
typedef struct order{
    int s_seat;
    int e_seat;
    char *name;
}order;

/*
Theater rows
*/
typedef struct theaterrow{
    order** listorders;
    int max_size;
    int cur_size;
}theaterrow;

// Returns a pointer to a dynamically allocated order storing the given
// start row, end row, and the name this_name. Note: strcpy should be
// used to copy the contents into the struct after its name field is
// dynamically allocated.
order* make_order(int start, int end, char* this_name);

// This function will allocate the memory for one theaterrow, including
// allocating its array of orders to a default maximum size of 10, and
// setting its current size to 0.
theaterrow* make_empty_row();

// Assuming that order1 and order2 point to orders on the same row, this
// function returns 1 if the orders conflict, meaning that they share at
// least 1 seat in common, and returns 0 otherwise.
int conflict(order* order1, order* order2);

// Returns 1 if the order pointed to by this_order can be added to the
// row pointed to by this_row. Namely, 1 is returned if and only if
// this_order does NOT have any seats in it that are part of any order
// already on this_row.
int can_add_order(theaterrow* this_row, order* this_order);

// This function tries to add this_order to this_row. If successful,
// the order is added and 1 is returned. Otherwise, 0 is returned and
// no change is made to this_row. If the memory for this_row is full,
// this function will double the maximum # of orders allocated for the
// row (via realloc), before adding this_order, and adjust max_size and
// cur_size of this_row.
void add_order(theaterrow* this_row, order* this_order);

// This function returns 1 if the seat number seat_no is contained in
// the range of seats pointed to by myorder, and returns 0 otherwise.
int contains(order* myorder, int seat_no);

// If seat_num in the row pointed to by this_row is occupied, return a
// pointer to the string storing the owner’s name. If no one is sitting
// in this seat, return NULL.
char* get_row_owner(theaterrow* this_row, int seat_num);

// If seat_num seat number in row number row is occupied, return a
// pointer to the owner’s name. Otherwise, return NULL.
char* get_owner(theaterrow** theater, int row, int seat_num);

// Frees all memory associated with this_order.
void free_order(order* this_order);

// Frees all memory associated with this_row.
void free_row(theaterrow* this_row);

int main(void){
    theaterrow** theater = calloc(MAXROWS+1, sizeof(theaterrow*));// Allocating memory for theater

    order* order1;// Where the orders will be stored
    char option[MAXLEN];// Stores the user choice, such as buy, lookup, and exit
    int r, s, e;// Row, Start seat, and End seat
    char name[MAXLEN];// Stores owners name

    for(int i=0; i<=MAXROWS; i++){
        theater[i] = make_empty_row();// Creates empty rows that is stored in each iteration of theater
    }

    scanf("%s", option);// Gets the first choice that the user makes 

    while(strcmp(option, "EXIT") != 0){// While loop will continue as long as EXIT is not entered

        if(strcmp(option, "BUY") == 0){
            scanf("%d %d %d %s", &r, &s, &e, name);// Gets the row, start seat, end seat, and person buying those variable

            order1 = make_order(s, e, name);// Makes order using info we just got and stores in order1
        
            if(can_add_order(theater[r], order1)){// Checks if the order can actually be made, makes sure theres no conflict with other orders
                add_order(theater[r], order1);// If order can be made then the order will finally be added and print out success
                printf("SUCCESS\n");
            } 
            else {// If order can't be added then it will print failure
                printf("FAILURE\n");
            }
        }

        else if(strcmp(option, "LOOKUP") == 0){
            scanf("%d %d", &r, &s);// Stores row and seat number

            char *owner = get_owner(theater, r, s);// Checks who or if anyone owns that row/seat and stores it in name variable

            if(owner != NULL){// Runs as long as name is not NULL
                printf("%s\n", owner);// Prints the name of row/seat owner
            }
            else{// Runs if name is equal to NULL
                printf("None\n");
            }
        }
        
        scanf("%s", option);// Gets other choices after fisrt iteration because the other scanf is outside the while
    }
    for (int i = 0; i < MAXROWS; i++) {
        free_row(theater[i]);
    }
    free(theater);
}

order* make_order(int start, int end, char* this_name){
    order *orders = (order*)malloc(sizeof(order));// Allocates memory for the order

    // Uses function variables to store info into struct
    orders->s_seat = start;
    orders->e_seat = end;
    orders->name = malloc(strlen(this_name) + 1);// Allocates memory for name
    strcpy(orders->name, this_name);// Copies this_name variables into the structs name

    return orders;
}

theaterrow* make_empty_row(){
    theaterrow *row = (theaterrow*)malloc(sizeof(theaterrow));// Allocates memory for row

    row->listorders = (order**)malloc(INITSIZE * sizeof(order*));// Allocates 10 blocks of memory for listorders
    row->max_size = INITSIZE;// Assigns max_size to 10
    row->cur_size = 0;// Assigns cur_size to 0

    return row;
}

int conflict(order* order1, order* order2){
    if(order1->e_seat < order2->s_seat){// If the end seat is before the start there is no way there can be ant conflict
        return 0;
    }
    if(order2->e_seat < order1->s_seat){
        return 0;
    }
    else{
        return 1;
    }
}

int can_add_order(theaterrow* this_row, order* this_order){
    for (int i = 0; i < this_row->cur_size; i++) {
        if (conflict(this_row->listorders[i], this_order)){// Uses conflict function to check if seats are already assigned to someone
            return 0;
        }
    }
    return 1;
}

void add_order(theaterrow* this_row, order* this_order){
    if (this_row->cur_size == this_row->max_size) {
        this_row->max_size *= 2;
        this_row->listorders = realloc(this_row->listorders, this_row->max_size * sizeof(order*));// This will reallocate memory for order if max size is met. Reallocates by doubling the previous size
    }

    this_row->listorders[this_row->cur_size] = this_order;// Adds order
    this_row->cur_size++;
}

int contains(order* myorder, int seat_no){
    if(seat_no >= myorder->s_seat && seat_no <= myorder->e_seat){// Checks if seat_no is within the orders seats
        return 1;
    }
    
    return 0;
}

char* get_row_owner(theaterrow* this_row, int seat_num){
    for(int i = 0; i < this_row->cur_size; i++){
        if(contains(this_row->listorders[i], seat_num)){// Uses contains to see if search matches an actual order
            return this_row->listorders[i]->name;// Returns the owners name 
        }
    }

    return NULL;// Will return NULL if no one owns the seat searched
}

char* get_owner(theaterrow** theater, int row, int seat_num){
    return get_row_owner(theater[row], seat_num);
}

void free_order(order* this_order){
    free(this_order->name);
    free(this_order);
}

void free_row(theaterrow* this_row){
    for (int i = 0; i < this_row->cur_size; i++) {
        free_order(this_row->listorders[i]);
    }
    free(this_row->listorders);
    free(this_row);
}