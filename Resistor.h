#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor* next;

public:
   Resistor(string name_,double resistance_,int endpoints_[2]);

   ~Resistor();

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance

   void setResistance (double resistance_);

   // you *may* create either of the below to print your resistor
   void print ();
   
   int getNode(int node);
   
   //a resistor list should be able to access members of a resistor
   friend class ResistorList;
};

#endif	/* RESISTOR_H */
