//
//  eval.cpp
//  Homework 2
//
//  Created by Brian Chang on 4/30/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <string>

using namespace std;

string removeSpaces(string infix);
int precedence(char chr);
string postfixConversion( string infix, string postfix);

//Initialize the operand stack to empty
//For each character ch in the postfix string
//    if ch is an operand
//        push the value that ch represents onto the operand stack
//    else // ch is a binary operator
//        set operand2 to the top of the operand stack
//    pop the stack
//        set operand1 to the top of the operand stack
//    pop the stack
//    apply the operation that ch represents to operand1 and
//            operand2, and push the result onto the stack
//When the loop is finished, the operand stack will contain one item,
//  the result of evaluating the expression

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

string removeSpaces(string infix)            //trivial space remover fxn.
{
    string spacesRemoved = "";               //initalise an empty string
    
    for (int i = 0; i < infix.size(); i++)   //walk through the infix string
    {
        if (infix[i] != ' ')                 //if char isn't a space
            spacesRemoved += infix[i];       //add it to the return string
    }
    return spacesRemoved;
}

int precedence(char chr)    //trivial precendence fxn.
{
    switch (chr) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            return -1;
    }
}

string postfixConversion( string infix, string postfix)
{
    postfix = "";                           //    Initialize postfix to empty
    stack<char> operatorStack;              //    Initialize the operator stack to empty
    
    for (int i = 0; i < infix.size(); i++)  //    For each character ch in the infix string
    {
        char chr = infix[i];

        switch (chr)                        //Switch (chr)
        {
            case 'T':                       //case true operand
            case 'F':                       //case false operand
                postfix += chr;             //append to end of postfix.
                break;                      //break
                
            case '(':                       //case open parantheses
                operatorStack.push(chr);    //push to stack
                break;                      //break;
            
            case ')':                       //case closed parantheses
                while (operatorStack.top() != '(')       //keep popping until we get to the open parantheses, add to postfix
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();        //pop the open parantheses.
                break;                      //break;
            
            case '!':                       //case operators
            case '&':
            case '^':
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(chr) <= precedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();     //append top of stack to postfix
                    operatorStack.pop();                //pop stack
                }
                operatorStack.push(chr);                //push the char
                break;                                  //break
                
            default:
                break;
        }
    }
        
    while (!operatorStack.empty())          //    While the stack is not empty
    {
        postfix =+ operatorStack.top();     //        append the stack top to postfix
        operatorStack.pop();                //            pop the stack
    }
    
    return postfix;
}

//Initialize postfix to empty
//Initialize the operator stack to empty
//For each character ch in the infix string
//    Switch (ch)
//      case operand:
//        append ch to end of postfix
//        break
//      case '(':
//        push ch onto the operator stack
//        break
//          case ')':
//          // pop stack until matching '('
//        While stack top is not '('
//          append the stack top to postfix
//          pop the stack
//        pop the stack  // remove the '('
//        break
//      case operator:
//        While the stack is not empty and the stack top is not '('
//                and precedence of ch <= precedence of stack top
//            append the stack top to postfix
//                pop the stack
//            push ch onto the stack
//            break
//While the stack is not empty
//    append the stack top to postfix
//        pop the stack



















//int main()
//{
//string pf;
//    bool answer;
//    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
//    assert(evaluate("T^", pf, answer) == 1);
//    assert(evaluate("F F", pf, answer) == 1);
//    assert(evaluate("TF", pf, answer) == 1);
//    assert(evaluate("()", pf, answer) == 1);
//    assert(evaluate("()T", pf, answer) == 1);
//    assert(evaluate("T(F^T)", pf, answer) == 1);
//    assert(evaluate("T(&T)", pf, answer) == 1);
//    assert(evaluate("(T&(F^F)", pf, answer) == 1);
//    assert(evaluate("T|F", pf, answer) == 1);
//    assert(evaluate("", pf, answer) == 1);
//    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
//                           &&  pf == "FF!TF&&^"  &&  !answer);
//    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
//    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
//    cout << "Passed all tests" << endl;
//}
