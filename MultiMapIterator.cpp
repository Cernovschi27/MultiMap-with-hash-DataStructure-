#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	// Complexitate timp :O(m)
	poz = 0;
	while (poz < col.m && col.l[poz] == nullptr) poz++;
	if (poz < col.m)
		curent = col.l[poz];
	else curent = nullptr;
}



TElem MultiMapIterator::getCurrent() const{
	// Complexitate timp :Theta(1)
	if (!valid())
		throw std::exception();
	return curent->e;
}

bool MultiMapIterator::valid() const {
	// Complexitate timp :Theta(1)
	return (poz < col.m) && (curent != nullptr);
}

void MultiMapIterator::next() {
	// Complexitate timp :O(m)
	if(!valid())
		throw std::exception();
	if(curent->urm!=nullptr)
		curent = curent->urm;
	else {
		poz = poz + 1;
		while (poz < col.m && col.l[poz] == nullptr)
			poz++;
		if (poz < col.m)
			curent = col.l[poz];
		else
			curent = nullptr;
	}
}

void MultiMapIterator::first() {
	// Complexitate timp :O(m)
	poz = 0;
	while (poz < col.m && col.l[poz] == nullptr)
		poz++;
	if (poz < col.m)
		curent = col.l[poz];
}

