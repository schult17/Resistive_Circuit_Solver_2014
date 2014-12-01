#ifndef _RESISTOR_CC
#define _RESISTOR_CC

#include "Resistor.h"

/*Constructor:
 *Parameters: 
 *rIndex_ = index of reistor in array
 *name_ = name of resistor
 *resistance_ = resistance of resistor
 *endpoints_ = two nodes to which resistor is connected*/
Resistor::Resistor(string name_, double resistance_, int endpoints_[2])
{
    //initalize resistor private members
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
}

//Destructor
Resistor::~Resistor(){}

/*Mutator:
 *Function: to modify the resistance of the Resistor object
 *Parameters: resistance_ = resistance to be changed in resistor object 
 *Return: void*/ 
void Resistor::setResistance(double resistance_)
{
    resistance = resistance_;
}

/*Accessor: 
 *Function: returns the name of the resistor
 *Parameters: none
 *Return: string, the name of the Resistor object*/
string Resistor::getName() const 
{
    return name;
}

/*Accessor: 
 *Function:returns the resistance of the resistor object
 *Parameters: none
 *Return: double, returns the resistance of the Resistor object*/
double Resistor::getResistance() const 
{
    return resistance;
}

/*Accessor: 
 *Function: prints the resistor and its members according to format
 *Parameter: none
 *Return: void*/
void Resistor::print()
{
    cout << left << setw(20) << name << " " << right << setw(8) << fixed 
            << setprecision(2) << resistance << " Ohms " << endpointNodeIDs[0] 
            << " -> " << endpointNodeIDs[1] << endl;
}

/*Accessor
 Function: returns the node connected to the resistor, that does not coresspond
 to the given node # (the other node)
 Parameter: integer 'node' which is the first connection to the resistor
 Return: integer, the other node connected to the resistor*/
int Resistor::getNode(int node)
{
    //return the node that is NOT equivilant to the current node ('node')
    if(this->endpointNodeIDs[0] != node)
    {
        return this->endpointNodeIDs[0];
    }
    else
    {
        return this->endpointNodeIDs[1];
    }
}

#endif /* RESISTOR_CC */
