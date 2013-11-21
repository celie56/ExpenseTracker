#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "expense.h"
#include "print.h"
using namespace std;

// This is the testing area for my potential one-day
// financing program that will bring in text journal entries
// and provide some easy calculations
// -Yours Truly,
// Chris Elie

// Todo:
// 1) Allow for comments in my data (example: //October)
//X2) Distinguish between months
//X3) Generate list of types (IN PROGRESS)
// 4) Add comment type for each event (example: sushi)
//X5) Create analysis output
//X6) Truly split date by / (Should be set now)


// Functions Declarations
int current_month();
void print_interface();
bool parse_input(vector<expense> expenses, vector<string> types);
void print_output(string title, double out);
bool type_exists(vector<string> types, string t);
double Spending(vector<expense> e, int month, string type);
// End Functions Declarations

int main(int argc, char *argv[]){
	// Clears command prompt screen
	// Change the command to "clear" to function properly in a linux terminal
	system("cls");

	// Declarations
	ifstream input;		// Input file
	if (argc == 1){		// If no file is specified, the default file is used
		input.open("Expenses.txt");
	}
	else{				// Alternative file is specified
		string temp = argv[1];
		input.open(temp.c_str());
	}
	size_t entries = 0;						// amount of entries
	vector<expense> expenses(entries);		// main data vector
	size_t num_types = 0;					// amount of types
	vector<string> types(num_types);		// list of types
	// End Declarations


	// Parse input to vector here
	string d, a, t;
	while (input.good()){
		input >> d >> a >> t;
		expenses.push_back(expense(d, a, t));
		if (!type_exists(types, t)){
			types.push_back(t);
			num_types++;
		}
		entries++;
	}

	bool done = 0; // holds false until user decides they want to quit
	do{
		print_interface();						// Interface
		done = parse_input(expenses, types);	// I/O
	} while (!done);

	// Closing Statements
	input.close();		// Close input file
	return 0;
}

// Calculation Functions

// ---------------------------------------------------------------
// Calculations
// ---------------------------------------------------------------

double Total_Spending(vector<expense> e){
	double sum = 0;
	for (int i = 0; i < e.size(); i++){
		sum += e[i].getamount();
	}
	return sum;
}

double Spending(vector<expense> e, int month, string type){
	double sum = 0;
	for (int i = 0; i < e.size(); i++){
		if (e[i].getdate().getmonth() == month &&
			e[i].gettype() == type)
		{
			sum += e[i].getamount();
		}
	}
	return sum;
}

// ---------------------------------------------------------------
// Types
// ---------------------------------------------------------------

// Helper for adding type to type list
bool type_exists(vector<string> types, string t){
	for (int i = 0; i < types.size(); i++){
		if (types[i] == t)
			return true;
	}
	return false;
}

void print_types(vector<string> types){
	for (int i = 0; i < types.size(); i++){
		cout << endl << types[i];
	}
	cout << endl;
}

// ---------------------------------------------------------------
// Time Functions
// ---------------------------------------------------------------
// Gets and returns the current month
int current_month(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return 1 + ltm->tm_mon;
}

// ---------------------------------------------------------------
// Interface Functions
// ---------------------------------------------------------------

void analysis(vector<expense> e, vector<string> t){
	cout << endl << "----------------------------" << endl;
	for (int i = 0; i < t.size(); i++){
		print_space(t[i], Spending(e, current_month(), t[i]));
	}
	cout << "----------------------------" << endl << endl;
}

// Manually chose month and type of spending
void select_spending(vector<expense> e){
	cout << endl
		 << "Please enter month then type in form mm type" << endl
		 << ">>";
	int month;
	string type;
	cin >> month >> type;
	print_output(type, Spending(e, month, type));
}

// Main Menu Navigation
bool parse_input(vector<expense> expenses, vector<string> types){
	int i = 0;
	cin >> i;
	switch (i){
	case 1: // Spending To Date
		print_output("Total Spending", Total_Spending(expenses));
		break;
	case 2:
		print_output("Food Spending This Month",
					 Spending(expenses, current_month(), "food"));
		break;
	case 3:
		select_spending(expenses);
		break;
	case 4:
		analysis(expenses, types);
		break;
	case 5: return 1;
		break;
	}
	return 0;
}

// End Interface Functions