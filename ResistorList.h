/* 
 * File:   ResistorList.h
 * Author: tannerys
 *
 * Created on October 19, 2014, 12:40 AM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Resistor.h" 

using namespace std;

class ResistorList
{
private:
    Resistor* head;
    
public:
    ResistorList();
    ~ResistorList();
    
    void insertResistor(string name, double resistance, int endpoints[2]);
    void insertHelp(Resistor** head, string name, double resistance, int endpoints[2]);
    Resistor* findResistor(string name);
    void deleteResistor(string);
    void deleteResistorHelp(Resistor** head, string name);
    void printList();
    int countRes();
    void deleteAllHelp(Resistor** head);
    Resistor* returnHead();
    void nullHead();
    void fillList(Resistor**& list);
};

#endif	/* RESISTORLIST_H */
