#ifndef _NODE_LIST_CC
#define _NODE_LIST_CC

#include "Node.h"
#include "NodeList.h"
#define MIN_ITERATION_CHANGE 0.0001

/*Constructor:
 Function: sets head pointer too NULL (empty linked list)*/
NodeList::NodeList()
{
    head = NULL;
}

/*Destructor:
 Function: Before deleting NodeList, call 'deleteAllHelp' 
 too delete all nodes in linked list of nodes, and set head to NULL*/
NodeList::~NodeList()
{
    //send recursive delete function the head pointer of list to delete all nodes
    //before destroying object
    deleteAllHelp(&(this->head));
}

/*Mutator:
 Function: Recursively delete all nodes in linked list, end to start
 Parameters: Pointer to the head of a linked list (reference)
 Return: void*/
void NodeList::deleteAllHelp(Node** head)
{
    //If the current head is NULL..
    if(*head != NULL)
    {
        //Call delete on the next node
        deleteAllHelp(&((*head)->next));
        
        //after the proceeding line has bee completed (at end of list)
        //delete the current head, which deletes from tail to head
        delete(*head);
	*head = NULL;
    }
    //The destructor of the resistor list takes care of the Resistor Objects
}

/*Accessor:
 Function: find a node in the linked list
 Parameters: integer, the ID of the node to be found
 Return: Pointer to Node with corresponding ID (NULL if DNE)*/
Node* NodeList::findNode(int nodeID)
{   
    //temp pointer to the head of the list, of nodes
    Node* curr_node = this->head;
    
    //iterate over list until the current node is NULL (end)
    while(curr_node != NULL)
    {
        //if we have a matching node, break from loop
        //if our current node is greater than the node to find,
        //return NULL (nodes inserted in order)
        if(curr_node->nodeID == nodeID) {break;}
	else if (curr_node->nodeID > nodeID){return NULL;}       
 
        //otherwise, go to the next node
        curr_node = curr_node->next;
    }
    
    //return the current node, either the node when we broke from the loop,
    //or NULL if we get to the end
    return curr_node;
}

/*Accessor:
 Function: find a resistor in the linked list of nodes (all nodes)
 Parameters: string 'name' of resistor
 Return: pointer to the coresponding resistor*/
Resistor* NodeList::findResistor(string name)
{
    //temp pointer to the head of the list of nodes
    Node* temp_node_head = this->head;
    
    //iterate over list until the current node is NULL (end)
    while(temp_node_head != NULL)
    {
        //try and find resistor in resistor list using findResistor()
        Resistor* curr_res = temp_node_head->res_head.findResistor(name);
        
        //if the resistor is we returned is non-NULL, return it
        if(curr_res != NULL)
        {
            return curr_res;
        }
        
        //otherwise go to the next node
        temp_node_head = temp_node_head->next;
    }
    
    //if we get to the end of the list of nodes, the resistor was not found!
    return NULL;
}

/*Mutator:
 Function: insert a node into the list, in ascending order (recursive)
 Parameters: reference to the head pointer of the list and the ID of the
 Node to be inserted
 Return: void*/
void NodeList::insertNode(Node** head, int nodeID)
{
    //creating a new Node pointer
    Node* newNode = NULL;
    
    //if the head is NULL we are at the end of the list, we should insert
    if(*head == NULL)
    {
        //make a new node
        *head = new Node(nodeID);
    }
    else if(nodeID < (*head)->nodeID)   //if the new nodes ID is less than currents..
    {
        //make a new node, with the node ID
        newNode = new Node(nodeID);
        
        //the new Nodes next is equal to the current node (insert before)
        newNode->next = *head;
        
        //this makes previous pointer point to newNode (through recursion)
        *head = newNode;
    }
    else
    {
        //if neither of these cases are met, call the same function on the heads next
        insertNode(&((*head)->next), nodeID);
    }
}

/*Mutator:
 Function: insert OR find a node in the list
 Parameters: integer, the ID number of the node
 Return: A pointer to a Node object (if found)*/
Node* NodeList::findORinsert(int nodeID)
{
    //try and find the node
    Node* temp = this->findNode(nodeID);
    
    //if found (non NULL), return it, otherwise, insert it using insertNode
    if(temp != NULL)
    {
        return temp;
    }
    else
    {
        //insert the node
        insertNode(&(this->head), nodeID);
        return NULL;
    }
}

/*Mutator:
 Function: delete a resistor in the list (multiple deletions)
 Parameters: string, name of the resistor
 Return: void*/
void NodeList::deleteResistor(string name)
{
    //temp pointer to head of list of nodes
    Node* curr_node = this->head;
    
    //iterate over entire list of nodes
    while(curr_node != NULL)
    {
        //try and delete the resistor in current node
        curr_node->res_head.deleteResistor(name);
        
        //move on to the next node
        curr_node = curr_node->next;
    }
    
    //clear the empty nodes from the list
    this->clearEmptyNodes();
}

/*Accessor:
 Function: print all the nodes in the list
 Parameters: none
 Return: void*/
void NodeList::printAllNodes()
{
    cout << "Print:" << endl;
    Node* temp = this->head;
    
    //iterate over entire list of nodes
    while(temp != NULL)
    {
        //if the head node of the resistor list is not NULL (no resistors)
	if((temp->res_head).returnHead() != NULL)
	{
            //print the entire node
	    temp->print(temp->nodeID);
	}
        
        //move to next node
        temp = temp->next;
    }

}

/*Mutator:
 Function: set the resistance of a given node
 Parameters: string , name of resistor to be modified; double, new resistance of
 the resistor
 Return: void*/
void NodeList::setResistance(string name , double resistance)
{
    //pointer to head of list of nodes
    Node* temp_head = this->head;
    
    //holds the old resistive value
    double old_res;
    
    //small optimization
    int count2 = 0;
    
    //iterate over all nodes in list
    while(temp_head != NULL)
    {
        //try and find resistor with given name
        Resistor* temp = temp_head->res_head.findResistor(name);
        
        //if found, temp will not be NULL...
        if(temp != NULL)
        {   
            //hold the old resistive value
            old_res = temp->getResistance();
            
            //set the new resistive value
            temp->setResistance(resistance);
            
            //increment counter
            count2++;
        }
        
        //max amount of resistors that will be found in nodes is two(only two connections)
        //so break out if we have already changed two resistors
        if(count2 == 2){break;}
        
        //move to next node
        temp_head = temp_head->next;
    }
    
    cout << "Modified: resistor " << name << " from " << fixed << setprecision(2) 
                    << old_res << " Ohms to " << fixed 
                    << setprecision(2) << resistance << " Ohms" << endl;
}

/*Mutator:
 Function: clear nodes that aren't necessary (not set and have no resistors)
 Parameters: none
 Return: void*/
void NodeList::clearEmptyNodes()
{
    //temp pointer to head of node list
    Node* curr_node = this->head;
    
    //iterate over all nodes
    while(curr_node != NULL)
    {
        //if the node has no resistors connected AND is not set to a voltage
        //delete that node and move to next
        if((curr_node->res_head).returnHead() == NULL && !curr_node->setV)
        {
            //get the ID of the name
	    int tempID = curr_node->nodeID;
            
            //move to the next node before deleting
	    curr_node = curr_node->next;
            
            //delete the node that is not needed
            this->deleteNode(&(this->head), tempID);
        }
        else
	{
	    curr_node = curr_node->next;
	}
    }
}

/*Mutator:
 Function: clear the entire network of all resistors and unnecessary nodes
 Parameters:none
 Return: void*/
void NodeList::clearNetwork()
{
    //temp pointer to head of nodes
    Node* curr_node = this->head;
    
    //iterate over all nodes
    while(curr_node != NULL)
    {
        //Temp pointer to head of list of Resistor objects
        Resistor* head_res = (curr_node->res_head).returnHead();
        //delete all of the resistors in that list
        (curr_node->res_head).deleteAllHelp(&(head_res));
        
        //NULL the head of the list (didn't work in the other function)
        (curr_node->res_head).nullHead();
        
        //move to next NODE
        curr_node = curr_node->next;
    }
    
    //clear all of the nodes (all resistors deleted, so only nodes left are
    // nodes that have their voltages set)
    this->clearEmptyNodes();
}

/*Mutator:
 Function: Nullify the head of the list
 Parameters: none
 Return: void*/
void NodeList:: nullHead()
{
    this->head = NULL;
}

/*Mutator:
 Function: delete a node in the list
 Parameters: node ID to be deleted
 Return void*/
void NodeList::deleteNode(Node** head, int nodeID)
{
    //if the current NODE is NULL (end of list, we are done)
    if(*head != NULL)
    {
        //if the current node and node to be deleted are equal
        if((*head)->nodeID == nodeID)   
        {
            //temp pointer to the node we are deleting
            Node* delPTR = *head;
            
            //Case 1: if we are deleting tail pointer
            if((*head)->next == NULL)
            {
                //delete the pointer  (last object)
                delete(delPTR);
                //set current to NULL (so that the previous node points to NULL)
                *head = NULL;
            }
            else        //Case 2: we are deleting in the list (not tail)
            {
                //make the previous pointers next (*head) equal to the deleting 
                //pointers next, IE, skip the link over the node being deleted)
                *head = (*head)->next;
                delete(delPTR);
            }
        }
        else    //if the current node is not to be deleted
        {
            //call the same function of the next node
            deleteNode(&((*head)->next), nodeID);
        }
    }
}

/*Mutator:
 Function: set the voltage of a node
 Parameters: int, ID of node to be set, double, voltage to be set at
 Return: void*/
void NodeList::setV(int nodeID, double voltage)
{
    //try and find the node to be set, otherwise insert it!
    Node* temp = this->findORinsert(nodeID);
    
    //if we found the node (non NULL)
    if(temp != NULL)
    {
        //set the voltage
        temp->setVoltage(voltage);
    }
    else        //if we didn't find the node originally, we inserted it, so...
    {
        //find it again, and set the voltage
	Node* find = findNode(nodeID);
        find->setVoltage(voltage);
    }
    
    cout << "Set: node " << nodeID << " to " << setprecision(2) << fixed
	<< voltage << " Volts" << endl; 
}

/*Mutator:
 Function: set the voltage of a node
 Parameters: int, ID of node to be unset
 Return: void*/
void NodeList::unsetV(int nodeID)
{
    //temp pointer to head of node list
    Node* temp = this->findNode(nodeID);
    
    //if we found the node
    if(temp != NULL)
    {
        //unset the voltage of the node
        temp->unsetV();
        
        //if it doesn't have any resistors connected, its useless, delete it.
	if((temp->res_head).returnHead() == NULL)
	{
	    this->deleteNode(&(this->head), temp->nodeID);
	}
    }
    
    cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
}

/*Accessor:
 Function: check if a node is set or not (for solve)
 Parameters: none
 Return: bool, if a node is set of not*/
bool NodeList::checkSet()
{
    //temp pointer to head of node list
    Node* curr = this->head;
    
    //iterate over entire node list
    while(curr != NULL)
    {
        //if the current node is set AND has resistors connected, we can solve
        if(curr->setV && (curr->res_head).returnHead() != NULL)
        {
            return true;
        }
        
        //move to next node
        curr = curr->next;
    }
    
    //if we didn't find one that was connected and set, we can't solve, return false
    return false;
}

/*Accessor?:
 Function: solve the current circuit
 Parameters: pointer to the head node
 Return: void*/
void NodeList::solve(Node* head)
{
    //check if we can solve the circuit
    if(!this->checkSet())
    {
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }
    
    //how many nodes are connected to the current node
    int numNodesConnected = 0;
    
    //maximum change of the the node voltages
    double maxChange;
    
    //pointer to current node in the list
    Node* curr_head;
    
    //do, while to make sure we get into the loop once, until max change is less
    //than MIN_ITERATION_CHANGE (0.0001), GAUSSIAN SIEDEL
    do
    {
        //set pointer back to head pointer
        curr_head = head;
        
        //temp variable for old voltage
        double old_voltage = 0;
        
        //set max change back to 0 before going through nodes again
        maxChange = 0;
        
        //this loop will iterate over entire list of nodes
        while(curr_head != NULL)
        {
            //set the old voltage of the node to temp variable 'old_voltage'
            old_voltage = curr_head->voltage;
            
            //only do this method if the voltage of the current node is not set
            if(!curr_head->setV)
            {
                //get the number of nodes connected to the current node
                numNodesConnected = curr_head->getResCount();
                
                //making an array of node voltages to calculate current node voltage
                double* node_voltages = new double[numNodesConnected];
                
                //a list of all the resistors connected to the current node
                Resistor** resistors = new Resistor*[numNodesConnected];
                
                //fill the list of resistors connected to current node
                (curr_head->res_head).fillList(resistors);

                //temp variable for the current connection to the node
                int connect_node = 0;
                
                //loop over all of the current nodes connections
                for(int i = 0; i < numNodesConnected; i++)
                {
                    //use Resistor object method to find OTHER node connected to it
                    connect_node = resistors[i]->getNode(curr_head->nodeID);
                    
                    //find the node in the list of nodes
                    Node* node = this->findNode(connect_node);
                    
                    //add this nodes voltage to the list
                    node_voltages[i] = node->voltage;
                }

                //now we have a list of resistors and node voltages
                
                //temp variables to make calculation in handout more clear
                double mult1 = 0;
                double mult2 = 0;

                //iterate over all of the node voltages and resistors and do
                //calculations described in 4.4.2 of the hand out
                for(int j = 0; j < numNodesConnected; j++)
                {
                    mult1 += (1/(resistors[j]->getResistance()));
                    mult2 += (node_voltages[j] / (resistors[j]->getResistance()));
                }

                //temp variable for new voltage of node
                double v = 0;
                v = (1/mult1)*(mult2);

                //edit, don't set, the current voltage
                curr_head->editVoltage(v);   

                //check if this change is greater than the current max change in the system
                if(fabs(old_voltage - v) > maxChange)
                {
                    //if so, change the new max change
                    maxChange  = fabs(old_voltage - v);
                }

                //delete all dynamic arrays and set pointers to NULL to do 
                //loop again (depending on status of max change)
                delete []resistors;
                delete []node_voltages;
                resistors = NULL;
                node_voltages = NULL;
            }
        
            //move to next node and do inner loop again, until the node is NULL
            curr_head = curr_head->next;
        }
        //only do loop again if max change is greater than 0.0001
    }while(maxChange > MIN_ITERATION_CHANGE);
    
    //print out formatting, print all nodes and their voltages
    cout << "Solve:" << endl;
    
    Node* curr_node = head;
    while(curr_node != NULL)
    {
	if((curr_node->res_head).returnHead() != NULL)
        {
	    cout << "  "; 
            cout << "Node " << curr_node->nodeID << ": " << setprecision(2) << fixed 
                    << curr_node->voltage << " V" << endl;
	}
	
	curr_node = curr_node->next;
    }
}

/*Accessor:
 Function: return a pointer to the head Node
 Parameters: none
 Return: Node object pointer to head of list*/
Node* NodeList::returnHead()
{
    return this->head;
}

#endif
