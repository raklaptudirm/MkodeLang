# Mkode
Mkode is a new programming language designed by raklaptudirm. 
This is v0.1.2.7, a pre-release.
Mkode is an LOOPBNEOOP(Like OOP but not exactly OOP) or lup-benup(Pronounciation) language developed by Mridutpal Kar, written in C++.
In this file, the main structures and ideas of Mkod will be discussed.

## Classes:
Classes in Mkode are defined as blocks of codes whih are indipendent of each other. Each class owns a set of variables, arrays and functions which can be used by it, but if it doesn't own the variables, arrays or functions, it can't use them. Classes are executed top to bottom.
Class declaration: 

    newObject:class[main] {
                   }

## Functions:
Functions are code blocks which can take inputs and run code according to them when called by the classes. They are not executed on their own.
Function declaration:

    newObject:function[calc[var a, int num]] {
                      }
Function usage: function:

    calc["hi",13];
Output in functions: 

    calc:out[var];
No output function: 

    calc:out[void];

## Flowing concept:
Flowing is a new concept in Mkode. Flowing a variable, array, function into a class means allowing the class to use them. Multiple objects can also be flowed into multiple classes.
Flowing: 

    newObject:function[abc]:main{
         }

## Variables:
Variables in Mkode are weak typed. Or, they have no paticular data type. But they are Static typed, or have to be declared.
Variable declaration: 

    newObject:var[a,b,c];

## Console functions:
Mkode provides three main console functions: clear, out, nextLine; which are used to clear the console, to print in the console and to move the cursor to the next line respectively.
Usage: 

    Console:clear[];
    Console:out["hello world"];
    Console:nextLine[2]; //The number specifies the number of lines to skip.
The print string is created as follows:[a&a&a&a];
'a' can be replaced by both constants and variables and expressions.
Example: 

    Console:out["hi" & var & "Hello world" & num];

## Input:
    Kode:in[datatype];//Data types can be int, float, string, char, boolean
Storage: 

    integer=Kode:in[int];

## Halt function:
The halt function stops the execution of the program immidiately when this statement is encountered.
Usage: 

    Kode:halt[];

## If usage:

    if []{
    } elseIf [] {
    } else {
    }

## Path selection:
Path selection is just like switching in Java or C++.
Usage: 

    proceedTo[] {
    path[a]{
    } path [b]{
    }path[c]{
    }
    }
