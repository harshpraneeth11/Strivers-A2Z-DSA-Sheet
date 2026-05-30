/*
QUESTION:
Given an integer array nums, return the number of longest increasing subsequences.
Notice that the sequence has to be strictly increasing.

Concise Approach
1. Let:
    len[i] = length of LIS ending at i
    cnt[i] = number of LIS ending at i
2. Initialize len[i] = cnt[i] = 1.
3. For every i, check all j < i:
    If nums[j] < nums[i]:
        If len[j] + 1 > len[i]:
            Update len[i] = len[j] + 1
            Set cnt[i] = cnt[j]
        Else if len[j] + 1 == len[i]:
            Add cnt[j] to cnt[i]
4. Find the maximum LIS length maxLen.
5. Sum cnt[i] for all indices where len[i] == maxLen.
Time: O(n²)
Space: O(n)

CODE:
*/

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> len(n, 1);   // LIS length ending at i
    vector<int> cnt(n, 1);   // Number of LIS ending at i

    int maxLen = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {

                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }

        maxLen = max(maxLen, len[i]);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (len[i] == maxLen) {
            ans += cnt[i];
        }
    }

    return ans;
}
