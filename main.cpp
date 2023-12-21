#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string str;
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> str;
    in.close();
    int n;
    n = str.length();
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        matrix[i][i] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        if (str[i] == str[i + 1])
            matrix[i][i + 1] = 2;
        else
            matrix[i][i + 1] = 1;
    }

    for (int i = n - 3; i > -1; i--) {
        for (int j = 2; j < n; j++) {
            if (i < j) {
                if (str[i] == str[j])
                    matrix[i][j] = matrix[i + 1][j - 1] + 2;
                else
                    matrix[i][j] = max(matrix[i + 1][j], matrix[i][j - 1]);
            }
        }
    }
    string result;
    int i = 0;
    int j = n - 1;
    int length = matrix[0][n - 1];
    while (length > 0 && i <= j) {
        if (str[i] == str[j]) {
            result += str[i];
            i++;
            j--;
            length -= 2;
        } else {
            if (matrix[i][j - 1] < matrix[i + 1][j])
                i++;
            else
                j--;
        }
    }
    for (int k = matrix[0][n - 1] / 2 - 1; k > -1; k--) {
        result += result[k];
    }
    out << matrix[0][n - 1] << endl;
    out << result;
    out.close();
    return 0;
}