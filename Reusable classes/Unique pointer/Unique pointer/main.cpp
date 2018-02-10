#include <iostream>
#include <utility>
#include "uniquePtr.h"

class Shape
{
public:
	virtual ~Shape() = default;

	virtual int getParameter()const = 0;
};


class Rectangle : public Shape
{
public:
	Rectangle(int a, int b) : a(a), b(b) {}
	virtual ~Rectangle()override = default;

	virtual int getParameter()const override { return a*b; }

private:
	int a;
	int b;
};


class Triangle : public Shape
{
public:
	Triangle(int a, int b, int c) : a(a), b(b), c(c) {}	
	virtual ~Triangle() = default;

	virtual int getParameter()const override { return a*b*c; }

private:
	int a;
	int b;
	int c;
};

uniquePtr<Shape> makeRectangle()
{
	return uniquePtr<Shape>(new Rectangle(10,20));
}

uniquePtr<Shape> makeTriangle()
{
	return uniquePtr<Shape>(new Triangle(10, 20, 30));
}


int main()
{

	uniquePtr<Shape> ptr(makeTriangle());

	ptr = makeTriangle();

	uniquePtr<Shape> ptr2(std::move(ptr));

	return 0;
}