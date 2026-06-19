/*
QUESTION:
Given an array with both positive and negative integers, we need to compute the length of the largest subarray with a sum of 0.

Example:
Input:
N = 8
A[] = {15, -2, 2, -8, 1, 7, 10, 23}
Output: 5
Explanation: The largest subarray with a sum of 0 will be -2, 2, -8, 1, 7.
*/
    
// TC : O(N^2) and SC : O(1)

int solve(vector<int>& a) {
    int maxLen = 0;

    for (int i = 0; i < a.size(); i++) {
        int sum = 0;
        for (int j = i; j < a.size(); j++) {
            sum += a[j];
            if (sum == 0) {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}
_____________________________

// TC : O(N) and SC : O(N)

int solve(vector<int>& a) {
    int maxLen = 0, sum = 0;
    unordered_map<int, int> ump;

    for (int i = 0; i < a.size(); i++) {
        sum += a[i];
        if (sum == 0) maxLen = i + 1;
        else if (ump.find(sum) != ump.end()) maxLen = max(maxLen, i - ump[sum]);  
            // We take the [prev+1, i] and don't take the prev actually
        else ump[sum] = i;
    }
    return maxLen;
}
