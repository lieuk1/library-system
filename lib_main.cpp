#include <iostream>
#include <limits> // numeric_limits
#include "book_h.h"
	// STUDENT HEADER ?
using namespace std;

/*
Enter system as student or admin
Student
	Search books
	Check in/out books
Admin
	Add/delete books
	Modify books
*/

int main() {

	int opt;
	do {
		cout << "\tLIBRARY COMPUTER SYSTEM\n";
		cout << "\t0. QUIT\n";
		cout << "\t1. SEARCH\n";
		cout << "\t2. CHECK IN\n";
		cout << "\t3. CHECK OUT\n";
		cout << "\t4. ADD/DELETE (ADMIN)\n";
		cout << "\t5. MODIFY (ADMIN)\n";

			// EDIT ERROR CHECK
		while(cout << "Enter : " && (!(cin >> opt) || (opt != 0 && opt != 1 && opt != 2))) {
			cout << "-> Invalid input <-\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// QUIT
		if(opt == 0) {
			break;
		}

		else if(opt == 1) {

		}

		else if(opt == 2) {

		}
	} while(opt != 0);

	return 0;
} // MAIN END