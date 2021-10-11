#include "Stack.h"
#include "hashmap.h"
#include <QString>
#include <QVector>
#include <QDebug>

#ifndef CONVERTFUNC_H
#define CONVERTFUNC_H

double calc(const double& num1, const double& num2, const char& op);

class Expression{
private:
    Stack<char> opStack;    //stack that stores the operators, updates lively
    Stack<double> numStack;    //stack that stores the numbers, updates lively
    Stack<char> errorInput; //stack that stores error inputs in order to simple backspace operation
    QString expString;      //string of the expression, used for html convertion and backspace operation (rebuilds the state of stacks)
    QString opChange;
    QString numChange;

    int inputCons;  //constraint of next input num, used for %
    /*Constraint map:
     * 000000 Nothing acceptable
     * 100000 accept (
     * 010000 accept operators
     * 001000 accept integer
     * 000100 accept dot
     * 000010 accept fracture
     * 000001 accept minus
     */

    void rebuildStacks();   //rebuild stacks from the exp string
    void update(int index);       //calculate the objects in the stack and update the stack for new operations

public:
    Expression() : inputCons(0b101011){}
    Expression(QString exp) : expString(exp), inputCons(0b101011) { rebuildStacks(); }   //build an expression from a string
    void insert(char c);    //insert new character to the expression
    void backSpace();       //delete one character from the expString
    void clr();             //clear the current expression
    bool prepare(); //true if stack refresh is needed
    QString expStr();
    QString numDifStr();
    QString opDifStr();
    QString numStackToStr();
    QString opStackToStr();
    QString expToHtml();    //convert the expString to html syntax
    QString resToHtml();    //convert the result to html syntax
};

#endif // CONVERTFUNC_H
