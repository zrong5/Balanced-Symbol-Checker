# Balanced-Symbol-Checker
## Programming Praticum
This is a C program that will determine whether input is given with properly balanced symbols. We will often use symbols together to specify the beginning and ending of an item, such as the use of parentheses in a mathematic expression or the use of curly braces in a C, C++ or Java program. This will be checking the following symbol pairs:
* parentheses: ( )
* curly braces: { }
* square brackets: [ ]
* angle brackets: < >

This program make use of a stack implemented in a dynamic array. This dynamic array is grows to a larger size when a push operation would be done to a full array causing an array overflow. This array will grow by 2 additional positions once it is full everytime.

## Input
The input for this program will come from standard input. Each line of input will be a single
expression that is to be checked for balanced symbols. The program will loop to read in multiple lines of input. If the input on
the line contains only the letter q or Q, the program will quit.

## Output
For each line of input, program will display the input and specify whether the expression
* is balanced
* is unbalanced because it is expecting a different closing symbol (the wrong closing symbol is
on the top of the stack)
* is unbalanced because it is missing an opening symbol (stack is empty when a closing symbol is
encountered)
* is unbalanced because it is missing a closing symbol (line ends while the stack is not empty)
For the unbalanced expression, print the “up arrow” character at the place where the unbalanced error
occurred. 

The following are some examples output showing the 4 possible outcomes:
( ( a a ) < > [ [ [ { [ x ] } ]]] <>)
Expression is balanced
( ( a a ) < > [ [ [ { [ x ] ]]] <>)
                            ^ expecting }
( ( a a ) ) < > > [ [ [ { [ x ] } ]]] <>)
            ^ missing <
( ( a a ) < > [ [ [ { [ x ] } ]]]
          ^ missing ) 
