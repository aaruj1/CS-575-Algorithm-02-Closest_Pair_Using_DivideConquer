This code identifies the closest pair of co-ordinates (either 2-dimensional or 3-dimensional) and reports them. Two algorithms namely Brute-force and Divide-and-Conquer have been implemented. The code takes two command-line arguments: one is an input filename which will have the set of co-ordinates, and other is an output file where it will write the closest pair co-ordinate indices and distance between them.

Input file must provide point in the following manner.
n 
x1 y1 (z1)
x2 y2 (z2)
x3 y3 (z3)
.
.
.
.
.
xn yn (zn)


This code also works in 3-dimension space.

Below are the steps to run the submission.c:

Step 1: Use the makefile to compile the code
        $make all

Step 2: Run the code with 2 command line-argument input file and output file name 
	$./submission input.txt output.txt

If any problem contact me at : aaruj1@binghamton.edu
