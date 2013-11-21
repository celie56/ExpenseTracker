#ifndef PRINT_H
#define PRINT_H

// Prints the main menu
void print_interface(){
	std::cout
		<< "Welcome to my spending data" << endl
		<< "-----------------------------" << endl
		<< "1) Total Spending To Date" << endl
		<< "2) Food this month" << endl
		<< "3) Specific Spending" << endl
		<< "4) Reports" << endl

		<< "5) Exit" << endl
		<< ">> "
		;
}

// Prints output from calculation all pretty-like
void print_output(string title, double out){
	std::cout << endl
		<< "----------------------------" << endl
		<< title << ":" << endl
		<< "  " << out << endl
		<< "----------------------------"
		<< endl << endl;
}

void print_space(string type, double out){
	std::cout << type;
	for (int i = 0; i < 20 - type.length(); i++){
		std::cout << " ";
	}
	std::cout << "$ " << out << endl;
}

#endif