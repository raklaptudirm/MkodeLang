![Mkode](https://github.com/raklaptudirm/Mkode_compiler/blob/master/Mkode_icon.png)

# Mkode
Mkode is a new programming language designed by raklaptudirm. 
This is `v0.3.2.1`, a pre-release.
Mkode is an LOOPBNEOOP(Like OOP but not exactly OOP) or lup-benup(Pronounciation) language, written in C++.
In this file, the main structures and ideas of Mkode will be discussed.

Get the Sublime Text syntax highlighter [here](https://github.com/raklaptudirm/Mkode_syntax_highlighter).
# Features of Mkode:
Mkode is the programming language for the future. Mkode's syntax is consistent and their are no data types for variables. But that doesn't mean you cant take input or convert to any particular data type. Mkode is also free from any sort of run-time errors: If the syntax is correct, there will be no errors.
Mkode also converts the value of variables to another data type automatically when required. So `"1"+1` results in `2`. To join strings, the operator `@` is used. Therefor, `"1"@1` results in `11`.
# Building the compiler:
To build the compiler, download the code files of the release you want to use. Using a C++ compiler run the `.cpp` file and generate an `.exe` file.
# Using the compiler:
### Version `v0.1.4.0` and older:
To use the compiler, write your code in the Source.mkode file and run the `.exe` file.
### Later versions:
To use the compiler, write your code in a file and run the `.exe`. Provide the file path to the compiler. 
## Comments:
Comments in Mkode are done as follows:
`#`for single line comments:

    #Single Line Comment
 `#'` and `'#` for multi line comments:
 
     #' Multi Line
     comment'#


## Classes: (Not Implimented)
Classes in Mkode are defined as blocks of codes which are independent of each other. Each class owns a set of variables, arrays and functions which can be used by it, but if it doesn't own the variables, arrays or functions, it can't use them. Classes are executed top to bottom.
Class declaration: 

    New:class[main] {
                   }

## Functions: (Not Implimented)
Functions are code blocks which can take inputs and run code according to them when called by the classes. They are not executed on their own.
Function declaration:

    New:function[calc[dstring a, int num]] {
                      }
Function usage: function:

    calc["hi",13];
    
Output in functions: 

    calc:out[var];
No output function: 

    calc:out[void];

## Flowing concept: (Not Implimented)
Flowing is a new concept in Mkode. Flowing a variable, array, function into a class means allowing the class to use them. Multiple objects can also be flowed into multiple classes.
Flowing: 

    newObject:function[abc]:main{
         }

## Variables:
Variables in Mkode are weak typed. Or, they have no paticular data type. But they are Static typed, or have to be declared. The default value of variables in Mkode is 0.
Variable declaration: 

    New:var[a,b,c];

## Strings in Mkode:
Mkode supports two types of strings. The ustring and the cstring.

Ustrings are written inside double quotes("").
`Console:out["abc\""];`
Output:
`abc"`

Cstrings are written inside single quotes('').
`Console:out['abc\"'];`
Output:
`abc\'`

In otherwords, ustring(unconverted string) parses the escape sequences while cstring(converted string) doesn't.

## Backslash and Escape Sequences:
Supported sequences:
1) \\" -> "
2) \\' -> '
3) \s -> \

Backslash can be used freely(without the escape sequence) in not only cstrings but also in ustrings, if the next character is not an escape sequence character.
Or,
`Console:out["abc\ "];`
Output:
`abc\ `

## Console functions:
Mkode provides three main console functions: `clear`, `out`, `nextLine`; which are used to clear the console, to print in the console and to move the cursor to the next line respectively.
Usage: 

    Console:clear[];
    Console:out["hello world"];
    Console:nextLine[2]; //The number specifies the number of lines to skip.
The print string is created as follows:`[a@a@a@a];`
`a` can be replaced by both constants and variables and expressions.
Example: 

    Console:out["hi" @ var @ "Hello world" @ num];

## Input:
    Kode:in[]:var_name;

## Halt function:
The halt function stops the execution of the program immidiately when this statement is encountered.
Usage: 

    Kode:halt[];
## Delay Function:
    Kode:delay[time_in_milliseconds];
    
## If usage: (Not Implimented)

    if []{
    } elseIf [] {
    } else {
    }

## Path selection: (Not Implimented)
Path selection is just like switching in Java or C++.
Usage: 

    proceedTo[] {
    path[a]:
    path[b]:
    path[c]:
    }
