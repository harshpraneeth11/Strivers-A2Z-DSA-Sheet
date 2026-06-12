/*QUESTION:
Given a list arr of N integers, print the sums of all subsets in it.

Example:
Input:
N = 2
arr[] = {2, 3}
Output:
0 2 3 5
Explanation:
When no element is taken, the sum is 0.
When only 2 is taken, the sum is 2.
When only 3 is taken, the sum is 3.
When elements 2 and 3 are taken, the sum is 2 + 3 = 5.

Approach:

Time Complexity: O(2^N), where N is the size of the array.
Space Complexity: O(N), where N is the size of the array (for recursion stack and storing subset sums).

CODE:*/

class Solution {
public:
    void solve(int i, vector<int>& nums, int sum, vector<int>& res) {

        if (i == nums.size()) {
            res.push_back(sum);
            return;
        }

        // TAKE
        solve(i + 1, nums, sum + nums[i], res);

        // NOT TAKE
        solve(i + 1, nums, sum, res);
    }

    vector<int> subsetSums(vector<int>& nums) {
        vector<int> res;
        solve(0, nums, 0, res);
        return res;
    }
};

// _____________________________________

class Solution {
public:
    void solve(int start, vector<int>& nums, int sum, vector<int>& res) {

        res.push_back(sum);

        for (int i = start; i < nums.size(); i++) {
            solve(i + 1, nums, sum + nums[i], res);
        }
    }

    vector<int> subsetSums(vector<int>& nums) {
        vector<int> res;
        solve(0, nums, 0, res);
        return res;
    }
};
