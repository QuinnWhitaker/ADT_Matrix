# ADT_Matrix
A menu-based program that calculates the sum, difference, and product of user-defined custom matrices. 

Functionality:

The program holds a max of 10 matrices (that are removed after the program closes). Each are initialized as empty.
The main menu has six operations numbered 0-5. To operate the menu, specify the number of the operation, followed by which matrix/matrices will be used.

0 - New Matrix

Usage: 0 <matrix>
The matrix chosen is replaced with a new one defined by the user. The program will ask for dimensions, (in the format ROWS COLUMNS) followed by the contents of each row (in the format COLUMN1 COLUMN2 ... COLMUNX) then create a matrix of the given specifications.
  
1 - Add Matrix

Usage: 1 <matrix_1> <matrix_2> <matrix_3>
The sum of matrix_1 + matrix_2 replaces the contents of matrix_3 unless the operation is not possible.

2 - Subtract Matrix

Usage: 2 <matrix_1> <matrix_2> <matrix_3>
The difference of matrix_1 - matrix_2 replaces the contents of matrix_3 unless the operation is not possible.

3 - Multiply Matrix

Usage: 3 <matrix_1> <matrix_2> <matrix_3>
The product of matrix_1 * matrix_2 replaces the contents of matrix_3 unless the operation is not possible.

4 - Print Matrix

Usage: 4 <matrix>
  
The matrix chosen is printed to the screen.

5 - Quit

Usage: 5
  
The program stops running.
