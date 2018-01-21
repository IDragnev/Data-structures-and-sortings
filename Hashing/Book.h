#ifndef __BOOK_H_INCLUDED__
#define __BOOK_H_INCLUDED__

#include <iostream>

class Book
{
public:
	Book(const char* name);
	Book(const Book&);
	~Book();

	Book& operator=(const Book&);

	const char* getName()const;
	void setName(const char*);

private:
	char* name;
};

std::ostream& operator<<(std::ostream& out, const Book&);

#endif //__BOOK_H_INCLUDED__