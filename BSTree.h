#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	    int nelem;
	    BSNode<T> *root;
	    BSNode<T>* search(BSNode<T>* n, T e) const{
		    
		    if(n == nullptr){
                            throw std::runtime_error("Error en la busqueda");
                    } 
		    else if(n->elem < e){
			    return search(n->right, e);
		    }
		    else if(n->elem > e){
			    return search(n->left, e);
		    }
		    else{
			    return n;
		    }
	    }

	    BSNode<T>* insert(BSNode<T>* n, T e){
		    if(n == nullptr){
			    return new BSNode<T>(e); //crea un nuevo nodo
		    }
		    else if(n->elem == e){
			    throw std::runtime_error("El elemento ya existe");
		    }
		    else if(n->elem < e){
			    n->right = insert(n->right, e);
		    }
		    else{
			    n->left = insert(n->left, e);
		    }
		    return n;
	    }

	    //muestra los elementos de menor a mayor
	   void print_inorder(std::ostream &out, BSNode<T>* n) const{
		   if(n != nullptr){ 
		   	if(n->left != nullptr){
			    print_inorder(out, n->left);
			    
		    	}
			 out<<n->elem<<std::endl; 
		    	if(n->right != nullptr){
			    print_inorder(out, n->right);
			  
		    	}
	  	 }	
	   }


	    BSNode<T>* remove(BSNode<T>* n, T e){ //falta el delete!!!
		    if(n == nullptr){
			    throw std::runtime_error("Error en la búsqueda");
		    }
		    else if (n->elem < e){
			    n->right = remove(n->right, e);
		    }
		    else if (n->elem > e){
			    n->left = remove(n->left, e);
		    }
		    else{
			    if(n->left != nullptr && n->right != nullptr){
				    n->elem = max(n->left);
				    n->left = remove_max(n->left);
			    }
			    else {
			    	BSNode<T> * aux = n;
				if(n->left != nullptr){
					n = n->left;
			    	}
			    	else {
				    n = n->right;
			    	}
				delete aux;
			    }
		    }
		    return n;
	    }

	    T max(BSNode<T>* n) const{
		    if(n == nullptr){
			    throw std::runtime_error("Error en la búsqueda");
		    }
		    else if(n->right != nullptr){
			    return max(n->right);
		    }
		    else{ //encuentra el elemento y lo devuelve
			    return n->elem;
		    }
	    }

	    BSNode<T>* remove_max(BSNode<T>*n){
		     if(n == nullptr){
                            throw std::runtime_error("Error en la búsqueda");
                    }
		    
		     else if(n->right == nullptr){
			     BSNode<T>* aux = n->left;
			     delete n;
			     return aux;
		    }
		    else{
			    n->right = remove_max(n->right);
			    return n;
		    }
	    }
	    
	    void delete_cascade(BSNode<T>* n){
		    if(n != nullptr){
			    delete_cascade(n->left);
			    delete_cascade(n->right);
			    delete n;
			   
		    }
		    
	    }

        
    public:
	    BSTree(){
		   nelem = 0;
		   root = nullptr; 
		    
	    }
	    int size() const{
	    	return nelem;
	    }

	    T search(T e) const{
	    	return search(root, e)->elem;
	    }

	    T operator[](T e) const{
		    BSNode<T>* aux = search(root, e);
		    if(aux != nullptr){
			    return aux->elem;
		    }
		    else{
			    throw std::runtime_error("Error en la búsqueda");
		    }
	    }
	    
	    
	    void insert(T e){
	    	root = insert(root, e);
		nelem++;
	    }
	    	
	    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		    bst.print_inorder(out, bst.root);
		    return out;
	    }

	    void remove(T e){
		    root = remove(root,e);
		    nelem--;
	    }
	    ~BSTree(){
		    delete_cascade(root);
		    root = nullptr;
	    }  




        
    
};

#endif
