/*
	Description:			This program is made for aiding the user to Budget their 
							Monthly Allowance on their everyday expenses.
	Programmed By:			Gian Chill A. Laolao	CS-ST S20A
	Last Modified:			December 4, 2022
	Version:				V1.0 
	Acknowledgements:		https://en.cppreference.com/w/c
*/

#include <stdio.h>
#include "BudgetFunc.c" //includes the file for User defined Functions

int main()
{
	
	int nDay = 0; //day counter
	int nExit = 1; //program end condition
	char cChoice; //user choice 
	float fCurrentBalance = 0; //current balance
	float fMonthAllow; //monthlyallowance
	float fExpenses = 0, fTotalExpenses; //expenses for the day and total expenses
	float fFoodnDrinkB, fTranspoB, fHealthB, fHouseB, fLeisureB, fSchoolB; //Budget for each category
	float fFoodnDrinkT, fTranspoT, fHealthT, fHouseT, fLeisureT, fSchoolT; //total expense for each category
	float fFoodnDrink, fTranspo, fHealth, fHouse, fLeisure, fSchool; //day expense for each category
	float fSavings, fSavingsB, fTotalSavings = 0; //monthly savings, alloted savings and total savings
	
	
	printf ("\t\tBUDGET 101 - a Budgetting Program\n\n"); //introduction
	
	
	/*	Calls the getMonthAllow Function that has the code for getting
				the user input for MonthlyAllowance. The returned value is then assigned to 
				the variable fMonthAllow. 
	*/
		fMonthAllow = getMonthlyAllow ();
		
	do
	{		
	
		nDay++; //adds 1 to the day counter
	
		if (nDay % 30 == 1) //executes code block if its the first day of the month
		{	
			//	Passes the address for each Budget Category. 
			getBudget (&fFoodnDrinkB, &fTranspoB, &fHealthB, &fHouseB, 
				 	&fLeisureB, &fSchoolB, &fExpenses, fMonthAllow, &fSavingsB);
		}	
	
		startDay(&fFoodnDrinkT, &fTranspoT, &fHealthT, &fHouseT, &fLeisureT, &fSchoolT, //initializes values for start of each day
				&fFoodnDrink, &fTranspo, &fHealth, &fHouse, &fLeisure, &fSchool,
				&fTotalExpenses, &fExpenses, &fCurrentBalance, fMonthAllow, &fSavings, nDay);
	
		do
		{
			displayDayDetails(fFoodnDrink, fTranspo, fHealth, fHouse,  fLeisure, fSchool, //displays details
						      fExpenses, nDay, fCurrentBalance, fSavings, fTotalSavings); 
		
			printf ("\nCHOOSE AN OPTION:\n"
					"\t0 - Exit Program || 1 - Add Expense || 2 - Add Savings || 3 - Use Savings || 4 - End Day or Month\n");	
			scanf (" %c", &cChoice); //scans user choice
		
			switch (cChoice)
			{
				case '0': //case for exiting the program
				{
					printf ("\n\tExiting Program...\n"); 
				
					nExit = 0; //exits program if nExit = 0
				
					break;		
				}
				case '1': //case for Adding Expense
				{			
					addExpense (&fFoodnDrink, &fTranspo, &fHealth, &fHouse,    //gets additional expense on chosen category
								&fLeisure, &fSchool, &fExpenses, &fCurrentBalance);				
					break;
				}
				case '2': //case for Adding Savings
				{	
					addSavings (&fSavings, &fTotalSavings, &fCurrentBalance); //adds savings
					break;
				}
				case '3': //case for Using Savings
				{
					useSavings (&fTotalSavings, &fCurrentBalance, &fSavings); //savings that will be used
					break;
				}
				case '4': //case for ending the Day or ending the month
				{
					do
					{
						printf ("	\nEND DAY or END MONTH:\n"
								"\t0 - Return to Options || 1 - End Day || 2 - End Month\n");
						scanf (" %c", &cChoice); //scans user choice
						
						switch (cChoice)
						{
						case '0': //case for returning for user options
							{
								printf ("Returning to Options... \n");
								cChoice++;
								break;
							}
						case '1': //case for ending the Day
							{
							
								nExit = endDay(fCurrentBalance, &fTotalExpenses, fExpenses, &fFoodnDrinkT, 
								   				&fTranspoT, &fHealthT, &fHouseT, &fLeisureT, &fSchoolT, 	
								   				fFoodnDrink, fTranspo, fHealth, fHouse, fLeisure, fSchool, nDay); //functions for ending the day
								//nExit is 0 if Current Balance is less than 300 and it is not the last day of the month, else value is 1
								if (nExit == 1)
								{
									displayDetails (nDay, fCurrentBalance, fTotalSavings);
								
									printf ("\n\n----------------END OF DAY %d----------------\n", nDay);
			
									if (nDay % 30 == 0)
									{
										displayBudgetReport(fFoodnDrinkB, fTranspoB, fHealthB, fHouseB, fLeisureB, fSchoolB,
															fFoodnDrinkT, fTranspoT, fHealthT,  fHouseT, fLeisureT, fSchoolT,
															fTotalExpenses, fSavings, fSavingsB);	//displays budget report	
															
										printf ("\n-----------------NEW MONTH-------------------\n");
										printf("Allowance: %9.2f", fMonthAllow); //prints the amount of allowance
									}
								
								}
								else //prints end program message
								{
									printf ("\n\tNo Money for the Month. Exiting Program...\n");
								}
								
								cChoice = '0'; //exit do while loop, starts next day
								
								break;
							}
						case '2':
							{
								nExit = endMonth(&nDay, &fCurrentBalance, &fTotalExpenses, fExpenses, &fFoodnDrinkT,  //function for ending the month
								   		   		 &fTranspoT, &fHealthT, &fHouseT, &fLeisureT, &fSchoolT, 	
								  		     	 fFoodnDrink, fTranspo, fHealth, fHouse, fLeisure, fSchool);
									//returns the value for nExit
								if (nExit == 1) //if nExit is 1
								{
									displayDetails (nDay, fCurrentBalance, fTotalSavings); //displays details
										
									displayBudgetReport(fFoodnDrinkB, fTranspoB, fHealthB, fHouseB, fLeisureB, fSchoolB,
															fFoodnDrinkT, fTranspoT, fHealthT, fHouseT, fLeisureT, fSchoolT,
															fTotalExpenses, fSavings, fSavingsB); //displays the budget report
								
									printf ("\n-----------------NEW MONTH-------------------\n"); 
									printf("\nAllowance: %9.2f\n", fMonthAllow); //prints the amount of allowance
							
								}
								else //prints end program message
								{	
									printf ("\n\tNo Money for the Month. Exiting Program...\n");
								}
								
								cChoice = '0'; //exit do while loop, starts next month
								
								break;
							}
						default: //prints error message
							{
								printf ("\n----------------INVALID OPTION------------------\n");
							}
						}
						
					} while (cChoice != '0' && cChoice != '1' && cChoice != '2'); //loops until the choice is one of the given cases 
					
					
					break;
				}
				default: //prints error message
				{ 
					printf ("\n----------------INVALID OPTION------------------\n");
				}
			}
		
		} while (cChoice != '0'); //loops until the choice is not 0
	
	} while (nExit != 0); 
	//loops until user choice is not "Exit Program" or nExit value is not 0
	
	printf ("\n\t\tProgram Exit\n"); //exit statement	
	
return 0;
}
