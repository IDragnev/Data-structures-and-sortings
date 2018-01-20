#include "Item.h"

Item::Item(char c)
	:
	key(c)
{
	;
}


bool Item::isNull()const
{
	return key == '#';
}


void Item::setKey(char c)
{
	key = c;
}


char Item::getKey()const
{
	return key;
}


void Item::makeNull()
{
	key = '#';
}