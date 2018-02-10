#include <iostream>
#include <utility>
#include "uniquePtr.h"

#include "Shapes.h"

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