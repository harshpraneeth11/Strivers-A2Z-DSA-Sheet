/*
QUESTION:
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1,
return the area of the largest rectangle in the histogram.

Example:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where the width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
*/

// Brute force approach - TC : O(N^2) and SC : O(1)
// For every i -> j, we do minHeight * width

int largestarea(int arr[], int n) {
  int maxArea = 0;
  for (int i = 0; i < n; i++) {
    int minHeight = INT_MAX;
    for (int j = i; j < n; j++) {
      minHeight = min(minHeight, arr[j]);
      maxArea = max(maxArea, minHeight * (j - i + 1));
    }
  }
  return maxArea;
}
________________________________________________

/*
APPROACH:
To find the largest rectangle area, we can use the concept of a stack.
The idea is to maintain a stack of indices of the heights in non-decreasing order.
For each height, we compare it with the top of the stack.
If the current height is greater than the top of the stack, we push its index onto the stack.
Otherwise, we keep popping elements from the stack and calculate the area using the popped index as the right boundary.
The left boundary can be obtained from the new top of the stack.
By doing this, we ensure that the heights in the stack are always in non-decreasing order.
Finally, we calculate the area for each popped element and update the maximum area found so far.

CODE:
*/


vector<int> prevSmaller(vector<int>& arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] > arr[i])    // only one is >, another is >=
            st.pop();
        if (!st.empty())
            ans[i] = st.top();
        st.push(i);
    }
    return ans;
}

vector<int> nextSmaller(vector<int>& arr) {
    stack<int> st;
    vector<int> ans(arr.size(), arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        if (!st.empty())
            ans[i] = st.top();
        st.push(i);
    }
    return ans;
}

int largestRectangleArea(vector<int>& heights) {
    vector<int> prev = prevSmaller(heights);
    vector<int> next = nextSmaller(heights);

    int ans = INT_MIN;
    for (int i = 0; i < heights.size(); i++) {
        ans = max(ans, (next[i] - prev[i] - 1) * heights[i]);    
    }
    return ans;
}

/*
COMPLEXITY ANALYSIS:
- The time complexity of the solution is O(n), where n is the number of elements in the heights array.
  This is because we iterate through the array once to calculate the previous and next smaller elements.
- The space complexity is O(n) as well since we use two additional arrays to store the previous and next smaller elements.
*/
________________________________________

/*  Optimal 2 - one stack only unlike 2 as above
Case 1: cur >= st.top()
Push the current index to the stack as it might form a larger rectangle.

Case 2: cur < st.top()
Pop bars from the stack and calculate the area for the popped bar using the difference between the current index and the index of the new top of the stack.
Because: A smaller bar blocks the rectangle extension of taller bars.
So taller bars must end here.

Case 3: After processing all bars, there may still be bars left in the stack:
Pop the remaining bars and calculate the area for each, considering the width as the total width from the start to the end of the histogram.
*/

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;  // stack to store 'indices'
    int maxArea = 0;
    
    for (int i = 0; i < n; i++) {
        // While stack is not empty and current bar is smaller than bar at stack top
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int height = heights[st.top()];
            st.pop();
            int width = (st.empty()) ? i : i - st.top() - 1;    // If empty, this is the smallest of all
            maxArea = max(maxArea, height * width);  // calculate area and update max area
        }
        st.push(i);  // Push current bar 'index'
    }
    
    // Now pop the remaining bars, each can be a potential answer
    while (!st.empty()) {
        int height = heights[st.top()];
        st.pop();
        int width = (st.empty()) ? n : n - st.top() - 1;
        maxArea = max(maxArea, height * width);
    }
    
    return maxArea;
}
