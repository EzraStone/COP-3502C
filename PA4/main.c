/* 
COP 3502C Assignment 4
This program is written by: Ezra Stone
*/

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#define EPSILON 0.0001 // Threshhold that will be used to check if two doubles are equal

typedef struct group {
    int groupSize;
    double radians;
    int groupNumber;
} group;

typedef struct result {
    int firstGroup;
    int secondGroup;
    double degrees;
} result;

double doubleCompare(double d1, double d2) {
    if (fabs(d1 - d2) < EPSILON) {// Gets the absolute value of the difference between double 1 and 2, then checks if it's less than the epsilon
        return 1;
    } else {
        return 0;
    }
}

int compareTo(result *ptrPtr1, result *ptrPtr2) {
    if ((*ptrPtr1).firstGroup < (*ptrPtr2).firstGroup) {// returns negative 1 if the first pointers first group is less than the second pointers
        return -1;
    } 
    else if ((*ptrPtr1).firstGroup > (*ptrPtr2).firstGroup) {// returns 1 if the first pointers first group is less than the second pointers
        return 1;
    } 
    else {
        if ((*ptrPtr1).secondGroup < (*ptrPtr2).secondGroup) {// returs negative 1 if the first pointers second group is less than the second pointers second group
            return -1;
        } 
        else if ((*ptrPtr1).secondGroup > (*ptrPtr2).secondGroup) {// returns 1 if the first pointers second group is grater than the the second pointer
            return 1;
        } 
        else {
            return 0;// Groups are equal
        }
    }
}

void groupMerge(group arr[], int l, int m, int r) {
    int sizeLeft = m - l + 1; //Calculates the size of left by doing mid - left + 1
    int sizeRight = r - m; // Calculates the size of right by doing right - mid

    // Create temporary arrays for left and right subarrays
    group *L = (group *)malloc(sizeLeft * sizeof(group));
    group *R = (group *)malloc(sizeRight * sizeof(group));

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < sizeLeft; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < sizeRight; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0; // Index of left subarray
    int j = 0; // Index of right subarray
    int k = l; // Index of merged subarray

    while (i < sizeLeft && j < sizeRight) {
        if (L[i].radians <= R[j].radians) {
            arr[k] = L[i];
            i += 1;
            k += 1;
        } else {
            arr[k] = R[j];
            j+= 1;
            k += 1;
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < sizeLeft) {
        arr[k] = L[i];
        i += 1;
        k += 1;
    }

    // Copy the remaining elements of R[], if any
    while (j < sizeRight) {
        arr[k] = R[j];
        j += 1;
        k += 1;
    }

    // Free allocated memory
    free(L);
    free(R);
}

/*
l is for left index and r is right index of the
sub-array of arr to be sorted
*/
void groupMergeSort(group arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2; // Calculate mid index to avoid integer overflow
        // Recursive calls 
        groupMergeSort(arr, l, mid);
        groupMergeSort(arr, mid + 1, r);
        groupMerge(arr, l, mid, r);
    }
}

void resultMerge(result arr[], int l, int m, int r) {
    int sizeLeft = m - l + 1;
    int sizeRight = r - m;

    // Create temporary arrays for left and right subarrays
    result *L = (result*)malloc(sizeLeft * sizeof(result));
    result *R = (result*)malloc(sizeRight * sizeof(result));

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < sizeLeft; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < sizeRight; i++) {
        R[i] = arr[m + 1 + i];
    }

    // Merge the temporary arrays back into arr[l..r]
    int i = 0; // Index of left subarray
    int j = 0; // Index of right subarray
    int k = l; // Index of merged subarray

    while (i < sizeLeft && j < sizeRight) {
        if (compareTo(&L[i], &R[j]) <= 0) {// Using compareto to see if groups return a negative or a zero
            arr[k] = L[i];
            i += 1;
            k += 1;
        } else {
            arr[k] = R[j];
            j += 1;
            k += 1;
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < sizeLeft) {
        arr[k] = L[i];
        i += 1;
        k += 1;
    }

    // Copy the remaining elements of R[], if any
    while (j < sizeRight) {
        arr[k] = R[j];
        j += 1;
        k += 1;
    }

    // Free allocated memory
    free(L);
    free(R);
}

void resultMergeSort(result arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2; // Calculate mid index to avoid overflow
        resultMergeSort(arr, l, mid);
        resultMergeSort(arr, mid + 1, r);
        resultMerge(arr, l, mid, r);
    }
}

/*
Function will help calculate the max angle
*/
double maxAngle(group *arr, int numberOfGroups){
    double max = arr[0].radians + 2 * M_PI - arr[numberOfGroups-1].radians;// 2 * pi are added to the first angle in the group then subtracted by the last angle

    // Iterates through all the groups and calculates the high among them
    for(int i=0; i < numberOfGroups-1; i++){
        double high = arr[i+1].radians - arr[i].radians;
        // if one of the highs found is greater than the current max change that high to max
        if(high > max){
            max = high;
        }
    }

    return max * 180 / M_PI; // returns value in degrees
}

int main() {
    int numberOfGroups;
    double projectorAngle;
    int x, y, numOfPeople;
    int resultNum = 0;

    // Scans the number of groups in the theater and the current projector angle
    scanf("%d %lf", &numberOfGroups, &projectorAngle);

    // Allocate the momory for the groups and the results
    group *groups = malloc(numberOfGroups * sizeof(group));
    result *results = malloc(numberOfGroups * sizeof(result));

    // Iterates through number of groups and recieves info necessary for them
    for (int i = 0; i < numberOfGroups; i++) {
        scanf("%d %d %d", &x, &y, &numOfPeople);
        groups[i].groupSize = numOfPeople;
        groups[i].radians = atan2(y, x);// Calculates the angle in radians using x and y
        groups[i].groupNumber = i;
    }

    groupMergeSort(groups, 0, numberOfGroups - 1);// Sorting the groups

    double max = maxAngle(groups, numberOfGroups);// Calculate and stores our max angle

    double gap = groups[0].radians + 2 * M_PI - groups[numberOfGroups-1].radians;// Calculates the gap
    gap *= 180 / M_PI;// Takes the previous gap and multiplies by 180 over pi to convert to degrees

    if(doubleCompare(max, gap)){
        int index1 = groups[0].groupNumber;// First group
        int index2 = groups[numberOfGroups-1].groupNumber;// Last group

        if(index1 > index2){// Swap if first is greater than the last
            int temp = index1;
            index1 = index2;
            index2 = temp;
        }

        // Reassign them to correct place if need be
        results[0].firstGroup = index1;
        results[0].secondGroup = index2;
        resultNum += 1;
    }

    for(int i=0; i < numberOfGroups-1; i++){
        double angle = groups[i+1].radians - groups[i].radians;
        angle *= 180 / M_PI;// Converts the groups radians to degrees

        if(doubleCompare(angle, max)){
            int index1 = groups[i].groupNumber;// First group
            int index2 =  groups[i+1].groupNumber;// Last group

            if(index1 > index2){// Swaps if first is greater than the last
                int temp = index1;
                index1 = index2;
                index2 = temp;
            }

            // Reassign them to correct place if need be
            results[resultNum].firstGroup = index1;
            results[resultNum].secondGroup = index2;
            resultNum += 1;
        }
    }

    resultMergeSort(results, 0, resultNum - 1);// Sort the results
   
    printf("Max projection degree without harming %.4lf\n", max);// Prints the max angle possible
      
    printf("Closest possible group pairs in order:\n");

    // Prints the closest pairs 
    for (int i = 0; i < resultNum; i++) {
        printf("%d %d\n", results[i].firstGroup, results[i].secondGroup);
    }
    
    // Frees memory
    free(groups);
    free(results);
}