// ADS Praktikum 1.1 Printer
// Name: Max Mustermann
#pragma once
#include <queue>

class Printer
{
    //std::queue<Job> jobs; //prinzip: first in first out
    std::priority_queue<Job> jobs;
    int queueSize; //max size von queue
public:
    Printer(int size);
    bool addNewJob(const Job& job); //job kann nicht modifiziert werden und als referenz sein
    void startPrinting();
};