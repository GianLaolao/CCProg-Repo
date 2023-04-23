/* 
	Description: 
	This file contains all functions that will be used for the Main Function. 
	It is categorized as Functions for Displaying Details, Functions for Monthly Input,
	Functions for Daily Input and Start of Day, and Functions for End Day or End Month.
*/


//	FUNCTIONS FOR DISPLAYING DETAILS


/* This is a function for displaying the current day, total savings and the current balance.
	@param nDay - the day counter
	@param fCurrentBalance - the current balance
	@param fTotalSavings - total savings
*/

void displayDetails (int nDay, float fCurrentBalance,float fTotalSavings)
{
		printf ("\nCurrent Day: 			Day %d"
				"\nTotal Savings: %22.2f"
			 	"\nBalance:	 %20.2f\n", nDay, fTotalSavings, fCurrentBalance);
}


/* This is a function for displaying the current expenses for the day on each category
	@param fFoodnDrink - day expense for Food and Drink	 
	@param fTranspo -  day expense for Transportation
	@param fHealth - day expense for Health
	@param fHouse - day expense for House and Utilities
	@param fLeisure - day expense for Leisure
	@param fSchool - day expense for School
*/

void displayExpenses (float fFoodnDrink, float fTranspo, float fHealth, 
					  float fHouse, float fLeisure, float fSchool)
{
		
	printf ("\n\n-------------EXPENSES BREAKDOWN-------------\n");
	printf ("Food and Drink:		%20.2f\n" 	
			"Transportation:		%20.2f\n"
			"Health:			%20.2f\n"
	 		"House and Utilities:	%20.2f\n"
	 		"Leisure:		%20.2f\n"
		 	"School:			%20.2f\n"
			"---------------------------------------------\n",  
			 fFoodnDrink, fTranspo, fHealth, fHouse, fLeisure, fSchool);
}


/* This function displays the details for the day
	@param fFoodnDrink - day expense for Food and Drink
	@param fTranspo - day expense for Transportation
	@param fHealth - day expense for Health
	@param fHouse - day expense for House and Utilities
	@param fLeisure - day expense for Leisure
	@param fSchool - day expense for School
	@param fExpenses - sum of all expenses on each category for the day 
	@param nDay - the day counter
	@param fCurrentBalance - the current balance
	@param fSavings - total savings for the month
	@param fTotalSavings - overall total savings
*/

void displayDayDetails (float fFoodnDrink, float fTranspo, float fHealth, float fHouse, float fLeisure, float fSchool, 
						float fExpenses, int nDay, float fCurrentBalance, float fSavings, float fTotalSavings)
{
	fFoodnDrink = fFoodnDrink + 300;
	fHouse = fHouse + 4000 * (nDay % 30 == 1);
		
	printf ("\nCurrent Day: 			Day %d"
			"\nCurrent Total Expenses:	%13.2f", nDay, fExpenses);
	displayExpenses(fFoodnDrink, fTranspo, fHealth, fHouse, 
					fLeisure, fSchool);
	printf	("\nTotal Savings: %22.2f"
		     "\nThis Month Savings: %17.2f"
			 "\nCurrent Balance:	 %12.2f\n", fTotalSavings, fSavings,  fCurrentBalance);
}


/*  This function is for checking if the total expense was Within oe Over the budget
	@param fBudget - the allocated budget
	@param fExpense - the total expense
*/

void checkExpenses (float fBudget, float fExpense)
{
	if (fBudget >= fExpense)
	{
		printf ("\t - Within the Budget\n");
	}
	else 
	{
		printf ("\t - Over the Budget\n");
	}
}


/*	This function is for displaying the Budget Report at the last day of the month
	@param pFoodnDrinkB - budget for Food and Drink
	@param pTranspoB - budget for Transportation
	@param pHealthB - budget for Health
	@param pHouseB - budget for House and Utilities
	@param pLeisureB - budget for Leisure 
	@param pSchoolB - budget for School
	@param pFoodnDrinkT - Total expenses for the month for Food and Drink
	@param pTranspoT - Total expenses for the month for Transportation
	@param pHealthT - Total expenses for the month for Health
	@param pHouseT - Total expenses for the month for House and Utilities
	@param pLeisureT - Total expenses for the month for Leisure
	@param pSchoolT - Total expenses for the month for School
	@param pTotalExpenses - total monthly expenses
	@param fCurrentBalance - the current balance
*/

void displayBudgetReport (float fFoodnDrinkB, float fTranspoB, float fHealthB, 
						  float fHouseB, float fLeisureB, float fSchoolB,
						  float fFoodnDrinkT, float fTranspoT, float fHealthT,
						  float fHouseT, float fLeisureT, float fSchoolT,  
						  float fTotalExpenses, float fSavings, float fSavingsB)
{
	
	float fBudget;	//sum of all Budget categories
	
	fBudget = fFoodnDrinkB + fTranspoB + fHealthB + fHouseB + fLeisureB + fSchoolB; 
	
	
	printf ("\n\t\tBudget Report\n"
			"------------------------------------------------------\n");
	printf ("\t\t\tAllocated\t Spent\n");
	printf ("Food and Drink:		%9.2f %12.2f", fFoodnDrinkB, fFoodnDrinkT);
		checkExpenses(fFoodnDrinkB, fFoodnDrinkT);
			 //function for checking wheter the expense is Within or Over the budget
	printf ("Transportation:		%9.2f %12.2f", fTranspoB, fTranspoT);
		checkExpenses(fTranspoB, fTranspoT);
	printf ("Health:			%9.2f %12.2f", fHealthB, fHealthT);
		checkExpenses(fHealthB, fHealthT);
	printf ("House and Utilities:	%9.2f %12.2f", fHouseB, fHouseT);
		checkExpenses(fHouseB, fHouseT);
	printf ("Leisure:		%9.2f %12.2f", fLeisureB, fLeisureT);
		checkExpenses(fLeisureB, fLeisureT);
	printf ("School:			%9.2f %12.2f", fSchoolB, fSchoolT);
		checkExpenses(fSchoolB, fSchoolT);
	printf ("\nTOTAL:			%9.2f %12.2f\n\n", fBudget, fTotalExpenses); //total Budget Allocated and Expenses 
	printf ("\t\t\tAllocated\t Saved\n");
	printf ("Savings:		%9.2f %12.2f\n", fSavings, fSavingsB); //amount of money saved
	
	
	
}


//      fUNCTIONS FOR MONTHLY INPUT


/*	This function is for getting the input for Monthly Allowance, if condition is met, returns that value.
	Precondition: fMonthAllow must be non-negative
	@param nDay - the say counter
	@return fMonthAllow - user input for fMonthAllow
*/
float getMonthlyAllow () 
{
	float fMonthAllow; //input for monthyallow

		do 
		{	
			printf ("\nEnter Monthly Allowance:	"); 
			scanf ("%f", &fMonthAllow); //scans user input
			
			if (fMonthAllow < 13000.00) //Conditional statements to determine if fMonthAllow is < 13000
			{			
				printf ("\tMonthly Allowance must be atleast Php 13000.00"); //Error message
			}
		} while (fMonthAllow < 13000.00); //Loop will continue until condition becomes false	
	
	return fMonthAllow;	//returns the value the user inputs
}


/*	This function is for getting the amount of Allocated Budget in each category. 
	Gets the user input for each category then stores it in a pointer. 
	Precondition: All input are non-negative.
	@param pFoodnDrinkB is the Budget for Food and Drink
	@param pTranspoB is the budget for Transportation
	@param pHealthB is the budget for Health
	@param pHouseB is the budget for House and Utilities
	@param pLeisureB is the budget for Leisure 
	@param pSchoolB is the budget for School
	@param pExpenses is total expenses for the day
	@param fMonthAllow is the Monthly Allowance
*/
void getBudget (float* pFoodnDrinkB, float* pTranspoB, float* pHealthB, float* pHouseB, 
				  float* pLeisureB, float* pSchoolB, float* pExpenses, float fMonthAllow, float* pSavingsB) 
{	
	
	printf ("\n\tAllocate Budget for the Month\n");
	printf ("-----------------------------------------------\n"); 
	
	do
	{	
		do	
		{		
			printf ("\tFood And Drink: \t");
			scanf ("%f", pFoodnDrinkB); //scans user input
				
			if (*pFoodnDrinkB < 9000) //prints error message when input is less than 9000
			{
				printf ("\t\tFood and Drink must be more than Php9000\n"); //error message
			}
			
		} while (*pFoodnDrinkB < 9000); //loops until condition is false
		
		//same case as other categories
		
		do 
		{
			printf ("\tTransportation: \t");
			scanf ("%f", pTranspoB);
			
			if (*pTranspoB < 0)
			{
				printf ("\t\tInvalid Input\n");
			} 
			
		} while (*pTranspoB < 0);
		
		do
		{
			printf ("\tHealth: \t\t");
			scanf ("%f", pHealthB);
			
			if (*pHealthB < 0)
			{
				printf ("\t\tInvalid Input\n"); 
			}
			
		} while (*pHealthB < 0);	 
		
		do
		{	
			printf ("\tHouse and Utilities: \t");
			scanf ("%f", pHouseB);
				
				if (*pHouseB < 4000)
				{
					printf ("\t\tHouse and Utilities must be more than Php4000\n");
						
				}
				
		} while (*pHouseB < 4000);
	
		do
		{
			printf ("\tLeisure: \t\t");
			scanf ("%f", pLeisureB);
			
			if (*pLeisureB < 0)
			{
				printf ("\t\tInvalid Input\n");
				 
			}
			
		} while (*pLeisureB < 0);
		
		do 
		{
			printf ("\tSchool: \t\t");
			scanf ("%f", pSchoolB);
			
			if (*pSchoolB < 0)
			{
				printf ("\t\tInvalid Input\n");
				 
			}
			
		} while (*pSchoolB < 0);
		
			do 
		{
			printf ("\tSavings: \t\t");
			scanf ("%f", pSavingsB);
			
			if (*pSavingsB < 0)
			{
				printf ("\t\tInvalid Input\n");
				 
			}
			
		} while (*pSavingsB < 0);
	
		*pExpenses = *pFoodnDrinkB + *pTranspoB + *pHealthB + *pHouseB + *pLeisureB + *pSchoolB + *pSavingsB;
		//adds each category
		
		if (fMonthAllow != *pExpenses) //checks if Monthly Allowance equal to Expenses
		{
			printf ("\n----------Budget and Savings must be Equal to Monthly Allowance-------\n\n"); 
			//error message
		}    
		
		
	} while (fMonthAllow != *pExpenses); //loops while pExpenses is greater than fMonthAllw
}


//    FUNCTIONS FOR DAILY INPUT / START OF DAY


/*	This function initializes the variables for the 1st day of each month and start of next day.
	Variables that resets every month will have a value of 0.
	@param pFoodnDrinkT - Total expenses for the month for Food and Drink
	@param pTranspoT - Total expenses for the month for Transportation
	@param pHealthT - Total expenses for the month for Health
	@param pHouseT - Total expenses for the month for House and Utilities
	@param pLeisureT - Total expenses for the month for Leisure
	@param pSchoolT - Total expenses for the month for School
	@param pFoodnDrink - Daily expense for Food and Drink
	@param pTranspo - Daily expense for Transportation
	@param pHealth - Daily expense for Health
	@param pHouse - Daily expense for House and Utilities
	@param pLeisure - Daily expense for Leisure
	@param pSchool - Daily expense for School
	@param pTotalExpenses - total expense for the month
	@param pCurrentBalance - current balance for the day
	@param fMonthAllow - Monthly Allowance
	@param pSavings - savings for the month
	@param nDay - day counter
*/
void startDay (float* pFoodnDrinkT, float* pTranspoT, float* pHealthT, float* pHouseT, 
				float* pLeisureT, float* pSchoolT, float* pFoodnDrink, float* pTranspo, 
				float* pHealth, float* pHouse, float* pLeisure, float* pSchool, 
				float* pTotalExpenses, float* pExpenses, float* pCurrentBalance, 
				float fMonthAllow, float* pSavings, int nDay) 
{
	
	if (nDay % 30 == 1) //will execute if its the first day of the month
	{
	*pFoodnDrinkT = *pHouseT = *pTranspoT = *pHealthT =  *pLeisureT = *pSchoolT  = 0.00;
		//resets Total expenses for each category to 0
	*pTotalExpenses = 0.00;
		//resets Total expenses (Monthly) to 0
	*pSavings = 0.00;
		//resets Monthly savings to 0;
	*pCurrentBalance = *pCurrentBalance + fMonthAllow;
		//adds the Monthly Allowance to the Current balance
	*pHouseT += 4000;
		//adds 4000 to the House Total expense (Monthly)
	}
	
	*pFoodnDrink = *pTranspo = *pHealth = *pHouse = *pLeisure = *pSchool = 0; 
		//resets Daily expense to 0
	*pExpenses = 300 + (4000 * (nDay % 30 == 1));
		//adds 300 and adds 4000 if its the first day of the month
	*pFoodnDrinkT += 300;
		//adds 300 to the total expense for Food and Drink
	*pCurrentBalance = *pCurrentBalance - *pExpenses;
		//deducts expenses to the Current Balance
	
}			


/* This function is for adding expenses for a chosen category. User will input a choice representing a cateogry.
	Then the user will input a value, if it displays no error message, the value is stored. 
	Precondition: Amount inputs are Postive or greater than 0
	@param pFoodnDrink - added expense for Food and Drink 
	@param pTranspo - added expense for Transportation
	@param pHealth - added expense for Health
	@param pHouse - added expense for House and Utilities
	@param pLeisure - added expense for Leisure
	@param pSchool - added expense for School
	@param pExpenses - total daily expense + expense on each category
	@param pCurrentBalance - current balance - expense on each category
*/
void addExpense (float* pFoodnDrink, float* pTranspo, float* pHealth, float* pHouse, 
				float* pLeisure, float* pSchool, float* pExpenses, float* pCurrentBalance)
{
	char cChoice; //users category choice
	float fExpenses = 0; //sum of additional expenses in all categories
	float food, transpo, health, house, leisure, school; //amount inputs
	
	food = transpo = health = house = leisure = school = 0; //initializes input to 0
	
	do
	{	
		do
		{	
			printf ("\nCurrent Balance:		%12.2f", *pCurrentBalance); 
			displayExpenses(food, transpo, health, house, leisure, school); //displays input expenses in each categories
			printf ("Total:			%20.2f\n", fExpenses);
			
			printf ("\nChoose an Option:\n"
					"\t0 - Exit || A - Add Food || B - Add Transpo || C - Add Health\n"
					"\tD - Add House || E - Add Leisure || F - Add School\n");
			scanf (" %c", &cChoice); //scans input
			
			switch (cChoice)
			{	
				case '0': //exits function
				{
					printf ("Exit Add Expense...\n");
					break;
				}
				case 'A': case 'a': 
				{
					do
					{
					printf ("\nFOOD AND DRINK\n"
							"Add Amount: "); 
					scanf ("%f", &food); //scans amount input
					
						if (food < 0 || food > *pCurrentBalance) //prints error message if input is negative or greater than the current balance
						{
							printf ("\tInvalid Input\n"); //error message
						}
					} while (food < 0 || food > *pCurrentBalance);
					
					break;
				}
				case 'B': case 'b':
				{
					do
					{
					printf ("\nTRANSPORTATION\n"
						"Add Amount: ");
					scanf ("%f", &transpo);	
					
						if (transpo < 0 || transpo > *pCurrentBalance)
						{
							printf ("\tInvalid Input\n");
						}
					} while (transpo < 0 || transpo > *pCurrentBalance);
					break;
				}
				case 'C': case 'c':
				{
					do
					{
					printf ("\nHEALTH\n"
						"Add Amount: ");
					scanf ("%f", &health);
					
						if (health < 0 || health > *pCurrentBalance)
						{
							printf ("\tInvalid Input\n");
						}
					} while (health < 0 || health > *pCurrentBalance);	 
					break;
				}
				case 'D': case 'd':
				{
					do 
					{
					printf ("\nHOUSE AND UTILITIES\n"
						"Add Amount: ");
					scanf ("%f", &house);	
					
						if (house < 0 || house > *pCurrentBalance) 
						{
							printf ("\tInvalid Input\n");
						}
					} while (house < 0 || house > *pCurrentBalance);
					break;
				}
				case 'E': case 'e':
				{
					do
					{
					printf ("\nLEISURE\n"
						"Add Amount: ");
					scanf ("%f", &leisure);	
					
						if (leisure < 0 || leisure > *pCurrentBalance)
						{
							printf ("\tInvalid Input\n");
						}
					} while (leisure < 0 || leisure > *pCurrentBalance);
					break;		
				}
				case 'F': case 'f':
				{
					do
					{
					printf ("\nSCHOOL\n"
						"Add Amount: ");
					scanf ("%f", &school);	
					
						if (school < 0 || school > *pCurrentBalance)
						{
							printf ("\tInvalid Input\n");
						}
					} while (school < 0 || school > *pCurrentBalance);
					break;
				}
				default: //prints error message if input is not 0 or A - F
				{
					printf ("\n----------------INVALID OPTION------------------\n"); //error message
				}
			}
			
			fExpenses = food + transpo + health + house + leisure + school;
			//sums the amount of all category
		} while (cChoice != '0');
		
		if (fExpenses > *pCurrentBalance) //error message
		{
			printf ("\nINVALID AMOUNT\n");
			food = transpo = health = house = leisure = school = 0;
			//resets inputs to 0
		}
	
	} while (fExpenses > *pCurrentBalance);	//repeats until condition is false

	*pFoodnDrink += food; //adds the user input for each category to the day expense of same category
	*pTranspo += transpo; 
	*pHealth += health; 
	*pHouse += house; 
	*pLeisure += leisure;
	*pSchool += school;
				
	*pExpenses = *pExpenses + fExpenses; //adds fExpenses to current Daily expenses		
	*pCurrentBalance -= fExpenses; //subtracts total added expense to current balance			
}

/* 	This function is for adding savings for the month and Total Savings.
	The user inputs the amount they want to save.
	Precondition: Amount input is Postive or greater than 0
	@param pSavings - monthly savings
	@param pTotalSavings - the total savings, does not reset monthly
	@param pCurrentBalance - basis for the amount of savings
*/

void addSavings (float* pSavings, float* pTotalSavings, float* pCurrentBalance)
{
	float savings; //amount input
	
	printf ("\nCurrent Balance:  %.2f\n", *pCurrentBalance); 
	
	do	
	{
		printf ("\nAdd Anount to Save: ");
		scanf ("%f", &savings); //gets user input
		
		if (savings < 0 || savings > *pCurrentBalance) //prints error message if input is negative or greater than current balance
		{
			printf ("\tINVALID AMOUNT!"); //error message
		}
	} while (savings > *pCurrentBalance || savings < 0);//loops if input is negative or greater than current balance
	
	*pSavings += savings; //adds savings to pSavings (monthly savings)
	*pCurrentBalance = *pCurrentBalance - savings; //subtracts savings from fCurrentBalance
	*pTotalSavings += savings; //adds savings to pTotalSavings
}

/*  This is a function for using the total savings. 
	The user will input the amount they want to add to their current balance.
	Precondition: Amount input is Positive or greater than 0
	@param pTotalSavings - the total savings of the user
	@param pCurrentBalance - the current balance
	@param pSavings - savings for the month
*/
void useSavings (float* pTotalSavings, float* pCurrentBalance, float* pSavings)
{
	float useSavings; //amount input
	 
	printf ("\nCurrent Savings:	%.2f\n", *pTotalSavings);
	
	do
	{
		printf ("\nAdd Amount to Use:	"); 
		scanf ("%f", &useSavings); //gets user input
	
		if (useSavings > *pTotalSavings || useSavings < 0) //prints error message if input is negative or greater than total savings
		{
			printf ("\tINVALID AMOUNT!"); //error message
		}
	} while (useSavings > *pTotalSavings || useSavings < 0);//loops if input is negative or greater than total savings
	
	*pTotalSavings -= useSavings; //subtracts the amount from total savings
	*pSavings -= useSavings; //subtracts amount for counter for savings for the month
	*pCurrentBalance += useSavings; //adds the used savings to current balance
}


//      FUNCTIONS FOR DAY END OR MONTH END


/*  This function is for ending the day. 
	Adds the daily expenses (fExpenses) to the monthly expenses (pTotalExpenses)
	@param fCurrentBalance - the current balance
	@param pTotalExpenses - total monthly expenses
	@param fExpenses - daily expenses
	@param pFoodnDrinkT - Total expenses for the month for Food and Drink
	@param pTranspoT - Total expenses for the month for Transportation
	@param pHealthT - Total expenses for the month for Health
	@param pHouseT - Total expenses for the month for House and Utilities
	@param pLeisureT - Total expenses for the month for Leisure
	@param pSchoolT - Total expenses for the month for School
	@return 1 if there is enough money for the next day
	@return 0 if there is not enough money for the next day
*/
int endDay (float fCurrentBalance, float* pTotalExpenses, float fExpenses, float* pFoodnDrinkT, 
			float* pTranspoT, float* pHealthT, float* pHouseT, float* pLeisureT, float* pSchoolT, 
			float fFoodnDrink, float fTranspo, float fHealth, float fHouse, float fLeisure, float fSchool, int nDay)
{
	*pTotalExpenses += fExpenses; //adds the daily expense to the monthly expense
	
	*pFoodnDrinkT += fFoodnDrink; //adds additional expense to total monthly expense for each category
	*pTranspoT += fTranspo; 
	*pHealthT += fHealth;
	*pHouseT += fHouse;
	*pLeisureT += fLeisure;
	*pSchoolT += fSchool;
	
	if (nDay % 30 != 0) //if its not the last day of the month
	{
		return fCurrentBalance >= 300; //returns 1 or 0
	}
	else 
	{
		return fCurrentBalance >= 0; //returns 1 or 0
	} 
}

/* 	This function is for ending the month, updates the day counter to the next month, 
	deducts 300 for each days passed and prints on how many days has passed.
	@param pDay - the day counter which will be updated to the next month
	@param pCurrentBalance - the current balance
	@param pFoodnDrinkT - total expense for Food and Drink
	@param fExpenses - total additional expenses from each category
	@param pTotalExpenses - total monthly expenses
	@param fExpenses - total daily expense
	@param pFoodnDrinkT - Total expenses for the month for Food and Drink 
	@param pTranspoT - Total expenses for the month for Transportation
	@param pHealthT - Total expenses for the month for Health
	@param pHouseT - Total expenses for the month for House and Utilities
	@param pLeisureT - Total expenses for the month for Leisure
	@param pSchoolT - Total expenses for the month for School
	@return 1 if the current balance is greater than or equal to 0
	@return 0 if current balance is less than 0 
*/
int endMonth (int* pDay, float* pCurrentBalance, float* pTotalExpenses, float fExpenses, float* pFoodnDrinkT, 
			  float* pTranspoT, float* pHealthT, float* pHouseT, float* pLeisureT, float* pSchoolT, 
			  float fFoodnDrink, float fTranspo, float fHealth, float fHouse, float fLeisure, float fSchool)
{	
	int i; //stores value for days passed
					 
	for (i = 0; (*pDay + i) % 30 != 0 && *pCurrentBalance >= 0; i++) 
	//keeps looping until pDay + i is equal to the end of the month (30, 60...)
	//or the current balance is less than 0
	{ 
		*pCurrentBalance -= 300; //subtracts 300 
	}

		*pDay += i; //adds the days passed to current day
	
	printf ("\n----------------%d DAYS has Passed----------------\n", i); //prints how many days has passed
	
			*pFoodnDrinkT += 300 * i + fFoodnDrink; //adds 300 * days passed plus additional expense for food and drink to total monthly expense
			*pTranspoT += fTranspo; //adds additional expense to total monthly expense for each category
			*pHealthT += fHealth;
			*pHouseT += fHouse;
			*pLeisureT += fLeisure;
			*pSchoolT += fSchool;
			
		*pTotalExpenses += 300 * i + fExpenses; //adds daily food expense times pass and daily expense to total monthly expense

	return (*pCurrentBalance >= 0); //returns 1 or 0
}



