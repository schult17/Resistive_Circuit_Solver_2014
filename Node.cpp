#ifndef _NODE_CC
#define _NODE_CC

#include "Node.h"

//Constructor
Node::Node(int nodeID_)
{   
    nodeID = nodeID_;
    next = NULL;
    voltage = 0;
    setV = false;
}

//Destructor
Node::~Node(){}

/*Mutator:
 *Function:add a resistor to list of resistors
 *Parameters: restsitor info, name, resistance and node connections
 *Return: void*/
void Node::addResistor(string name, double resistance, int endpoints[2])
{
    this->res_head.insertResistor(name, resistance, endpoints);
}

/*Accessor:
 *Parameters: nodeIndex = index of node to be printed
 *prints header message of printNode, when coupled with getResID, will print entire node
 *Return: void*/
void Node::print(int nodeIndex)
{
    cout << "Connections at node " << nodeIndex 
        << ": " << this->getResCount() << " resistor(s)" << endl;
    
    this->res_head.printList();
}

/*Accessor: 
 *Function: returns the number of resistors in node
 *Parameters: none
 *Return: int, the amount of resistors connected to the node 'numRes'*/
int Node::getResCount()
{
    return this->res_head.countRes();
}

/*Accessor:
 Function: return the node ID of a node
 Parameter: none
 Return: integer, nodes ID number*/
int Node::getNodeID()
{
    return this->nodeID;
}

/*Mutator:
 Function: sets the voltage flag to true and sets voltage 
 Parameters: voltage to be set too
 Return: void*/
void Node::setVoltage(double voltage)
{
    this->setV = true;
    this->voltage = voltage;
}

/*Mutator:
 Function: edits the voltage without setting setV flag
 Parameters: voltage to be set
 Return: void*/
void Node::editVoltage(double voltage)
{
    this->voltage = voltage;
}

/*Mutator:
 Function: sets voltage of node to 0 and lowers setV flag
 Parameters: None
 Return: void*/
void Node::unsetV()
{
    this->setV = false;
    this->voltage = 0;
}

/*Accessor:
 Function: Checks status of setV flag (voltage source)
 Parameters: none
 Return: Boolean, set or unset*/
bool Node::checkSet()
{
    return setV;
}

#endif /* NODE_CC */
