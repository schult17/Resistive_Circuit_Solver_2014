#ifndef _RESISTOR_LIST_CC
#define _RESISTOR_LIST_CC

#include "ResistorList.h"

/*Constructor:
 Function: set head of resistor list to NULL*/
ResistorList::ResistorList()
{
    head = NULL;
}

/*Destructor:
 Function: delete all resistors in list before destroying object (deleting a node)*/
ResistorList::~ResistorList()
{   
    //before deleting a List, delete all of the resistors in the list
    deleteAllHelp(&(this->head));
    
    //this was causing some undefined behaviour in my program
    this->head = NULL;
}

/*Mutator:
 Function: delete all nodes in linked list recursively (tail to head)
 Parameters: reference via double pointer to head of list
 Return: void*/
void ResistorList::deleteAllHelp(Resistor** head)
{
    //if the current resistor is not NULL
    if(*head != NULL)
    {
        //call the function on the next resistor
        deleteAllHelp(&((*head)->next));
        
        //delete the resistor once the previous line has been satisfied and NULL pointer
        delete(*head);
	*head = NULL;
    }
}

/*Mutator:
 Function: NULLify head of list
 Parameters: none
 Return: void*/
void ResistorList::nullHead()
{
    this->head = NULL;
}

/*Helper:
 Function: to send head pointer of list to insert
 Parameters: new resistor info
 Return: void*/
void ResistorList::insertResistor(string name, double resistance, int endpoints[2])
{
    insertHelp(&(this->head), name, resistance, endpoints);
}

/*Mutator:
 Parameters: double pointer to head of resistor list; string, name of new resistor
 double, resistance of new resistor, int[], endpoints of new resistor
 Return: void*/
void ResistorList::insertHelp(Resistor** head, string name, double resistance, int endpoints[2])
{
    //if the head is NULL we are at the end of the list, so insert a new resistor
    if(*head == NULL)
    {
        *head = new Resistor(name, resistance, endpoints);
        return; 
    }
    else        //otherwise, move to next resistor and try and insert again
    {
        //this gets rid of the cases we need to check in non-recursive
        insertHelp(&((*head)->next), name, resistance, endpoints);
    }
}

/*Helper:
 Function: to send head pointer of list to insert
 Parameters: name of resistor to be deleted
 Return: void*/
void ResistorList::deleteResistor(string name)
{   
    deleteResistorHelp(&(this->head), name);   
}

/*Mutator:
 Parameters: double pointer to head of resistor list; string, name of resistor to be deleted
 Return: void*/
void ResistorList::deleteResistorHelp(Resistor** head, string name)
{
    //if the current resistor is NULL (end of list, we are done)
    if(*head != NULL)
    {
        //if the current resistor and resistor to be deleted have the same name
        if((*head)->name == name)
        {
            // temp pointer to the resistor to be deleted
            Resistor* delPTR = *head;

            //Case 1: if we are deleting tail pointer
            if((*head)->next == NULL)
            {
                //delete the pointer  (last object)
                delete(delPTR);
                
                //set current to NULL (so that the previous resistor points to NULL)
                *head = NULL;
            }
            else
            {
                //make the previous pointers next (*head) equal to the deleting 
                //pointers next, IE, skip the link over the resistor being deleted)
                *head = (*head)->next;
                delete(delPTR);
            }
        }
        else    //if the current resistor is not to be deleted
        {
            //call the same function of the next resistor
            deleteResistorHelp(&((*head)->next), name);
        }
    }
}

/*Accessor:
 Function: find resistor of given name in list
 Parameters: string, name of resistor to be found
 Return: pointer to object with given name*/
Resistor* ResistorList::findResistor(string name)
{
    //temp pointer to head of list of resistors
    Resistor* curr_res = this->head;
    
    //iterate over entire list of resistors
    while(curr_res != NULL)
    {
        //if the current resistor is the resistor we want, break out of loop
        if(curr_res->name == name) {break;}
        
        //move to next resistor
        curr_res = curr_res->next;
    }
    
    //return the resistor (NULL if not found, if found, we return the curr_res)
    return curr_res;
}

/*Accessor:
 Function: print list of resistors
 Parameters: none
 Return: void*/
void ResistorList::printList()
{
    //temp pointer to head of resistor list
    Resistor* curr_res = this->head;
    
    //loop over entire list of resistors
    while(curr_res != NULL)
    {
        //print the resistor
        cout << "  ";
        curr_res->print();
        curr_res = curr_res->next;
    }
}

/*Accessor:
 Function: Count resistors in list
 Parameters: none
 Return: void*/
int ResistorList::countRes()
{
    //return variable
    int count = 0;
    
    //temp pointer to head of resistor list
    Resistor* temp = this->head;
    
    //iterate over list to count resistors
    while(temp != NULL)
    {
        //increment count
        count++;
        
        //move to next resistor
        temp = temp->next;
    }
    
    return count;
}

/*Accessor:
 Function: return pointer to head of list
 Parameters: none
 Return: void*/
Resistor* ResistorList::returnHead()
{
    return this->head;
}

/*Accessor:
 Function: fill a list of points to point to objects in Resisttor list
 Parameters: double pointer to array of resistors, by reference
 Return: void*/
void ResistorList::fillList(Resistor**& list)
{
    //pointer to head of list
    Resistor* curr_res = this->head;
    
    //index variable for 'list', because of the use of method countRes(), we are
    //guranteed to have same size in 'list' as in the resistor list
    int index = 0;
    
    //literate over entire listof resistors
    while(curr_res != NULL)
    {
        //point the pointer in list, at the current resistor
        list[index] = curr_res;
        
        //move to the next resistor and increment the index for 'list'
        curr_res = curr_res->next;
        index++;
    }
}

#endif /*_RESISTOR_LIST_CC*/
