#include <stdlib.h>
#include<ctype.h>
#include <stdio.h>
#include <string.h>
struct Dog
{
	char name[50];
	float weight;
	int age;

	char type[50];
	int dogAge;
};

void getData(struct Dog allDogs[], int *amountPtr);
void seeYear(struct Dog allDogs[],int *amountPtr);
void display(struct Dog allDogs[], int *amountPtr);
void readFile(struct Dog allDogs[], int *amountPtr);
void writeFile(struct Dog allDogs[], int *amountPtr);
int main()
{

	int amount = 0;
	struct Dog allDogs[10]= {};
	char choice;
	char fileChoice;




	printf("Would you like to read in from a file? Y/N");
	scanf(" %c", choice);
	getchar();



	while( choice == 'y' && choice == 'Y'  )
	{

		readFile(allDogs, &amount);


		seeYear(allDogs,&amount);
		display(allDogs,&amount);
		break;

	}


	while( choice != 'y' || choice != 'Y'  )
	{



		printf("How many dogs do you have?");
		scanf("%d", &amount);
		getchar();

		while(amount < 1 || amount > 10)
		{
			printf("Error please try again.");
			printf("How many dogs do you have?");
			scanf("%d", &amount);
			getchar();
		}





		getData(allDogs,&amount);
		seeYear(allDogs,&amount);
		display(allDogs,&amount);




		printf("Would you like to write this in to a file");
		scanf(" %c", &fileChoice);
		getchar();


		while( fileChoice =='y' || fileChoice == 'Y')
		{

			writeFile(allDogs, &amount);



			break;
		}

	}


}


void getData(struct Dog allDogs[], int *amountPtr)
{
	for(int x = 0; x < *amountPtr; x++)
	{
		printf("What is the dogs name?\n");
		fgets(allDogs[x].name,50,stdin);
		allDogs[x].name[strcspn(allDogs[x].name, "\n")] = '\0';

		printf("How much does the dog weigh?\n");
		scanf("%f", &allDogs[x].weight);
		getchar();

		printf("How old is the dog in human years?\n");
		scanf("%d", &allDogs[x].age);
		getchar();
	}
}

void seeYear(struct Dog allDogs[], int *amountPtr)
{
	for(int x = 0; x < *amountPtr; x++)
	{
		if(allDogs[x].weight <= 20)
		{
			strcpy(allDogs[x].type, "Small");

			if(allDogs[x].age == 1)
				allDogs[x].dogAge = 15;
			else if(allDogs[x].age == 2)
				allDogs[x].dogAge = 23;
			else if(allDogs[x].age == 3)
				allDogs[x].dogAge = 28;
			else
				allDogs[x].dogAge = 28 + (4 * (allDogs[x].age - 3));
		}
		else if(allDogs[x].weight <= 50)
		{
			strcpy(allDogs[x].type, "Medium");

			if(allDogs[x].age == 1)
				allDogs[x].dogAge = 14;
			else if(allDogs[x].age == 2)
				allDogs[x].dogAge = 23;
			else if(allDogs[x].age == 3)
				allDogs[x].dogAge = 30;
			else
				allDogs[x].dogAge = 30 + (5 * (allDogs[x].age - 3));
		}
		else
		{
			strcpy(allDogs[x].type, "Large");

			if(allDogs[x].age == 1)
				allDogs[x].dogAge = 12;
			else if(allDogs[x].age == 2)
				allDogs[x].dogAge = 21;
			else if(allDogs[x].age == 3)
				allDogs[x].dogAge = 29;
			else
				allDogs[x].dogAge = 29 + (7 * (allDogs[x].age - 3));
		}
	}
}


void display(struct Dog allDogs[], int *amountPtr)
{
	printf("Dog name     Dog Weight     Years in Human     Years in Dog\n");
	for(int x =0; x < *amountPtr; x++)
	{
		printf("%s     %s dog     %d     %d\n", allDogs[x].name, allDogs[x].type, allDogs[x].age, allDogs[x].dogAge);
	}

}

void readFile(struct Dog allDogs[], int *amountPtr)
{
	char place[50];
	printf("What is the file name ?");
	fgets(place,50,stdin);
	place[strcspn(place, "\n")] = '\0';


	FILE *input = fopen(place,"r");

	if( input == NULL)
	{
		printf("Error readinf file");
		exit(0);
	}




	char line[300];
	char *sp;

	int x = 0;
	while(fgets(line,100,input) != NULL)
	{

		sp = strtok(line,",");

		strcpy(allDogs[x].name, sp);
		sp = strtok(NULL,",");
		allDogs[x].weight = atof(sp);

		sp = strtok(NULL,",");
		allDogs[x].age = atoi(sp);




		x++;
	}

	*amountPtr = x;





	fclose(input);


}


void writeFile(struct Dog allDogs[], int *amountPtr)
{
	char place[50];

	printf("What is the file name? ");
	fgets(place, 50, stdin);
	place[strcspn(place, "\n")] = '\0';

	strcat(place, ".csv");

	FILE *output = fopen(place, "w");

	if(output == NULL)
	{
		printf("Error writing file.\n");
		exit(0);
	}

	for(int x = 0; x < *amountPtr; x++)
	{
		fprintf(output, "%s,%.2f,%d\n",
		        allDogs[x].name,
		        allDogs[x].weight,
		        allDogs[x].age);
	}

	fclose(output);


}
