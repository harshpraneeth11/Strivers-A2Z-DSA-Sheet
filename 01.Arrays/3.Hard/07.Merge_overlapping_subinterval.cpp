/*
QUESTION:
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals and return an array of non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

APPROACH:
Merge Overlapping Subintervals :
i) Brute force
2 traversal, TC : O(NlogN + 2N)
We check if the current is already merged or not, we 'continue' to next iteration
If not, then we check all the next intervals which have next_start <= cur_end and try to include them

ii) Optimal, TC : O(NlogN + N), single for loop
If the current interval does not lie in the last interval, insert it new
Else if it lies, then update the prev as follows,
ans.back()[1] = max(ans.back()[1], arr[i][1]);

CODE:
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        vector<vector<int>> ans;

        for(int i = 0; i < n; i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];

            // already covered by previous merge
            if(!ans.empty() && end <= ans.back()[1]) continue;

            for(int j = i + 1; j < n; j++) {
                if(intervals[j][0] <= end)  end = max(end, intervals[j][1]);    
                else break;
            }
            ans.push_back({start, end});
        }
        return ans;
    }
};

// _________________________________________________________________

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    
    for(int i = 1; i < intervals.size(); i++){
        if(ans.back()[1] >= intervals[i][0]){
            ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
        else{
            ans.push_back(intervals[i]);
        }
    }
    
    return ans;
}

/*
TIME COMPLEXITY: O(nlogn), where n is the number of intervals in the input.
The sorting step takes O(nlogn) time, and the merging step takes O(n) time.
Overall, the time complexity is dominated by the sorting step.
SPACE COMPLEXITY: O(n), where n is the number of intervals in the input.
We are using additional space to store the merged intervals in the `ans` vector.
*/

