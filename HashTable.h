#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

	    private:
		    int n;
		    int max;
		    ListLinked<TableEntry<V>>* table;
       
	    public:
		    HashTable(int size){
			n = 0;
		    	max = size;
			table = new ListLinked<TableEntry<V>>[size]();
		    }
		    ~HashTable(){
		    	delete[] table;
		    }

		    int h(std::string key){
			    int acu=0;
			    for(char c : key){
			    	acu += c;
			    }
			    return acu % max;
		    }
		    int capacity(){
			return max;
		    }
		    
		    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		    	out << "HashTable [entries: "<< th.n <<", capacity: " << th.max << "]"<< std::endl;
			out << "==============" << std::endl << std::endl;
			for(int i=0; i<th.max; i++){
				out << " == Cubeta " << i <<" ==" <<std::endl << std::endl;
				out << "List => [";
				if(th.table[i].size() != 0){
					out << std::endl;
					for(int j = 0; j < th.table[i].size(); j++){
						out << "  ('" << th.table[i].get(j).key << "' => " << th.table[i].get(j).value << ")"<< std::endl;
					}
				}
				out << "]" << std::endl << std::endl;
			}
			out << "==============" << std::endl;
			return out;
		    }

		    V operator[](std::string key){
			return search(key);
		    }

		    void insert(std::string key, V value){
			try{	
		    	    	search(key);	

			}catch(std::runtime_error& e){
				table[h(key)].prepend(TableEntry<V>(key, value));
				n++;
		    		return;

			}
			throw std::runtime_error("key '"+key+"' already exists!");
		    }

		    V search(std::string key){
		    	for(int i = 0;  i<table[h(key)].size(); i++){
				if(table[h(key)].get(i).key == key)
					return table[h(key)].get(i).value;
			}
			throw std::runtime_error("Key '"+key+"' not found!");	
		    }
		    V remove(std::string key){
			    for(int i = 0;  i< table[h(key)].size() ;i++){
				    if(table[h(key)].get(i).key == key){				    
					    TableEntry<V> val=table[h(key)].remove(i);
					    n--;
					    return val.value;
				    }
			    }
			    throw std::runtime_error("Key '"+key+"' not found!");
		    }
		    
		    int entries(){
			    return n;
		    }

};

#endif
