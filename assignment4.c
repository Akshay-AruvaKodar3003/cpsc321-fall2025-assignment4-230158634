/* 
Akshay Arulkrishnan
230158634
CPSC 321 - Assignment 4
15-11-2025
*/

#include <stdio.h>

#define NUMBER_OF_CUSTOMERS 5      
#define NUMBER_OF_RESOURCES 4      

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// matrix
void compute_need(int n, int m) {
    for (int i = 0; i < n; i++) {           // each customer
        for (int j = 0; j < m; j++) {       // each resource
            need[i][j] = maximum[i][j] - allocation[i][j];  
        }
    }
}

// safety algorithm
int is_safe(int n, int m, int safeSeq[]) {
    int work[NUMBER_OF_RESOURCES];      // temp avail
    int finish[NUMBER_OF_CUSTOMERS];    // done flag

    for (int j = 0; j < m; j++) work[j] = available[j]; 
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int ok = 1;   

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        ok = 0;
                        break;
                    }
                }

                if (ok) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];   // give back

                    safeSeq[count++] = i;    // add seq
                    finish[i] = 1;           // mark done
                    found = 1;
                    break;
                }
            }
        }

        if (!found) return 0;     // unsafe
    }

    return 1;   // safe
}

int main() {
    printf("Banker's Algorithm\n");

     int n, m;   // sizes

    //input
    printf("Enter number of customers (processes): ");
    scanf("%d", &n);    // read customers

    printf("Enter number of resources: ");
    scanf("%d", &m);   // read resources

    //total instances
    int totalInstances[NUMBER_OF_RESOURCES];   // total res
    printf("Enter number of instances of each resource type (%d values): ", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &totalInstances[j]);   // read totals
    }

    // available
    printf("Enter available resources (%d values): ", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);    // read available
    }

    // maximum matrix
    printf("Enter maximum demand matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);   // read max
        }
    }

    // allocation matrix
    printf("Enter current allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);  // read allocation
        }
    }

    // matrix
    compute_need(n, m); 

    // request
    int customerID;   // req customer
    int request[NUMBER_OF_RESOURCES];   // req vector

    printf("Enter Resource Request: ");
    scanf("%d", &customerID); 
    for (int j = 0; j < m; j++) {
        scanf("%d", &request[j]);    // read req
    }

    return 0;
}
