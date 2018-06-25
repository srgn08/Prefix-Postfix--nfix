//
// Created by sergen on 28.07.2017.
//

#include "StackDefinition.h"
using namespace std;

StackDefinition::StackDefinition()
    {
   	top=-1;
    }


    void StackDefinition::push_element(string element)
    {
        stack[++top]=element;
    };

    string StackDefinition::pop_element()
    {
        if(top<0)
        {
            cout<<endl<<"Stack is empty";
            return 0;
        }
        else
        {
            string return_element=stack[top];
            top--;
            return return_element;
        }

    }



