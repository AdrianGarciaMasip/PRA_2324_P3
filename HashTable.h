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

		int h(std::string key){
			//Suma ASCII caracteres % tamaño tabla hash
			int sum = 0;
			for(char c : key){
				sum += (int)c;
			}

			return sum % max;
		}
	public:
		HashTable(int size){
			table = new ListLinked<TableEntry<V>>[size];
			max = size;
			n = 0;
		}

		~HashTable(){
			delete[] table;
		}
		int capacity(){
			return max;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			out << "HashTable [entries: " << th.n << ", capacity, " << th.max <<"]" << std::endl << "==============";
			for(int i = 0; i < th.max; i++){
				out << "\n\n" << "== Cubeta " << i << " ==" << "\n\n";
				out << th.table[i];
			}
			out << "\n\n" << "==============" << std::endl;
			return out;
		}

		V operator[](std::string key){
			return search(key);
		}

		//Metodos de Dict.h
		void insert(std::string key, V value) override{
			//Utilizar la funcion hash para encontar la cubeta
			int cubeta = h(key);
			//comprovar que la key no este repetida | -1 -> no encontrado
			if(table[cubeta].search(key) == -1){
				table[cubeta].prepend(TableEntry<V>(key, value));
			}else{
				throw std::runtime_error("Key '" + key + "' already exists!");
			}
			n++;
		}

		V search(std::string key) override{
			//Buscamos la cubeta en la que podria estas
			int cubeta = h(key);

			for(int i = 0; i < table[cubeta].size(); i++){
				if(table[cubeta].get(i).key == key){
					return table[cubeta].get(i).value;
				}
			}
			throw std::runtime_error("Key '" + key + "' not found!");
		}

		V remove(std::string key) override{
			//Buscamos la cubeta en la que podria estar
			int cubeta = h(key);                                                                                        //Buscamos la key si devuelve -1 no esta
			int pos = table[cubeta].search(key);
			if(pos == -1){
				throw std::runtime_error("Key '" + key + "' not found!");
			}
			n--;
			return table[cubeta].remove(pos).value;
		}

		int entries() override{
			return n;
		}
};
#endif
