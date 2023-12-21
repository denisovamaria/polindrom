#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

pair<int, string> longestPalindrome(const string& s) {
    int n = s.length();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            if (s[i] == s[j] && len == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }

    int length = dp[0][n - 1];

    string palindrome;
    palindrome.reserve(length);

    int i = 0, j = n - 1;
    while (i < j) {
        if (s[i] == s[j]) {
            palindrome.push_back(s[i]);
            ++i;
            --j;
        } else if (dp[i][j - 1] > dp[i + 1][j]) {
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

    return make_pair(length, palindrome);
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string s;
    input >> s;

    pair<int, string> result = longestPalindrome(s);

    output << result.first << endl;
    output << result.second << endl;

    input.close();
    output.close();

    return 0;
}