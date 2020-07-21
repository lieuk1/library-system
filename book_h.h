/********************************************************************
* Name          : Kristella Lieu
* Date Created  : 2020 July 18
* Last Modified : 2020 July 21
* GitHub Link   : https://github.com/lieuk1/library-system.git
*
* Project	    : Library Management System
*********************************************************************/

/******************************
*		 BOOK HEADER FILE
*******************************/

#include <iostream>
using namespace std;

#ifndef BOOK_H
#define BOOK_H

class Book {
	public:
		void create_book();
		void show_book();

		void set_title(char* title);
		void set_author(char* author);
		void set_status(char status);
		void set_isbn(long long isbn);

		string get_title();
		string get_author();
		char get_status();
		long long get_isbn();

	private:
		char title_[50];
		char author_[50];
		char status_; // A/U, AVAILABLE/UNAVAILABLE
		long long isbn_; // 13 DIGITS
};

#endif