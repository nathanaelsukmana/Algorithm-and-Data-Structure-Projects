// ADS Praktikum 1.2 BST
// Name: Max Mustermann
#pragma once

//4
#include <queue>

/**
* Struktur zur Darstellung eines Knotens eines (Binär-)Baumes
*
* @param data Zahlenwert der im Baum gespeichert wird
* @param left Linkes Kind des Knotens
* @param right Rechtes Kind des Knotens
*
*/

//1
struct node
{
	int data;
	int height;
	node* left, * right;
};

/**
* Klasse zur Darstellung eines Binärbaumes
*
* @param root Wurzelknoten des Baumes
*
*/
class bst
{
	node* root = nullptr;
public:
	node* find(int value);
	void insert(int value);
	void deleteValue(int value);

	//4 In Public aufgrund Die Lage von Ausgabe von Struktur des Baumes auf der Konsole
	void printInorder(node* knoten);
	void printPreorder(node* knoten);
	void printPostorder(node* knoten);
	void printLevelorder(node* knoten);

	//5 getter
	node* getRoot();

private:
	void insert_impl(node* current, int value);
};