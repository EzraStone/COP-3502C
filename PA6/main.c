/* 
COP 3502C Assignment 6
This program is written by: Ezra Stone
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTLEN 24
#define TABLESIZE 300007

// Global Variable to calculate the time complexity
int time_complexity = 0;

typedef struct item {
    char name[MAXSTLEN + 1];
    int qty;
    int saleprice;
} item;

typedef struct chainNode {
    item* itemPtr;
    struct chainNode* next;
} chainNode;

typedef struct hashTable {
    chainNode** lists;
    int size;
} hashTable;

int hashfunction(char* word, int size) {
    int len = strlen(word);
    int res = 0;

    for (int i = 0; i < len; i++)
        res = (1151 * res + (word[i] - 'a')) % size;

    return res;
}

// This function will intialize the tables 
void initTable(struct hashTable* h, int size) {
    h->size = size;
    // Allocate the memory needed for the lists by multiplying it by size
    h->lists = malloc(size * sizeof(chainNode*));

    // Set all lists to NULL
    for (int i = 0; i < size; i++) {
        h->lists[i] = NULL;
    }

}

// This function will process the orders
void buyItem(hashTable* hTable, char* itemName, int quantity, int totalPrice, int* totalCash) {
    int pos = hashfunction(itemName, hTable->size);

    int itemCost = totalPrice;

    // Check if the item already exists in the hash table
    chainNode* current = hTable->lists[pos];
    

    while (current != NULL) {
        // Search was made so add 1 to the time complexity
        time_complexity++;
        
        // Check if the item name is already in the list using string compare
        if (strcmp(current->itemPtr->name, itemName) == 0) {
            // If the item is found we only need to update the quantity size and totalCash amount
            current->itemPtr->qty += quantity;
            *totalCash -= totalPrice;
            // Print the new order to the screen
            printf("%s %d %d\n", itemName, current->itemPtr->qty, *totalCash);
            return;
        }
        // Move to the next
        current = current->next;
    }

    // If the item doesn't exist create a new item and insert it into the hash table
    item* newItem = malloc(sizeof(item));

    strncpy(newItem->name, itemName, MAXSTLEN);
    newItem->qty = quantity;
    newItem->saleprice = totalPrice;

    // Create a new node
    chainNode* newNode = malloc(sizeof(chainNode));
    
    newNode->itemPtr = newItem;
    newNode->next = hTable->lists[pos];
    hTable->lists[pos] = newNode;

    // Update time complexity because a new order was made
    time_complexity++;

    // Update the cash cause an order was made
    *totalCash -= totalPrice;
    // Print it to the screen
    printf("%s %d %d\n", itemName, newItem->qty, *totalCash);
}


void sellItem(hashTable* hTable, char* itemName, int quantity, int* totalCash) {
    int pos = hashfunction(itemName, hTable->size);

    // Check if the item exists in the hash table
    chainNode* current = hTable->lists[pos];

    while (current != NULL) {
        // Add 1 to the time complexity because a search was done
        time_complexity++;

        // Check if item is in the hash table already
        if (strcmp(current->itemPtr->name, itemName) == 0) {
            // Checks to see if the quantity we want to sell is not going over the quantity we currently own
            if (current->itemPtr->qty >= quantity) {
                current->itemPtr->qty -= quantity;
                // Add the new amount to total cash
                *totalCash += quantity * current->itemPtr->saleprice;
                printf("%s %d %d\n", itemName, current->itemPtr->qty, *totalCash);
                return;
            } 
            // If the order made does go above what we currently have we will just see everying owned
            else {
                // int is needed so we do not lose the amount that will be stored before setting it to 0
                int curAmount = current->itemPtr->qty;
                // Completely empty the orders qty
                current->itemPtr->qty = 0;
                // Add the new amount to total cash
                *totalCash += curAmount * current->itemPtr->saleprice;
                printf("%s %d %d\n", itemName, current->itemPtr->qty, *totalCash);
                return;
            }
        }
        // Move to the next
        current = current->next;
    }
}

void changePrice(hashTable* hTable, char* itemName, int newPrice) {
    int pos = hashfunction(itemName, hTable->size);

    chainNode* current = hTable->lists[pos];

    while (current != NULL) {
        // Add 1 because a search was done
        time_complexity++;
        if (strcmp(current->itemPtr->name, itemName) == 0) {
            // if the item is found in our table we will update the price to 
            current->itemPtr->saleprice = newPrice;
            return;
        }
        current = current->next;
    }
}

int main() {
    int num_of_commands;
    int quantity;
    int total_price;
    int total_cash = 100000;
    int new_price;
    char item[MAXSTLEN + 1];
    char command_choice[MAXSTLEN + 1];
    hashTable hTable;

    // Get the number of commands that will we used
    scanf("%d", &num_of_commands);

    // Initialize
    initTable(&hTable, TABLESIZE);

    // Goes through the number of commands variable we just recieved
    for (int i = 0; i < num_of_commands; i++) {
        // Gets the command that the user is choosing
        scanf("%s", command_choice);

        // All the command choices and there corresponding functions
        if (strcmp("buy", command_choice) == 0) {
            scanf("%s %d %d", item, &quantity, &total_price);
            buyItem(&hTable, item, quantity, total_price, &total_cash);

        } else if (strcmp("sell", command_choice) == 0) {
            scanf("%s %d", item, &quantity);
            sellItem(&hTable, item, quantity, &total_cash);

        } else if (strcmp("change_price", command_choice) == 0) {
            scanf("%s %d", item, &new_price);
            changePrice(&hTable, item, new_price);
        }
    }

    // Print the final amount and time complexity at the end
    printf("%d\n", total_cash);
    printf("%d\n", time_complexity);

    // Freeing memory
    for (int i = 0; i < hTable.size; i++) {
        chainNode* current = hTable.lists[i];
        while (current != NULL) {
            chainNode* temp = current;
            current = current->next;
            free(temp->itemPtr);
            free(temp);
        }
    }
    free(hTable.lists);

    return 0;
}
