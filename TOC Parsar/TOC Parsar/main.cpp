#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

#define EVEN_NUMBER_RULES 10
#define PALINDROME_RULES 27
#define MAX_RULES 

char run_machine(char rules[MAX_RULES][5], string input,int debug_mode,int rule_size);		 //Running the turing machine

char* get_next_rule(char state, char character, char rules[MAX_RULES][5],int rule_size);	//Getting the rules for moving the read/write head of the machine

int debug_mode_menu();																		//Choose the option for displaying turing machine configuration.Integer option is returned

int string_check_menu();																	//Choose the option of checking whether the string is an even number or a palindrome. Integer option is returned

int run_again_menu();																		//Choose to run or not run the turing machine again.Integer option is returned



int main(){

	//Even number transition table 
	char even_number_rules[EVEN_NUMBER_RULES][5]={ {'0','1','1','U','R'},
												   {'0','0','5','U','R'},
												   {'5','1','1','1','R'},
												   {'5','0','1','0','R'},
												   {'5','U','A','U','H'},
												   {'1','1','1','1','R'},
												   {'1','0','1','0','R'},
												   {'1','U','3','U','L'},
												   {'3','1','R','1','H'},
												   {'3','0','A','0','H'}};

	//Palindrome rules transition table
	char palindrome_rules[PALINDROME_RULES][5] ={ {'0','1','1','U','R'},
										    	  {'0','0','4','U','R'},
												  {'0','U','A','U','H'},
												  {'1','1','1','1','R'},
												  {'1','0','1','0','R'},
												  {'1','X','1','X','R'},
												  {'4','1','4','1','R'},
												  {'4','0','4','0','R'},
												  {'4','X','4','X','R'},
												  {'1','U','2','U','L'},
												  {'4','U','5','U','L'},
												  {'2','X','2','X','L'},
												  {'2','1','3','X','L'},
												  {'2','U','A','U','H'},
												  {'2','0','R','0','H'},
												  {'5','0','3','X','L'},
												  {'5','X','5','X','L'},
												  {'5','U','A','U','H'},
												  {'5','1','R','1','H'},
												  {'3','1','3','1','L'},
												  {'3','0','3','0','L'},
												  {'3','X','3','X','L'},
												  {'3','U','6','U','R'},
												  {'6','X','6','X','R'},
												  {'6','1','1','X','R'},
												  {'6','0','4','X','R'},
												  {'6','U','A','U','H'}};	
	
	int run_again=0;

	do{
		string input = "";
		char output = NULL;
		int debug_mode=0;
		int option=0;
		bool string_valid = true;

		system("cls");

		do{

			string_valid=true;

			cout<<"\nEnter String to process, input only 0 s or 1 s: "<<endl<<"=> "; 
			cin>>input;
			input = input.append("U");															 //adding the space at the end of the string to inidcate its end

			for(int i=0;i<input.length();i++){													 //Checking the string to ensure its alphabet is 0s and 1s
			
				if(input[i]!='0'&&input[i]!='1'&& input[i]!='U'){

					cout<<"\nThat is an invalid string, input only 0s or 1s\n";
					string_valid=false;
					break;
					}
			}
		}while(string_valid==false);															//If the string is of the alphabet string_valid!=false therefore stop looping and if not it will exit the for and repeat the loop until the string is valid
		
		 system("cls");
		
		//Choose what validation must be performed- an even number or a palindrome
		  option = string_check_menu();

		  system("cls");

		//Choose to print out the configuration values of the turing machine
		debug_mode = debug_mode_menu();


		switch(option){

			case 1: output = run_machine(even_number_rules,input,debug_mode,EVEN_NUMBER_RULES);
					break;

			case 2: output = run_machine(palindrome_rules,input,debug_mode,PALINDROME_RULES);
					break;

			case 3:	exit(0);

			default: cout<<"Not sure what to do";
					break;
		}
	
		printf("\n\nOutput : \n");

		if(output=='A' && option == 1)
		{
			printf("The machine is in an accepted state, hence the string is an Even Number\n");
		}
		else if(output=='R'&& option == 1)
		{
			printf("The machine is in a rejected state, hence the string is NOT an Even Number\n");
		}
		else if(output=='A' && option == 2)
		{
			printf("The machine is in an accepted state, hence the string is a Palindrome\n");
		}
		else if(output=='R'&& option == 2)
		{
			printf("The machine is in a rejected state, hence the string is NOT a Palindrome\n");
		}

		system("pause");

		 system("cls");

		run_again = run_again_menu();

	}while(run_again != 2);							                                               //User and enter and test as many string as desire
}


int run_again_menu(){ // Gives the user the option of re-entering another string and check whether the string is an even number or a palindrome. Integer option is returned
	
	int option = 0;
	bool string_valid = true;

	do{

		string_valid = true;

		cout<<"\nDo you want to run the machine again?\n";
		cout<<"\n1: Yes";
		cout<<"\n2: No";
		cout<<"\n=> ";

		cin>>option;

		
		if(option!=1&&option!=2)
			string_valid = false;

	}while(string_valid==false);											//loops until 1 0r 2 is choosen

	return option;
}

int string_check_menu()														//Allow the user to choose the option of checking whether the string is an even number or a palindrome. Integer option is returned
{	
	int option = 0;
	bool string_valid = true;

	do{
		string_valid = true;										
		cout<<"\nWhich check do you want the parsar to perform?";
		cout<<"\n1: Even Number";
		cout<<"\n2: Palindrome string";
		cout<<"\n=> ";

		cin>>option;

		if(option!=1&&option!=2)
			string_valid = false;
	}while(string_valid==false);									//loops until 1 0r 2 is choosen

	return option;
}

int debug_mode_menu()												//Allowing the user the option of tracing/displaying the turing machine configuration
{	
	int option = 0;
	bool string_valid = true;

	do{

		string_valid=true;


		cout<<"\nDo you want to turn on debug Mode?";				
		cout<<"\n1: Yes";
		cout<<"\n2: No";
		cout<<"\n=> ";
		
		cin>>option;

		if(option!=1 && option!=2)
			string_valid=false;
		

	}while(string_valid == false);									//loops until 1 0r 2 is choosen

	return option;
}


char run_machine(char rules[MAX_RULES][5], string input,int debug_mode,int rule_size)
{ 

	char state = '0';
	int pointer = 0;			//Use as the index for the input array
	int direction = 1;			//allows the machine to move forward or backward
	char character = NULL;		//Character that the machine read off the input
	char * next_rule = NULL;	//An array that contains information about the next rule


	//Loop forever until function returns
	while(true){

		character = input[pointer]; //Read character from input, assigning one symbol of the string to character  

		//Print machine configuration if debug mode is true
		if(debug_mode==true)
		{
			cout<<"\nCurrent State: "<<state<<"\tHead Position: "<< pointer<<"\n\nTape :";

			for(int i=0;i<input.length();i++){     
				cout<<input[i];
			}

			cout<<"\n";

			Sleep(10);								 
		}


		//Pass the current state and current character and get the next resulting state, next character to be written and the direction to go
		//rules is the transition table & rule_size is the constants declared uptop for even or palindrome 
		next_rule = get_next_rule(state,character,rules,rule_size); 

		//Check if the next state is a Reject or Accept state and end the run machine function.
		if(next_rule[2]=='R'||next_rule[2]=='A')
		{ 
			return next_rule[2]; //return the Reject or Accept state 
		}

		//Determine the next direction, R - right, L - left
		if(next_rule[4]=='R')
			direction=1;
		else if(next_rule[4]=='L')
			direction=-1;
		else if(next_rule[4]=='H')
			direction=0;

		//Assign next state to current state
		state = next_rule[2];

		//Assign next state character
		input[pointer] = next_rule[3];

		//Move head (pointer) in the appropriate direction
		pointer += direction;
	}
}

char* get_next_rule(char state, char character, char rules[MAX_RULES][5],int rule_size)
{

	char * rule = NULL; //Array to store next rule

	//Scan through the given rules to find the next rule base on the current state and character

	for(int i=0;i<rule_size;i++)
	{ 
		if((rules[i][0]==state) &&(rules[i][1]==character))
		{
			rule = rules[i];  
		}
	}

	return rule; //return the first index of the row for the rule(next state, next chracter, direction) to be applied
}
