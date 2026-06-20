/*
QUESTION:
Given an integer array nums, return the number of reverse pairs in the array.
A reverse pair is a pair (i, j) where:
0 <= i < j < nums.length and
nums[i] > 2 * nums[j].

Example:
Input: nums = [1,3,2,3,1]
Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

APPROACH:
To solve this problem, we can use the merge sort algorithm. While merging the two sorted subarrays, we can count the number of reverse pairs.

1. Define a variable 'rev_pair' to store the count of reverse pairs.
2. Implement the 'merge' function to merge two subarrays and count the reverse pairs.
3. Implement the 'mergesort' function to recursively divide the array into subarrays and perform merge sort.
4. Initialize 'rev_pair' to 0 and call the 'mergesort' function on the given array.
5. Return the 'rev_pair' as the result.

CODE:
*/

/* NOTE :-
mid is present with left section
we go from left=0 to mid, in this process if right satisfies, we do m++ till it can
This number for sure satisfies in the next left index too, so no worries
In the last problem, we do directly left_size-i directly, but here it is not possible
As the comparison we are doing is left[i] <> right[i], but we are supposed to do left[i] <> 2 * right[i]
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int merge(vector<int>& nums, int start, int mid, int end) {
        int left_size = mid - start + 1;
        int right_size = end - mid;

        vector<int> left(left_size);
        vector<int> right(right_size);

        for (int i = 0; i < left_size; i++) {
            left[i] = nums[start + i];
        }
        for (int i = 0; i < right_size; i++) {
            right[i] = nums[mid + 1 + i];
        }

        // count reverse pairs
        int count = 0;
        int j = 0;

        for (int i = 0; i < left_size; i++) {
            while (j < right_size && (long long)left[i] > 2LL * right[j]) {
                j++;
            }
            count += j;
        }

        // merge step
        int i = 0;
        j = 0;
        int k = start;

        while (i < left_size && j < right_size) {
            if (left[i] <= right[j]) {
                nums[k++] = left[i++];
            } else {
                nums[k++] = right[j++];
            }
        }

        while (i < left_size) {
            nums[k++] = left[i++];
        }

        while (j < right_size) {
            nums[k++] = right[j++];
        }

        return count;
    }

    int mergesort(vector<int>& nums, int start, int end) {
        if (start >= end) return 0;

        int mid = start + (end - start) / 2;

        int left = mergesort(nums, start, mid);
        int right = mergesort(nums, mid + 1, end);
        int cross = merge(nums, start, mid, end);

        return left + right + cross;
    }

    int reversePairs(vector<int>& nums) {
        return mergesort(nums, 0, nums.size() - 1);
    }
};
/*
TIME COMPLEXITY: O(n log n), where n is the size of the array.
SPACE COMPLEXITY: O(n), where n is the size of the array.
*/
