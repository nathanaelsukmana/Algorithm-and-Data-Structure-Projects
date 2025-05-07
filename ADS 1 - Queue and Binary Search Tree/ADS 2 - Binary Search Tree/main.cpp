// ADS Praktikum 1.2 BST
// Name: Max Mustermann
#include "bst.h"

//5
#include <iostream>

int main()
{
	//TODO: Main Methode (5)
    
	//

	bst baum;

	int values[] = {46, 83, 95, 22, 17, 68, 11, 82, 21, 31, 54, 99, 74};
		for(int i = 0; i < 13; i++){
			baum.insert(values[i]);
		}

	std::cout << "Inorder: \n";
	baum.printInorder(baum.getRoot());
	std::cout << "\n";

	std::cout << "Suche 17: ";
	std::cout << (baum.find(17) ? "Gefunden" : "Nicht gefunden") << "\n";

	std::cout << "Suche 11: ";
	std::cout << (baum.find(11) ? "Gefunden" : "Nicht gefunden") << "\n";
	std::cout << std::endl;

	int loeschen[] = {68, 21, 17, 95};
	for(int i = 0; i < 4; i++){
		baum.deleteValue(loeschen[i]);
	} 

	std::cout << "\nErneute Suche\n";
	std::cout << "Suche 17: ";
	std::cout << (baum.find(17) ? "Gefunden" : "Nicht gefunden") << "\n";

	std::cout << "Suche 11: ";
	std::cout << (baum.find(11) ? "Gefunden" : "Nicht gefunden") << "\n";

	std::cout << "\nPreorder: \n";
	baum.printPreorder(baum.getRoot());
	std::cout << "\nInorder: \n";
	baum.printInorder(baum.getRoot());
	std::cout << "\nPostorder: \n";
	baum.printPostorder(baum.getRoot());
	std::cout << "\nLevelorder: \n";
	baum.printLevelorder(baum.getRoot());
	std::cout << std::endl;

	system("PAUSE");
	return 0;
}