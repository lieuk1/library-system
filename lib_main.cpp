#include <iostream>
#include <limits> // numeric_limits
#include <fstream>
#include "book_h.h"
	// STUDENT HEADER ?
using namespace std;

/***********************
* FUNCTION DECLARATIONS
************************/

void search_bk(string title); // SEARCH FOR BOOK FROM FILE
void check_in_out(int option, long long isbn); // UPDATE BOOK STATUS IN FILE
void file_bk(); // CREATE BOOK AND WRITE TO FILE
void delete_bk(long long isbn); // DELETE BOOK FROM FILE


/***********************
*         MAIN
************************/

int main() {

	int opt;
	do {
		cout << "LIBRARY COMPUTER SYSTEM\n";
		cout << "\t0. QUIT\n";
		cout << "\t1. SEARCH\n";	// ADD OPTION TO SEARCH BY ?
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

		string title;
		long long isbn;

		switch(opt) {
			// QUIT
			case 0:
				break;
			// SEARCH
			case 1:
				cout << "Enter title : ";
				cin.ignore();
				getline(cin, title);
				cout << "\n";

				search_bk(title);

				break;
			// CHECK IN
			case 2:
				cout << "Enter book ISBN (13 digits) : ";
				while(!(cin >> isbn)) {
					cout << "Invalid input. Enter book ISBN : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				check_in_out(1, isbn);

				break;
			// CHECK OUT
			case 3:
				cout << "Enter book ISBN (13 digits) : ";
				while(!(cin >> isbn)) {
					cout << "Invalid input. Enter book ISBN : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				check_in_out(2, isbn);

				break;
			// ADD (ADMIN)
			case 4:
				cout << "Enter admin password : ";
				cin.ignore();
				getline(cin, password);

				if(password == ADMIN_PASSWORD) {
					file_bk();
					cout << "Book added.\n\n";
				}
				else {
					cout << "Incorrect password.\n\n";
				}

				break;
			// DELETE (ADMIN)
			case 5:
				cout << "Enter admin password : ";
				cin.ignore();
				getline(cin, password);

				if(password == ADMIN_PASSWORD) {
					cout << "Enter book ISBN (13 digits) : ";
					while(!(cin >> isbn)) {
						cout << "Invalid input. Enter book ISBN : ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					
					delete_bk(isbn);
					cout << "\n";
				}
				else {
					cout << "Incorrect password.\n\n";
				}

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

void search_bk(string title) {
	Book bk;
	bool found = false;

	ifstream inFS;
	inFS.open("books.dat", ios::binary);
	if(!inFS) {
		cout << "File could not open.\n";
		return;
	}

	while(inFS.read(reinterpret_cast<char *> (&bk), sizeof(Book))) {
		// IF TITLE FOUND, PRINT BOOK INFORMATIOn
		if(bk.get_title() == title) {
			found = true;
			bk.show_book();
			cout << "\n";
		}
	}

	inFS.close();

	if(!found)
		cout << "No results found.\n\n";
}

void check_in_out(int option, long long isbn) {
	Book bk;
	bool found = false;

	fstream File;
	File.open("books.dat", ios::binary | ios::in | ios::out);
	if(!File) {
		cout << "File could not open.\n";
		return;
	}

	while(!File.eof() && !found) {

		File.read(reinterpret_cast<char *> (&bk), sizeof(Book));

		if(bk.get_isbn() == isbn) {
			found = true;
			
			// CHECK IN
			if(option == 1) {
				cout << "Checking in book... ";
				bk.set_status('A');
				cout << "\nBook checked in.\n\n";
			}
			// CHECK OUT
			else if(option == 2) {
				cout << "Checking out book... ";
				bk.set_status('U');
				cout << "\nBook checked out.\n\n";
			}
		}

		// MODIFY BOOK STATUS IN FILE
		int pos = (-1)*static_cast<int>(sizeof(Book));
		File.seekp(pos, ios::cur);
		File.write(reinterpret_cast<char *> (&bk), sizeof(Book));
		
	} // WHILE LOOP END

	File.close();

	if(!found)
		cout << "\nNo results found.\n\n";

}

void file_bk() {
	Book bk;
	bk.create_book();

	ofstream outFS;
	outFS.open("books.dat", ios::binary | ios::app);
	outFS.write(reinterpret_cast<char *> (&bk), sizeof(Book));
	outFS.close();
}

	// ADD CONFIRMATION PROMPT
void delete_bk(long long isbn) {
	Book bk;
	bool found = false;

	ifstream inFS;
	ofstream outFS;

	inFS.open("books.dat", ios::binary);
	if(!inFS) {
		cout << "File could not open.\n";
		return;
	}

	outFS.open("temp.dat", ios::binary);

	while(inFS.read(reinterpret_cast<char *> (&bk), sizeof(Book))) {
		if(bk.get_isbn() != isbn)
			outFS.write(reinterpret_cast<char *> (&bk), sizeof(Book));
		else if(bk.get_isbn() == isbn)
			found = true;
	}

	inFS.close();
	outFS.close();

	if(!found)
		cout << "\nNo results found.\n";

	// REMOVE OLD FILE AND RENAME NEW FILE NOT INCLUDING GIVEN BOOK
	remove("books.dat");
	rename("temp.dat", "books.dat");
}