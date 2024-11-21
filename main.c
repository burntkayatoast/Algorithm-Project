/*
program description:
    task 1: sorting line logs according to date and time, month first then day, hour and minute
    task 2: sorting according to issue codes and then line code
    task 3: searching for an issue code and when it first occurs
    task 4: finds the number of issues in issue code
author: renée low
date: 27/03/24
*/

#include <stdio.h>
#include <string.h>

#define SIZE 100
#define ENTRIES 10

// Data structures
struct batchDate {
    int day;
    int month;
    int hour;
    int minute;
};

struct LogProduct {
    int lineCode;
    int batchCode;
    struct batchDate date;
};

struct LogIDs {
    int prodID;
    int issueCode;
    char IssueDesc[SIZE];
    int resCode;
    char resDesc[SIZE];
    int employeeID;
};

struct LogFinal {
    struct LogProduct product;
    struct LogIDs IDs;
};

// Function signatures
// ctrl + f "MERGE SORT"
void mergeSort(struct LogFinal[], int, int);
void merging(struct LogFinal[], int, int, int);

// ctrl + f "LINE CODE MERGE SORT"
void lineMerging(struct LogFinal[], int, int, int);
void lineSort(struct LogFinal[], int, int);

// ctrl + f "ISSUE CODE MERGE SORT"
void issueMerging(struct LogFinal[], int, int, int);
void issueSort(struct LogFinal[], int, int);

// ctrl + f "SEARCH"
void search(struct LogFinal[]);
// ctrl + f "ISSUE REPORT"
void issueReport(struct LogFinal[]);



int main() {
    int i = 0;

    struct LogFinal entry[ENTRIES] = {
        // LogProduct 01 + LogIDs 01
        {{1, 1000, {1, 1, 6, 35}}, {777, 0, "No issue here", 1800, "description here", 401}},
        // LogProduct 02 + LogIDs 02
        {{1, 2000, {2, 3, 24, 13}}, {888, 77000, "faulty component", 1900, "description here", 402}},
        // LogProduct 03 + LogIDs 03
        {{1, 3000, {6, 1, 10, 60}}, {999, 55000, "poor build", 2000, "description here", 403}},
        // LogProduct 04 + LogIDs 04
        {{2, 4000, {18, 4, 5, 56}}, {111, 55000, "poor build", 2100, "description here", 101}},
        // LogProduct 05 + LogIDs 05
        {{2, 5000, {20, 11, 17, 10}}, {222, 77000, "faulty component", 2200, "description here", 102}},
        // LogProduct 06 + LogIDs 06
        {{2, 6000, {5, 7, 5, 46}}, {333, 55000, "poor build", 2300, "description here", 103}},
        // LogProduct 07 + LogIDs 07
        {{3, 7000, {30, 4, 13, 29}}, {444, 88000, "cracked", 2400, "description here", 301}},
        // LogProduct 08 + LogIDs 08
        {{3, 8000, {28, 10, 20, 14}}, {555, 55000, "poor build", 2500, "description here", 302}},
        // LogProduct 09 + LogIDs 09
        {{4, 9000, {12, 3, 12, 51}}, {666, 77000, "faulty component", 2600, "description here", 201}},
        // LogProduct 10 + LogIDs 10
        {{4, 10000, {20, 6, 2, 9}}, {101, 99000, "loose", 2700, "description here", 202}},
    };

    printf("PRINTING BEFORE SORT");
    printf("\nLine Code:\tBatch Code:\tDate: day/month hour:minute\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%d\t\t%d/%d %d:%d\n", entry[i].product.lineCode, entry[i].product.batchCode, entry[i].product.date.day, entry[i].product.date.month, entry[i].product.date.hour, entry[i].product.date.minute);
    }

    printf("Product ID:\tIssue Code:\tIssue Desc:\t\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%d\t\t%s\n", entry[i].IDs.prodID, entry[i].IDs.issueCode, entry[i].IDs.IssueDesc);
    }

    printf("Res Code:\tRes Desc:\t\tEmployee ID:\t\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%s\t%d\n", entry[i].IDs.resCode, entry[i].IDs.resDesc, entry[i].IDs.employeeID);
    }

    // Calls function to merge
    mergeSort(entry, 0, ENTRIES -1); // -1 adjusts the last index to exclude the zero-index at the end of the array

    // TASK 1 -- SORTING BASED ON DAY/MONTH AND HOUR/MINUTE
    printf("\nTASK 01 -- LOG LINE ENTRIES SORTED BY DATE");
    printf("\nLine Code:\tBatch Code:\tDate: day/month hour:minute\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%d\t\t%d/%d %d:%d\n", entry[i].product.lineCode, entry[i].product.batchCode, entry[i].product.date.day, entry[i].product.date.month, entry[i].product.date.hour, entry[i].product.date.minute);
    }

    printf("Product ID:\tIssue Code:\tIssue Desc:\t\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%d\t\t%s\n", entry[i].IDs.prodID, entry[i].IDs.issueCode, entry[i].IDs.IssueDesc);
    }

    printf("Res Code:\tRes Desc:\t\tEmployee ID:\t\n");
    for (i = 0; i < ENTRIES; i++) {
        printf("%d\t\t%s\t%d\n", entry[i].IDs.resCode, entry[i].IDs.resDesc, entry[i].IDs.employeeID);
    }

    // TASK 2 -- SORTING ACCORDING TO ISSUE CODE
    issueSort(entry, 0, ENTRIES - 1);

    printf("\nTASK 02 -- REPORT SORTED BASED ON ISSUE CODE");
    printf("\nLine Code:\tProduct ID:\tIssue Code:");
    for (i = 0; i<ENTRIES; i++) {
        printf("\n%d\t\t%d\t\t%d", entry[i].product.lineCode, entry[i].IDs.prodID, entry[i].IDs.issueCode);
    }

    // TASK 2 -- SORTING ACCORDING TO LINECODE
    lineSort(entry, 0, ENTRIES - 1);

    printf("\n\nTASK 02 -- REPORT SORTED BASED ON LINE CODE");
    printf("\nLine Code:\tProduct ID:\tIssue Code:");
    for (i = 0; i<ENTRIES; i++) {
        printf("\n%d\t\t%d\t\t%d", entry[i].product.lineCode, entry[i].IDs.prodID, entry[i].IDs.issueCode);
    }

    // TASK 3 -- SEARCHING FOR EARLIEST OCCURENCE OF ISSUE CODE
    search(entry);

    // TASK 4 -- ISSUE SUMMARY
    printf("\n\nTASK 04 -- ISSUE REPORT");
    issueReport(entry);

    return 0;
}


/* -------FUNCTIONS FOR TASK 1-------*/

// Merge sort functions
// subarray = smaller portions of original array. Merge sort divides arrays into until each sub array contains one element. Then they're merged
// part1 = starting index of the subarray
// part2 = end index of first subarray and start of the second one. 
// part3 = end index of second subarray
void merging(struct LogFinal sorting[], int part1, int part2, int part3) {
    int i, j, k;
    int subArr1 = part2 - part1 + 1; 
    int subArr2 = part3 - part2;
    // subArr1 = finds size of 1st subarray. equation finds the no. of elements from part1 to part2. +1 makes sure the array size includes the end element of part1
    // subArr2 = finds size of 2nd subarray. equation finds the no. of elements between the right index and middle index.

    // temp array to make it easier to merge. Splits original  array into two 
    struct LogFinal left[subArr1], right[subArr2];

    // copies elements from original array to temporary arrays
    for (i = 0; i < subArr1; i++) {
        left[i] = sorting[part1 + i];
    } // "i" iterates through the elements in the first subarray. "part1 + i" finds the position of the element of the original array so it can be copied into the temporary array
    for (j = 0; j < subArr2; j++) {
        right[j] = sorting[part2 + 1 + j];
    } // "+1" moves index to the right bc we want to copy elements from next index after the middle element.

    // merging temp arrays back into one
    i = 0, j = 0;
    k = part1; //starts at 0 , from the beginning of the array

    // sorts according to month first, then day, hour and minute
        while (i < subArr1 && j < subArr2) {
        if (left[i].product.date.month < right[j].product.date.month ||
            (left[i].product.date.month == right[j].product.date.month && left[i].product.date.day < right[j].product.date.day) ||
            (left[i].product.date.month == right[j].product.date.month && left[i].product.date.day == right[j].product.date.day && left[i].product.date.hour < right[j].product.date.hour) ||
            (left[i].product.date.month == right[j].product.date.month && left[i].product.date.day == right[j].product.date.day && left[i].product.date.hour == right[j].product.date.hour && left[i].product.date.minute < right[j].product.date.minute)) {
            sorting[k] = left[i];
            i++;
        } else {
            sorting[k] = right[j];
            j++;
        }
        k++;
    }

    // copies rest of the elements of the subbarrays that has remaining elements.
    while (i < subArr1) {
        sorting[k] = left[i];
        i++;
        k++;
    }
    while (j < subArr2) {
        sorting[k] = right[j];
        j++;
        k++;
    } // makes sure the elements are placed in the right position after they have been sorted
}
// this function divides array into smaller arrays and recursively sorts them then merges them together
void mergeSort(struct LogFinal sorting[], int part1, int part3) {
    if (part3 > part1) {
        int part2 = part1 + (part3 - part1) / 2;

        // sorts first half (left)
        mergeSort(sorting, part1, part2);
        // sort second half (middle index and right)
        mergeSort(sorting, part2 + 1, part3);

        // merging the two sorted halves
        merging(sorting, part1, part2, part3);
    }
}


/* ------- FUNCTIONS FOR TASK 2 -------*/
// exact same merge code for task 1 but sorts according line code or issue code

// LINE CODE MERGE SORT
void lineMerging(struct LogFinal sorting[], int part1, int part2, int part3) {
    int i, j, k;
    int subArr1 = part2 - part1 + 1;
    int subArr2 = part3 - part2;

    // temp array to make it easier to merge
    struct LogFinal left[subArr1], right[subArr2];

    // copies elements from original array to temporary arrays
    for (i = 0; i < subArr1; i++) {
        left[i] = sorting[part1 + i];
    }
    for (j = 0; j < subArr2; j++) {
        right[j] = sorting[part2 + 1 + j];
    }


    i = 0, j = 0;
    k = part1;

    // sorts line logs according to the line Code and merges temp arrays back into one
    while (i < subArr1 && j < subArr2) {
        if (left[i].product.lineCode < right[j].product.lineCode) { 
            sorting[k] = left[i];
            i++;
        } else {
            sorting[k] = right[j];
            j++;
        }
        k++;
    }

    // copies the rest of the elements of left[] and right[]
    while (i < subArr1) {
        sorting[k] = left[i];
        i++;
        k++;
    }
    while (j < subArr2) {
        sorting[k] = right[j];
        j++;
        k++;
    }
}
void lineSort(struct LogFinal sorting[], int part1, int part3) {
    if (part3 > part1) {
        int part2 = part1 + (part3 - part1) / 2;

        // sorts first half (left)
        lineSort(sorting, part1, part2);
        // sort second half (middle index and right)
        lineSort(sorting, part2 + 1, part3);

        // merging the two sorted halves
        lineMerging(sorting, part1, part2, part3);
    }
}
// ISSUE CODE MERGE SORT
void issueMerging(struct LogFinal sorting[], int part1, int part2, int part3) {
    int i, j, k;
    int subArr1 = part2 - part1 + 1;
    int subArr2 = part3 - part2;

    // temp array to make it easier to merge
    struct LogFinal left[subArr1], right[subArr2];

    // copies elements from original array to temporary arrays
    for (i = 0; i < subArr1; i++) {
        left[i] = sorting[part1 + i];
    }
    for (j = 0; j < subArr2; j++) {
        right[j] = sorting[part2 + 1 + j];
    }

    // merging temp arrays back into one
    i = 0, j = 0;
    k = part1; 

    // sorts the line logs according to issue code
    while (i < subArr1 && j < subArr2) {
        if (left[i].IDs.issueCode < right[j].IDs.issueCode) {
            sorting[k] = left[i];
            i++;
        } else {
            sorting[k] = right[j];
            j++;
        }
        k++;
    } 

    // copying rest of elements of left[] and right[]
    while (i < subArr1) {
        sorting[k] = left[i];
        i++;
        k++;
    }
    while (j < subArr2) {
        sorting[k] = right[j];
        j++;
        k++;
    }
}
void issueSort(struct LogFinal sorting[], int part1, int part3) {
    if (part3 > part1) {
        int part2 = part1 + (part3 - part1) / 2;

        // sorts first half (left)
        issueSort(sorting, part1, part2);
        // sort second half (middle index and right)
        issueSort(sorting, part2 + 1, part3);

        // merging the two sorted halves
        issueMerging(sorting, part1, part2, part3);
    }
}


/* ------- FUNCTIONS FOR TASK 3 -------*/
// SEARCH
void search(struct LogFinal entry[]) {
    int searchCode;
    int i = 0;
    int found = 0;


    printf("\n\nTASK 03 -- ISSUE CODE SEARCH");
    printf("\nEnter Issue Code: ");
    scanf("%d", &searchCode); // lets user to enter in an issue code

    // this compares the issue codes to the user's input and sees if they're the same
    for (i = 0; i<ENTRIES; i++) {
        if  (entry[i].IDs.issueCode == searchCode) {
            found = 1;
            break; // breaks out of the loop once it finds the first match
        } 
    }

    if (found == 1) {
        printf("The first occurence of Issue code %d. Line Code %d, Product ID %d", entry[i].IDs.issueCode, entry[i].product.lineCode, entry[i].IDs.prodID);
    } else {
        printf("Issue code not found");
    }

}


/*------FUNCTIONS FOR TASK 4-------*/
// ISSUE REPORT
void issueReport(struct  LogFinal entry[]) {
    int i;
    int issueCount = 0;

    // if the issue code isn't 0, the number of issues will be 1
    printf("\nProduct ID:\tNo. of Issues:");
    for (i = 0; i<ENTRIES; i++) {
        if (entry[i].IDs.issueCode != 0) {
            issueCount = 1;
        } else {
            issueCount = 0;
        }
        printf("\n%d\t\t%d", entry[i].IDs.prodID, issueCount);
    }
}



