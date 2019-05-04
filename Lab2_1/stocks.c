#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUMBER_OF_TURNS 30
#define BUY_OPTION 1
#define SELL_OPTION 2
#define END_TURN_OPTION 3
#define STARTING_MONEY 15.00
char **names;
float *prices;
int *inventory;
int number_of_listings;
float cash = STARTING_MONEY;
int turn;

int input(char *file_name);

void display_market();

void display_inventory();

void display_game_state();

void end_turn();

void sell();

void buy();

void menu();

void free_arrays();

int input(char *file_name)
{
	FILE *file_pointer = fopen(file_name, "r");

	if (file_pointer) {
		fscanf(file_pointer, "%d", &number_of_listings);
		names = malloc(sizeof(char *) * number_of_listings);
		prices = malloc(sizeof(float) * number_of_listings);
		inventory = malloc(sizeof(int) * number_of_listings);
		
		int listing;
		char temp[100];
		for(listing=0; listing < number_of_listings; listing++) {
			inventory[listing] = 0;
			fscanf(file_pointer, "%s %f", temp, &prices[listing]);
			names[listing] = malloc(sizeof(char) * strlen(temp) + 1); // we add 1 for the terminating character
			strcpy(names[listing], temp);
		}
		
		fclose(file_pointer);
		return 1; // we return one because the file existed and we accessed it
	}
	
	return 0;// we return zero becuase the file did not exist so we return false
}
void display_game_state()
{
	printf("TURN #%d",turn);
	printf("\n~~~~~~~~~~~~~~~~~The Market~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-11s\n","Stock Name","Stock Price" );
	display_market();
	printf("\n~~~~~~~~~~~~~~~~~Inventory~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-15s %-11s\n","Stock Name","Stock Quantity", "Stock Value" );
	display_inventory();
	printf("Your available cash: %-11.2f\n",cash);
}

void display_market()
{
	int i;
	for (i = 1; i <= number_of_listings; i++) {
		printf("%d. %-30s $%-11.2f\n", i, names[i-1], prices[i-1]);
	}
}

void display_inventory()
{
	int i;
	for (i = 1; i <= number_of_listings; i++) {
		printf("%d. %-30s %-15d $%-11.2f\n", i, names[i-1], inventory[i-1], prices[i-1] * inventory[i-1]);
	}
}

void menu()
{
	int choice = 0;
	do {
		printf("\nOptions:\n");
		printf("1) Buy Stock\n");
		printf("2) Sell Stock\n");
		printf("3) End Turn\n");
		printf("Enter your choice: ");
		
		scanf("%d", &choice);
		switch(choice) {
			case BUY_OPTION:
				buy();
				break;
			case SELL_OPTION:
				sell();
				break;
			case END_TURN_OPTION:
				end_turn();
				break;
			default:
				printf("Invalid Selection");
				break;
		}
	} while (choice != END_TURN_OPTION);
	
		// Continue showing this menu until the end turn option is selected. (Hint use do-while loop)
		// Use a switch statement to call the appropriate method from the user's selection.
}

void buy()
{
	printf("\n~~~~~~~~~~~~~~~~~Buy Options~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-11s\n","Stock Name","Stock Price" );
	display_market();
	printf("Your available cash: %-11.2f\n",cash);
	printf("Enter the number of the stock you would like to invest in: ");
	
	int selection;
	scanf("%d", &selection);
	selection--;
	if (selection >= 0 && selection < number_of_listings)
		{
			if (prices[selection] <= cash)
			{
				int quantity;
				printf("Enter the amount of stock you wish to buy: ");
				scanf("%d", &quantity);
				if (quantity > 0)
				{
					if ((prices[selection] * quantity) < cash)
					{
						inventory[selection] = quantity;
						cash -= prices[selection] * quantity;
						printf("Your available cash after the transaction: %-11.2f\n",cash);
					}
					else
					{
						printf("You do not have enough money to purchase that quantity\n");
					}
				}
				else
				{
					printf("The quantity must be positive.\n");
				}
			}
			else
			{
				printf("Not enough cash to purchase any of that stock.\n");
			}
		}
		else
		{
			printf("Invalid selection.\n");
		}
}

void sell()
{
	printf("\n~~~~~~~~~~~~~~~~~Sell Options~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-15s %-11s\n","Stock Name","Stock Quantity", "Stock Value" );
	display_inventory();
	printf("Enter the number of the stock you would like to sell from: ");

	int selection;
	scanf("%d", &selection);
	selection--;
	if (selection >= 0 && selection < number_of_listings)
	{
		if (inventory[selection] > 0)
		{
			int quantity;
			printf("Enter the quantity of stock you wish to sell: ");
			scanf("%d", &quantity);
			if (quantity <= inventory[selection])
			{
				cash += prices[selection] * quantity;
				inventory[selection] -= quantity;
				printf("Your available cash after the transaction: %-11.2f\n",cash);
			}
			else
			{
				printf("You do not have that much of this stock.\n");
			}
		}
		else
		{
			printf("You do not own any of this stock.\n");
		}
	}
	else
	{
		printf("Invalid selection\n");
	}

}

void end_turn()
{
	printf("Turn ended\n");
	printf("Market prices will change\n");
	
	int listing;
	for (listing = 0; listing < number_of_listings; listing++) {
		prices[listing] *= ((rand() % 50) + 75.00) / 100.00;
	}
	
	turn++;
}
void free_arrays()
{
	free(prices);
	free(inventory);
	int listing;
	for (listing = 0; listing < number_of_listings; listing++) {
		free(names[listing]);
	}
	free(names);
}

int main()
{	
	// Completed for you
	srand(time(NULL));
	if (! input("input.txt"))
	{
		printf("Error reading in the input");
		return -1;
	}
	turn = 0;
	while( turn != NUMBER_OF_TURNS)
	{
		display_game_state();
		menu();
	}
	display_game_state();
	free_arrays();
	return 0;
}
