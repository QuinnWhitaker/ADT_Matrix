#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "matrix.h"
using namespace std;

const int MAX_MAT = 10; /// Number of matrices in the matrix array.
MatrixType matrices[MAX_MAT];
int options[OP_NUM];

/// Returns whether or not the designated value in the options matrix is greater than -1 and less than the matrix max.
/// (if a valid value has been inserted into that space)
/// This function is used in the switch statement to determine whether to stop asking for input.
bool isVal(int val)
{
    if (val < 0 && val >= OP_NUM) return false;
    return (options[val] > -1 && options[val] < MAX_MAT);
}

bool quit = false;
bool opened_file = false;
int main()
{
    ofstream myfile;

    for (int y = 0; y < MAX_MAT; y++) /// Sets all values in the array of matrices to the default matrix.
    {
        MatrixType m_t;
        matrices[y] = m_t;
    }
    while (true) /// Loops the menu until prompted to quit.
    {
        cout << "Choice and Parameters:" << endl;
        cout << "0 New Matrix          Usage: 0 <matrix>" << endl;
        cout << "1 Add Matrices        Usage: 1 <matrix> <matrix> <matrix>" << endl;
        cout << "2 Subtract Matrices   Usage: 2 <matrix> <matrix> <matrix>" << endl;
        cout << "3 Multiply Matrices   Usage: 3 <matrix> <matrix> <matrix>" << endl;
        cout << "4 Print Matrix        Usage: 4 <matrix>" << endl;
        cout << "5 Quit                Usage: 5" << endl;
        cout << "Enter Choice and Parameters: ";
        init_options();

        for (int i = 0; i < OP_NUM; i++)
        {
            int item;
            cin >> item;
            options[i] = item;
            if (options[0] == 0 || options[0] == 4 ) /// If the first number is 0 or 4, break if the next number is a valid index in the matrix array.
            {
                if (isVal(1))
                {
                    cin.clear();
                    break;
                }
            }
            else if (options[0] == 5)
            {
                quit = true;
                cin.clear();
                break;
            }
            else if (options[0] > 0 && options[0] < 4){}
            else
            {
                cin.clear();
                break;
            }
        }

        switch (options[0]) /// This switch statement checks what the first value on the line is.
        {
        case 0:
            if (isVal(1))
            {
                cout << "Creating a new matrix at " << options[1] << "." << endl;
                matrices[options[1]] = GetNewMatrix();
                cout << "Here is your new matrix: " << endl;
                matrices[options[1]].PrintToScreen();
            }
        case 1:
            if (isVal(1) && isVal(2) && isVal(3))
            {
                cout << "Attempting to add matrix " << options[1] << " and matrix " << options[2] << ", placing the result in matrix " << options[3] << "." << endl;
                matrices[options[1]].Add(matrices[options[2]], matrices[options[3]]);
            }
            break;
        case 2:
            if (isVal(1) && isVal(2) && isVal(3))
            {
                cout << "Attempting to subtract matrix " << options[2] << " from matrix " << options[1] << ", placing the result in matrix " << options[3] << "." << endl;
                matrices[options[1]].Sub(matrices[options[2]], matrices[options[3]]);
            }
            break;
        case 3:
            if (isVal(1) && isVal(2) && isVal(3))
            {
                cout << "Attempting to multiply matrix " << options[1] << " and matrix " << options[2] << ", placing the result in matrix " << options[3] << "." << endl;
                matrices[options[1]].Mult(matrices[options[2]], matrices[options[3]]);
            }
            break;
        case 4:
            if (isVal(1))
            {
                if (!opened_file)
                {
                    myfile.open ("DataOut.txt");
                    opened_file = true;
                }

                cout << "Printing the following to DataOut.txt: " << endl;
                matrices[options[1]].PrintToScreen();
                matrices[options[1]].Print(myfile);
            }

            break;
        default:
            break;
        }
        if (quit) break;
    }
    cout << "Closing program." << endl;
    myfile.close();
}
