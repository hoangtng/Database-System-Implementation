
#ifndef SCHEMA_H
#define SCHEMA_H

#include <stdio.h>
#include <string>
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"

struct att_pair
{
	char *name;
	Type type;
};

struct Attribute
{
	char *name;
	Type myType;

	// Default constructor
	Attribute() : name(nullptr), myType(Int) {} // Initialize with default values

	// Parameterized constructor
	Attribute(const char *name, Type type)
	{
		this->name = new char[strlen(name) + 1]; // Allocate memory
		strcpy(this->name, name);				 // Copy the string
		myType = type;
	}

	// Destructor to free allocated memory
	~Attribute()
	{
		delete[] name; // Free the allocated memory
	}
};

class OrderMaker;
class Schema
{

	friend class Record;

public:
	// gives the attributes in the schema
	int numAtts;
	Attribute *myAtts;

	// gives the physical location of the binary file storing the relation
	char *fileName;

	// gets the set of attributes, but be careful with this, since it leads
	// to aliasing!!!
	Attribute *GetAtts();

	// returns the number of attributes
	int GetNumAtts();

	// this finds the position of the specified attribute in the schema
	// returns a -1 if the attribute is not present in the schema
	int Find(char *attName);

	// this finds the type of the given attribute
	Type FindType(char *attName);

	// this reads the specification for the schema in from a file
	Schema(char *fName, char *relName);

	// this composes a schema instance in-memory
	Schema(char *fName, int num_atts, Attribute *atts);

	// deepcopy constructor
	Schema(const Schema &sch);

	// this constructs a sort order structure that can be used to
	// place a lexicographic ordering on the records using this type of schema
	int GetSortOrder(OrderMaker &order);

	~Schema();

	// Added by Yifan
	std::string toString();
};

#endif
