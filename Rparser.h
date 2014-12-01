/* 
 * File:   Rparser.h
 * Author: schult17
 *
 * Created on October 4, 2014, 2:29 PM
 */

#ifndef RPARSER_H
#define	RPARSER_H

using namespace std;

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

bool printErrorInvalidArg(bool);
bool printErrorTooFewArg(bool, bool);
bool printErrorTooManyArgs(char);
bool printAllError(string);
bool printRless0Error(double);
bool printErrorSameNode(int, int);
bool checkLastInput(stringstream&);
bool checkAfterInput(char);
void insertR(NodeList&, string, double, int, int);
void modifyR(NodeList&, string, double);
void printR(NodeList&, string);
void printNodeAll(NodeList&);
void printNode(NodeList&, int);
void deleteR(NodeList&, string name);
void deleteAll(NodeList&);

#endif	/* RPARSER_H */
