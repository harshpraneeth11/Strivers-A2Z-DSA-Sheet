/*
QUESTION:
Given string num representing a non-negative integer num, and an integer k,
return the smallest possible integer after removing k digits from num.

Example:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
*/

/*
num = "1432219", k = 3

1
14
1 (pop 4), push 3 → 13
1 (pop 3), push 2 → 12
122
12 (pop 2), push 1 → 121
1219

Answer = 1219

When a smaller digit arrives, we remove larger digits before it because:
A smaller digit appearing earlier always produces a smaller overall number: 
1 3 2 and k = 1: 1 2 is better than 1 3
*/

class Solution {
public:
    string removeKdigits(string num, int k) {
        string st;         // we are using a string that functions as stack directly

        // Monotonic Stack + Greedy removal.
        for (char digit : num) {
            while (!st.empty() && k > 0 && st.back() > digit) {
                st.pop_back();
                k--;
            }
            st.push_back(digit);
        }

        // If removals are still left -- 12345 and k = 1, remove the last digit
        while (k > 0) {
            st.pop_back();
            k--;
        }

        // Remove leading zeros          
        // 1 2 0 0 1 -> if we remove 1 2, then 0 0 1, we have to remove those 0's
        int i = 0;
        while (i < st.size() && st[i] == '0')
            i++;

        string ans = st.substr(i);
        return ans.empty() ? "0" : ans;
    }
};
/*
Complexity Analysis:
- The code iterates through each digit in the input string, so the time complexity is O(n),
  where n is the length of the input string.
- The space complexity is O(n) as well since the stack can potentially store all the digits in the input string.
*/
