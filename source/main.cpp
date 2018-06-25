 #include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include "StackDefinition.h"

using namespace std;

void convert_prefix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output); //convert function from input to convert prefix format
void convert_infix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output); //convert function from input to convert infix format
void convert_postfix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output); //convert function from input to convert postfix format
void convert_output(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output);  //convert function from input to convert output format
int control_operator(int number1, int number2, string op);  // this function used output format and make operations to come operator
bool control_paranthesis(string op , string op2);  // this functions used infix format and controlled paranthesis is important or not



int main(int argc, char*argv[]) {
    char* file_name;

    file_name=argv[1];
    int t=0;
    string line=" ";
    ifstream myfile (file_name); //input file
    ofstream myfile2 (argv[2]);  //prefix
    ofstream myfile3 (argv[3]);  //infix
    ofstream myfile4 (argv[4]);  //postfix
    ofstream myfile5 (argv[5]);  //output
    StackDefinition number[100];         //stack of have numbers
    StackDefinition operator_stack[100]; //stack of have operators
    int index=0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )    //program read input and take a line
        {
            string array[1000];
            array[index]=line;



    char value[100];
    string value2=array[index];
    strcpy(value,value2.c_str());
    char *keep;
    string temp=" ";
    keep = strtok (value," \t");    // program split of tab or space
    while (keep != NULL)
    {

        temp=keep;
        if(temp!="*" && temp!="/" && temp!="-" && temp!="+" && temp!="^")   //operator or number controls
        {
            number[t].push_element(temp);   //if input is number , number pushed in number stack
        }

        else
        {
            operator_stack[t].push_element(temp);  // if input is operator , operator pushed in operator stack
        }
        keep = strtok (NULL, " ");
    }



    convert_prefix(number[t],operator_stack[t],myfile2);   // program call convert prefix function
    convert_postfix(number[t],operator_stack[t],myfile4);  // program call convert postfix function 
    convert_infix(number[t],operator_stack[t],myfile3);    // program call convert infix function
    convert_output(number[t],operator_stack[t],myfile5);   // program call convert output function

            t++;
            index++;
        }


        myfile.close();
        myfile2.close();
        myfile4.close();
        myfile3.close();
        myfile5.close();
    }

    return 0;
}

void convert_prefix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output)
{
    StackDefinition numbers;
    StackDefinition operators;
    int i=0;
    int z=number_stack.top;
    int y=operator_stack.top;
    while(i<=z)
    {
        numbers.push_element(number_stack.stack[z]);
        z--;
    }

    while(i<=y)
    {
        operators.push_element(operator_stack.stack[y]);
        y--;
    }
    while(i<numbers.top) // this loop pop the element and write output file
    {
        output<<operators.pop_element()<<" ";
        output<<numbers.pop_element()<<" ";
    }
    output<<numbers.pop_element()<<" ";
    output<<endl<<"";

}

bool control_paranthesis(string op , string op2) //paranthesis control
{
    if(op=="*")  //if input "*" and another input is "^", program put paranthesis
    {
        if(op2!="^")
            return true;
        else
            return false;
    }


    else if(op=="/")
    {
        if(op2!="^")
            return true;
        else
            return false;
    }


    else if(op=="-")
    {
        if(op2=="+")
            return true;
        else
            return false;
    }


    else if(op=="+")
    {
        if(op2=="-")
            return true;
        else
            return false;
    }


    else
        return true;

}


void convert_infix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output)

{


    StackDefinition numbers;

    StackDefinition operators;
    int control=0,i=0,index=0;
    string op=" ",op2=" ";
    bool flag_paranthesis;
    int z=number_stack.top;

    int y=operator_stack.top;

    while(i<=z)

    {

        numbers.push_element(number_stack.stack[z]);

        z--;

    }


    while(i<=y)

    {

        operators.push_element(operator_stack.stack[y]);

        y--;

    }



    while(i<=operators.top)
    {
        if(index==0)
        {
            output<<numbers.pop_element()<<" ";
            op=operators.pop_element();
            output<<op<<" ";
        }

        else
        {
            op2=operators.pop_element();
            flag_paranthesis = control_paranthesis(op, op2);
            if(flag_paranthesis==true)
	    {
		output<<"("<<" ";
		control++;
	    }
                

            output<<numbers.pop_element()<<" ";
            output<<op2<<" ";
            op=op2;
            
        }
        index++;

    }
    output<<numbers.pop_element()<<" ";
    while(i<control)
    {
        output<<")"<<" ";
	i++;
    }

    output<<endl;
}






void convert_postfix(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output)
{

    StackDefinition numbers;
    StackDefinition operators;
    int i=0;
    int z=number_stack.top;
    while(i<=z)
    {
        numbers.push_element(number_stack.stack[z]);
        z--;
    }

    operators=operator_stack;
    while(i<=numbers.top)
    {
        output<<numbers.pop_element()<<" ";
    }

    while(i<=operators.top)
    {
        output<<operators.pop_element()<<" ";
    }
    output<<endl;
}

void convert_output(StackDefinition number_stack ,StackDefinition operator_stack, ofstream &output)

{


    StackDefinition numbers;

    StackDefinition operators;

    numbers=number_stack;
    operators=operator_stack;
    int i=0,control=1,result=0,flag=0;
    int number1,number2;
    string op=" ";
    while(i<=operators.top)
    {

        if(control==1)
        {
            number1=atoi(numbers.pop_element().c_str());
            number2=atoi(numbers.pop_element().c_str());
            op=operators.pop_element();
            if(op=="/" && number1==0)  // divided by zero control
            {
                output<<"Nan";
                i=operators.top+1;
                flag++;
            }
            else
                result = control_operator(number2,number1,op);

        }
        else
        {
            number1=result;
            number2=atoi(numbers.pop_element().c_str());
            op=operators.pop_element();
            if(op=="/" && number1==0)
            {
                output<<"NaN";  //program write divided by zero
                i=operators.top+1;
                flag++;
            }
            else
                result=control_operator(number2,number1,op);


        }
        control++;
    }


    if(flag!=1)  // if program see divided by zero error , program dont write result
        output<<result;

    output<<endl;
}




int control_operator(int number1, int number2, string op) // program make a operations to input operator
{
    int result=0;
    if(op=="*")
        result=number1*number2;

    else if(op=="/")
        result=number1/number2;



    else if(op=="-")
        result=number1-number2;

    else if(op=="+")
        result=number1+number2;

    else
        result=pow(number1,number2);

    return result;
}
