#include "MyHashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


/**
 * @brief Berechnet den Hash-Wert eines gegebenen Schl�ssels (String) mithilfe der DJB2-Hashfunktion.
 *
 * @param key Der Schl�ssel, der gehasht werden soll.
 * @return Der berechnete Hash-Wert modulo der Tabellengr��e.
 */
unsigned int MyHashTable::hash(const std::string& key) const {
    // DJB2 Variante
    unsigned int h = 5381; //anfangswert von djb2
    for (char c : key) {
        h = ((h << 5) + h) + c; // h * 33 + c formell
    }
    return h % table.size(); //module mit table size, denn ergebnis passend in hash table
}

/**
 * @brief Vergr��ert die Hash-Tabelle und f�hrt ein Rehashing aller existierenden Eintr�ge durch.
 *
 * Diese Methode wird aufgerufen, wenn maxLoadFactor �berschritten wird.
 */
void MyHashTable::rehash() {
    /*
    * TODO Vergr��ern der Hash-Tabelle und erneutes Hashen aller bestehenden Eintr�ge
    */

    int doubleSize = table.size() * 2;

    int primzahl = getNextPrime(doubleSize);

    std::vector<Entry> oldTable = table;

    table = std::vector<Entry>(primzahl);

    numElements = 0;

    //jede position in old table
    for(int i = 0; i < oldTable.size(); i++){
        if(oldTable[i].occupied){ //wenn die pos gefuellt ist
            insert(oldTable[i].acc); //einfuegen die ausgelesene elemente in neue tabelle
        }
    }
}

/**
 * @brief F�gt einen neuen Account in die Hash-Tabelle ein.
 *
 * Je nach gew�hlter Kollisionsbehandlungsstrategie (linear, quadratisch oder doppeltes Hashing)
 * wird ein freier Platz gesucht. Falls maxLoadFactor �berschritten ist, wird vor dem Einf�gen rehashed.
 *
 * @param acc Der einzuf�gende Account.
 */
void MyHashTable::insert(const Account& acc) {
    /*
    * TODO Einf�gen eines neuen Accounts in die Hash-Tabelle anhand der gew�hlten Kollisionsstrategie
    */

   //fast voll, deswegen +1
    if ((double)(numElements + 1) / table.size() > maxLoadFactor) {
        rehash(); 
    }

    std::string key = acc.website + acc.username;

    //gewuenschte pos
    unsigned int baseHash = hash(key);

    unsigned int index = baseHash;

    //counter fuer method wenn kollision
    int i = 0;

    //r = primezahl fuer double hashing
    int R = getLastPrime(table.size());
    int secondaryHash = R - (baseHash % R);

    //ueberprueft ob slot occupied
    while (table[index].occupied) {
        if (hashMethod == 1) { //linear probing
            index = (baseHash + i) % table.size();
        } else if (hashMethod == 2) { //quadratic probing
            index = (baseHash + i * i) % table.size();
        } else if (hashMethod == 3) { //double hashing
            index = (baseHash + i * secondaryHash) % table.size();
        }
        i++;
    }

    table[index].acc = acc; //in slot index, acc/account wird darin ausgefullt
    table[index].occupied = true; //gefullte slot markieren
    numElements++; //account addiert sich
}

/**
 * @brief �berpr�ft Login-Daten (Website, Benutzername und Passwort-Hash).
 *
 * Durchsucht die Hash-Tabelle nach einem passenden Eintrag und vergleicht den Passwort-Hash.
 *
 * @param website Die Website des Accounts.
 * @param username Der Benutzername.
 * @param passwordHash Der gehashte Wert des Passworts.
 * @return true, wenn die Login-Daten g�ltig sind, sonst false.
 */
bool MyHashTable::login(const std::string& website, const std::string& username, const std::string& passwordHash) const {
    
    /*
    *
    * TODO Pr�fung, ob die eingegebenen Parameter mit einem Eintrag der Hash-Tabelle �bereinstimmen.
    *
    */
    std::string key = website + username;
    unsigned int baseHash = hash(key);
    unsigned int index = baseHash;
    int i = 0;

    int R = getLastPrime(table.size());
    int secondaryHash = R - (baseHash % R);

    while (table[index].occupied) {
        //daten check, ob uebereinstimmen
        if (table[index].acc.website == website &&
            table[index].acc.username == username &&
            table[index].acc.passwordHash == passwordHash) {
            return true;
        }

        //wenn nicht uebereinstimmen, gehe ins naechste slot
        if (hashMethod == 1) {
            index = (baseHash + i) % table.size();
        } else if (hashMethod == 2) {
            index = (baseHash + i * i) % table.size();
        } else if (hashMethod == 3) {
            index = (baseHash + i * secondaryHash) % table.size();
        }
        i++;
    }

    return false;
}

/**
 * @brief Gibt alle gespeicherten Eintr�ge (Website + Benutzername) auf der Konsole aus.
 */
void MyHashTable::listEntries() const {
    
    /*
    * TODO Ausgabe aller Eintr�ge der Hash-Tabelle als Kombination aus Website und Benutzername.
    */
   for (size_t i = 0; i < table.size(); i++) {
        if (table[i].occupied) {
            std::cout << "Website: " << table[i].acc.website << ", Username: " << table[i].acc.username << std::endl;
        }
    }

}

/**
 * @brief Bestimmt die n�chstgr��ere Primzahl nach einer gegebenen Zahl.
 *
 * @param x Startwert f�r die Suche.
 * @return Die n�chstgr��ere Primzahl.
 */
int MyHashTable::getNextPrime(int x)
{
    x = x + 1;
    bool found = true;
    while (true)
    {
        found = true;
        for (int i = 2; i <= sqrt(x); i++)
        {
            if (x % i == 0)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return x;
        }
        x += 1;
    }
}

/**
 * @brief Bestimmt die n�chstkleinere Primzahl vor einer gegebenen Zahl.
 *
 * @param x Startwert f�r die Suche.
 * @return Die n�chstkleinere Primzahl.
 */
int MyHashTable::getLastPrime(int x) const
{
    x = x - 1;
    bool found = true;
    while (true)
    {
        found = true;
        for (int i = 2; i <= sqrt(x); i++)
        {
            if (x % i == 0)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return x;
        }
        x -= 1;
    }
}

