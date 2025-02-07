#include <iostream>
using namespace std;

void displayMatrix(int matrix[100][100], int n) 
{
    cout << "\nMatrix Representation:\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}
void printSpiral(int matrix[100][100], int n) 
{
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    cout << "\nSpiral Order Output:\n";
    while (top <= bottom && left <= right) 
    {
        // Moving left --> right
        for (int i = left; i <= right; i++)
            cout << matrix[top][i] << " ";
        top++;
        // Moving top --> bottom
        for (int i = top; i <= bottom; i++)
            cout << matrix[i][right] << " ";
        right--;
        // Moving right --> left (if still in boundary)
        if (top <= bottom) 
        {
            for (int i = right; i >= left; i--)
                cout << matrix[bottom][i] << " ";
            bottom--;
        }
        // Moving bottom --> top (if still in boundary)
        if (left <= right) 
        {
            for (int i = bottom; i >= top; i--)
                cout << matrix[i][left] << " ";
            left++;
        }
    }
    cout << endl;
}
int main() 
{
    int n;
    cout << "Enter the matrix size (n x n): "; //should be a square matrix
    cin >> n;
    int matrix[100][100];  // Assuming max size is 100x100

    // Taking input
    cout << "Enter matrix elements row-wise:\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> matrix[i][j];
        }
    }
    displayMatrix(matrix, n);
    printSpiral(matrix, n);
    return 0; //b_s
}
