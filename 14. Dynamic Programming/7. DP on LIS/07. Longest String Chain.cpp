/*
LeetCode 1048 — Longest String Chain (Concise)

You are given a list of words.
A word A is a predecessor of B if:
You can insert exactly one character anywhere in A to form B
(without changing the order of existing characters)

Goal:
Find the maximum length chain of words such that:
word1 → word2 → word3 → ... → wordk
where each word is a predecessor of the next.

Key Points:
Each step adds 1 character
You must use words from the given list only
A single word is a valid chain of length 1

Output:
Return the maximum chain length

Example:
Input: ["a","ba","bca","bdca"]
Output: 4
Chain: a → ba → bca → bdca

⚡ Constraints Insight:
n ≤ 1000
word length ≤ 16
*/

// TC : O(nlogn) for sorting and for n words, we do 
// substr(0, i) and substr(i+1) → O(L)
// We do this L times → O(L)
// We do this for n words → O(n)
// TC : O(n L^2) + O(nlogn)

// dp[word] = longest chain ending at this word 

class Solution {
public:

    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(),
             [](const string& a, const string& b) {
                 return a.size() < b.size();
             });

        unordered_map<string, int> dp;
        int ans = 1;

        for (string &word : words) {
            dp[word] = 1;

            for (int i = 0; i < word.size(); i++) {
                // skip the character at position i
                string prev = word.substr(0, i) + word.substr(i + 1);

                if (dp.find(prev) != dp.end()) {
                    // max of all (dp[prev] + 1), if no prev then 1.
                    dp[word] = max(dp[word], dp[prev] + 1);
                }
            }

            ans = max(ans, dp[word]);
        }

        return ans;
    }
};

// _______________________________________________________________

class Solution {
public:

bool compare(string& s1, string& s2){
    if(s1.size() != s2.size() + 1) return false;
    
    int first = 0;
    int second = 0;
    
    while(first < s1.size()){
        if(second < s2.size() && s1[first] == s2[second]){
            first ++;
            second ++;
        }
        else first ++;
    }
    
    return (second == s2.size());
}

static bool comp(const string& s1, const string& s2){
    return s1.size() < s2.size();
}

int longestStrChain(vector<string>& words){

    int n = words.size();
    sort(words.begin(), words.end(), comp);
    
    vector<int> dp(n, 1);
    int maxi = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){

            if(compare(words[i], words[j])){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxi = max(maxi, dp[i]);
    }
    return maxi;
}
};
