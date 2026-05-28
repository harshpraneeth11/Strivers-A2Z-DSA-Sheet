/*
We can't print the longest sequence, but we can get the length of it O(NlogN) instead of O(N^2)
If arr[i] is > last element of temp,  extend the subsequence
If arr[i] is <= last element of temp, replace the element in temp with arr[i]
If we are not extending and instead replacing, it means this is not the LIS till now, it is another, 
this can be LIS, if there is an extension
{ 1, 7, 8,  4, 5, 6, -1, 9}
temp = { 1, 7, 8 } -> { 1, 4, 8 }  Here 7 gets replaced by 4 as it is the element >= 4
If 4 is there, replace 4 with 4
*/

// Function to find the length of the longest increasing subsequence

#include <bits/stdc++.h>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
    vector<int> tail;

    for (int x : nums) {
        auto it = lower_bound(tail.begin(), tail.end(), x);

        if (it == tail.end()) {
            tail.push_back(x);
        } else {
            *it = x;
        }
    }

    return tail.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lengthOfLIS(nums);
}
