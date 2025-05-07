// ADS Praktikum 1.2 BST
// Name: Max Mustermann
#include <iostream>
#include "bst.h"

//4
#include <queue>

/**
* Start-Funktion zur Suche eines Integer-Zahlenwertes im Baum
*
* @param value Integer-Zahlenwert, der gesucht werden soll
*
*/
//2
node* bst::find(int value)
{
	//TODO: Suche im BST
    node* current = root; //traversal pointer beginnt vom root

    if(current == nullptr || current->data == value){
        return current;
    }
    
    if (value < current->data){
        bst leftSubtree; //neue objekt
        leftSubtree.root = current->left; //neue wurzel setzen
        return leftSubtree.find(value); //suchen fortfahren in leftSubtree
    } else {
        bst rightSubtree;
        rightSubtree.root = current->right;
        return rightSubtree.find(value);
    }
	//TODO: Return demo node ersetzen
	//return new node;
	//
}
/**
* Funktion zum Einfügen eines Integer-Zahlenwertes in den Baum
*
* @param value Integer-Zahlenwert, der eingefügt werden soll
*
*/

//1
void bst::insert(int value)
{
	if (!root) //root ist leer
		root = new node{ value, 0, NULL, NULL };
	else
		insert_impl(root, value);
}

/**
* Rekursive Funktion zum Einfügen eines Integer-Zahlenwertes im Baum
*
* @param current Knoten, hinter den eingefügt werden soll
* @param value Integer-Zahlenwert, der eingefügt werden soll
*
*/

//1
void bst::insert_impl(node* current, int value) //current ist root
{
	if (value < current->data)
	{
		if (!current->left)
			current->left = new node{ value, 0, NULL, NULL };
		else
			insert_impl(current->left, value);
	}
	else
	{
		if (!current->right)
			current->right = new node{ value, 0, NULL, NULL };
		else
			insert_impl(current->right, value);
	}

    //height update nach rekursive ende insert_impl
    int leftHeight = (current->left != nullptr) ? current->left->height : -1; //-1 als default wert, wenn 0 nicht geht
    int rightHeight = (current->right != nullptr) ? current->right->height : -1;
    current->height = std::max(leftHeight, rightHeight) + 1; //max nimmt groessere zahl von beiden zahlen

}

/*
	TODO: Ausgabe des BST in In-, Pre-, Post und Levelorder
    
*/

//4
/**
 * Rekursive Funktion zum Ausgabe in Inorder Form
 * 
 * @param knoten Knoten, von dem die Inorder Ausgabe starten oder fortgesetzt wird
 * 
*/

void bst::printInorder(node* knoten){
    if(knoten != nullptr){
        printInorder(knoten->left);
        std::cout << knoten->data << ", Hoehe: " << knoten->height << std::endl;
        printInorder(knoten->right);
    }
}

/**
 * Rekursive Funktion zum Ausgabe in Preorder Form
 * 
 * @param knoten Knoten, von dem die Inorder Ausgabe starten oder fortgesetzt wird
 * 
*/

void bst::printPreorder(node* knoten){
    if(knoten != nullptr){
        std::cout << knoten->data << ", Hoehe: " << knoten->height << std::endl;
        printPreorder(knoten->left);
        printPreorder(knoten->right);
    }
}

/**
 * Rekursive Funktion zum Ausgabe in Postorder Form
 * 
 * @param knoten Knoten, von dem die Inorder Ausgabe starten oder fortgesetzt wird
 * 
*/

void bst::printPostorder(node* knoten){
    if(knoten != nullptr){
        printPostorder(knoten->left);
        printPostorder(knoten->right);
        std::cout << knoten->data << ", Hoehe: " << knoten->height << std::endl;
    }
}

/**
 * Funktion zum Ausgabe in Levelorder Form
 * 
 * @param knoten Knoten, von dem die Inorder Ausgabe starten oder fortgesetzt wird
 * 
*/
void bst::printLevelorder(node* knoten) {
    if (knoten == nullptr){
        return;
    }

    std::queue<node*> q;
    q.push(knoten);

    while (!q.empty()) {
        node* current = q.front();
        q.pop();

        std::cout << current->data << ", Hoehe: " << current->height << std::endl;

        if (current->left != nullptr){
            q.push(current->left);
        }
            
        if (current->right != nullptr){
            q.push(current->right);
        }
            
    }
}

/**
 * Funktion zum Knotenloeschen in dreien Faellen
 * 
 * @param value gewuenschte Knoten ist zu loeschen
 * 
*/
//3
void bst::deleteValue(int value)
{
	//TODO: Löschen im BST
	node* current = root;
    node* parent = nullptr;

    //zu loeschende value in baum suchen
    while(current != nullptr && current->data != value){
        parent = current;
        if(value < current->data){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(current == nullptr){
        std::cout << value << " ist geloescht." << std::endl;
        return;
    }

    //1. Keine Nachfolger (in der bedingung)
    if(!current->left && !current->right){
        if(current == root){
            delete root;
            root = nullptr;
        //ob links oder rechts
        } else if(parent->left == current){
            delete current;
            parent->left = nullptr;
        } else if(parent->right == current){
            delete current;
            parent->right = nullptr;
        }
        std::cout << value << " ist geloescht." << std::endl;

    }

    //2. Eine Nachfolger
    else if((current->left == nullptr && current->right != nullptr) || (current->left != nullptr && current->right == nullptr)){
        
        //child suchen
        node* child = nullptr;
        if(current->left != nullptr){
            child = current->left;
        } else {
            child = current->right;
        }

        if(current == root){
            delete current;
            root = child;
        } else if(parent->left == current){
            delete current;
            parent->left = child;
        } else if(parent->right == current){
            delete current;
            parent->right = child;
        }

        std::cout << value << " ist geloescht." << std::endl;
    }

    //3. Zwei Nachfolgern
    else if(current->left != nullptr && current-> right != nullptr){
        node* successorParent = current;
        node* successor = current->right; //kleinste value in right subtree

        while(successor->left != nullptr){
            successorParent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        if(successorParent->left == successor){
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        
        delete successor;
        std::cout << value << " ist geloescht." << std::endl;
    }
	//
}

/**
 * Knoten Getter fuer Ausgabe
*/
node* bst::getRoot() {
    return root;
}

