// ADS Praktikum 1.1 Printer
// Name: Max Mustermann
#include "job.hpp"
#include "printer.h"

int main()
{
    // TODO Erstellen Sie das Szenario aus der Aufgabenstellung
    Printer Printer(6); //class und konstruktor

    //konstruktor heisst job in job.hpp
    Printer.addNewJob(Job("John",10)); 
    Printer.addNewJob(Job("Jerry",4));
    Printer.addNewJob(Job("Jimmy",5));
    Printer.addNewJob(Job("George",2));
    Printer.addNewJob(Job("Bill",11));
    Printer.addNewJob(Job("Kenny",10));
    
    Printer.startPrinting();
    
    system("PAUSE");
    return 0;
    //
}