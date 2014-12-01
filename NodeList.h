/* 
 * File:   NodeList.h
 * Author: tannerys
 *
 * Created on October 19, 2014, 12:40 AM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include <cmath>
//#include "Node.h"

using namespace std;

class NodeList
{
private:
    Node* head;
    
public:
    NodeList();
    ~NodeList();
    
    Node* findNode(int nodeID);
    Node* findORinsert(int nodeID);
    Resistor* findResistor(string name);
    void insertNode(Node** nodes, int nodeID);
    void deleteResistor(string name);
    void deleteAllHelp(Node** head);
    void clearNetwork();
    void printAllNodes();
    void setResistance(string name , double resistance);
    void clearEmptyNodes();
    void deleteNode(Node** head, int nodeID);
    void setV(int, double);
    void unsetV(int);
    bool checkSet();
    void solve(Node* head);
    Node* returnHead();
    void nullHead();
};
#endif	/* NODELIST_*/
