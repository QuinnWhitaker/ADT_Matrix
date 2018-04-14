#include <iostream>
#include <sstream>
#include <string>
#include "matrix.h"
#include <fstream>
using namespace std;

extern int options[OP_NUM];
void init_options() /// Sets all values in the options array to -1.
{
    for (int x = 0; x < OP_NUM; x++)
    {
        options[x] = -1;
    }
}
/// Returns an integer inputted by the user. Returns -1 if they did not enter an int.
int getInt()
{
    int r = 0;
    while(true)
    {
        string s;
        cin >> s;

        stringstream stream(s);
        if(stream >> r)
        {
            break;
            continue;
        }
        cout << "Expected integer - try again: ";
        return -1;
    }
    return r;
}

/// These three functions are used to determine whether a given set of dimensions is valid.
bool isValidHeight(int rows)
{
    return (rows > 0 && rows <= MAX_ROWS);
}

bool isValidWidth(int cols)
{
    return (cols > 0 && cols <= MAX_COLS);
}

bool areValid(int rows, int cols)
{
    bool r = true;
    if (!isValidHeight(rows))
    {
        cout << "Error: Invalid number of rows." << endl;
        r = false;
    }

    if (!isValidWidth(cols))
    {
        cout << "Error: Invalid number of columns." << endl;
        r = false;
    }
    return r;
}


/// This function takes an int and returns how many spaces it occupies, for printing purposes.
int howManySpaces(int x)
{
    /// if the int is zero, we'll know immediately that it only has one digit.
    if (x == 0) return 1;
    int r = 1; /// The return value
    int t = 10; /// This index will continuously multiply by ten until it is greater than or equal to x.
    /// Each time it multiplies, r will be increased by 1.

    /// If x is negative, the negative sign takes up one space, so increment r by one.
    /// The algorithm that will be used however is only implemented by positive numbers, so multiply
    /// x by -1.
    if (x < 0)
    {
        r++;
        x *= -1;
    }

    while (true)
    {
        if (x < t) return r;
        r++;
        t*=10;
    }
}

int MatrixType::maxSpaces()
{
    int maxSpaces = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int i2 = 0; i2 < numCols; i2++)
        {
            int h = howManySpaces(values[i][i2]);
            if (maxSpaces < h) maxSpaces = h;
        }
    }
    return maxSpaces;
}

MatrixType::MatrixType()
{
    /// Initializes the matrix, and makes it an empty 1x1 matrix by default.
    SetSize(1, 1);
    MakeEmpty();
}

int MatrixType::getRows()
{
    return numRows;
}

int MatrixType::getCols()
{
    return numCols;
}

void MatrixType::MakeEmpty()
{
    /// Sets all values of the matrix to 0, and sets it as a new matrix.
    values[MAX_ROWS][MAX_COLS] = {0};
    isEmpty = true; /// If all values in the matrix are zero, the matrix is empty.
}

void MatrixType::SetSize(int rowsSize, int colSize)
{
    /// Changes the size of the matrix to the inputted values, if they are valid.

    /// Checks if the values are valid. If not, stops the function.
    if (!areValid(rowsSize, colSize)) return;


    /// If the values are valid it begins to resize the matrix.
    /// If the matrix is not a new matrix, this searches the two dimensional array for nonzero entries.
    /// Although some arrays may have 0 in them, 0 is also the default value of an array.
    /// If a value is not 0, it is set to 0 (the default value) if its location falls outside of the newly set matrix size.
    if (!isEmpty)     /// If the matrix isn't empty it will search the two dimensional array for nonzero entries.
    {
        for (int i = 0; i < MAX_ROWS; i++)
        {
            for (int i2 = 0; i2 < MAX_COLS; i2++)
            {
                if (i >= rowsSize || i2 >= colSize) values[i][i2] == 0;
            }
        }
    }
    /// Sets the private variables indicating the array size to the new values. Declares that the sizes have have determined.
    numRows = rowsSize;
    numCols = colSize;
}

void MatrixType::StoreItem(int item, int row, int col)
{
    /// Inserts a value into the specified location of the two dimensional array, if the location is valid.

    /// Checks if the destination exists within the size of the matrix. If not, stops the function.
    if (row < 0 || row > numRows)
    {
        cout << "Error: Invalid row specified." << endl;
        return;
    }

    if (col < 0 || col > numCols)
    {
        cout << "Error: Invalid column specified." << endl;
        return;
    }

    /// Replaces the previous value at the selected location with the new one.
    values[row][col] = item;
    if (item != 0 && isEmpty) isEmpty = false; /// If a nonzero entry was added to an empty matrix, the matrix is no longer empty.
}

void MatrixType::Print(ofstream& outfile)
{
    int m = maxSpaces();

    for (int i = 0; i < numRows; i++)
    {
        outfile << "[ ";
        for (int i2 = 0; i2 < numCols; i2++)
        {
            for (int i3 = 0; i3 < (m - howManySpaces(values[i][i2])); i3++)
            {
                outfile << " ";
            }
            outfile << values[i][i2] << " ";
        }
        outfile << "]\n";
    }
    outfile << "\n";

}
void MatrixType::PrintToScreen()
{
    /// Prints the matrix with brackets to the screen.

    /// For printing purposes, the highest number of spaces among the values in the matrix will be found.
    /// This index will be compared to each value in the matrix. If a value's space count is greater than
    /// the index, the index will be increased to that number.

    int m = maxSpaces();
    /// Each row will begin with a left bracket and end with a right bracket.
    /// Each column will be separated by at least one space, and then rightmost aligned on
    /// a number of spaces equal to the highest space count.

    for (int i = 0; i < numRows; i++)
    {
        cout << "[ ";
        for (int i2 = 0; i2 < numCols; i2++)
        {
            for (int i3 = 0; i3 < (m - howManySpaces(values[i][i2])); i3++)
            {
                cout << " ";
            }
            cout << values[i][i2] << " ";
        }
        cout << "]" << endl;
    }
}

bool MatrixType::AddSubCompatible(MatrixType otherOperand)
{
    /// Checks whether the current matrix and the inputted matrix can be added and subtracted.
    /// Two matrices can be added or subtracted only if both have the same number of rows and columns.
    return ((numRows == otherOperand.getRows()) && (numCols == otherOperand.getCols()));
}

bool MatrixType::MultCompatible(MatrixType otherOperand)
{
    /// Checks whether the current matrix and the inputted matrix can be multiplied.
    /// Two matrices can be added or subtracted only if the number of columns in the first matrix equals the number of rows in the second matrix.
    return (numCols == otherOperand.getRows());
}

void MatrixType::Add(MatrixType otherOperand, MatrixType& result)
{
    /// Takes three matrices, adding the first two and storing the result in the third.

    /// Checks that the matrices can be added, if not the function stops.
    if (!AddSubCompatible(otherOperand))
    {
        cout << "Error: These matrices cannot be added." << endl;
        return;
    }
    /// Sets the size of the third matrix to the first.
    result.SetSize(numRows, numCols);
    /// Sets each value of the third matrix to the sum of the corresponding values of the first two.
    for (int i = 0; i < numRows; i++)
    {
        for (int i2 = 0; i2 < numCols; i2++)
        {
            result.values[i][i2] = values[i][i2] + otherOperand.values[i][i2];
        }
    }
    cout << "Matrices successfully added." << endl;
    result.PrintToScreen();
}

void MatrixType::Sub(MatrixType otherOperand, MatrixType& result)
{
    /// Takes three matrices, subtracting the second from the first and storing the result in the third.

    /// Checks that the matrices can be subtracted, if not the function stops.
    if (!AddSubCompatible(otherOperand))
    {
        cout << "Error: These matrices cannot be subtracted." << endl;
        return;
    }
    /// Sets the size of the third matrix to the first.
    result.SetSize(numRows, numCols);
    /// Sets each value of the third matrix to the difference of the corresponding values of the first two.
    for (int i = 0; i < numRows; i++)
    {
        for (int i2 = 0; i2 < numCols; i2++)
        {
            result.values[i][i2] = values[i][i2] - otherOperand.values[i][i2];
        }
    }
    cout << "Matrices successfully subtracted." << endl;
    result.PrintToScreen();
}

void MatrixType::Mult(MatrixType otherOperand, MatrixType& result)
{
    /// Takes three matrices, multiplies the first two and stores the result in the third.

    /// Checks that the matrices can be multiplied. If not, the function stops.
    if (!MultCompatible(otherOperand))
    {
        cout << "Error: These matrices cannot be multiplied." << endl;
        return;
    }
    MatrixType temp_mat; /// Temporary matrix, operations will be applied to this, and post-product the result matrix will become this.
    temp_mat.SetSize(numRows, otherOperand.getCols());
    /// Matrix 1 and 2 are multiplied using the dot product
    int sum = 0;/// The value which will be inputted into the current location of the result matrix.
            /// Each column of the first matrix in this row will be multiplied by each row in this column,
            /// and the results will each be added to this sum.
    for (int i = 0; i < numRows; i++) /// Row on the result matrix and first matrix.
    {
        for (int i2 = 0; i2 < otherOperand.getCols(); i2++) /// Column on the result matrix and second matrix.
        {
            for (int i3 = 0; i3 < numCols; i3++) /// Column on the first matrix and row on the second matrix.
            {
                sum += (values[i][i3]*otherOperand.values[i3][i2]);
            }
            temp_mat.values[i][i2] = sum;
            sum = 0; /// sum is reset to 0 to determine the new value
        }
    }
    /// Sets the size of the third to the height of the first matrix by the width of the second.
    result = temp_mat;
    cout << "Matrices successfully multiplied." << endl;
    result.PrintToScreen();
}



/// This function creates a new Matrix outside of the Matrix class.
MatrixType GetNewMatrix()
{
    /// Creates a new matrix.
    MatrixType temp_mat; /// Temporary Matrix, to be returned.
    int nrows; /// New matrix width
    int ncols; /// New matrix height

    /// Prompts for width and length, retries if values are lower than one or greater than max.

    cout << "Enter dimensions <row> <column>: ";
    nrows = getInt();
    while (!isValidHeight(nrows))
    {
        cout << "Invalid number of rows (Max rows " << MAX_ROWS << ") - try again: ";
        nrows = getInt();
    }
    ncols = getInt();
    while (!isValidWidth(ncols))
    {
        cout << "Invalid number of columns (Max columns " << MAX_COLS << ") - try again: ";
        ncols = getInt();
    }


    /// Matrix size is set to the determined values.
    temp_mat.SetSize(nrows, ncols);
    /// For each entry in the matrix, the user is prompted to enter an integer.
    for (int i = 0; i < nrows; i++)
    {
        cout << "Row " << i << ": ";
        for (int i2 = 0; i2 < ncols; i2++)
        {
            temp_mat.StoreItem(getInt(), i, i2);
        }
    }
    return temp_mat;
}
