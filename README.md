brainfuck
===========

An interpreter for the Brainfuck programming language written in C.


Version: 0.5.1


Features
--------
1. Circular memory tape of size 64KB
2. Tape cells can store signed integers
3. Can take Brainfuck programs as input in the form of files or directly as sequence of operators, passed as argument.
4. Sample Brainfuck programs can be found in the 'examples' directory.


Installation
-----------
Simply running 'make' at the command prompt will create the executable named 'bf' in the current working directory.
For proper installation, run these two commands at the command prompt:

$ make

\# make install (as root/superuser)

To uninstall, run:

\# make uninstall (as root/superuser)


Usage
-----
1. Running a Brainfuck program, stored in a file:
	To run the Hello World! example, which is available as 'hello_world.bf' in the examples directory, run the following line:

	$ bf -f examples/hello_world.bf

	To get the output "Hello World!" (without quotes).

2. Passing a sequence of Brainfuck operators directly to the interpreter:
	To execute a set of operations, such as >>+++. (which prints the content of the third cell after incrementing the existing value by three), run the 'bf' program as:

	$ bf -e '>>+++.'

3. Displaying help:
	$ bf -h

4. Running a program and then obtaining contents of tape cells:
	Run a program, as shown in either case 1 or case 2, with the only change being the addition of a '-t' option:

	$ bf -f examples/hello_world.bf -t 10

	This will display the result and then display the contents of cells 0 through 10.


Help
----
View the man page for brainfuck by typing 'man bf' at the command line.

E-mail: rohit305jha@gmail.com (Rohit Jha)
