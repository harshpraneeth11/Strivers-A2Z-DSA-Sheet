/*QUESTION:
Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sum to target. 
Each number in candidates may only be used once in the combination. 
Note: The solution set must not contain duplicate combinations.

Example:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
Explanation: The sum of the combinations [1,1,6], [1,2,5], [1,7], and [2,6] is equal to the target 8.


Time Complexity: O(N * 2^N), where N is the size of the array of candidates. In the worst case, we may have to explore all possible combinations, which is exponential.
Space Complexity: O(target), as the maximum depth of the recursion tree is determined by the target sum.

CODE:*/


// Take / Not-Take (Binary choice recursion)

class Solution {
public:
    void solve(int i, int target, vector<int>& candidates, vector<int>& temp, vector<vector<int>>& ans) {
        
        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        if (i == candidates.size() || target < 0) return;

        // TAKE
        if (candidates[i] <= target) {
            temp.push_back(candidates[i]);
            solve(i + 1, target - candidates[i], candidates, temp, ans);
            temp.pop_back();
        }

        // NOT TAKE → skip all duplicates
        int next = i + 1;
        while (next < candidates.size() && candidates[next] == candidates[i]) {
            next++;
        }

        solve(next, target, candidates, temp, ans);
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> ans;
        vector<int> temp;

        solve(0, target, candidates, temp, ans);
        return ans;
    }
};

// ____________________________________________________________________

// For-loop (Choice expansion template)

class Solution {
public:
    void solve(int start, int target, vector<int>& candidates, vector<int>& temp, vector<vector<int>>& ans) {

        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {

            // skip duplicates at same level
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            if (candidates[i] > target) break;

            temp.push_back(candidates[i]);
            solve(i + 1, target - candidates[i], candidates, temp, ans); // i+1 (no reuse)
            temp.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        sort(candidates.begin(), candidates.end());
        vector<int> temp;
        solve(0, target, candidates, temp, ans);
        return ans;
    }
};

// _____________________________
