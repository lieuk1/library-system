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
void modify_bk(int option, long long isbn); // MODIFY BOOK INFO


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
				cout << "Enter admin password : ";
				cin.ignore();
				getline(cin, password);

				// CORRECT PASSWORD
				if(password == ADMIN_PASSWORD) {
					cout << "\tMODIFICATION MENU\n";
					cout << "\t0. QUIT\n";
					cout << "\t1. Title\n";
					cout << "\t2. Author\n";
					cout << "\t3. ISBN\n";

					cout << "Enter option : ";
					while(!(cin >> opt) || opt < 0 || opt > 3) {
						cout << "Invalid input. Enter option : ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}

					// QUIT
					if(opt == 0) {
						break;
					}
					// OPTION 1-3
					else {
						cout << "Enter book ISBN (13 digits) : ";
						while(!(cin >> isbn)) {
							cout << "Invalid input. Enter book ISBN : ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						modify_bk(opt, isbn);
						cout << "\n";
					}
				}
				// INCORRECT PASSWORD
				else {
					cout << "Incorrect password.\n\n";
				}

				break;
			// DEFAULT
			default:
				break;
		} // SWITCH END

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
		// IF TITLE FOUND, PRINT BOOK INFORMATION
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
				bk.set_status('a');
				cout << "\nBook checked in.\n\n";
			}
			// CHECK OUT
			else if(option == 2) {
				cout << "Checking out book... ";
				bk.set_status('u');
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

void delete_bk(long long isbn) {
	// CONFIRMATION PROMPT
	char confirm;
	cout << "Confirm deletion (y/n) : ";
	while(!(cin >> confirm) || (confirm != 'y' && confirm != 'n')) {
		cout << "Invalid input. Confirm deletion (y/n) : ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// IF NOT CONFIRMED. EXIT FUNC
	if(confirm == 'n') {
		cout << "Deletion canceled.\n";
		return;
	}

	// IF CONFIRMED.
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
	inFS.seekg(0, ios::beg);

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
	else
		cout  <<"Deletion confirmed.\n";

	// REMOVES OLD FILE AND RENAMES NEW FILE NOT INCLUDING GIVEN BOOK
	remove("books.dat");
	rename("temp.dat", "books.dat");
}

void modify_bk(int option, long long isbn) {
	Book bk;
	bool found = false;

	fstream File;
	File.open("books.dat", ios::binary | ios::in | ios::out);
	if(!File) {
		cout << "File could not open.\n";
		return;
	}

	while(!File.eof() && found == false) {

		File.read(reinterpret_cast<char *> (&bk), sizeof(Book));

		if(bk.get_isbn() == isbn) {
			cout << "\n";
			bk.show_book();
			cout << "\n";

			if(option == 1) {
				char title[50];
				cout << "Enter new title : ";
				cin.ignore();
				cin.getline(title, 50);
				bk.set_title(title);
			}
			else if(option == 2) {
				char author[50];
				cout << "Enter new author : ";
				cin.ignore();
				cin.getline(author, 50);
				bk.set_author(author);
			}
			else if(option == 3) {
				long long isbn;
				cout << "Enter new ISBN (13 digits) : ";
				while(!(cin >> isbn)) {
					cout << "Invalid input. Enter new ISBN : ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				bk.set_isbn(isbn);
			}

			int pos = (-1)*static_cast<int>(sizeof(bk));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&bk), sizeof(Book));
			cout << "Modified book.\n\n";
			bk.show_book();
			found = true;
		}

	}

	File.close();

	if(!found)
		cout << "\nNo results found.\n";

}