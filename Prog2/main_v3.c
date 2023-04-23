
/*
************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in
studying and applying the concepts learned. We have constructed the functions and their
respective algorithms and corresponding code by ourselves. The program was run, tested,
and debugged by our own efforts. We further certify that we have not copied in part or
whole or otherwise plagiarized the work of other students and/or persons.

	Dela Cruz, Diego, 		12205842
	Laolao, Gian Chill A., 	12207713
************************************************************************************************
*/


/*
	Pre-processor Directives
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "functions.c" //function file


/*
	Function checkPID returns the index for the struct array
	@param personnel[] - the struct array with a type of person
	@param pID - personnel ID that will be checked
	@param i - a local variable used in the for loop
	@return -1 if the pID is not in the struct array
	Pre-condition: person personnel[] has values
				   pID is an integer
*/
int 
checkPID(person personnel[], int pID )
{
	int i;

	if(pID == 0)
	{
		return -1; //return -1 if pID is 0
	}


	for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
	{
		if (pID == personnel[i].personnelID)
		{
			return i; //return index number
		}
	}

	printf ("ID not found...\n"); //error message 

	return -1; //return -1 if pID is not found
}


/*
	Function checkPrID returns the index for the struct array
	@param project[] - the struct array with a type of project
	@param peID - project ID that will be checked
	@param i - a local variable used in the for loop
	@return -1 if the prID is not in the struct array
	Pre-condition: project projects[] has values
				   prID is an integer
*/
int 
checkPrID(project projects[], int prID)
{
	int i;

	if(prID == 0)
	{
		return -1; //return -1 if prID is 0
	}

	for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
	{
		if (prID == projects[i].projectID) 
		{
			return i; //return index number
		}
	}

	printf ("ID not found...\n"); //error message 

	return -1; //return -1 if ID not found
}


/*
	Function checkTID returns the index for the struct array
	@param tasks[] - the struct array with a type of task
	@param tID - task ID that will be checked
	@param i - a local variable used in the for loop
	@return -1 if the prID is not in the struct array
	Pre-condition: task tasks[] has values
				   tID is an integer
*/
int 
checkTID(task tasks[], int tID)
{
	int i;

	if(tID == 0)
	{
		return -1; //return -1 if tID is 0
	}

	for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
	{
		if (tID == tasks[i].taskID)
		{
			return i; //return index number
		}
	}

	printf ("ID not found...\n"); //error message 

	return -1; //return -1 if tID is not found
}

/*
	Function checkLogin checks if the input is in the file *fp
	@param *fp - file pointer
	@param check[] - string that will be checked and compared
	@param line - line number of the string in the text file
	@param cBuffer[40] - string that will contain the content of the line in the file
	@param nNum - counter for the line number
	@return 0 if string (check[]) is in the file, else return 1
	Pre-condition: *fp must be the preloaded.txt file
*/
int 
checkLogin(FILE *fp, char check[], int line)
{
	char sBuffer[40];
	int nNum = 1;

	rewind(fp);
	
	while (fgets (sBuffer, sizeof sBuffer, fp) != NULL) //loops until it scans a blank line (NULL)
	{	
		sBuffer[strlen(sBuffer) - 1] = '\0'; //replaces \n to \0

		if (nNum % 6 == line)
		{
			if (strcmp (check, sBuffer) == 0)
			{
				return 0; //return 0 if check is in file
			}
		}
		nNum++;
	}
	return 1; //return 1 if check is not in file
}

/*
	Function checkLogin2 checks if the input is in the personnel struct array, returns index
	@param personnel[] - struct array with the type of person
	@param check[] - string that will be checked and compared
	@param n - value of 1 if check[] is username, 2 if password
	@param i - local variable used in for loop, represents the index number
	@return -1 if string is not in the struct array, else return i
*/
int 
checkLogin2 (person personnel[], char check[], int n)
{
	int i;

	for (i = 0; i < 100; i++) //loops until i reaches 100 or if one of the statement is true
	{
		if (n == 1 && strcmp(personnel[i].username, check) == 0) //n = 1 if username
		{
			return i; //return index number
		}
		else if (n == 2 && strcmp(personnel[i].password, check) == 0) //n = 2 if password
		{
			return i;
		}
	}
	
	return -1; //return -1 if check is not found
}


/*
	Function changePass changes user password if the password is temporary (password)
	@param personnel[] - struct array with the type of person
	@param username[] - username of user
	@param i - local variable used in for loop
	@param sBuffer - string variable that holds the new password
	Pre-condition - personnel[] must contain values
*/
void
changePass(person personnel[], char username[])
{
	int i;
	char sBuffer[40];

	for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
	{
		if (strcmp(personnel[i].username, username) == 0)
		{

			printf ("\n\n\tFirst time Login, change your password.\n");

			do
			{		
				
				printf ("\n\tEnter your New Password: ");
				fgets(sBuffer, sizeof(sBuffer), stdin);

				sBuffer[strlen(sBuffer) - 1] = '\0'; //replaces \n to \0

				if (strcmp(sBuffer, "password\0") == 0)
				{
					printf ("\n\tYour New Password must no be the same as your Initial Password.");
				}
				else
				{
					strcpy(personnel[i].password, sBuffer);
				}

			} while (strcmp(sBuffer, "password\0") == 0);
		} 
	}	
}

/*
	Function login contains the login menu 
	@param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
	@param *fPreloaded - file pointer for preloaded.txt
	@param sUsername[] - string variable that holds the username input
	@param sPassword[] - string variable that holds the password input
	@param i - local variable used in while loop, represents array index
	@param ch - local variable that stores a character from typing password
	@return 0 to end, return 1 if File is NULL
	Pre-condition: preloaded.txt must contain information
*/
int 
login(person personnel[], project projects[], task tasks[])
{
	FILE *fPreloaded = fopen ("preloaded.txt", "r");
	char sUsername[40];
	char sPassword[40];
	int i = 0;
	char ch;

	system("cls");

	if(fPreloaded == NULL) //if file pointer is NULL, exits function
	{
		printf ("\n\tError. File not Found\n"); //error message
		return 1;
	}

	fflush(stdin);

	printf("\n\n=========== LOGIN MENU ===========\n");
	printf("\n\tEnter username: ");
	fgets(sUsername, 40, stdin);
	
	sUsername[strlen(sUsername) - 1] = '\0'; //replaces \n to \0

	printf("\tEnter password: ");
	
	while((ch = getch()) != 13)	//loops until user presses Enter, getch gets the character inputted then assigns in ch
		{	
			if (ch == 8 && i > 0) //8 represents backspace in ASCII
			{
				printf ("\b \b"); //removes the character, mimics backspace
				i--;
				sPassword[i] = '\0';
			}
			else if (ch != 8)
			{
				sPassword[i] = ch; //puts character in ch to sPassword[i]
				printf("*"); //prints * to hide character inputted
				i++;
			}
			
		}
	sPassword[i] = '\0'; //adds NULL char to end of string
	
	if (checkLogin (fPreloaded, sUsername, 2) == 0 || 
		checkLogin2 (personnel, sUsername, 1) != -1)
	{
		if (checkLogin (fPreloaded, sPassword, 3) == 0)
		{
			printf ("\n\n\tLogged In.\n\n");
			fclose (fPreloaded);

			admin(personnel, projects, tasks);
			
		}
		else if (strcmp(sPassword, "password") == 0)
		{
			
			changePass(personnel, sUsername);

			printf ("\n\tPassword Changed, Log-in again.\n");

		}
		else if (checkLogin2(personnel, sPassword, 2) != -1)
		{
			printf ("\n\tLogged In.\n\n");

			switch (personnel[checkLogin2(personnel, sUsername, 1)].access)
			{
				case 1: //case if access number is 1
					admin(personnel, projects, tasks);
					break;
				case 2: //case if access number is 2
					manager(projects, tasks, personnel);
					break;
				case 3: //case if access number is 3
					user(personnel, tasks, sUsername);
					break;
				case 0:
					printf ("\n\tAccount is archived...\n");
			}
		}
		else
		{
			printf ("\n\n\tIncorrect Password.\n\n"); //error message
		}
	}	
	else 
	{
		printf ("\n\n\tInvalid Username or User Data not Imported.\n\n"); //error message
	}
	
	return 0;
}

/*
	Function import scans and inputs information from file to struct array
	@param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
	@param i - local variable used in while loop, represents array index
	@param nNum - counter for the line number
	@param sBuffer - string variable that holds the string from the file
	@param cChoice - hold the user input for choice
	@param sDate[] - holds the user input for date
	@param sPerson[] - represent the personnel file name of the exported file
	@param sProj[] - represent the project file name of the exported file
	@param sTask[] - represent the task file name of the exported file
	@param *fpPerson - file pointer for personnel text file 
	@param *fpProj - file pointer for project text file
	@param *fpTask - file pointer for task text file
	@return 1 to end, return -1 if File is NULL
	Pre-condition: personnel_(date), project_(date), and task_(date) must exist
*/
int 
import(person personnel[], project projects[], task tasks[])
{
	int i;
	int nNum;
	char sBuffer[255];
	char cChoice;
	
	char sDate[9];
	char sPerson[20] = "personnel_";
	char sProj[20] = "project_";
	char sTask[20] = "task_";

	FILE *fpPerson;
	FILE *fpProj;
	FILE *fpTask;

	fflush(stdin);

		printf ("\nEnter Date of File: [YYYYMMDD] ");
		scanf ("%s", sDate);
		
		strcat(sPerson, sDate);
		strcat(sProj, sDate);
		strcat(sTask, sDate);
	
	do //loops until user inputs 4 
	{
		nNum = 1; //initialization of variables
		i = 0;

		fflush(stdin);

		printf ("\nEnter which Data to Import: \n"
				"          [1] Personnel\n"
				"          [2] Project\n"
				"          [3] Task\n"
				"          [4] Main Menu\n\t");
		scanf (" %c", &cChoice);

		switch(cChoice)
		{
			case '1':
			{
				fpPerson = fopen (sPerson, "r");

				rewind(fpPerson); //puts file position to the beginning of the file

				if (fpPerson == NULL)
				{
					printf ("\n\tFILE NOT FOUND...\n"); //error message
					return -1;
				}

				while (fgets(sBuffer, sizeof(sBuffer), fpPerson) != NULL) //loops until scans blank line (NULL)
				{
					switch (nNum % 6) 
					{
						case 1: //case for personnel ID and personnel name
							sscanf(sBuffer, "%d %[^\n]", &personnel[i].personnelID, personnel[i].name); //scans string, inputs integer to personnelID, scans until newline and inputs to name 
							break;
						case 2: //case for personnel username
							strcpy (personnel[i].username, sBuffer);
							personnel[i].username[strlen(sBuffer) - 1] = '\0'; //replaces \n to \0
							break;
						case 3: //case for personnel password
							strcpy (personnel[i].password, sBuffer);
							personnel[i].password[strlen(sBuffer) - 1] = '\0';
							break;
						case 4: //case for personnel active status
							personnel[i].active = atoi(sBuffer); //converts string to int then assign to variable
							break;
						case 5: //case for personnel acces
							personnel[i].access = atoi(sBuffer); //converts string to int then assign to variable
							break;
						case 0: //case if its the 6th line
							i++; //increments for next index
							break;
					}
					nNum++; //represent the nth line in the file
				}

				fclose(fpPerson); //closes file
				printf ("\n\tPersonnel Data Imported...\n");

				break;
			}
			case '2':
			{
				fpProj = fopen (sProj, "r");

				rewind(fpProj);

				if (fpProj == NULL)
				{
					printf ("\n\tFILE NOT FOUND...\n");
					return -1;
				}

				while (fgets(sBuffer, sizeof(sBuffer), fpProj) != NULL) //loops until scans blank line (NULL)
				{
					switch (nNum % 6)
					{
						case 1: //case for project ID and project name
							sscanf(sBuffer, "%d %[^\n]", &projects[i].projectID, projects[i].name);
							break;
						case 2: //case for project status 
							projects[i].status = atoi(sBuffer);
							break;
						case 3: //case for project completion
							projects[i].completion = atof(sBuffer);
							break;
						case 4: //case for project description
							strcpy(projects[i].description, sBuffer);
							projects[i].description[strlen(sBuffer) - 1] = '\0';
							break;
						case 5: //case for the assigned personnel ID on the project
							projects[i].personnelID = atoi(sBuffer);
							break;
						case 0: //case if its the 6th line
							i++; //increments for next index
							break;
					}
					nNum++; //represents the nth line in the file
				}

				fclose(fpProj); //closes file
				printf ("\n\tProject Data Imported...\n");

				break;
			}
			case '3':
			{
				fpTask = fopen (sTask, "r");

				rewind(fpTask);

				if (fpTask == NULL)
				{
					printf ("\n\tFILE NOT FOUND...\n");
					return -1;
				}

				while (fgets(sBuffer, sizeof(sBuffer), fpTask) != NULL) //loops until scans blank line (NULL)
				{
					switch (nNum % 10)
					{
						case 1: //case for task ID and task name
							sscanf(sBuffer, "%d %[^\n]", &tasks[i].taskID, tasks[i].name);
							break;
						case 2: //case for task sequence
							tasks[i].sequence = atoi(sBuffer);
							break;
						case 3: //case for task description
							strcpy (tasks[i].description, sBuffer);
							tasks[i].description[strlen(sBuffer) - 1] = '\0';
							break;
						case 4: //case for task project ID
							tasks[i].projectID = atoi(sBuffer);
							break;
						case 5: //case for task start date
							strcpy (tasks[i].startDate, sBuffer);
							tasks[i].startDate[strlen(sBuffer) - 1] = '\0';
							break;	
						case 6: //case for task end date
							strcpy (tasks[i].endDate, sBuffer);
							tasks[i].endDate[strlen(sBuffer) - 1] = '\0';
							break;
						case 7: //case for task duration
							tasks[i].totalDuration = atof (sBuffer);
							break;
						case 8: //case for task status
							tasks[i].status = atoi (sBuffer);
							break;
						case 9: //case for task assigned personnel ID
							tasks[i].assignID = atoi (sBuffer);
							break;
						case 0: //case for 10th line
							i++; //increments for next index
							break;
					}
					nNum++; //represents the nth line
				}
				
				fclose(fpTask);
				printf ("\n\tTask Data Imported...\n");

				break;
			}
			case '4':
			{
				printf ("\n\tReturning to Main Menu...\n");
				break;
			}
			default:
			{
				printf ("\n\tInvalid Input...\n");
			}
		}

	} while (cChoice != '4');

	return 1;
}

/*
	Function export prints data from struct array to text file
	@param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
	@param i - local variable used in while loop, represents array index
	@param cChoice - hold the user input for choice
	@param sDate[] - holds the user input for date
	@param sPerson[] - represent the personnel file name of the exported file
	@param sProj[] - represent the project file name of the exported file
	@param sTask[] - represent the task file name of the exported file
	@param *fPerson - file pointer for personnel text file 
	@param *fProj - file pointer for project text file
	@param *fTask - file pointer for task text file
	@param t - variable which contains time since January 1 1970 00:00 in integer
	@param date - a struct contains time and date
	@param d - integer containing the current date
*/
void 
export(person personnel[], project projects[], task tasks[])
{
	int i;
	char cChoice;
	char sDate[9];
	char sPerson[20] = "personnel_";
	char sProj[20] = "project_";
	char sTask[20] = "task_";
	FILE *fPerson;
	FILE *fProj;
	FILE *fTask;

	time_t t = time(NULL); //assigns time since January 1 1970 00:00 to t
	struct tm date = *localtime(&t); //takes t, converts to t to different formats and stores in date struct
	int d;

    d = ((date.tm_year + 1900) * 10000) + ((date.tm_mon + 1) * 100) + date.tm_mday; //converts dates to YYYYMMDD

    itoa(d, sDate, 10); //converts d to string and stores in sDate, 10 represent base number (Decimal)

	do //loops until user inputs 4
	{

		fflush(stdin);

		printf ("\nEnter which Data to Export: \n"
				"          [1] Personnel\n"
				"          [2] Project\n"
				"          [3] Task\n"
				"          [4] Main Menu\n\t");
		scanf (" %c", &cChoice);

		switch(cChoice)
		{
			case '1': //case for exporting Personnel
			{
				strcat(sPerson, sDate);

				fPerson = fopen(sPerson, "w");

				for (i = 0; i < 100; i++) //loops until i reaches 100
				{
					if (personnel[i].personnelID / 1000 > 0 && personnel[i].personnelID / 1000 <= 3) 
					{
						fprintf (fPerson, "%d %s\n", personnel[i].personnelID, personnel[i].name);
						fprintf (fPerson, "%s\n", personnel[i].username);
						fprintf (fPerson, "%s\n", personnel[i].password);
						fprintf (fPerson, "%d\n", personnel[i].active);
						fprintf (fPerson, "%d\n", personnel[i].access);
						fprintf (fPerson, "\n");
					}
				}
				
				fclose(fPerson); //closes file
				printf ("\n\tPersonnel Data Exported...\n");

				break;
			}
			case '2':
			{
				strcat(sProj, sDate);

				fProj = fopen(sProj, "w");

				for (i = 0; i < 100; i++) //loops until i reaches 100
				{
					if (projects[i].projectID / 1000 == 4)
					{
						fprintf (fProj, "%d %s\n", projects[i].projectID, projects[i].name);
						fprintf (fProj, "%d\n", projects[i].status);
						fprintf (fProj, "%.2f\n", projects[i].completion);
						fprintf (fProj, "%s\n", projects[i].description);
						fprintf (fProj, "%d\n", projects[i].personnelID);
						fprintf (fProj, "\n");
					}
				}

				fclose(fProj); //closes file
				printf ("\n\tProject Data Exported...\n");

				break;
			}
			case '3':
			{
				strcat(sTask, sDate);

				fTask = fopen(sTask, "w");

				for (i = 0; i < 100; i++) //loops until i reaches 100
				{
					if (tasks[i].taskID / 1000 == 5)
					{
						fprintf (fTask, "%d %s\n", tasks[i].taskID, tasks[i].name);
						fprintf (fTask, "%d\n", tasks[i].sequence);
						fprintf (fTask, "%s\n", tasks[i].description);
						fprintf (fTask, "%d\n", tasks[i].projectID);
						fprintf (fTask, "%s\n", tasks[i].startDate);
						fprintf (fTask, "%s\n", tasks[i].endDate);
						fprintf (fTask, "%.2f\n", tasks[i].totalDuration);
						fprintf (fTask, "%d\n", tasks[i].status);
						fprintf (fTask, "%d\n", tasks[i].assignID);
						fprintf (fTask, "\n");
					}
				}

				fclose (fTask); //closes file
				printf ("\n\tTask Data Exported...\n");

				break;
			}
			case '4':
			{
				printf ("\n\tReturning to Main Menu...\n");
				break;
			}
			default:
			{
				printf ("\n\tInvalid Input...");
			}
		}

	} while (cChoice != '4');

}


int 
main()
{
	char cChoice;
	person personnel[100];
	project projects[100];
	task tasks[100];


	printf ("\t\n============== WELCOME ==============\n\n");

	do //loops until user inputs 4
	{
		fflush(stdin);

		printf ("\n========= MAIN MENU ==========\n"
				"\n\t[1] Log In\n"
				"\t[2] Import Data\n"
				"\t[3] Export Data\n"
				"\t[4] Exit\n\t");
		scanf (" %c", &cChoice);

		switch(cChoice)
		{
			case '1': //case for Log In Menu
				login(personnel, projects, tasks);
				break;
			case '2': //case for Importing data
				printf ("\n======== Import Data ========...\n");
				import(personnel, projects, tasks);
				break;
			case '3': //case for Exporting data
				printf ("\n======== Export Data ========\n");
				export(personnel, projects, tasks);
				break;
			case '4': //case for Exiting program
			{
				do //loops if user input is not Y or N
				{
					printf ("\nMake sure your Data is Exported before Exiting.\n" 
							"Confirm Exit.  [Y / N]\n");
					scanf (" %c", &cChoice);

					if (cChoice != 'Y' && cChoice != 'N')
					{
						printf ("\n\tInvalid Input...\n"); //error message
					}
				} while (cChoice != 'Y' && cChoice != 'N');

				if (cChoice == 'Y')
				{
					printf ("\tExiting Programs...\n");
					cChoice = '4';
				}
				else
				{
					printf ("\n\tReturning to Main Menu...\n");
				}
				break;
			}		
			default:
				printf ("\tInvalid Input.\n"); //error message

		}

	} while (cChoice != '4');
		
	return 0;
}