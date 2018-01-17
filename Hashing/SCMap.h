#ifndef __SEPARATE_CHAIN_HASH_MAP_H_INCLUDED__
#define __SEPARATE_CHAIN_HASH_MAP_H_INCLUDED__

template <typename Item, typename Key, typename HashFun>
class SCMap
{
private:
	template <typename Item, typename Key>
	struct Node
	{
		Node(const Item& item, const Key& key, Node<Item,Key>* next = nullptr);

		Item item;
		Key key;
		Node<Item, Key>* next;
	};

public:
	SCMap(int size);
	SCMap(const SCMap&);
	~SCMap();

	SCMap& operator=(const SCMap&);

	int getCount()const;
	bool isEmpty()const;

	void insert(const Item&, const Key&);
	void remove(const Key&);
	Item* search(const Key&);
	
private:
	int count;
	int size;
	Node<Item, Key>** chains;
	HashFun function;

private:
	static Node<Item, Key>* cloneChain(const Node<Item, Key>* first, Node<Item, Key>** last = nullptr);
	static void clearChain(Node<Item, Key>* first);
};

#endif //__SEPARATE_CHAIN_HASH_MAP_H_INCLUDED__