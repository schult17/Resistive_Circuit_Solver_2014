/* 
 * File:   main.cpp
 * Author: tannerys
 *
 * Created on September 20, 2014, 6:50 PM
 */
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"

int main(int argc, char** argv) {
    
    NodeList nodes;
    
    //string variables, line is stream and command is read first
    string command, line;
    
    //do while loop ensures an initial engagement into the loop 
    do
    {
        //setting command to something incase of blank input
        command = " ";
        
        //prompting formatting
        cout << "> ";
        
        //gets line from cin
        getline(cin, line);
        
        //if eof is inputted break from loop, done
        if(cin.eof()){break;}
        
        //creates a string stream of the inputted line and reads the original command
        stringstream lineStream(line);
        lineStream >> command;
        
        //variables for parsing, reinitialized for every input line
        string arg0;
        double arg1 = 0;
        int arg2 = 0;
        int arg3 = 0;
        
        if(command == "insertR")
        {
            lineStream >> arg0;
            //First input is string, the only three checks we must do are:
            //too few arguments, invalid argument, 'all' keyword error
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(printAllError(arg0)){continue;}
            
            lineStream >> arg1;
            //second input is a double, the only three checks we need are:
            //too few arguments, invalid argument, or a negative resistance
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(checkAfterInput(lineStream.peek())){continue;}
            if(printRless0Error(arg1)){continue;}
            
            lineStream >> arg2;
            //third input is a integer, the only three checks we need are:
            //too few arguments, invalid argument, or a out of range node
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(checkAfterInput(lineStream.peek())){continue;}
            
            lineStream >> arg3;
            //third and last input is a integer, the only four checks we need are:
            //too few arguments, invalid argument, or a out of range node and last input check
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(checkAfterInput(lineStream.peek())){continue;}
            
            //only function we use same node check, then check last input
            if(printErrorSameNode(arg2, arg3)){continue;}
            if(checkLastInput(lineStream)){continue;}
            
            //if all is well, and none of the checks were true 
            //(didn't continue to bottom of do, while) insert new resistor
            insertR(nodes, arg0, arg1, arg2, arg3);
        }
        else if(command == "modifyR")
        {
            lineStream >> arg0;
            //First input is string, the only three checks we must do are:
            //too few arguments, invalid argument, 'all' keyword error
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(printAllError(arg0)){continue;}
            
            lineStream >> arg1;
            //second and last input is a double, the only four checks we need are:
            //too few arguments, invalid argument, negative resistance and last input check
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(checkAfterInput(lineStream.peek())){continue;}
            if(printRless0Error(arg1)){continue;}
            if(checkLastInput(lineStream)){continue;}
            
            //if all is well, modify
            modifyR(nodes, arg0, arg1);
        }   
        else if(command == "printR")
        {
            lineStream >> arg0;
            //first and only input is a string, the only three inputs we need are:
            //too few arguments, invalid argument, and last input check
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(printErrorInvalidArg(lineStream.fail())){continue;}
            if(checkLastInput(lineStream)){continue;}http://www.undergrad.engineering.utoronto.ca/site3.aspx
            
            //if all is well, if the argument is 'all', use printAll to print
            //them all, otherwise use printR to print a specific resistor
            printR(nodes, arg0);
        }
        else if(command == "printNode")
        {
            //the input here is either a string ('all') or a integer (nodeid)
            //read an integer first (arg2)
            lineStream >> arg2;
            //check for too few arguemnts first!
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            //if enough arguments, AND the lineStream fails(didn't get an int)...
            if(lineStream.fail())
            {
                //clear the flags
                lineStream.clear();
                
                //try and read a string
                lineStream >> arg0;
                
                //check for invalid arguments and last input
                if(printErrorInvalidArg(lineStream.fail())){continue;}
                if(checkAfterInput(lineStream.peek())){continue;}
                
                //if the all is well and the string is 'all' print all nodes
                //if word is not 'all' invalid argument!
                //nested if statements are incase they enter a string that is not all
                //AND they enter too many arguments (special case only for printNode)
                if(arg0 == "all")
                {
                    if(checkLastInput(lineStream)){continue;}
                    printNodeAll(nodes);
                }
                else{cout << "Error: invalid argument" << endl;}
                continue;
            }
            //if lineStream didn't fail, check last input again, and node out of range
            if(checkAfterInput(lineStream.peek())){continue;}
            if(checkLastInput(lineStream)){continue;}
            
            //if all is well print node.
            printNode(nodes, arg2);
        }
        else if(command == "deleteR")
        {
            lineStream >> arg0;http://www.undergrad.engineering.utoronto.ca/site3.aspx
            //first and only input is a string, the only three inputs we need are:
            //too few arguments, invalid argument, and last input check
            if(printErrorTooFewArg(lineStream.eof(), lineStream.fail())){continue;}
            if(checkLastInput(lineStream)){continue;}
            
            //if arg0 is keyword 'all', delete all resistors, otherwise delete 
            //specified resistor by name
            if(arg0 == "all"){deleteAll(nodes);}
            else{deleteR(nodes, arg0);}
        }
        else if(command == "setV")
        {
            lineStream >> arg2;http://www.undergrad.engineering.utoronto.ca/site3.aspx
            lineStream >> arg1;
            nodes.setV(arg2, arg1);
        }
        else if(command == "unsetV")
        {
            lineStream >> arg2;
            nodes.unsetV(arg2);
        }
        else if(command  == "solve")
        {
            nodes.solve(nodes.returnHead());
        }
        else{cout << "Error: invalid command" << endl;}
        
        //if flags were set, clear them. getline() never fails so nothing to do
        //there. and if cin.eof() is set, we are done!
        lineStream.clear();
        
    }while(!cin.eof());
    
    //clear cin incase we use this somewhere else (not necessary)
    cin.clear();
    
    return 0;
}
