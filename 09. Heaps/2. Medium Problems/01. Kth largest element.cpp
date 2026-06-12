/*
QUESTION:
Given an integer array nums and an integer k, return the kth largest element in the array.
*/

// Approach 1 : minHeap means small at top. push elements one by one and keep only k in the PQ
// Approach 2 : maxHeap means large at top. push all elements and remove k-1, so, the kth largest will be at top.

// Time: O(n log k)  -  as stack contains k elements at each position
// Space: O(k)

Push elements ony by one into minHeap
If the size > k, pop one by one
So, at the end we get kth largest at top and 1st largest at bottom

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq; // min heap

    for (int num : nums) {
        pq.push(num);

        if (pq.size() > k) {
            pq.pop();
        }
    }
    return pq.top();
}


Push all elements into n elements in the maxHeap
Pop the k-1 elements, here top is max element
So, at the end we get the kth largest on top
and least at the bottom

// TC : O(nlogn + klogn) = O(nlogn)

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int> pq; // max heap

    for (int num : nums) {
        pq.push(num);
    }

    for (int i = 0; i < k - 1; i++) {
        pq.pop();
    }
    return pq.top();
}
