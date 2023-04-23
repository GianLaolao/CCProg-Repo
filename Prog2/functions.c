/*
    This file contains all functions used for each Access number in the program.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "variables.h" //header file containing struct variables and function declaration

//Function declaration
void showPersonnel(person personnel[]);
void showTasks(task tasks[]);
void showProjects(project projects[]);

/*
    Function getDate returns the current date as an integer
    @param t - variable which contains time since January 1 1970 00:00 in integer
	@param date - a struct contains time and date
	@param d - integer containing the current date
    @return d, the current date as an integer
*/
int 
getDate ()
{
    time_t t = time(NULL);
	struct tm date = *localtime(&t);
    int d;

    d = ((date.tm_mon + 1) * 1000000) + (date.tm_mday * 10000) +  + (date.tm_year + 1900);

    return d;
}


// ADMIN FUNCTIONS

/*
    Function IDnum returns a randomized personnel ID
    @param access - access number of user
    @param nID - contains initial number for personnel ID
    @return randomized ID
*/
int 
IDnum(int access)
{
    int nID = access * 1000;

    srand (time(NULL)); //initialized random number to current time

    return nID + (rand() % 1000);
}

/*
    Function addUser adds a new user
    @param personnel[] - struct array with the type of person
    @param sName[] - string variable that hold the name input
    @param sUsername[] - string variable that holds the username input
	@param sPassword[] - string variable that holds the temporary password 
    @param nActive - variable that hold active status
    @param nAccess - varible that holds the access number
    @param nIDnum - variable that holds the personnel ID
    @param i - local variable used in for loop
    @return 0 if end of function or if values assigned to a struct
    
*/
int 
addUser(person personnel[])
{
    char sName[40];
    char sUsername[40];
    char sPassword[40] = "password\0";
    int nActive;
    int nAccess;
    int nIDnum;
    int i;

    fflush(stdin);
    
    printf ("\n========== Add New User ==========\n");

    do //loops if length of name is greater than 40
    {
        printf ("\nInput Name: ");
        fgets (sName, 40, stdin);

        sName[strlen(sName) - 1] = '\0'; //changes \n to \0

        if (strlen(sName) > 40)
            printf ("Max Characters is 40."); //error message

    } while (strlen(sName) > 40);
    
    do //loops if length of username is greater than 40
    {
        printf ("Input username: ");
        fgets (sUsername, 40, stdin);

        sUsername[strlen(sUsername) - 1] = '\0'; //changes \n to \0

        if (strlen(sUsername) > 40)
            printf ("Max Characters is 40."); //error message

    } while (strlen(sUsername) > 40);

    do //loops if input is not 1 or 2
    {
        printf ("Input Status: [1] Active\n"
                "              [2] Archive\n\t");
        scanf ("%d", &nActive);

        if (nActive > 2 || nActive < 1)
            printf ("Invalid Input."); //error message

    } while (nActive > 2 || nActive < 1);
        
    do //loops if input is not 1 to 3
    {
        printf ("User Access: [1] Admin\n"
                "             [2] Manager\n"
                "             [3] User\n\t");
        scanf ("%d", &nAccess);

         if (nAccess > 3 || nAccess < 1)
            printf ("Invalid Input."); //error message

    } while (nAccess > 3 || nAccess < 1);
       
    nIDnum = IDnum(nAccess);

    for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
    {
        if (personnel[i].personnelID == 0 || personnel[i].personnelID == '\0')
        {
            personnel[i].personnelID = nIDnum;
            strcpy(personnel[i].name, sName);             
            strcpy(personnel[i].username, sUsername);
            strcpy(personnel[i].password, sPassword);
            personnel[i].active = nActive;
            personnel[i].access = nAccess;
            
            return 0;
        }
    } 

    return 0;
}


/*
    Function updateUser updates user info
    @param personnel[] - struct array with the type of person
    @param nPerID - personnel ID chosen
    @param i - contains the index number of nPerID in personnel struct array
    @param cChoice - choice of user 
    Pre-condition: personnel[] must have values or must have personnel info
*/
int 
updateUser(person personnel[])
{
    int nPerID;
    int i;
    char cChoice;
    
    printf ("\n=========== Update User ===========\n\n");

    showPersonnel(personnel); 

    do //loops if nPerID is -1 or m
    {
        printf ("\nEnter Personnel ID: [0] Exit\n");
        scanf ("%d", &nPerID);

        if (nPerID == 0)
        {
            return -1;
        }

        i = checkPID(personnel, nPerID);

     } while (i == -1);

    if (i != -1)
    {
        printf ("\n===== Input Changes. =====\n"); 

        do //loops until cChoice is 4
        {   
            fflush(stdin);

            printf ("\nPersonnel ID: %d\n"
                    "Username:     %s\n"
                    "Password:     %s\n"
                    "Access:       %d\n", 
                    personnel[i].personnelID, personnel[i].username, personnel[i].password, personnel[i].access);

            printf("\nChange Info:  [1] Username\n"
                    "              [2] Password\n"
                    "              [3] Access Number\n"
                    "              [4] Exit\n\t");
            scanf (" %c", &cChoice);

            switch (cChoice)
            {
                case '1': //case for changing username
                {
                    fflush(stdin);
                    printf ("\nEnter New Username: ");
                    fgets(personnel[i].username, 40, stdin);
                    personnel[i].username[strlen(personnel[i].username) - 1] = '\0';
                    break;
                }
                case '2': //case for changing password
                {
                    fflush(stdin);
                    printf ("\nEnter New Password: ");
                    fgets(personnel[i].password, 40, stdin);
                    personnel[i].password[strlen(personnel[i].password) - 1] = '\0';
                    break;
                }  
                case '3': //case for changing access number
                {
                    do
                    {
                        printf ("User Access:   [1] Admin\n"
                                "               [2] Manager\n"
                                "               [3] User\n\t");
                        scanf ("%d", &personnel[i].access);

                        if (personnel[i].access > 3 || personnel[i].access < 1)
                            printf ("Invalid Input.");

                    } while (personnel[i].access > 3 || personnel[i].access < 1);
                }
                case '4': 
                {
                    printf ("\n\tReturning to Admin Menu....\n");
                    break;
                }
                default:
                {
                    printf ("\n\tInvalid Input.\n");
                }
            }

        } while (cChoice != '4');

        return 0;
    }
        
    return 0;
}

/*
    Function deleteUser deletes a specific user and its info 
    @param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
    @param nPerID - personnel ID chosen
    @param i - contains the index number of nPerID in personnel struct array
    @param j - local variable used in for loop
    @return -1 if user inputs 0 in Personnel ID to exit, return 0 if end of function
    Pre-condition: personnel[] must have user info
*/
int 
deleteUser(person personnel[], project projects[], task tasks[])
{
    int nPerID;
    int i, j;

    printf ("\n=========== Delete User ===========\n\n");

    for (i = 0; i < 100; i++)
    {
        if (personnel[i].personnelID / 1000 <= 3 && personnel[i].personnelID / 1000 > 0) 
        {
            printf ("   %d    %s\n"
                    "       Active: %d\n", personnel[i].personnelID, personnel[i].name, personnel[i].active);
        }
    }

    do 
    {
        printf ("\nEnter Personnel ID: [0] Exit\n");
        scanf ("%d", &nPerID);

        if (nPerID == 0)
        {
            return -1;
        }

        i = checkPID(personnel, nPerID);

        for (j = 0; j < 100; j++)
        {
            if (personnel[i].personnelID == projects[j].personnelID)
            {
                projects[j].personnelID = 1000;
            }
            else if (personnel[i].personnelID == tasks[j].assignID)
            {
                tasks[j].assignID = 1000;
            }
        }


        if (i != -1)
        {
            personnel[i].personnelID = 0;
            strcpy (personnel[i].username, "'\0'");
            strcpy(personnel[i].password, "'\0'");
            personnel[i].active = '\0';
            personnel[i].access = '\0';
            printf ("User Deleted...");
        }
        
    } while (i == -1 && nPerID != 0);

    return 0;
}

/*
    Function archiveUser changes personnel active status and access number to 0
    @param personnel[] - struct array with the type of person
    @param nPerID - personnel ID chosen
    @param i - contains the index number of nPerID in personnel struct array
    @return -1 if user inputs 0 to Personnel ID to exit, return 0 if end of function
    Pre-condition: A user must exist and is active
*/
int 
archiveUser(person personnel[])
{
    int nPerID;
    int i;

    printf ("\n========== Archive User ==========\n\n");

    showPersonnel(personnel);

    do // loops if i == -1
    {
        printf ("\n\nEnter Personnel ID: [0] Exit\n");
        scanf ("%d", &nPerID);

        if (nPerID == 0)
        {
            return -1;
        }

        i = checkPID(personnel, nPerID);

        if (i != -1) 
        {
            personnel[i].active = 0;
            personnel[i].access = 0;
            printf ("User Has Been Archived.");
            return 0;
        }
        
    } while (i == -1);

    
    return 0;
}

/*
    Function assignProject assigns a personnel to a project
    @param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
    @param i - local variable used in for loop
    @param j - stores the index number of a project
    @param k - stores the index number of a personnel
    @param nPerID - personnel ID chosen
    @param nProjID - project ID chosen
    @return -1 if there are no Active Projects and Active Managers, else return 0 if end of function
    Pre-condition: personnel[] and project[] must have values
*/
int 
assignProject(person personnel[], project projects[])
{
    int i, j, k, a = 0, b = 0;
    int nPerID;
    int nProjID;
    
    printf ("\n============ Assign Projects ============\n\n");

    showProjects(projects);

    printf ("\n======= Active Managers =======\n\n");
    for (i = 0; i < 100; i++)
    {
        if (personnel[i].access == 2 && personnel[i].active == 1)
        {
            printf ("   %d  %s\n", personnel[i].personnelID, personnel[i].name);
        }
        else
            b++;
    }

    if (b == i)
    {
        printf ("\t No Active Managers...\n");
        b = 0;
    }

    if (a == b)
    {
        return -1;
    }

    printf ("\n======== Assign Project =========\n");

    do 
    {
        printf ("\nEnter Project ID: [0] Exit\n");
        scanf ("%d", &nProjID);

        if (nProjID == 0)
        {
            return -1;
        }

        j = checkPrID(projects, nProjID);

        if (j != -1 && projects[j].status != 3)
        {
            printf("------------------------\n");
        }
        else
        {
            printf ("\tProject is Inactive.\n");
        }
      
    } while (j == -1);

    do 
    {
        printf ("\nEnter Personnel ID: [0] Exit\n");
        scanf ("%d", &nPerID);

        if (nPerID == 0)
        {
            return -1;
        }

        k = checkPID(personnel, nPerID);

        if (k != -1)
        {
            if (personnel[k].access == 2 && personnel[k].active == 1 )
            {
                projects[j].personnelID = personnel[k].personnelID;
                printf ("\nProject Assigned.\n");
            }
        }
      
    } while (k == -1);

   return 0; 
}

/*
    Function admin has the Admin Menu
    @param personnel[] - struct array with the type of person
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
    @param cChoice - variable for user choice
    Pre-condition: User must have access number of 1
*/
void 
admin(person personnel[], project projects[], task tasks[])
{
    char cChoice;

    system("cls"); //clears screen

    do //loops until user choice is 6
    {
        fflush(stdin);

        printf ( "\n\n============== ADMIN MENU ================\n"
                "Please enter the number of your option \n\n"
                "\t[1] Add new user\n"
                "\t[2] Update user\n"
                "\t[3] Delete user\n"
                "\t[4] Archive user\n"
                "\t[5] Assign Project\n"
                "\t[6] Back to main menu\n\t");

        scanf(" %c", &cChoice);

        switch (cChoice)
        {
            case '1': //case for adding user
            {
                addUser(personnel);
                break;   
            }
            case '2': //case for updating user info
            {  
                updateUser(personnel);
                break;
            }
            case '3': //case for deleting user
            {
                deleteUser(personnel, projects, tasks);
                break;
            }
            case '4': //case for changing user active status
            {
                archiveUser(personnel);
                break;
            }
            case '5': //case for assigning a project to user
            {
                assignProject(personnel, projects);
                break;
            }
            case '6': //case for returnning to main menu
            {
                printf ("\nReturning to Main Menu...\n\n");
                break;
            }
            default:
            {   
                printf ("\tInvalid Input.\n"); //error message
            } 
               
        }

     } while (cChoice != '6');   
}



// MANAGER FUNCTIONS

/*
    Function getID returns a randomized ID for either Project or Task
    @param num - 1 if Project ID, 2 if Task ID
	@param tasks[] - struct array with the type of task
    @param projects[] - struct array with the type of project
    @param nProjID - base number for project ID
    @param nTaskID - base number for task ID
    @return randomized Project ID if num is 1, return randomized Task ID if num is 2
    Pre-condition: num must be 1 or 2
*/
int 
getID(int num, task tasks[], project projects[])
{
    int nProjID = 4000;
    int nTaskID = 5000;
    
    srand (time(NULL)); //initialized random value function

    if (num == 1)
    {
        return nProjID + (rand() % 1000);
    }
    else if (num == 2)
    {
        
        return nTaskID + (rand() % 1000);
    }

    return 0;
}

/*
    Function addProject adds a project and its info
    @param projects[] - struct array with the type of project
    @param tasks[] - struct array with the type of task
    @param i - local variable used in for loop
    @param sName - string variable that stores the project name
    @param sDesc - string variable that stores the project description
*/
int 
addProject(project projects[], task tasks[])
{
    int i;
    char sName[40];
    char sDesc[100];

    printf ("\n========== Add Project ==========\n\n");

    fflush (stdin);  //clears the stdin input file

    printf ("Enter Project Name: ");
    fgets (sName, 40, stdin); 
    sName[strlen(sName) - 1] = '\0'; //replaces \n with \0

    fflush (stdin);

    printf ("Enter Project Short Description:\n\t");
    fgets (sDesc, 100, stdin);
    sDesc[strlen(sDesc) - 1] = '\0';

    for (i = 0; i < 100; i++) //loops until 100 or if condition is true
    {
        if (projects[i].projectID == 0 || projects[i].projectID == '\0')
        {
            
            projects[i].projectID = getID(1, tasks, projects);
            strcpy(projects[i].name, sName);
            projects[i].status = 1;
            strcpy(projects[i].description, sDesc);
            return 0;
        }
    }
    return 0;
}

/*
    Function getDays returns the number of days on a specific month
    @param month - represents a month as an integer
    @param year - represents the year as an integer
    @return number of days a month has
*/
int 
getDays(int month, int year)
{
    switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: //case for months with 31 days
		{
            return 31;
		}
		case 2: //case for February
		{
			if (year % 4 == 0) //returns 29 if year is a leap year
            {
                return 29;
            }
            else if (year % 4 != 0) //returns 28 is year is not a leap year
            {
                return 28;
            }
		}
		case 4: case 6: case 9: case 11: //case for months with 30 days
		{
			return 30;
		}
	}
	
	return 0;
}

/*
    Function computeDura computes the total duration of a project
    @param start[] - start date of a project
    @param end[] - end date of a project
    @param sD - stores the day of start date
    @param eD - stores the day of end date
    @param sM - stores the month of start date
    @param eM - stores the month of end date
    @param sY - stores the year of start date
    @param eY - stores the year of end date
    @param nDayS - stores the remaining days in the month starting from the sD
    @param nMonth - stores the months in between start month and end month
    @param i - local variable used in for loop
    @param m - represents the month after the start month
    @param y - represents the year of the start date
    @return number of days between start date and end date including the start date
    Pre-condition: start[] must be earlier than end[]
*/
float 
computeDura(char start[], char end[])
{  
    int sD;
    int eD;
    int sM;
    int eM;
    int sY;
    int eY;
    
    int nDayS, nMonth, i, m, y;
    
    float fDays = 0.00;

    sM = atoi(start) / 1000000;
    eM = atoi(end) / 1000000;
    sD = (atoi(start) / 10000) % 100;
    eD = (atoi(end) / 10000) % 100;  
    sY = atoi(start) % 10000;
    eY = atoi(end) % 10000;
    
	nDayS = getDays(sM, sY) - sD;
	
	if (eM == sM  && eY == sY)
	{
		return eD - sD + 1;
	}
	else if (eY > sY)
	{
		nMonth = (12 - sM) + (eM - 1) + ((eY - sY) - 1) * (12 * ((eY - sY) > 1));
	}
    else
	{
		nMonth = (eM - sM) - 1;
	}
	
	m = sM + 1;
	y = sY;
	
	for (i = 0; i < nMonth; i++)
	{
		fDays += getDays(m, y);
		
		if (m != 12)
		{
			m++;
		}
		else if (m == 12)
		{
			m = 1;
			y++;
		}
	}
	
    return 1 + fDays + nDayS + eD;
}

/*
    Function getSeq returns the sequence number of a task
    @param tasks[] - struct array with the type of task
    @param i - local variable used in for loop, represents the index numebr
    @param nSeq - stores the initial sequence number
    @return the highest sequence number + 1
*/
int 
getSeq(task tasks[])
{
    int i, nSeq = 0;

    for (i = 0; i < 100; i++) //loops until i reaches 100 or if statement is true
    {
       if (tasks[i].sequence > nSeq) //checks if there is a higher sequence number
            nSeq = tasks[i].sequence; //assigns the higher sequence number to nSeq
    }

    return nSeq + 1; //returns the highest sequence number + 1
}

/*
    Function checkDate checks if the start date is later than the end date
    @param start[] - start date of a project
    @param end[] - end date of a project
    @param s - stores the start date as an integer
    @param e - stores the end date as an integer
    @return 0 if start date is earlier than the end date, return 1 if start date is later than the end date
*/
int 
checkDate(char start[], char end[])
{
    int s, e;

    s = atoi(start); 
    e = atoi(end); 

    if (s % 10000 < e % 10000)
    {
        return 0;
    }
    else if (s % 10000 == e % 10000)
    {
        if (s / 10000 < e / 10000)
        {
            return 0;
        }
    }

    return 1;
}

/*
    Function addTask adds a task and its info
    @param tasks[] - struct array with the type of task
	@param projects[] - struct array with the type of project
    @param i - local variable used in for loop
    @param sName[] - string variable storing the task name 
    @param nSeq - stores the task sequence number
    @param sDesc[] - stores the task description
    @param nProjID - stores the task project ID
    @param sStart - stores the task start date
    @param sEnd - stores the task end date
    @param nStatus - stores task status
    @return 0 if task is added successfully, return 1 if end of function
*/
int 
addTask(task tasks[], project projects[])
{
    int i;
    char sName[40];
    int nSeq;
    char sDesc[100];
    int nProjID;
    char sStart[9];
    char sEnd[9];
    int nStatus;
    

    printf ("\n=========== Add Task ===========\n\n");

    fflush(stdin);

    printf ("Enter Task Name: ");
    fgets(sName, 40, stdin);
    sName[strlen(sName) - 1] = '\0';

    nSeq = getSeq(tasks);

    fflush (stdin);

    printf ("Enter Task Description:\n\t");
    fgets(sDesc, 100, stdin);
    sDesc[strlen(sDesc) - 1] = '\0';

    showProjects(projects);

    printf("\nAssign Task to a Project: \n");
    scanf ("%d", &nProjID);

    fflush(stdin);
    printf ("Enter Start Date: (Format: MMDDYYYY) ");
    fgets(sStart, 9, stdin);
    
    do
    {
        fflush(stdin);
        printf ("Enter End Date: (Format: MMDDYYYY) ");
        fgets(sEnd, 9, stdin);

        if(checkDate(sStart, sEnd))
            printf ("\n\tEnd Date must be later than Start Date.\n");
       
    } while (checkDate(sStart, sEnd));
    
        
    do
    {
         printf ("Enter Status: [1] Not Started\n"
                "              [2] In Progress\n"
                "              [3] Done\n\t");
        scanf ("%d", &nStatus);

        if (nStatus > 3 || nStatus < 1)
            printf ("\n\tInvalid Status...\n");

    } while (nStatus > 3 || nStatus < 1);
    
       


    for (i = 0; i < 100; i++)
    {
        if (tasks[i].taskID == 0 || tasks[i].taskID == '\0')
        {   
            tasks[i].taskID = getID(2, tasks, projects);
            strcpy (tasks[i].name, sName);
            tasks[i].sequence = nSeq;
            strcpy (tasks[i].description, sDesc);
            tasks[i].projectID = nProjID;
            strcpy (tasks[i].startDate, sStart);
            strcpy (tasks[i].endDate, sEnd);
            tasks[i].totalDuration = computeDura(sStart, sEnd);
            tasks[i].status = nStatus;
            tasks[i].assignID = 0;

            printf("Task ID :               %d\n", tasks[i].taskID);
            printf("Task Name :             %s\n", tasks[i].name);
            printf("Task Sequence :         %d\n", tasks[i].sequence);
            printf("Task Description :      \n\t%s\n\n", tasks[i].description);
            printf("Project ID :            %d\n", tasks[i].projectID);
            printf("Task Start date :       %s\n", tasks[i].startDate);
            printf("Task End date :         %s\n", tasks[i].endDate);
            printf("Task Total Duration :   %f\n", tasks[i].totalDuration);
            printf("Task Status :           %d\n", tasks[i].status);
            printf("Assigned Personnel ID : %d\n\n", tasks[i].assignID);

            return 0;
        }
    }

    return 1;
}

/*
    Function ask asks the user if they want to change an info
    @param s[] - contains the name of the info
    @param choice - stores the choice of user
    @return 1 if user choice is y (yes),  return 0 if n (no), return -1 if end of function
*/
int 
ask(char s[])
{
    char choice;

    do 
    {
        fflush(stdin);
        printf("Do you wish to change %s [y/n]? ", s);
        scanf(" %c", &choice);
        if(choice != 'y' && choice != 'n')
            printf("Invalid option! Try again.\n\n");
    } while(choice != 'y' && choice != 'n');

    if(choice == 'y')
        return 1;
    if(choice == 'n')
        return 0;

    return -1;
}

/*
    Function updateTask updates info on a task
    @param tasks[] - struct array with the type of task
	@param projects[] - struct array with the type of project
    @param i - stores the index number of a specific task in tasks[]
    @param a - variable used in a condition to exit do while loop
    @param id - stores the ID number
    @param choice - stores user choice
    @return 0 if end of function
    Pre-condition: tasks[] must have values
*/
int 
updateTask(task tasks[], project projects[])
{
    int i;
    int a = 0;
    int id;
    char choice;

    printf ("\n========== Update Task ==========\n\n");

    
        showTasks(tasks);

        do //loops until user choose not to update another task
        {
            do
            {
                printf("\nEnter task ID to update: [0] Exit\n");
                scanf("%d", &id);

                if (id == 0)
                {
                    return -1;
                }

                printf("\nFinding entered taskID...\n\n");

                i = checkTID(tasks, id);

            } while (i == -1);
                
                if(tasks[i].taskID == id) 
                {
                    printf("Task found! Printing details...\n\n");
                    do //loops until user chose not to update another detail
                    {
                        
                        printf("==== CURRENT TASK DETAILS ====\n\n");

                        printf("Task ID :               %d\n", tasks[i].taskID);
                        printf("Task Name :             %s\n", tasks[i].name);
                        printf("Task Sequence :         %d\n", tasks[i].sequence);
                        printf("Task Description :      \n\t%s\n\n", tasks[i].description);
                        printf("Project ID :            %d\n", tasks[i].projectID);
                        printf("Task Start date :       %s\n", tasks[i].startDate);
                        printf("Task End date :         %s\n", tasks[i].endDate);
                        printf("Task Total Duration :   %.2f\n", tasks[i].totalDuration);
                        printf("Task Status :           %d\n", tasks[i].status);
                        printf("Assigned Personnel ID : %d\n\n", tasks[i].assignID);

                        fflush(stdin);

                        if(ask("name")) 
                        {
                            fflush(stdin);
                            printf("Enter new task name: ");
                            fgets(tasks[i].name, 40, stdin);

                            tasks[i].name[strlen(tasks[i].name) - 1] = '\0';
                        }

                        if(ask("description")) 
                        {
                            fflush(stdin);
                            printf("Enter new task description: ");
                            fgets(tasks[i].description, 100, stdin);

                            tasks[i].description[strlen(tasks[i].description) - 1] = '\0';
                        }
                        if(ask("project ID")) 
                        {
                            do
                            {
                                printf("Enter new project ID: ");
                                scanf("%d", &tasks[i].projectID);

                                if (tasks[i].projectID == 0)
                                {
                                    printf ("\n\tProject ID must not be 0...\n");
                                }

                            } while (checkPrID(projects, tasks[i].projectID) == -1);
                        }
                        if(ask("start date")) 
                        {

                            do
                            {
                                fflush(stdin);
                                printf("Enter new task start date: ");
                                fgets(tasks[i].startDate, 9, stdin);

                                if (checkDate(tasks[i].startDate, tasks[i].endDate))
                                    printf ("\n\tStart Date must be earlier than End Date.\n");

                            } while (checkDate(tasks[i].startDate, tasks[i].endDate));
                            
                            
                        }
                        if(ask("end date")) 
                        {   
                            do
                            {
                                fflush(stdin); ///fix error, only scans 7 chars
                                printf("Enter new task end date: ");
                                fgets(tasks[i].endDate, 9, stdin);

                                if (checkDate(tasks[i].startDate, tasks[i].endDate))
                                    printf ("\n\tEnd Date must be later than Start Date.\n");

                            } while (checkDate(tasks[i].startDate, tasks[i].endDate));
                            
                            
                        }
                        
                        tasks[i].totalDuration = computeDura(tasks[i].startDate, tasks[i].endDate);

                        if(ask("status")) 
                        {
                            do //loops if task status is not 1 to 3
                            {
                                printf ("\nUpdate Task Status:    [1] Not Started\n"
                                        "                       [2] In Progress\n"
                                        "                       [3] Done\n\t");
                                scanf ("%d", &tasks[i].status);

                                if(tasks[i].status <= 0 || tasks[i].status > 3)
                                    printf ("\n\tInvalid Task Status...\n");

                            } while (tasks[i].status <= 0 || tasks[i].status > 3);
                        }

                        printf("\n\n==== NEW TASK DETAILS ====\n\n");

                        printf("Task ID :               %d\n", tasks[i].taskID);
                        printf("Task Name :             %s\n", tasks[i].name);
                        printf("Task Sequence :         %d\n", tasks[i].sequence);
                        printf("Task Description :      \n\t%s\n\n", tasks[i].description);
                        printf("Project ID :            %d\n", tasks[i].projectID);
                        printf("Task Start date :       %s\n", tasks[i].startDate);
                        printf("Task End date :         %s\n", tasks[i].endDate);
                        printf("Task Total Duration :   %.2f\n", tasks[i].totalDuration);
                        printf("Task Status :           %d\n", tasks[i].status);
                        printf("Assigned Personnel ID : %d\n\n", tasks[i].assignID);

                        do //loops until user choice is not y or n
                        {
                            printf("Do you still wish to make changes [y/n]? ");
                            scanf(" %c", &choice);
                            if(choice != 'y' && choice != 'n')
                                printf("Invalid choice! Try again.\n\n");
                        }while(choice != 'y' && choice != 'n');
                        
                        if(choice == 'n')
                        {
                            a = 1;
                        }
                            
                    } while (a == 0);
                }       

            do // loops until user choice us not y or n
            {
                printf("Do you want to update another task [y/n]? ");
                scanf(" %c", &choice);

                if(choice != 'y' && choice != 'n')
                    printf("Invalid choice! Try again.\n\n");

            } while(choice != 'y' && choice != 'n');

            if(choice == 'n')
            {
                a = 1;
            }

        } while(a == 0);

    return 0;
}

/*
    Function showPersonnel prints all active personnel
    @param personnel[] - struct array with the type of person
    @param i - local variable used in for loop
    @param j - local variable used in for loop
*/
void 
showPersonnel(person personnel[])
{
    int i = 0, j;

    printf ("\n======= Personnel List =======\n\n");

    for (j = 1; j <= 3; j++) //loops until j is greater than 3
    {
        for (i = 0; i < 100; i++) //loops until i reaches 100
        {
            if (personnel[i].personnelID / 1000 == j && personnel[i].active == 1)
            {
                printf ("   %d  %s\n", personnel[i].personnelID, personnel[i].username);
            }
        }
    }
   
    printf ("\n=============================\n");
}

/*
    Function showTasks prints all active tasks
    @param tasks[] - struct array with the type of task
    @param i - local variable used in for loop
*/
void 
showTasks(task tasks[])
{
    int i;

    printf ("\n======= Tasks List =======\n\n");

    for (i = 0; i < 100; i++)
    {
        if (tasks[i].taskID / 1000 == 5 && tasks[i].status != 3)
        {
            printf ("   %d  %s\n", tasks[i].taskID, tasks[i].name);
        }
    }

    printf ("\n=============================\n");
}

/*
    Function showProjects prints all active projects
    @param projects[] - struct array with the type of project
    @param i - local variable used in for loop
*/
void
showProjects(project projects[])
{
    int i;

     printf ("\n======= Projects List =======\n\n");

    for (i = 0; i < 100; i++)
    {
        if (projects[i].projectID / 1000 == 4 && projects[i].status != 3)
        {
            printf ("   %d  %s\n", projects[i].projectID, projects[i].name);
        }
    }

    printf ("\n=============================\n");
}

/*
    Function assignTask assigns a task to a personnel
    @param tasks[] - struct array with the type of task
    @param personnel[] - struct array with the type of person
	@param nID - stores the ID 
    @param i - stores the index number of a specific task in tasks[}
    @param j - used in for loop and stores the index number of a personnel in personnel[]
    @param cChoice - variable for user choice
    @return -1 if user chose to exit on Assign Task, return 0 if user chose Exit in menu
    Pre-condition: tasks[] and personnel[] must have values
*/
int 
assignTask(task tasks[], person personnel[])
{
    int nID;
    int i, j; 
    char cChoice;

    do
    {
        fflush(stdin);

        printf ("\nEnter choice:    [1] Show Task Detail\n"
                "                 [2] Assign Task\n"
                "                 [3] Exit\n\t");
        scanf (" %c", &cChoice);
    
        switch (cChoice)
        {
            case '1':
            {
                printf ("\n======== Task Details =========\n\n");

                showTasks(tasks);

                do
                {
                    printf ("\nEnter Task ID: ");
                    scanf ("%d", &nID);

                    i = checkTID(tasks, nID);

                    if (i != -1)
                    {
                        printf("Task ID :               %d\n", tasks[i].taskID);
                        printf("Task Name :             %s\n", tasks[i].name);
                        printf("Task Sequence :         %d\n", tasks[i].sequence);
                        printf("Task Description :      \n\t%s\n\n", tasks[i].description);
                        printf("Project ID :            %d\n", tasks[i].projectID);
                        printf("Task Start date :       %s\n", tasks[i].startDate);
                        printf("Task End date :         %s\n", tasks[i].endDate);
                        printf("Task Total Duration :   %f\n", tasks[i].totalDuration);
                        printf("Task Status :           %d\n", tasks[i].status);
                        printf("Assigned Personnel ID : %d\n\n", tasks[i].assignID);
                    }

                } while (i == -1);
                break;
            }
            case '2':
            {
                printf ("\n======== Assign Task =========\n\n");

                showTasks(tasks);

                do
                {
                    printf ("Enter Task ID: [0] Exit\n");
                    scanf ("%d", &nID);

                    if(nID == 0)
                    {
                        return -1;
                    }

                    i = checkTID(tasks, nID);

                    if (tasks[i].assignID != 0)
                    {
                        printf ("\n\tTask is already assigned...\n");
                    }

                } while (i == -1);


                printf ("\n     User List:\n\n");
                for (j = 0; j < 100; j++)
                {
                    if (personnel[j].personnelID != 0 && personnel[j].access == 3)
                        printf ("   %d  %s\n", personnel[j].personnelID, personnel[j].name);
                }

                do
                {
                    printf ("\nEnter Personnel ID: [0] Exit\n");
                    scanf ("%d", &nID);

                    if(nID == 0)
                    {
                        return -1;
                    }

                    j = checkPID(personnel, nID);

                    if (j != -1 && personnel[j].access == 3)
                    {
                        tasks[i].assignID = nID;
                        printf ("\n\tPersonnel assigned.\n");
                    }
                    else if (j != -1)
                    {
                        printf ("\n\tPersonnel does not have Access Number of 3...\n");
                    }

                } while (j == -1);
                break;
            }
            case '3':
                printf ("\n\tExiting...");
                break; 
            default:
            {
                printf ("\n\tInvalid Option...");
            }
        }
    } while (cChoice != '3' && cChoice != '2');

    return 0;
}

/*
    Function showDetails prints the details of a specific project
    @param projects[] - struct array with the type of project
    @param i - stores the index number of a project in projects[]
    @param nID - stores the user input for project ID
    @return -1 if user chose to exit, return 0 if end of function
    Pre-condition: projects[] must have values
*/
int 
showDetails(project projects[])
{
    int i = 0;
    int nID;

    showProjects(projects);

    do //loops if i is -1
    {
        printf ("\nEnter Project ID: [0] Exit\n");
        scanf ("%d", &nID);

        if (nID == 0)
        {
            return -1;
        }

        i = checkPrID(projects, nID);

    } while (i == -1);
    
        
    printf ("\n======== Projects Details ========\n\n");
    printf ("Project ID:            %d\n"
            "Project Name:          %s\n"
            "Project Status:        %d\n"
            "Project Completion:    %.2f\n"
            "Project Description:\n"   
            "           %s\n"
            "Assigned Manager ID:   %d\n", 
            projects[i].projectID, projects[i].name, projects[i].status, 
            projects[i].completion, projects[i].description, projects[i].personnelID);
    
    return 0;
}

/*
    Function shwoDelayed prints the details of the delayed task
    @param tasks[] - struct array with the type of task
    @param nDate - current date as an integer
    @param i - local variable used in for loop
    @param a - counter if there is a delayed task
    @param cD[] - stores the current date as a string
*/
void 
showDelayed(task tasks[], int nDate)
{
    int i;
    int a = 0;
    char cD[9];

    itoa(nDate, cD, 10); //converts nDate as a string and stores it in cD, 10 represents Decimal
    
    printf ("\n========== Delayed Task ==========\n\n");

        for(i = 0; i < 100; i++) //loops until i reaches 100
        {
            if(checkDate(cD, tasks[i].endDate) && (tasks[i].status != 3) && tasks[i].taskID != 0) 
            {
                printf("Task ID :               %d\n", tasks[i].taskID);
                printf("Task Name :             %s\n", tasks[i].name);
                printf("Task Sequence :         %d\n", tasks[i].sequence);
                printf("Task Description :      \n\t%s\n\n", tasks[i].description);
                printf("Project ID :            %d\n", tasks[i].projectID);
                printf("Task Start date :       %s\n", tasks[i].startDate);
                printf("Task End date :         %s\n", tasks[i].endDate);
                printf("Task Total Duration :   %f\n", tasks[i].totalDuration);
                printf("Task Status :           %d\n", tasks[i].status);
                printf("Assigned Personnel ID : %d\n\n", tasks[i].assignID);

                a = 1;
            }
        }
        if(a == 0)
            printf("No delayed tasks found! Nice!!!! :)\n\n");
}

/*
    Function runCompletion calculates the completion percentage of a project
	@param projects[] - struct array with the type of project
    @param tasks[] - struct array with the type of task
    @oaram nID - stores the user input nID
    @param i - stores the index number of a project in projects[]
    @param j - local variable used in for loop
    @param fNum - counter for tasks assigned in a project
    @param fDone - counter for assigned task in a project that is marked done
    @return -1 if user chose to exit, return 0 if end of function
*/
int 
runCompletion(project projects[], task tasks[])
{
    int nID;
    int i, j;
    float fNum = 0, fDone = 0;

    printf ("\n======== Run Project Completion ========\n\n");

    showProjects(projects);

    do
    {
        printf ("Enter Project ID: [0] Exit\n");
        scanf ("%d", &nID);

        if (nID == 0)
        {
            return -1;
        }

        i = checkPrID(projects, nID);

    } while (i == -1);
        
    for (j = 0; j < 100; j++)
    {
        if (tasks[j].projectID == projects[i].projectID)
        {
            fNum++;
            
            if (tasks[j].status == 3)
            {
                fDone++;
            }
            else if(tasks[j].status == 2)
            {
                projects[i].status = 2;
            }
            
        }
    }
    
    if (fNum > 0)
    {
        projects[i].completion = (fDone / fNum) * 100;

        printf ("\n\tProject Completion Updated.\n");

        printf ("\n%d  %s\n", projects[i].projectID, projects[i].name);
        printf ("   Completion: %.2f%%", projects[i].completion);

        if(projects[i].completion == 100)
        {
            projects[i].status = 3;
        }

    }
    else
    {
        printf ("\n\tNo Tasks assigned to this project...\n");
    }
    

    return 0;
}

/*
    Function manager contains the Manager Menu
	@param projects[] - struct array with the type of project
	@param tasks[] - struct array with the type of task
    @param personnel[] - struct array with the type of person
    @param cChoice - variable for user choice
    @param nDate - stores the current date as an integer
*/
void
manager(project projects[], task tasks[], person personnel[])
{
    char cChoice;
    int nDate;

    nDate = getDate(); //assigns the current date to nDate

    system("cls"); //clears screen

	do //loops until user choice is 9
    {

        fflush(stdin);

        printf( "\n\n============= MANAGER MENU =============\n"
                "Please enter the number of your option \n\n"
                "\t[1] Add new project\n"
                "\t[2] Add new task\n"
                "\t[3] Update task\n"
                "\t[4] Show personnel list\n"
                "\t[5] Assign task\n"
                "\t[6] Show project details\n"
                "\t[7] Show delayed task\n"
                "\t[8] Run project completion\n"
                "\t[9] Back to main menu\n\t");

        scanf (" %c", &cChoice);

        switch (cChoice)
        {
            case '1': //case for adding project
                addProject(projects, tasks);
                break;
            case '2': //case for adding task
                addTask(tasks, projects);
                break;
            case '3': //case for updating task
                updateTask(tasks, projects);
                break;
            case '4': //case for showing personnel
                showPersonnel(personnel);
                break;
            case '5': //case for assigning task
                assignTask(tasks, personnel);
                break;
            case '6': //case for showing project details 
                showDetails(projects);
                break;
            case '7': //case for showing delayed task/s
                showDelayed(tasks, nDate);
                break;
            case '8': //case for calculating project completion
                runCompletion(projects, tasks);
                break;
            case '9': //case for return to main menu
                printf ("\n\tReturning to Main Menu...\n\n");
                break;
            default:
                printf ("\n\tInvalid Input.\n"); //error message
        }
    } while (cChoice != '9');
}


// USER FUNCTIONS

/*
    Function showToday shows all tasks assigns to the user that is within the current date
    @param tasks[] - struct array with the type of task
    @param ID - personnel ID of user
    @param nDate - current date as an integer
    @param i - local variable used in for loop
    @param nStart - start date of a task as an integer
    @param nEnd - end date of a task as an integer
*/
void 
showToday(task tasks[], int ID, int nDate)
{
    int i;
    int nStart, nEnd;

    printf ("\n========== Task\\s Today ==========\n\n");

    for (i = 0; i < 100; i++) //loops until i reaches 100
    {   
        if (ID == tasks[i].assignID) 
        {
            nStart = atoi(tasks[i].startDate); //converts start date to integer
            nEnd = atoi(tasks[i].endDate); //converts end date to integer

            if (nStart / 10000 <= nDate / 10000 && nEnd / 10000 > nDate / 10000 
                && nStart % 10000 == nDate % 10000 && nEnd % 10000 >= nDate % 10000)
            {
                printf ("   %d     %s\n",tasks[i].taskID, tasks[i].name);
                printf ("    - %s\n\n", tasks[i]. description);
            }
                
        }
    }

}

/*
    Function showAllTask shows all tasks assigned to the user
    @param tasks[] - struct array with the type of task
    @param ID - personnel ID of user
    @param i - local variable used in for loop
*/
void 
showAllTask(task tasks[], int ID)
{
    int i;

    printf ("\n========== All Task\\s ==========\n\n");

    for (i = 0; i < 100; i++) //loops until i reaches 100
    {
        if (ID == tasks[i].assignID) 
        {
            printf ("   %d  %s\n",tasks[i].taskID, tasks[i].name);
        }
    }
}

/*
    Function updateTaskStatus updates the tasks specified by the user
    @param tasks[] - struct array with the type of task
    @param ID - personnel ID of user
    @param nTaskID - variable that contains the chosen task ID 
    @param i - contains the index number of a task in tasks[]
    @return -1 if user choose to exit, return 0 if end of function
*/
int 
updateTaskStatus(task tasks[], int ID)
{
    int nTaskID;
    int i;

    printf ("\n======= Update Task Status =======\n");

      for (i = 0; i < 100; i++) //loops until i reaches 100
    {
        if (ID == tasks[i].assignID) 
        {
            printf ("       %d  %s\n"
                    "Status: %d\n\n",tasks[i].taskID, tasks[i].name, tasks[i].status);
        }
    }

    do //loops if i == -1
    {
        printf ("\nEnter Task ID: [0] Exit\n");
        scanf ("%d", &nTaskID);

        if (nTaskID == 0)
        {
            return -1;
        }

        i = checkTID(tasks, nTaskID);

        if (i != -1)
        {   
            do //loops if input is not 1, 2 or 3
            {
                printf ("\nUpdate Task Status:    [1] Not Started\n"
                        "                       [2] In Progress\n"
                        "                       [3] Done\n\t");
                scanf ("%d", &tasks[i].status);

                if(tasks[i].status <= 0 || tasks[i].status > 3)
                    printf ("\n\tInvalid Task Status...\n");

            } while (tasks[i].status <= 0 || tasks[i].status > 3);
            
            printf ("\nTasks Updated");
        }

        
    } while (i == -1);

    return 0;
}

/*
    Function user contains the user menu
    @param personnel[] - struct array with the type of person
    @param tasks[] - struct array with the type of task
    @param username[] - contains the username of the user
    @param cChoice - contains the user choice
    @param i - used in for loop
    @param nID - contains the user personnel ID
    @param nDate - contains the current date as an integer
*/
void 
user(person personnel[], task tasks[], char username[])
{
    char cChoice;
    int i;
    int nID;
    int nDate;

    for (i = 0; i < 100; i++) //loops until i reaches 100
    {
        if (strcmp(personnel[i].username, username) == 0)
        {
            nID = personnel[i].personnelID;
        }
    }

    nDate = getDate(); //assigns current date to nDate

    system("cls"); //clears screen

    do //loops until user choice is 4
    {

        fflush(stdin);

       printf("\n\n============== USER MENU ===============\n"
            "Please enter the number of your option \n\n"
            "\t[1] Show Today's Task\n"
            "\t[2] Show All Assigned Task\n"
            "\t[3] Update Task Status\n"
            "\t[4] Back to main menu\n\t");

        scanf (" %c", &cChoice);

        switch (cChoice)
        {
            case '1': //case for showing tasks today
                showToday(tasks, nID, nDate);
                break;
            case '2': //case for showing all assigned task
                showAllTask(tasks, nID);
                break;
            case '3': //case for updating task status
                updateTaskStatus(tasks, nID);
                break;
            case '4': //case for returning to main meny
                printf ("\n\tReturning to Main Menu...\n\n");
                break;
            default:
                printf ("\n\tInvalid Input.\n");
        }

    } while (cChoice != '4');
}
