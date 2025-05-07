#pragma once
#include <string>
#include <vector>
#include <cmath>

/**
 * @brief Repr�sentiert einen Benutzer-Account mit Anmeldedaten.
 *
 * Diese Struktur enth�lt den Benutzernamen, den gehashten Passwortwert
 * sowie die zugeh�rige Website.
 */
struct Account {
    std::string username;
    std::string passwordHash;
    std::string website;
};

/**
 * @brief Eine einfache Hash-Tabelle zur Verwaltung von Benutzer-Accounts.
 *
 * Diese Klasse implementiert eine Hash-Tabelle, die Accounts (bestehend aus
 * Benutzername, gehashtem Passwort und Website) speichert. Die Klasse unterst�tzt
 * verschiedene Kollisionsbehandlungsstrategien.
 */
class MyHashTable {
private:
    /**
     * @brief Interner Eintrag in der Hash-Tabelle.
     *
     * Jeder Eintrag enth�lt einen Account sowie ein Flag, das angibt,
     * ob der Slot aktuell belegt ist.
     */
    struct Entry {
        Account acc;
        bool occupied = false;
    };
    std::vector<Entry> table;
    int numElements;
    int hashMethod;
    double maxLoadFactor = 0.6;

    unsigned int hash(const std::string& key) const;
    void rehash();
public:
    MyHashTable(int size = 8, int hashMethod_ = 1) : table(size), numElements(0), hashMethod(hashMethod_) {}
    void insert(const Account& acc);
    bool login(const std::string& website, const std::string& username, const std::string& passwordHash) const;
    void listEntries() const;
    int getNextPrime(int x);
    int getLastPrime(int x) const;
};