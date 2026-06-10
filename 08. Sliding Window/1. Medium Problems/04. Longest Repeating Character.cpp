/*QUESTION:
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

APPROACH:
1. Create an unordered_set ltrs to store all unique letters in the given string s.
2. Initialize a variable ans to keep track of the maximum length of the substring.
3. Iterate through each letter ltr in the set ltrs:
   - Initialize variables start and ltrCnt to track the starting index of the current substring and the count of ltr in the substring.
   - Iterate through each character in the string s:
     - If the character is equal to ltr, increment ltrCnt.
     - Enter a while loop to adjust the start index until the number of characters in the substring that are different from ltr is more than k.
     - During the adjustment, if the character at the start index is equal to ltr, decrement ltrCnt.
     - Increment the start index.
     - If the length of the current substring minus ltrCnt is at most k, update ans by taking the maximum of ans and the length of the current substring.
4. Return the maximum length of the substring (ans).

CODE:*/
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);

        int left = 0, right = 0;
        int maxFreq = 0;
        int best = 0;

        while (right < s.size()) {
            char c = s[right++];
            freq[c - 'A']++;

            maxFreq = max(maxFreq, freq[c - 'A']);

            // shrink if invalid
            while (right - left - maxFreq > k) {
                freq[s[left] - 'A']--;
                left++;
            }

            best = max(best, right - left);
        }

        return best;
    }
};
/*
COMPLEXITY ANALYSIS:
- Time complexity: O(N * L), where N is the length of the string s and L is the number of unique letters in the string. We iterate through the string and perform the sliding window operation for each unique letter.
    - L can have the max value of 26, so we can say the complexity would be O(N * 26) i.e O(N).
- Space complexity: O(L), as we store the unique letters in the set ltrs.
*/
