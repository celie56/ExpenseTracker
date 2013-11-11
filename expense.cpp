#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

// Todo:
// 1) Allow for comments in my data (example: //October)
// 2) Distinguish between months
// 3) Generate list of types
// 4) Add comment type for each event (example: sushi)


// Functions Declarations
double Total_Spending(vector<string> a);
double Total_Food_Spending(vector<string> a, vector<string> t);
double Spending_in_Month(vector<string> a, vector<string> d, int month);
int current_month();
int get_month(string date);
void print_total_food(vector<string> a, vector<string> t);
void print_total_spending(vector<string> amount);
void print_interface();
bool parse_input(vector<string> date, vector<string> amount, vector<string> type);
void print_output(string title, double out);



// All done with functions on functions

int main(int argc, char *argv[]){
	// This is the testing area for my potential one-day
	// financing program that will bring in text journal entries
	// and provide some easy calculations
	// -Yours Truly,
	// Chris Elie

	// Clears command prompt screen
	system("cls");

	// Declarations
	ifstream input;
	// If no file is specified, the default file is used
	if (argc == 1){
		input.open("Expenses.txt");
	}
	// Alternative file is specified
	else{
		string temp = argv[1];
		input.open(temp.c_str());
	}
	string i;
	size_t entries = 0;
	// End Declarations
	


	// Big Data Babies
	vector<string> date(entries);		// Holds the date in the form mm/dd/yy
	vector<string> amount(entries);		// Holds the amount of the expense
	vector<string> type(entries);		// Holds the category of expense



	// Parse input to vector here
	string d, a, t;
	while (input.good()){
		input >> d >> a >> t;
		date.push_back(d);
		amount.push_back(a);
		type.push_back(t);	
		entries++;
	}

	bool done = 0; // holds false until user decides they want to quit
	do{
		// Interface
		print_interface();

		// I/O
		done = parse_input(date, amount, type);
	} while (!done);
	// Closing Statements
	input.close();
	return 0;
}

// Functions on Functions
// All function definitions are to go down here
// They should all be declared at the top of the page

// Calculation Functions

// Will sum the amount of spending in vector a
double Total_Spending(vector<string> a){
	double sum = 0;
	for (int i = 0; i < a.size(); i++){
		sum += atof(a[i].c_str());
	}
	return sum;
}
// Will sum the total amount of spending on food
double Total_Food_Spending(vector<string> a, vector<string> t){
	double sum = 0;
	for (int i = 0; i < a.size(); i++){
		if (t[i] == "food"){
			sum += atof(a[i].c_str());
		}
	}
	return sum;
}
// Gets and returns the current month
int current_month(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return 1 + ltm->tm_mon;
}
// Takes the string in the format mm/dd/yy and returns the month in 1-12
int get_month(string date){
	return atoi(date.substr(0, date.find("/")).c_str());
}
// Sums the amount of spending during given month
double Spending_in_Month(vector<string> a, vector<string> d, int month){
	double sum = 0;
	for (int i = 0; i < a.size(); i++){
		if (get_month(d[i]) == month){
			sum += atof(a[i].c_str());
		}
	}
	return sum;
}


// Printing Functions

// prints total amount spent on food
void print_total_food(vector<string> a, vector<string> t){
	print_output("Total Food", Total_Food_Spending(a, t));
}
// Prints the total spending to date
void print_total_spending(vector<string> amount){
	print_output("Total Spending", Total_Spending(amount));
}
// Prints the total spending this month
void print_spending_this_month(vector<string> amount, vector<string> date){
	print_output("Spending This Month", Spending_in_Month(amount, date, current_month()));
}


// Interface Functions

// Prints output from calculation all pretty-like
void print_output(string title, double out){
	cout << endl 
		 << "----------------------------" << endl
		 << title << ":" << endl
		 << "  " << out << endl
		 << "----------------------------"
		 << endl << endl ;
}
// Prints the main menu
void print_interface(){
	cout 
		<< "Welcome to my spending data" << endl
		<< "-----------------------------" << endl
		<< "1) Total Spending To Date" << endl
		<< "2) Total food spending to date" << endl
		<< "3) Total Spending This Month" << endl

		<< "5) Exit" << endl
		<< ">> "
		;
}
// Brings in the data and figures out what the user wants
bool parse_input(vector<string> date, vector<string> amount, vector<string> type){
	int i = 0;
	cin >> i;
	switch (i){
	case 1:
		print_total_spending(amount);
		break;
	case 2:
		print_total_food(amount, type);
		break;
	case 3:
		print_spending_this_month(amount, date);
		break;
	case 5: return 1;
		break;
	}
	return 0;
}