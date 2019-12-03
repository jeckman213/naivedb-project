## Todo List:
- Update program to reflect project guidelines:
  1. A C source file named naivedb.c with just the main function for your shell program.
  2. A C source file named create.c with just the main function for the list program.
  3. A C source file named fileconverter.c with just the main function for the fileconverter
  program.
  4. A C source file named interfaceFunctions.c, which contains functions for handling the
  commands (i.e., quit and output redirection) that the shell program must perform.
  5. A C source file named input.c with the function char* getLine(FILE* stream). This
  function reads one line from the specified file and returns the result as a null terminated
  string. Note that this can be used to read from stdin by calling it as getLine(stdin). This
  source file can additionally contain helper functions.
  5
  6. A header file containing the structure definition(s) for your BST and function prototypes for
  functions related to your BSt table, i.e., inserting a node into the table, retrieving the number
  of flights given an airline code, and printing the contents of the tree to stdout.
  7. A header file containing the structure definition(s) of your hash table and the function prototypes for functions related to your hash table.
  8. The C file hashFunction.c which will be provided to you on Blackboard, and contains a
  hash function that you must use in your program.
  9. Your makefile should include a clean target.

