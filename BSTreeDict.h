#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
		 tree = new BSTree<TableEntry<V>>();
	}


	~BSTreeDict(){
		delete tree;
	}

	friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
		out<<*(bs.tree)<<std::endl;
		return out;
	}

	V operator[](std::string key){
		return tree->search(key).value;
	}

	void insert(std::string key, V value){
		TableEntry<V> aux(key, value);
                tree->insert(aux);

	}
        
	V search(std::string key){
		return tree->search(key).value;

	}
        
	V remove(std::string key){
		TableEntry<V> backup;
                backup.value = tree->search(key).value;
                tree->remove(key);
                return backup.value;


	}
        
	int entries(){
		return tree->size();
	}
        
};

#endif
