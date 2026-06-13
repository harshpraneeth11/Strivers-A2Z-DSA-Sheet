/*QUESTION:
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Example:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Approach:
We can use a recursive backtracking approach to generate all possible palindrome partitioning.
1. Create a helper function called 'solve' that takes the current index, the input string 's', a temporary vector to store the current partition, and the vector to store all partitions.
2. In the 'solve' function:
   - If the current index is greater than or equal to the size of the input string 's', add the current partition to the vector of partitions and return.
   - Iterate through all possible substrings starting from the current index to the end of the string.
   - Check if the current substring is a palindrome by using a helper function 'isPalindrome'.
   - If the current substring is a palindrome:
     - Add the current substring to the temporary partition vector.
     - Recursively call the 'solve' function with the updated index by incrementing it, the same input string 's', the updated temporary partition vector, and the vector of partitions.
     - Remove the last added substring from the temporary partition vector (backtracking).
3. Create the main function called 'partition' that calculates and returns the vector of partitions.
   - Initialize an empty vector to store the partitions.
   - Initialize an empty temporary vector to store the current partition.
   - Call the 'solve' function with the initial index as 0, the input string 's', the temporary partition vector, and the vector of partitions.
   - Return the vector of partitions.

Time Complexity: O(N * 2^N), where N is the length of the input string 's'. In the worst case, we can have 2^N possible partitions, and for each partition, we need to check if each substring is a palindrome, which takes O(N) time.
* 2^N strings are there and it takes O(N) to check palindrome or not
Space Complexity: O(N), where N is the length of the input string 's'. The space is used for storing the temporary partition vector and the vector of partitions.

CODE:*/

class Solution {
public:

    vector<vector<bool>> precompute(string &s) {

        int n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {

                if (s[i] == s[j]) {
                    if (j - i <= 2)             // if length is 1 or 2
                        pal[i][j] = true;
                    else
                        pal[i][j] = pal[i + 1][j - 1];
                }
            }
        }

        return pal;
    }

    void solve(int i, string &s, vector<string> &temp, vector<vector<string>> &ans,
               vector<vector<bool>> &pal) {

        if (i == s.size()) {
            ans.push_back(temp);
            return;
        }

        for (int j = i; j < s.size(); j++) {
            if (pal[i][j]) {
                temp.push_back(s.substr(i, j - i + 1));
                solve(j + 1, s, temp, ans, pal);
                temp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {2

        vector<vector<string>> ans;
        vector<string> temp;

        vector<vector<bool>> pal = precompute(s);

        solve(0, s, temp, ans, pal);

        return ans;
    }
};

// TC : O(N^2) + O(2^N) 
// O(N^2) for precomputation and O(2^N) for take / ntake at each position
// SC : O(N^2) + O(N) 
// O(N^2) for DP table and O(N) for recursive stack

// ___________________________________________________________________________________

// SC : O(N) for recursive stack
// TC : O(N 2^N) for take/ntake and isPalindrome check needs 'N'
class Solution {
public:

    bool isPalindrome(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    void solve(int i, string &s, vector<string> &temp, vector<vector<string>> &ans) {
        if (i == s.size()) {
            ans.push_back(temp);
            return;
        }

        for (int j = i; j < s.size(); j++) {
            if (isPalindrome(s, i, j)) {
                temp.push_back(s.substr(i, j - i + 1));
                solve(j + 1, s, temp, ans);
                temp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> temp;
        solve(0, s, temp, ans);
        return ans;
    }
};
