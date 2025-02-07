#include <iostream>
using namespace std;

void rotate90Clockwise(int matrix[][10], int N) 
{
    // Rotating layer by layer
    for (int layer = 0; layer < N / 2; layer++) 
    {
        int first = layer;
        int last = N - 1 - layer;

        for (int i = first; i < last; i++) 
        {
            int offset = i - first;
            //cyclic swaps
            int top = matrix[first][i];
            matrix[first][i] = matrix[last - offset][first]; // Left ---> Top
            matrix[last - offset][first] = matrix[last][last - offset]; // Bottom ---> Left
            matrix[last][last - offset] = matrix[i][last]; // Right ---> Bottom
            matrix[i][last] = top; // Top ---> Right
        }
    }
}

void printMatrix(int matrix[][10], int N) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    int N;
    cout << "Enter matrix size <=10(N x N): ";
    cin >> N;

    int matrix[10][10]; 
    cout << "Enter the matrix elements:\n";
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cin >> matrix[i][j];
        }
    }
    cout << "\nOriginal Matrix:\n";
    printMatrix(matrix, N);
    rotate90Clockwise(matrix, N);
    cout << "\nRotated Matrix:\n";
    printMatrix(matrix, N);
    return 0; //b_s
}
