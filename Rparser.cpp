#ifndef _Rparser_CC
#define _Rparser_CC

#include "Rparser.h"

//this function for determining if the input is invalid or too few arguments
//the function takes in a boolean parameters, the end of file flag
//of stringstream 'streamLine' and returns a boolean variableflag
bool printErrorInvalidArg(bool fail)
{
    //if the fail flag is set...
    if(fail)
    {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    //the boolean return values are to determine in the main 
    //function should continue (skip bad input) or keep parsing
    return false;
}

//this is a function for determing if there are two fe#ifndef _Rparser_CC
#define _Rparser_CC

#include "Rparser.h"

//this function for determining if the input is invalid or too few arguments
//the function takes in a boolean parameters, the end of file flag
//of stringstream 'streamLine' and returns a boolean variableflag
bool printErrorInvalidArg(bool fail)
{
    //if the fail flag is set...
    if(fail)
    {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    //the boolean return values are to determine in the main 
    //function should continue (skip bad input) or keep parsing
    return false;
}

//this is a function for determing if there are two few arguments in the stream
//the function takes in two boolean parameters, the end of file flag and fail flag
//of stringstream 'streamLine' and returns a boolean variable
bool printErrorTooFewArg(bool fail, bool eof)
{
    //if the fail flag is set (fail flag could be set without reaching end)...
    if(fail)
    {
        //...and the eof of file flag is set, then we have too few arguments!
        if(eof)
        {
            //print error message
            cout << "Error: too few arguments" << endl;
            return true;   
        }
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this is a helper function for determining if the input has too many arguments
//the function takes in one character variable 'peekChar' and returns a boolean variable
bool printErrorTooManyArgs(char peekChar)
{
    //if the next character is NOT the end of file character, too /* 
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
many arguments
    //.peek() is used along with (>> ws) to ignore white space
    if(peekChar != -1)
    {
        //print message
        cout << "Error: too many arguments" << endl;
        return true;
    }
    //boolean return values for continuing to end of loop 
    return false;
}

//this helper function is specifically for evaluating  and printing the error 
//associated with the misuse of the 'all' special command
//the function takes in a string variable, 'arg0'returns a boolean variable
bool printAllError(string arg0)
{
    //if the first argument is 'all'
    if(arg0 == "all")
    {
        //print error message
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return true;
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this helper function is for determining if the input resistance is less than 0
//the function takes in a double variable, 'arg1'returns a boolean variable
bool printRless0Error(double arg1)
{
    //if the second argument is less than 0..
    if(arg1 < 0)
    {
        //print error message
        cout << "Error: negative resistance" << endl;
        return true;
    } 
    //boolean return values for continuing to end of loop
    return false;
}

//this function is for determining if the inputted nodes are the same
//the function takes in a two integer variables, 'node1' and 'node2', returns a boolean variable
bool printErrorSameNode(int node1, int node2)
{
    //if the nodes are equal...
    if(node1 == node2)
    {
        //print error message
        cout << "Error: both terminals of resistor connect to node " << node1 << endl;
        return true;   
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this function is strictly for checking the last input of the stream for 
//and invalid argument of too many, it takes th stream 'lineStream' as an input,
//passed by reference, and outputs a boolean variable
bool checkLastInput(stringstream& lineStream)
{
    //if the next character in the line is a space.. we could just have whitespace
    //and EOF or another character, but not an invalid argument!
    if(lineStream.peek() == ' ')
    {
        //dummy variable 'peekCheck' is to check for another argument
        char peekCheck;
        //read from stream
        lineStream >> peekCheck;
        //we should get to the end of the file because its last input, if we don't...
        if(!lineStream.eof())
        {
            //print error message (because there is a space)
            cout << "Error: too many arguments" << endl;
            return true;
        }
    }
    //if the next character is NOT a space
    else
    {
        //dummy variable 'peekCheck' is to check for another argument
        char peekCheck;
        //read from stream
        lineStream >> peekCheck;
        //we should get an end of file because this is this last input, if we don't... 
        if(!lineStream.eof())
        {
            //print an invalid argument (because there is no space)
            cout << "Error: invalid argument" << endl;
            return true;
        }
    }    
    
    //I used a dummy variable "peekCheck" to read further into the stream.
    //so if nothing went wrong, re-set the flags and continue in parser function
    lineStream.clear();
    //boolean return values for continuing to end of loop
    return false;
}

//this function will check the next character after each input (for invalid inputs)
//must only occur after a read of a int (strings will be read regardless). This
//function takes a character (peek) as a input and returns a bool variable
bool checkAfterInput(char peek)
{
    //if peek reveals something thats not a char or space, its an invalid input
    //after the input has been read
    if(peek != ' ' && peek != -1)
    {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    
    return false;
}

/******************************************************************************/
/******************************************************************************/
/*                       Lab4 Functions Start Here                            */
/******************************************************************************/
/******************************************************************************/

void insertR(NodeList& nodes, string name, double resistance, int from_node, int to_node)
{   
    //check if the resistor already exists, print error if it does!
    if(nodes.findResistor(name))
    {
        cout << "Error: resistor " << name << " already exists" << endl;
        return;
    }
    
    //temp array of integers to pass to insertResistor()
    int nodeids[2];
    nodeids[0] = from_node;
    nodeids[1] = to_node;
        
    //find or insert both to and from node (if found, nothing happens, until next
    //block)
    nodes.findORinsert(from_node);
    nodes.findORinsert(to_node);
    
    //find first node (just inserted if it didn't exist) and insert the resistor
    Node* insert_res1 = nodes.findNode(from_node);
    insert_res1->addResistor(name, resistance, nodeids);
    
    //find second node (just inserted if it didn't exist) and insert the resistor
    Node* insert_res2 = nodes.findNode(to_node);
    insert_res2->addResistor(name, resistance, nodeids);
    
    cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance 
            << " Ohms " << from_node << " -> " << to_node << endl;
}

/*Function: Modify the resistance of a resistor
 *Parameters: Pointer to array of Resistor objects 'resistors', and a double value
 *which is the new resistance 'resistance'
 *Return: void*/
void modifyR(NodeList& nodes, string name, double resistance)
{
    Resistor* find_res = nodes.findResistor(name);
    
    if(find_res == NULL)
    {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else
    {
        nodes.setResistance(name, resistance);
    }
}

/*Function: print a Resistor object
 *Parameters: array of Resistor objects 'resistors', a string which is the name
 *of the resistor to be printed 'name'
 *Return: void*/
void printR(NodeList& nodes, string name)
{   
    //find the resistor in the list
    Resistor* find_res = nodes.findResistor(name);
    
    //if not found (NULL return for findResistor())
    if(find_res == NULL)
    {
        //print error
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else
    {
        //otherwise print the returned resistor
        cout << "Print:" << endl;
        find_res->print();
    }
}

/*Function: Print all connections to all Node objects
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void printNodeAll(NodeList& nodes)
{
    nodes.printAllNodes();
}

/*Function: Print all connections to a Node objects
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *and an integer value 'nodeIndex', the index of the node to print
 *Return: void*/
void printNode(NodeList& nodes, int nodeIndex)
{
    cout << "Print:" << endl;
    
    //find the node to be printed
    Node* print_node = nodes.findNode(nodeIndex);
    
    //if the returned node is non NULL, print it!
    if(print_node != NULL)
    {
        print_node->print(nodeIndex);
    }
}

/*Function: Delete all the resistors in the network
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void deleteR(NodeList& nodes, string name)
{
    //find the resistor to be deleted
    Resistor* find_res = nodes.findResistor(name);
    
    //if findResistor() returned NULL, it does not exist
    if(find_res == NULL)
    {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else        //otherwise, delete the resistor
    {
        nodes.deleteResistor(name);
        cout << "Deleted: resistor " << name << endl;
    }
}

/*Function: Delete the entire network (Resistor's and Node's)
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void deleteAll(NodeList& nodes)
{
    //clear the network of resistors and unnecessary nodes
    nodes.clearNetwork();
    cout << "Deleted: all resistors" << endl;
}
#endif /* RPARSER_CC */w arguments in the stream
//the function takes in two boolean parameters, the end of file flag and fail flag
//of stringstream 'streamLine' and returns a boolean variable
bool printErrorTooFewArg(bool fail, bool eof)
{
    //if the fail flag is set (fail flag could be set without reaching end)...
    if(fail)
    {
        //...and the eof of file flag is set, then we have too few arguments!
        if(eof)
        {
            //print error message
            cout << "Error: too few arguments" << endl;
            return true;   
        }
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this is a helper function for determining if the input has too many arguments
//the function takes in one character variable 'peekChar' and returns a boolean variable
bool printErrorTooManyArgs(char peekChar)
{
    //if the next character is NOT the end of file character, too many arguments
    //.peek() is used along with (>> ws) to ignore white space
    if(peekChar != -1)
    {
        //print message
        cout << "Error: too many arguments" << endl;
        return true;
    }
    //boolean return values for continuing to end of loop 
    return false;
}

//this helper function is specifically for evaluating  and printing the error 
//associated with the misuse of the 'all' special command
//the function takes in a string variable, 'arg0'returns a boolean variable
bool printAllError(string arg0)
{
    //if the first argument is 'all'
    if(arg0 == "all")
    {
        //print error message
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return true;
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this helper function is for determining if the input resistance is less than 0
//the function takes in a double variable, 'arg1'returns a boolean variable
bool printRless0Error(double arg1)
{
    //if the second argument is less than 0..
    if(arg1 < 0)
    {
        //print error message
        cout << "Error: negative resistance" << endl;
        return true;
    } 
    //boolean return values for continuing to end of loop
    return false;
}

//this function is for determining if the inputted nodes are the same
//the function takes in a two integer variables, 'node1' and 'node2', returns a boolean variable
bool printErrorSameNode(int node1, int node2)
{
    //if the nodes are equal...
    if(node1 == node2)
    {
        //print error message
        cout << "Error: both terminals of resistor connect to node " << node1 << endl;
        return true;   
    }
    //boolean return values for continuing to end of loop
    return false;
}

//this function is strictly for checking the last input of the stream for 
//and invalid argument of too many, it takes th stream 'lineStream' as an input,
//passed by reference, and outputs a boolean variable
bool checkLastInput(stringstream& lineStream)
{
    //if the next character in the line is a space.. we could just have whitespace
    //and EOF or another character, but not an invalid argument!
    if(lineStream.peek() == ' ')
    {
        //dummy variable 'peekCheck' is to check for another argument
        char peekCheck;
        //read from stream
        lineStream >> peekCheck;
        //we should get to the end of the file because its last input, if we don't...
        if(!lineStream.eof())
        {
            //print error message (because there is a space)
            cout << "Error: too many arguments" << endl;
            return true;
        }
    }
    //if the next character is NOT a space
    else
    {
        //dummy variable 'peekCheck' is to check for another argument
        char peekCheck;
        //read from stream
        lineStream >> peekCheck;
        //we should get an end of file because this is this last input, if we don't... 
        if(!lineStream.eof())
        {
            //print an invalid argument (because there is no space)
            cout << "Error: invalid argument" << endl;
            return true;
        }
    }    
    
    //I used a dummy variable "peekCheck" to read further into the stream.
    //so if nothing went wrong, re-set the flags and continue in parser function
    lineStream.clear();
    //boolean return values for continuing to end of loop
    return false;
}

//this function will check the next character after each input (for invalid inputs)
//must only occur after a read of a int (strings will be read regardless). This
//function takes a character (peek) as a input and returns a bool variable
bool checkAfterInput(char peek)
{
    //if peek reveals something thats not a char or space, its an invalid input
    //after the input has been read
    if(peek != ' ' && peek != -1)
    {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    
    return false;
}

/******************************************************************************/
/******************************************************************************/
/*                       Lab4 Functions Start Here                            */
/******************************************************************************/
/******************************************************************************/

void insertR(NodeList& nodes, string name, double resistance, int from_node, int to_node)
{   
    //check if the resistor already exists, print error if it does!
    if(nodes.findResistor(name))
    {
        cout << "Error: resistor " << name << " already exists" << endl;
        return;
    }
    
    //temp array of integers to pass to insertResistor()
    int nodeids[2];
    nodeids[0] = from_node;
    nodeids[1] = to_node;
        
    //find or insert both to and from node (if found, nothing happens, until next
    //block)
    nodes.findORinsert(from_node);
    nodes.findORinsert(to_node);
    
    //find first node (just inserted if it didn't exist) and insert the resistor
    Node* insert_res1 = nodes.findNode(from_node);
    insert_res1->addResistor(name, resistance, nodeids);
    
    //find second node (just inserted if it didn't exist) and insert the resistor
    Node* insert_res2 = nodes.findNode(to_node);
    insert_res2->addResistor(name, resistance, nodeids);
    
    cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance 
            << " Ohms " << from_node << " -> " << to_node << endl;
}

/*Function: Modify the resistance of a resistor
 *Parameters: Pointer to array of Resistor objects 'resistors', and a double value
 *which is the new resistance 'resistance'
 *Return: void*/
void modifyR(NodeList& nodes, string name, double resistance)
{
    Resistor* find_res = nodes.findResistor(name);
    
    if(find_res == NULL)
    {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else
    {
        nodes.setResistance(name, resistance);
    }
}

/*Function: print a Resistor object
 *Parameters: array of Resistor objects 'resistors', a string which is the name
 *of the resistor to be printed 'name'
 *Return: void*/
void printR(NodeList& nodes, string name)
{   
    //find the resistor in the list
    Resistor* find_res = nodes.findResistor(name);
    
    //if not found (NULL return for findResistor())
    if(find_res == NULL)
    {
        //print error
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else
    {
        //otherwise print the returned resistor
        cout << "Print:" << endl;
        find_res->print();
    }
}

/*Function: Print all connections to all Node objects
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void printNodeAll(NodeList& nodes)
{
    nodes.printAllNodes();
}

/*Function: Print all connections to a Node objects
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *and an integer value 'nodeIndex', the index of the node to print
 *Return: void*/
void printNode(NodeList& nodes, int nodeIndex)
{
    cout << "Print:" << endl;
    
    //find the node to be printed
    Node* print_node = nodes.findNode(nodeIndex);
    
    //if the returned node is non NULL, print it!
    if(print_node != NULL)
    {
        print_node->print(nodeIndex);
    }
}

/*Function: Delete all the resistors in the network
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void deleteR(NodeList& nodes, string name)
{
    //find the resistor to be deleted
    Resistor* find_res = nodes.findResistor(name);
    
    //if findResistor() returned NULL, it does not exist
    if(find_res == NULL)
    {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else        //otherwise, delete the resistor
    {
        nodes.deleteResistor(name);
        cout << "Deleted: resistor " << name << endl;
    }
}

/*Function: Delete the entire network (Resistor's and Node's)
 *Parameters: array of Node objects 'nodes' and array of Resistor objects 'resistors'
 *Return: void*/
void deleteAll(NodeList& nodes)
{
    //clear the network of resistors and unnecessary nodes
    nodes.clearNetwork();
    cout << "Deleted: all resistors" << endl;
}
#endif /* RPARSER_CC */
