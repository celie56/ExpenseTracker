#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
using namespace std;

// ---------------------------------------------------------------
// Date Class

// Problem: date doesn't work for single digits
// Solution: truly split by /
// THIS HAS BEEN FIXED (HOPEFULLY)

// ---------------------------------------------------------------

class date_c {
	int month, day, year;
	int parse_date(string &d);
public:
	date_c();
	date_c(string d);
	void set_date(string d);
	int getmonth();
	int getday();
	int getyear();
};

// Date Class Functions
date_c::date_c(){
	//should not occur
}
date_c::date_c(string d){
	// really shouldn't occur either
	// if you want to implement this, it should be the same as set_date()
}
void date_c::set_date(string d){
	month = parse_date(d);
	day = parse_date(d);
	year = parse_date(d);
}
int date_c::parse_date(string &d){
	int temp = d.find("/");
	int result = atoi(d.substr(0, temp).c_str());
	d = d.substr(temp + 1, d.length() - temp);
	return result;
}
int date_c::getmonth(){
	return month;
}
int date_c::getday(){
	return day;
}
int date_c::getyear(){
	return year;
}



// ---------------------------------------------------------------
// Expense Class
// ---------------------------------------------------------------

class expense {
	date_c date;
	double amount;
	string type;
public:
	expense();
	expense(string d, string a, string t);
	date_c getdate();
	double getamount();
	string gettype();
};

// Expense Class Functions
expense::expense(){
	// shouldn't happen
}
expense::expense(string d, string a, string t){
	date.set_date(d);
	amount = atof(a.c_str());
	type = t;
}
date_c expense::getdate(){
	return date;
}
double expense::getamount(){
	return amount;
}
string expense::gettype(){
	return type;
}


#endif