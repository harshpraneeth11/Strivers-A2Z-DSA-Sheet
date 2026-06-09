/*QUESTION:

Given a row-wise sorted matrix of size R*C where R and C are always odd, find the median of the matrix.

Example:

Input:
R = 3, C = 3
M = [[1, 3, 5], 
     [2, 6, 9], 
     [3, 6, 9]]
Output: 5
Explanation: Sorting matrix elements gives us {1, 2, 3, 3, 5, 6, 6, 9, 9}. Hence, 5 is the median. 

APPROACH:

To find the median of a row-wise sorted matrix, we can follow these steps:

CODE:*/
// if upper_bound gives i=3 is the first element that is greater than the mid, 
// then first 3 elements are less than mid.
// This is "binary search on Answer" / boundary search type. So, we don't use
// if(... = ...) return mid.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int median(vector<vector<int>> &matrix, int R, int C) {

        int low = INT_MAX;
        int high = INT_MIN;
        // Find minimum and maximum values in the matrix
        for (int i = 0; i < R; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][C - 1]);
        }
        // R, C are always odd in the question
        int required = (R * C) / 2;
         
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 0;

            // Count elements <= mid
            for (int i = 0; i < R; i++) {
                count += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            }
            if (count <= required)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return low;
    }
};
/*
TIME COMPLEXITY: O(R * log(C) * log(range)), where R is the number of rows, C is the number of columns, and range is the difference between the minimum and maximum elements in the matrix. 
                The algorithm performs binary search on each row, which takes O(log(C)) time, and the outer binary search iterates log(range) times.
SPACE COMPLEXITY: O(1) as the algorithm only uses a constant amount of additional space to store variables.
*/
