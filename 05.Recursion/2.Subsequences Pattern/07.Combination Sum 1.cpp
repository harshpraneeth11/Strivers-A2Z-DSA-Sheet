/*QUESTION:
Given an array of distinct integers candidates and a target integer target, return a list of all unique 
combinations of candidates where the chosen numbers sum to target. The same number may be chosen from 
candidates an unlimited number of times. Two combinations are unique if the frequency of at least one 
of the chosen numbers is different.

Example:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation: 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times. 
7 is a candidate, and 7 = 7. These are the only two combinations.

Approach:
Sort the array (optional, helps pruning)
Start DFS from index 0
Maintain a current combination (path)
If target == 0 → store the path as answer
If target < 0 → stop (backtrack)
Loop from start index → end:
   Pick current number
   Recurse with same index (reuse allowed)
   Remove last element (backtrack)
Move to next index to avoid duplicates
Return all valid combinations

Time Complexity: O(N^target), where N is the size of the array of candidates and target is the target sum. 
In the worst case, we may have to explore all possible combinations, which is exponential.
Space Complexity: O(target), as the maximum depth of the recursion tree is determined by the target sum.

CODE:*/

void solve(int i, vector<int>& candidates, int target, vector<int>& temp, vector<vector<int>>& ans) {
    if (target == 0) {
        ans.push_back(temp);
        return;
    }

    if (i == candidates.size() || target < 0)
        return;

    // Take
    if (candidates[i] <= target) {
        temp.push_back(candidates[i]);
        solve(i, candidates, target - candidates[i], temp, ans);
        temp.pop_back();
    }
    // Not Take
    solve(i + 1, candidates, target, temp, ans);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    sort(candidates.begin(), candidates.end());
    vector<int> temp;
    solve(0, candidates, target, temp, ans);
    return ans;
}
