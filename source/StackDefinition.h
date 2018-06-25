#ifndef UNTITLED3_STACKDEFINITION_H
#define UNTITLED3_STACKDEFINITION_H
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>

using namespace std;

class StackDefinition {
public:

    string stack[100];
    int top;
    StackDefinition();
    void push_element(string element);
    string pop_element();


};


#endif //UNTITLED3_STACKDEFINITION_H
