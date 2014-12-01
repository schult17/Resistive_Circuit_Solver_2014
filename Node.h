#ifndef NODE_H
#define NODE_H

using namespace std;

#include <iostream>
#include "ResistorList.h"

class Node
{
private:
    
   int nodeID;
   Node* next;
   ResistorList res_head; 
   double voltage;
   bool setV;
   
public:
   Node(int nodeID);
   ~Node();

   // Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
   void addResistor (string name, double resistance, int endpoints[2]);

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex);
   
   int getResCount();
   
   int getNodeID();
   
   void setVoltage(double);
   
   void editVoltage(double);
   
   void unsetV();
   
   bool checkSet();
   
   //Node list should access members of a node
   friend class NodeList;
};

#endif	/* NODE_H */ 
