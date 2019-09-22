#ifndef Argument_H
#define Argument_H

#include <vector>

/*
Abstract class representing an argument.
An abstract argumentation argument is intended to store some sort of information.

This class requires each argument to have an associated identifier.
*/

class Argument {
    
public:
    virtual int getArgID() = 0;
};

#endif