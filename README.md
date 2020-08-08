![Mkode](https://github.com/raklaptudirm/Mkode_compiler/blob/master/Mkode_icon.png)

![Mkode]( https://github.com/raklaptudirm/Mkode_compiler/blob/master/68747470733a2f2f7472617669732d63692e6f72672f6477796c2f657374612e7376673f6272616e63683d6d6173746572.svg )
# Mkode
Mkode is a new programming language designed by raklaptudirm. 
This is v0.1.4.0, a pre-release.
Mkode is an LOOPBNEOOP(Like OOP but not exactly OOP) or lup-benup(Pronounciation) language developed by Mridutpal Kar, written in C++.
In this file, the main structures and ideas of Mkode will be discussed.
# Features of Mkode:
Mkode is the programming language for the future. Mkode's synatx is consistent and their are no data types for variables. But that doesn't mean you cant take input or convert to any particular data type. Mkode is also free from any sort of run-time errors: If the syntax is correct, there will be no errors.
Mkode also converts the value of variables to another data type automatically when required. So "1"+1 results in 2. To join strings, the operator @ is used.
# Building the compiler:
To build the compiler, download the code flies of the release you want to use. Using a C++ compiler(Dev is reccomended) run the .dev file and generate an .exe file. Write your code in the "Source.mkode" file and run the .exe file.
## Comments:
Comments in Mkode are done as follows:
/# for single line comments:

    #Single Line Comment
 #' and '# for multi line comments:
 
     #' Multi Line
     comment'#


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
    Kode:in[datatype];//Data types can be int, float, string, char, boolean, num, unsigned
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
    path[a]:
    path[b]:
    path[c]:
    }
