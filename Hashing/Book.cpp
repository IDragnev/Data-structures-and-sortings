#include "Book.h"


const char* Book::getName()const
{
	return name;
}


void Book::setName(const char* name)
{
	if (!name)
		throw std::invalid_argument("Name must be a valid string!");

	int size = strlen(name) + 1;
	char* buff = new char[size];
	strcpy_s(buff, size, name);

	delete[] this->name;
	this->name = buff;
}


Book::Book(const char* name)
	:
	name(nullptr)
{
	setName(name);
}


Book::Book(const Book& other)
	:
	name(nullptr)
{
	setName(other.name);
}


Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{		
		setName(other.name);
	}

	return *this;
}


Book::~Book()
{
	delete[] name;
}


std::ostream& operator<<(std::ostream& out, const Book& book)
{
	out << "Name: " << book.getName();

	return out;
}