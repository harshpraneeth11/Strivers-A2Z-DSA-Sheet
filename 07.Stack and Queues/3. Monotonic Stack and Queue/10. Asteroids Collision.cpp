/*
QUESTION:
We are given an array of integers representing asteroids in a row. Each asteroid moves at the same speed.
If two asteroids meet, the smaller one will explode. If both are the same size, both will explode.
Find out the state of the asteroids after all collisions.

APPROACH:
To solve this problem, we can use a stack to simulate the asteroid collisions.
1. We iterate through each asteroid in the given array.
2. For each asteroid, we check if it will collide with the asteroids in the stack.
   - If the current asteroid is moving to the right (positive direction), we simply push it onto the stack.
   - If the current asteroid is moving to the left (negative direction), we compare its size with the asteroids in the stack.
     - If the stack is empty or the top asteroid in the stack is also moving to the left, we push the current asteroid onto the stack.
     - If the top asteroid in the stack is moving to the right and its size is smaller than the current asteroid, we pop the top asteroid from the stack and continue the comparison.
     - If the top asteroid in the stack is moving to the right and its size is equal to or greater than the current asteroid, we do not push the current asteroid onto the stack and continue to the next asteroid.
3. After processing all the asteroids, the remaining asteroids in the stack represent the final state after collisions.

Example:
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

We have 4 cases
3 ->   4 ->
3 ->   <- 4
<- 3   <- 4
<- 3   4->

* 4 -> 3 ->
In this case, don't think that 4 is moving with more speed. Actually, it is size, not speed.
All are movign at same speed.

case 1,4 :- In the cases where current is right or stack is empty, we don't have a problem. We push it directly into stack
case 2 :-   But, if stack is positive and current is bigger negative, we pop all the st.top elements
Sp case :-  If both are equal, we pop it without pushing the new one
Now, if stack is empty (after popping the stack elements) or it is case 3, we push the current element into stack

* (int) is used for using size of vector

CODE:
*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& ast) {
        int n = ast.size();
        stack<int> s;
        for(int i = 0; i < n; i++) {
            // Case 1: If current asteroid is moving right or stack is empty, push it
            if(ast[i] > 0 || s.empty()) {
                s.push(ast[i]);
            }
            else {
                // Case 2: If stack has a positive asteroid and current is a bigger negative asteroid, pop the stack
                while(!s.empty() and s.top() > 0 and s.top() < abs(ast[i])) {
                    s.pop();
                }
                // Special case: If both are equal, pop the stack and don't push the new asteroid
                if(!s.empty() and s.top() == abs(ast[i])) {
                    s.pop();
                }
                else {
                    // Case 3: If stack is empty or the top is negative, push the current asteroid
                    if(s.empty() || s.top() < 0) {
                        s.push(ast[i]);
                    }
                }
            }
        }
        // Construct the result vector by popping elements from the stack
        vector<int> res(s.size());
        for(int i = (int)s.size() - 1; i >= 0; i--) {
            res[i] = s.top();
            s.pop();
        }
        return res;
    }
};

/*
COMPLEXITY ANALYSIS:
- Let n be the number of asteroids in the given array.
- The time complexity of the solution is O(n) because we iterate through each asteroid once.
- The space complexity is O(n) because in the worst case, all asteroids can be stored in the stack.
*/
