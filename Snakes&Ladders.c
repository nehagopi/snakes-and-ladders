/*CSEC 201.600 Fall 2021
  Homework - 3
  Group: Neha Gopinathan, Alia Albannai, Mahrukh, Hadi*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Function that gets the User input for the dice and returns the value to the main function*/
int usercall(){
	int n;
	printf("\nEnter dice number between 1-6: ");
	scanf("%d", &n);
	printf("Dice number: %d\n", n);
	printf("\n-------------------------------------------\n");
	return n;
}

int main(){
	int *ptr; 
	int p[100]; // Board Number
	int n; // dice number
	int a; //Location
	int j; //Score

	ptr = p;
	a = 0;
	j=0;

	srand(time(0));
   
   /*loop that initializes all elements of the board to 0*/
	for(int i=0; i<100; i++){ 
		p[i] = 0;
	}

   /*Sets random loacations for ladders*/
	for(int i=0;i<5;i++){ 
		int x = (rand() % 10);
		p[x] = 1;
	}
	
   /*Sets random locations for snakes*/
	for(int i=0;i<5;i++){ 
		int x = (rand() % 10);
		p[x] = 2;
	}

	p[0]=0;
	p[99]=0;			

	/*While loop that continues until player reaches final spot*/
	while(*ptr>=0 && *ptr<=99){
		j++;
		if(*ptr!=1 && *ptr!=2){
			n = usercall();
			while(n>6 || n<0){
				printf("\nEnter a valid number!");
				n = usercall();
			}
			a = a + n;
			if(ptr<&p[99])
				for(int i=0; i<n; i++)
					ptr++;
		}
		 //If value of the pointer lands on a ladder.
		if(*ptr == 1){
			int x = (rand() % 90) + 5; 
			a = a+x;
			for(int i=0;(i<x && i<100); i++){ 
				if(ptr >= &p[99]){ //if ladder lands exactly or exceeds the address of the last element, then the player wins.
					printf("\nYou have reached a ladder! Climb up %d steps.\nWe are at location: %d", x, a);
					printf("\nYou have won the game! Your score is: %d\n",j);
					exit(0);
				}
				ptr++;
			}
			printf("\nYou have reached a ladder! Climb up %d steps.\nWe are at location: %d\n", x, a);
			printf("\n");
		}
		//If value of the pointer lands on a snake
		else if (*ptr == 2){ 
			int x = (rand() % 90) + 5; 
			if(x>=a) 
				a = 0;
			else
				a =a-x;
			for(int i=(x-1); (i>=0 && ptr>=&p[0]); i--){
				ptr--;
				if(ptr>&p[99] || ptr<&p[0]){ //If the pointer goes beyond the limits of the array, the value is set back to the address of the first element
					ptr=&p[0];
					break;
				}
			}
			printf("\nOh no, you reached a snake! Slide down %d steps.\nWe are at location: %d\n", x, a);
			printf("\n");
		}
		//If value of pointer exceeds the last element.
		else if(ptr>=&p[99]){
			printf("\nYou have won the game! Your score is: %d\n", j);
			exit(0);
		}
		else{
			printf("\nWe are at location: %d", a);
			continue;
		}
	}
	return 0;
}
