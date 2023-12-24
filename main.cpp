#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string s;
    input >> s;

    int n = s.length();

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        matrix[i][i] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            if (s[i] == s[j] && len == 2) {
                matrix[i][j] = 2;
            } else if (s[i] == s[j]) {
                matrix[i][j] = matrix[i + 1][j - 1] + 2;
            } else {
                matrix[i][j] = max(matrix[i][j - 1], matrix[i + 1][j]);
            }
        }
    }

    int length = matrix[0][n - 1];

    string palindrome;
    palindrome.reserve(length);

    int i = 0, j = n - 1;
    while (i < j) {
        if (s[i] == s[j]) {
            palindrome.push_back(s[i]);
            ++i;
            --j;
        } else if (matrix[i][j - 1] > matrix[i + 1][j]) {
            --j;
        } else {
            ++i;
        }
    }

    if (i == j) {
        palindrome.push_back(s[i]);
    }

    for (int k = palindrome.length() - (length % 2) - 1; k >= 0; --k) {
        palindrome.push_back(palindrome[k]);
    }

    output << length << endl;
    output << palindrome << endl;

    input.close();
    output.close();

    return 0;
}
