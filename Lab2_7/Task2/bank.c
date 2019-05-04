/*
 *  bank.c
 *
 *  Created by AJ Bieszczad on 3/11/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 *  A bank has customers who can borrow money from a number of accounts.
 *  Then, they have to repay the funds.
 *
 */

#include "bank.h"

int numOfCustomers;        // the number of customers of the bank
int numOfAccounts;         // the number of accounts offered by the bank

int*available;    // the amount available of each customer
int**maximum;     // the maximum demand of each customer
int**allocation;  // the amount currently allocated to each customer
int**need;     // the remaining needs of each customer

/*
 Initialize the bank for a number of accounts and customers.
 */
void initBank(int avail[], int n, int m)
{
   // numOfAccounts is the number of accounts offered by the bank
   numOfCustomers = n;
   numOfAccounts = m;

   // initialize the accounts array
   available = calloc( numOfAccounts, sizeof(int) );
   arraycpy(available, avail, numOfAccounts);

   // create the array for storing the maximum demand by  each customer
   maximum = calloc( numOfCustomers, sizeof(int*) );
   allocation = calloc( numOfCustomers, sizeof(int*) );
   need = calloc( numOfCustomers, sizeof(int*) );
}

/*
 This function adds a customer to the bank system.
 It records its maximum fund demand with the bank.
 */
void addBankCustomer(int customerNum, int maxDemand[])
{
   maximum[customerNum] = calloc( numOfAccounts, sizeof(int) );
   arraycpy(maximum[customerNum], maxDemand, numOfAccounts);

   allocation[customerNum] = calloc( numOfAccounts, sizeof(int) );
   // we start with zero allocated

   need[customerNum] = calloc( numOfAccounts, sizeof(int*) );
   arraycpy(need[customerNum], maxDemand, numOfAccounts);
}

/*
 Outputs the state of the bank; i.e., funds in each account of each customer
 */

void displayBankState()
{
   printf("\n%13s", "Available = ");
   display(available, numOfAccounts);

   printf("\n%13s", "Allocation = ");
   for (int i = 0; i < numOfCustomers; i++)
      display(allocation[i], numOfAccounts);

   printf("\n%13s", "Max = ");
   for (int i = 0; i < numOfCustomers; i++)
      display(maximum[i], numOfAccounts);

   printf("\n%13s", "Need = ");
   for (int i = 0; i < numOfCustomers; i++)
      display(need[i], numOfAccounts);

   printf("\n");
}

/**
 Determines whether granting a request for loan results in leaving
 the system in a safe state or not.
 */
BOOLEAN isSafeState (int customerNum, int request[])
{
   if (lessOrSame(request, need[customerNum], numOfAccounts)) {
      if (lessOrSame(request, available, numOfAccounts)) {
         sub(available, request, numOfAccounts);

         for (int i = 0; i < numOfCustomers; ++i) {
            if (lessOrSame(need[i], available, numOfAccounts) && !allTrue(need[i], numOfAccounts)) {
               set(TRUE, need[i], numOfAccounts);
               i = 0;
            }
         }

         for (int i = 0; i < numOfCustomers; ++i) {
            if (!allTrue(need[i], numOfAccounts)) {
               return FALSE;
            }
         }

         return TRUE;
      }
      else {
         return FALSE;
      }
   }
   else {
      return FALSE;
   }
}

/*
 Make a request for a loan.
 */

BOOLEAN borrow(int customerNum, int funds[])
{
   BOOLEAN ret = isSafeState(customerNum, funds);

   if (ret == TRUE)
   {
      // if it is safe, allocate the funds to customer customerNum
      sub(available, funds, numOfAccounts);
      add(allocation[customerNum], funds, numOfAccounts);
      sub2(need[customerNum], maximum[customerNum], allocation[customerNum], numOfAccounts);
   }

   return ret;
}

/*
 Repay a loan.
 */
BOOLEAN repay(int customerNum, int funds[])
{
   BOOLEAN ret = lessOrSame(funds, allocation[customerNum], numOfAccounts);
   if (ret == TRUE)
   {
      add(available, funds, numOfAccounts);
      sub(allocation[customerNum], funds, numOfAccounts);
      sub2(need[customerNum], maximum[customerNum], allocation[customerNum], numOfAccounts);
   }
   
   return ret;
}