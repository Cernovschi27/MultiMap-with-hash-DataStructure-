#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

int HashFunction(const TKey& elem, int m)
{	//metoda diviziunii
	// Complexitate timp :Theta(1)
	TKey copy = elem;
	if (elem < 0)
		copy = elem * -1;
	return copy % m;
}
MultiMap::MultiMap() {
	//Complexitate timp:Theta(m)
	m = 13;
	length = 0;
	Hash = HashFunction;
	for (int i = 0; i < m; i++)
		l[i] = nullptr;
}

void MultiMap::add(TKey c, TValue v) {
	//Complexitate timp:Theta(1)
	//locatia de dispersie
	int position = Hash(c, m);
	//aloc nod
	TElem key = std::make_pair(c, v);
	PNod newnode = new Nod(key, nullptr);
	if (l[position] == nullptr)
	{
		l[position] = newnode;
	}
	else {
		newnode->urm = l[position];
		l[position] = newnode;

	}
	length++;
}


bool MultiMap::remove(TKey c, TValue v) {
	//Complexitate timp :O(n)(cautare nod + stergere)
	int position = Hash(c, m);
	PNod prev_pos=nullptr ;
	PNod current = l[position];
	while (current != nullptr and !(current->e.first == c and current->e.second == v))
	{
		prev_pos = current;
		current=current->urm;
	}
	if (current == nullptr)
		return false;//cheia nu se afla in map
	else
	{
		if (prev_pos != nullptr)
			prev_pos->urm = current->urm;
		else
			l[position] = current->urm;
	}
	length--;
	return true;
}


vector<TValue> MultiMap::search(TKey c) const {
	// Complexitate timp :Theta(alpha) alpha = m / numarul de elemente in medie Theta(1)
	std::vector<TValue> values;
	int position = Hash(c, m);
	PNod current = l[position];
	while (current != nullptr)
	{
		if (current->e.first == c)
			values.push_back(current->e.second);
		current = current->urm;
	}
	return values;
}


int MultiMap::size() const {
	// Complexitate timp :Theta(1)
	return length;
}


bool MultiMap::isEmpty() const {
	// Complexitate timp :Theta(1)
	return length == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
int MultiMap::nrvaluesforkey(TKey c)
{
	//Complexitate timp : Theta(alpha) alpha = m / numarul de elemente
	std::vector<TValue> values;
	values = search(c);
	return values.size();

}


MultiMap::~MultiMap() {
	//Complexitate timp O(n) n =nr de elemente 
	for (int i = 0; i < m; i++) {
		//se elibereaza memoria pentru lista i
		while (l[i] != nullptr) {
			PNod p = l[i];
			l[i] = l[i]->urm;
			delete p;
		}
	}
}

