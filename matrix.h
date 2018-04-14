#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

using namespace std;

const int MAX_ROWS = 10; /// Maximum number of rows in a matrix.
const int MAX_COLS = 10; /// Maximum number of columns in a matrix.
const int OP_NUM = 4; /// Maximum number of options to a line (Example "1 2 3 4");
 /// Array of options, to be used when asking for input.

void init_options();
int getInt();

bool isValidHeight(int rows);
bool isValidWidth(int cols);
bool areValid(int rows, int cols);

int howManySpaces(int x);

class MatrixType
{
public:
 MatrixType();
 int getRows();
 int getCols();
 void MakeEmpty();
 void SetSize(int rowsSize, int colSize);
 void StoreItem(int item, int row, int col);
 void Add(MatrixType otherOperand, MatrixType& result);
 void Sub(MatrixType otherOperand, MatrixType& result);
 void Mult(MatrixType otherOperand, MatrixType& result);
 void Print(ofstream& outfile);
 void PrintToScreen();
 bool AddSubCompatible(MatrixType otherOperand);
 bool MultCompatible(MatrixType otherOperand);


private:
 int maxSpaces();
 int values[MAX_ROWS][MAX_COLS];
 int numRows;
 int numCols;
 bool isEmpty;


};

MatrixType GetNewMatrix();

#endif // MATRIX_H_INCLUDED
