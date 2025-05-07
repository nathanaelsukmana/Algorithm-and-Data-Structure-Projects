// ADS Praktikum 1.1 Printer
// Name: Max Mustermann
#include <iostream>
#include <queue>
#include "job.hpp"
#include "printer.h"
int Job::count = 0;

/**
 * Konstruktor zur Erstellung Eines neuen Printer Objekt mit einer bestimmten Queue Size
 * @param size maximale anzahl an druckerauftraege, die gleichzeitig in der druckerwarteschlange sein duerfen
*/
Printer::Printer(int size)
{
    queueSize = size;
}

/**
 * Funktion zur Hinzufuegen von einem neuen Druckauftrag zur Warteschlange
 * @param job auftrag, der der warteschlage hinzugefuegt werden
*/
bool Printer::addNewJob(const Job& job)
    {
        if (jobs.size() == queueSize) //die warteschlange ist voll
            return false;
        std::cout << "Added job in the queue: " << job;
        jobs.push(job);
        return true;
    }

/**
 * Funktion zum Drucken aller Druckauftraege in der Warteschlange
*/
void Printer::startPrinting()
{
    while (not jobs.empty())
    {
        std::cout << "Processing job: "  << jobs.top(); //top, denn es ist priority queue
        jobs.pop();
    }
}



