#include <iostream>
#include <cstring> // strcpy
#include "book_h.h"
using namespace std;

/****************************
*    BOOK MEMBER FUNCTIONS
*****************************/

void Book::create_book() {
	cout << "Enter book title : ";
	cin.getline(title_, 50);

	cout << "Enter book author : ";
	cin.getline(author_, 50);

	cout << "Enter book ISBN : ";
	cin >> isbn_;

	cout << "Enter book status (a/u) : ";
	cin >> status_;
}

/*****************
*    SETTERS
******************/

void Book::set_title(char* title) {
	strcpy(title_, title);
}

void Book::set_author(char* author) {
	strcpy(author_, author);
}

void Book::set_status(char status) {
	status_ = status;
}

void Book::set_isbn(long long isbn) {
	isbn_ = isbn;
}

/*****************
*    GETTERS
******************/

string Book::get_title() {
	return string(title_);
}

string Book::get_author() {
	return string(author_);
}

char Book::get_status() {
	return status_;
}

long long Book::get_isbn() {
	return isbn_;
}