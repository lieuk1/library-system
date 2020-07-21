#include <iostream>
#include <limits> // numeric_limits
#include <fstream>
#include "book_h.h"
	// STUDENT HEADER ?
using namespace std;

/***********************
* FUNCTION DECLARATIONS
************************/

void file_book(); // CREATE BOOK AND WRITE TO BINARY FILE

/***********************
*         MAIN
************************/

int main() {

	int opt;
	do {
		cout << "\tLIBRARY COMPUTER SYSTEM\n";
		cout << "\t0. QUIT\n";
		cout << "\t1. SEARCH\n";
		cout << "\t2. CHECK IN\n";
		cout << "\t3. CHECK OUT\n";
		cout << "\t4. ADD (ADMIN)\n";
		cout << "\t5. DELETE (ADMIN)\n";
		cout << "\t6. MODIFY (ADMIN)\n";

		cout << "Enter option : ";
		while(!(cin >> opt) || opt < 0 || opt > 6) {
			cout << "Invalid input. Enter option : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		string password;
		string ADMIN_PASSWORD = "bookish19";

		switch(opt) {
			// QUIT
			case 0:
				break;
			// SEARCH
			case 1:
				break;
			// CHECK IN
			case 2:
				break;
			// CHECK OUT
			case 3:
				break;
			// ADD/DELETE (ADMIN)
			case 4:
				cout << "Enter admin password : ";
				cin.ignore();
				getline(cin, password);

				if(password == ADMIN_PASSWORD)
					file_book();
				else
					cout << "Incorrect password.\n";

				break;
			// DELETE (ADMIN)
			case 5:
				break;
			// MODIFY (ADMIN)
			case 6:
				break;
			// DEFAULT
			default:
				break;
		}

	} while(opt != 0); // DO WHILE END

	return 0;
} // MAIN END

/**********************
* FUNCTION DEFINITIONS
***********************/

void file_book() {
	Book bk;
	bk.create_book();

	ofstream outFS;
	outFS.open("books.dat", ios::binary | ios::app);
	outFS.write(reinterpret_cast<char *> (&bk), sizeof(Book));
	outFS.close();
}