

// struct for Projects
typedef struct 
{
	int projectID;
	char name [40];
	int status;
	float completion;
	char description[100];
	int personnelID;
} project;


// struct for Tasks
typedef struct
{
	int taskID;
	char name[40];
	int sequence;
	char description[100];
	int projectID;
	char startDate[9];
	char endDate[9];
	float totalDuration;
    int status;
	int assignID;
} task;


//struct for Personnels
typedef struct 
{
	int personnelID;
	char name[40];
	char username[40];
	char password [40];
	int active;
	int access;
} person; 


//function declaration for checkPID
int checkPID(person personnel[], int pID );


////function declaration for checkPrID
int checkPrID(project projects[], int prID);


//function declaration for checkTID
int checkTID(task tasks[], int tID);
