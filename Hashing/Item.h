#ifndef __ITEM_H_INCLUDED__
#define __ITEM_H_INCLUDED__

class Item
{
public:
	explicit Item(char c = '#');
	Item(const Item&) = default;
	virtual ~Item() = default;

	Item& operator=(const Item&) = default;

	bool isNull()const;
	char getKey()const;

	void setKey(char c);
	void makeNull();

private:
	char key;
};

#endif //__ITEM_H_INCLUDED__