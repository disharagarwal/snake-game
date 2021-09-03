#include<stdio.h> //In  order to get input and output
#include<conio.h> //In order to use kbhit and getch function
#include<stdlib.h> //In order to use rand function

int width=20,height=20; //global variables for defining the boundary of the game
int snakeX,snakeY; //x and y co-ordinates of the snake
int score,flag; //global variables, flag is used to control the movements of the snake and score stores the points of the user
int fruitx,fruity; //x and y co-ordinates of the fruit
int gameEnd; //global variable, gameEnd is used to end the game
int tailx[100],taily[100]; //To increase the size of the snake as the game progresses
int piece=0; //Used to increase the size of the snake based on the number of fruits eaten 
char name[30];


void draw() //Function to create the boundary of the game and to print the snake and fruit
{
	system("cls"); //clears the screen
	int i,j,k,ch;
	for(i=0;i<=height;i++) //Loop to add a new line after printing '#'
	{
		for(j=0;j<=width;j++) //Loop to print the boundary using '#'
		{
			if(i==0||i==height|| j==0|| j==width) //Condition to draw the required boundary(box type) 
			{
				printf("#");
			}
			else 
			{
				if(i==snakeX && j==snakeY) // To print the snake 
				{
					printf("*");
				}
				else if(i==fruitx && j==fruity) // To print the fruit
				{	
					printf("@");
				}
				else
				{
					ch=0;
					for(k=0;k<piece;k++)
					{
						if(i==tailx[k] && j==taily[k])
							{
								printf("*");
								ch=1;
							}
					}
					if(ch==0)
					printf(" "); // To print space otherwise
				}
			}
		}
		printf("\n"); // To move to next line
	}
	 printf("%s your score is : %d\n",name,score);	 //To display score
}







void setup() //Function to control the size and position of the snake and position of the fruit
{
	gameEnd=0; //s long as it is zero the game runs
	snakeX=width/2; //To make sure the snake is in the middle of the boundary
	snakeY=height/2; //To make sure the snake is in the middle of the boundary
	
	label1:
	fruitx=rand()%20; //To determine the position of the fruit randomly(for x co-ordinate)
	if(fruitx==0) //In case the fruit is positioned at the boundary
	{
		goto label1; //It goes back to label1 function and again determines the position of the fruit randomly(x co-ordinate) 
	}
	
	label2:
	fruity=rand()%20; //To determine the position of the fruit randomly(for y co-ordinate)
	if(fruity==0) //In case the fruit is positioned at the boundary
	{
		goto label2; //It goes back to label2 function and again determines the position of the fruit randomly(y co-ordinate)
	}
	score=0;//Initially score is zero
}






void input() // Analysing input from user
{
	if(kbhit()) // To check if a key has been pressed or not
	{
		switch(getch()) // To check which key has been pressed
		{
			case 72:   // 72 is the number for upper key 
				flag=1;
				break;
			case 80:		// 80 is the number for lower key
				flag=2;
				break;
			case 75:		// 75 for left key
				flag=3;
				break;
			case 77:		// 77 for right key
				flag=4;
				break;
			case 13:		// if i press enter game will end 
				gameEnd=1;
				break;
		}
	}
}







void logic() // Function to control the movements of the snake
{
	
	int i;
	int prevx,prevy,prev2x,prev2y; //Variables to control the size of the snake
	prevx=tailx[0]; //Changing the x co-ordinate of the snake in order to increase size
	prevy=taily[0]; //Changing the y co-ordinate of the snake in order to increase size
	tailx[0]=snakeX; //Changing the x co-ordinate of the snake in order to increase size
	taily[0]=snakeY; //Changing the y co-ordinate of the snake in order to increase size
	for(i=1;i<=piece;i++) //Loop to increase size based on the number of fruits eaten
	{
		prev2x=tailx[i];
		prev2y=taily[i];
		tailx[i]=prevx;
		taily[i]=prevy;
		prevx=prev2x;
		prevy=prev2y;
	}
	switch(flag)
	{
		case 1:
			snakeX--; // To make the snake move up
			break;
		case 2:
			snakeX++; // To make the snake move down
			break;
		case 3:
			snakeY--; // To make the snake move left
			break;
		case 4:
			snakeY++; // To make the snake move right
 			break;
			
		default :
			break;
	}
	if(snakeX==0 || snakeX==height || snakeY==0 || snakeY==width) //To end the game when snake touches the boundary
	{
		gameEnd=1;
	}
	if(snakeX==fruitx && snakeY==fruity) // When the snake eats the fruit, to determine the next position of the fruit
	{
		label3:
		fruitx=rand()%20; //To determine the position of the fruit randomly(for x co-ordinate)
		if(fruitx==0) //In case the fruit is positioned at the boundary
		{
			goto label3; //It goes back to label3 function and again determines the position of the fruit randomly(x co-ordinate) 
		}
	
		label4:
		fruity=rand()%20; //To determine the position of the fruit randomly(for y co-ordinate)
		if(fruity==0) //In case the fruit is positioned at the boundary
		{
			goto label4; //It goes back to label4 function and again determines the position of the fruit randomly(y co-ordinate)
		}
		score+=10;//Increments the score 
	        piece++; //Increments when the snake eats the fruit
		
	}
		
}



int main()
{
	char line[100];
	printf("enter the player name:\n");
	scanf("%[^\n]s",name);
	setup(); // To call the setup function
	
	
	while(gameEnd != 1) //As long as gameEnd is not equal to one, the game will not end so that we can run the functions
	{
		draw();  //Calls the function when game begins
		input(); //Calls the function when game begins
		logic(); //Calls the function when game begins
	}
	FILE *f1=fopen("snake.txt","a+");
	fprintf(f1,"%s\t %d\n",name,score);
	fclose(f1);
	if(f1==NULL)
		printf("printf file not found");
	else
	{
		printf("the score of pervious played games is:\n");
		FILE *f2=fopen("snake.txt","r");
		while(fgets(line,sizeof(line),f2))
		{
			printf("%s",line);
		}
		fclose(f2);
	}
	
	return 0;	
}