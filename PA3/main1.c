/* 
COP 3502C Assignment 3
This program is written by: Ezra Stone
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20 // MAx length of a name
#define MAX_PEOPLE 10 // Max amount of people allowed

// Global variables
int cantSit[MAX_PEOPLE][MAX_PEOPLE]; // 2D array of people who cant sit next to each other
char name[MAX_PEOPLE][MAX_LEN]; // 2D array that gets the names of the people at the movie
int popcorn[MAX_PEOPLE];// Array that determine if the user has popcorn by setting yes=1 and no=0

// Checks if the seating for the customers is conflicting
int seatingConflict(int arr[], int num_of_people) {
    for (int i = 0; i < num_of_people-1; i++) {// Using -1 here because its going to be checking an array, which starts at 0
        if (cantSit[arr[i]][arr[i+1]] == 0) {// Checking if cantSit is equal to 0 because this would mean they can not sit next to each other
            return 1;// Return 1 for conflict
        }      
    }
    return 0;
}

// Checks if the permute is valid
int isValid(int arr[], int num_of_people) {
    // Iterate through all the customers
    for (int i = 0; i < num_of_people; i++) {
        // The if's are checking if the current, next, and prior have popcorn or not.
        // If they do we will return 0;
        if (popcorn[arr[i]] == 1) {
            continue;
        }
        if(i+1 < num_of_people && popcorn[arr[i+1]] == 1 ){
            continue;
        }

        if(i-1 >= 0 && popcorn[arr[i-1]] == 1){
            continue;
        }
        return 0;
    }

    // Calling seating conflict to check if it's valid
    if (seatingConflict(arr, num_of_people)) {
        return 0;
    }

    return 1;
}

// This will print our valid permute
void printPermutArray(int arr[], int n){
    for(int i=0; i<n; i++) // Goes through all names of the permute
        printf("%s\n", name[arr[i]]); // Prints each name
    printf("\n");
}

// Gets the permutations
int mypermute(int arr[], int used[], int k, int n){
    if (k == n){ // Checks if the length has been reached
        if(isValid(arr, n)){ // Checks if its valid and returns 1 if true
            return 1;    
        }
    }

    int result = 0;

    for (int i = 0; i < n; i++){
        if (!used[i]){ // Checks if i was not used
            used[i] = 1; // Marks it as used
            arr[k] = i; // Transfer i to the the perm array at kth position
            result += mypermute(arr, used, k + 1, n);// Result will store the number of valid permutes
            used[i] = 0; // Unmark for the next
        }
    }

    return result; // Returns our total number of valid permutaions
}

int main(){
    int num_of_people; // Total number of people ordering
    int num_of_hates; // Number of pairs that can't sit next to eachother
    int s1;// Seat 1 and 2 which will be used to determine cantSits position
    int s2;
    char notSit1[MAX_LEN]; // Names of people who can not sit next to each other
    char notSit2[MAX_LEN];

    scanf("%d %d", &num_of_people, &num_of_hates);// Scan in the num of customer and pairs of people who can't sit next to each other

    for(int i=0; i<num_of_people; i++){
        scanf("%s %d", name[i], &popcorn[i]);// Scans the information for the customer like name and if they have popcorn or not  
    }

    int array[MAX_PEOPLE] = {0}; // Stores all the permutations
    int used[MAX_PEOPLE] = {0}; // Keeps track of what has been used

    for(int i=0; i<MAX_PEOPLE;i++){
        for(int j=0; j<MAX_PEOPLE; j++){
            cantSit[i][j] = 1; // Initialize every position of cantSit to 1 originally
        }
    }

    for(int i=0; i<num_of_hates; i++){
        scanf("%s %s", notSit1, notSit2); // Scans the names of the people who can't sit next to each other
        for(int j=0; j<num_of_people; j++){
            if(strcmp(name[j], notSit1) == 0){// Compares the current name to the first name who can't sit next to someone
                s1 = j; // Saves that position in s1
            }
            if(strcmp(name[j], notSit2) == 0){
                s2 = j;
            }
        }
        cantSit[s1][s2] = 0; // Sets cantSit to 0 using the positions gotten above
        cantSit[s2][s1] = 0;
    }

    printf("%d", mypermute(array, used, 0, num_of_people));// Prints permute return value

    return 0;
}
