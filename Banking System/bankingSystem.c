#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int intro(float balance[], int info[]);
int login(int info[]);
int menu();
int account();
void check(float balance[]);
void withdraw(float balance[]);
void deposit(float balance[]);
void transfer(float balance[]);
bool keep();
 
int main (){
	
	int a;
	int transaction;
	int info[] = {0, 0, 0};
	//[Account #][Pin #][Generations]
	float balance[] = {0, 0};
	//[Checking][Savings]
	
	srand (time(NULL));
	
	do{
		
		a = intro(balance, info);
		
		while(a){
			
			transaction = menu();
			
			switch(transaction){
				case 1:
					check(balance);
					break;
				case 2:
					withdraw(balance);
					break;
				case 3:
					deposit(balance);
					break;
				case 4:
					transfer(balance);
					break;
				case 5:
					//Cancel
					break;
				default:
					printf("Invalid option.\n");
			}

			a = keep();
		}
	}while(a != 3);
}

int intro(float balance[], int info[]){
	int a;
	int b;
	int c = 1;
	while(c){
		printf("-------------------------------------------\n");
		printf("1 - Login | 2 - Re/Generate | 3 - Terminate\n");
		printf("Your choice: ");
		scanf("%d", &a);	
		switch(a){
			case 1:
				if(info[2] == 0){
					printf("-------------------------------------------\n");
					printf("Please generate account information first.\n");
				} else {
					b = login(info);
					c = 0;
				}
				break;
			case 2:
				info[0] = rand() % 99999 + 10000;
				info[1] = rand() % 9999 + 1000;
				balance[0] = (rand() % 4999 + 1000) ;
				balance[1] = (rand() % 9999 + 5000) ;
				printf("-------------------------------------------\n");
				printf("Account#: %d\n", info[0]);
				printf("Pin    #: %d\n", info[1]);
				printf("You may now login or re-generate.\n");
				info[2]++;
				break;
			case 3:
				printf("-------------------------------------------\n");
				printf("Terminated.\n");
				printf("-------------------------------------------\n");
				exit(0);
				break;
			default:
				printf("Invalid Option.\n");
				break;
		}
	}
	return b;
}

int login(int info[]){
	int a;
	int b;
	int c = 0;
	int d = 1;
	printf("-------------------------------------------\n");
	printf("ATM MACHINE\n");
	do{
		printf("Enter account #: ");
		scanf("%d", &a);
		if(a != info[0]){
			printf("Invalid account number.\n");
		}
	}while(a != info[0]);
	do{
		printf("Enter pin     #: ");
		scanf("%d", &b);
		if(b != info[1]){
			c++;
			printf("Invalid pin number.\n");
			printf("Remaining attempts: %d\n", (3 - c));
		}
		if(c == 3){
			printf("-------------------------------------------\n");
			printf("Account #: %d - Locked.\n", info[0]);
			//Changes pin to dsibale login.
			info[1] = rand() % 9999 + 1000;
			//d = 0;
			return 0;
		}
	}while(b != info[1]);
	return d;
}

int menu(){
	int a;
	printf("-------------------------------------------\n");
	printf("What would you like to do?\n");
	printf("1 - Query\n");
    printf("2 - Withdraw\n");
    printf("3 - Deposit\n");
    printf("4 - Transfer\n");
	printf("5 - Cancel\n");
    printf("Your choice: ");
	scanf("%d", &a);
	return a;
}

int account(){
	int a;
	printf("-------------------------------------------\n");
	printf("Select which account:\n");
	printf("1 - Checking | 2 - Savings\n");
	printf("Your choice: ");
	scanf("%d", &a);
	--a;
	return a;
}

void check(float balance[]){
	int a;
	a = account();
	printf("Balance: $%.2f\n", balance[a]);
}

void withdraw(float balance[]){
	int a;
	float b;
	a = account();
	printf("Enter amount to be withdrawn: $");
	scanf("%f", &b);
	if(b <= balance[a]){
		balance[a] = balance[a] - b;
		printf("Updated balance: $%.2f\n", balance[a]);
	} else {
		printf("Sorry, you do not have sufficient funds.\n");
	}
}

void deposit(float balance[]){
	int a;
	float b;
	a = account();
	printf("Enter amount to be deposited: $");
	scanf("%f", &b);
	balance[a] = balance[a] + b;
	printf("Updated balance: $%.2f\n", balance[a]);
}

void transfer(float balance[]){
	int a;
	float b;
	printf("-------------------------------------------\n");
	printf("What would you like to do?\n");
	printf("1 - Checking --> Savings\n");
	printf("2 - Checking <-- Savings\n");
	printf("Your choice: ");
	scanf("%d", &a);
	--a;
	printf("Enter amount to be transferred: $");
	scanf("%f", &b);
	if(b <= balance[a]){
		if(a == 0){
			balance[a] = balance[a] - b;
			++a;
			balance[a] = balance[a] + b;
		} else if (a == 1){
			balance[a] = balance[a] - b;
			--a;
			balance[a] = balance[a] + b;
		}
	} else {
		printf("Sorry, you do not have sufficient funds.\n");
	}
	printf("Updated checking balance: $%.2f\n", balance[0]);
	printf("Updated savings balance: $%.2f\n", balance[1]);
}

bool keep(){
	int x;
	printf("-------------------------------------------\n");
	printf("Do you wish to choose another option?\n");
    printf("1 - Yes | 2 - No\nYour choice: ");
    scanf(" %d", &x);
	if(x == 2){
		x = 0;
	}
	if(x == 0){
		printf("-------------------------------------------\n");
		printf("Logged out.\n");
		}
	return x;
}