/*
**Question:**

Given an integer `rowIndex`, return the `rowIndex`th (0-indexed) row of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: `rowIndex = 3`

Output: `[1, 3, 3, 1]`
*/

/*
Pascal's Triangle :

Variation 1: Given row number r and column number c. Print the element at position (r, c) in Pascal’s triangle.
Variation 2: Given the row number n. Print the n-th row of Pascal’s triangle.
Variation 3: Given the number of rows n. Print the first n rows of Pascal’s triangle
[Element] -> [Row] -> [Complete]

Variation 1: i) nCr = n! / (r! * (n-r)!)
Put n = r-1 and r = c-1
This takes O(n) + O(r) + O(n-r)

ii) for (int i = 0; i < r; i++) {
      res = res * (n - i);
      res = res / (i + 1);
This gives answer in O(c) where r in nCr = c

Variation 2: i) For every column, we calculate the nCr. TC : O(n*r)

ii) If we observe, it is simply
Current element = prevElement * (rowNumber - colIndex) / colIndex
So, can be done in O(r) time

Variation 3: 
i) From variation 2's naive appraoch
for (int row = 1; row <= n; row++) {
    vector<int> tempLst; // temporary list
    for (int col = 1; col <= row; col++) {
        tempLst.push_back(nCr(row - 1, col - 1));
    ans.push_back(tempLst);
TC : O(r*r*c)

ii) Use variation 2's optimal appraoch
TC : O(r*r)

*/

why nCr ?
T(n, r) = T(n-1, r-1) + T(n-1, r)
n C r = n-1 C r-1 + n-1 C r            is famous formulae
They don't dig too much

Variation 1 :

int nCr(int n, int r) {
    long long res = 1;

    // calculating nCr:
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}

int pascalTriangle(int r, int c) {
    int element = nCr(r - 1, c - 1);
    return element;
}
________________

Variation 2 : (Approach 1)

int nCr(int n, int r) {
    long long res = 1;

    // calculating nCr:
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}

void pascalTriangle(int n) {
    // printing the entire row n:
    for (int c = 1; c <= n; c++) {
        cout << nCr(n - 1, c - 1) << " ";
    }
    cout << "n";
}
_________________________

(Approach 2)

void pascalTriangle(int n) {
    long long ans = 1;
    cout << ans << " "; // printing 1st element

    //Printing the rest of the part:
    for (int i = 1; i < n; i++) {
        ans = ans * (n - i);
        ans = ans / i;
        cout << ans << " ";
    }
    cout << endl;
}
_________________________

Variation 3 : (Approach 1)

int nCr(int n, int r) {
    long long res = 1;

    // calculating nCr:
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return (int)(res);
}

vector<vector<int>> pascalTriangle(int n) {
    vector<vector<int>> ans;

    //Store the entire pascal's triangle:
    for (int row = 1; row <= n; row++) {
        vector<int> tempLst; // temporary list
        for (int col = 1; col <= row; col++) {
            tempLst.push_back(nCr(row - 1, col - 1));
        }
        ans.push_back(tempLst);
    }
    return ans;
}
_________________________

(Approach 2)

vector<int> generateRow(int row) {
    long long ans = 1;
    vector<int> ansRow;
    ansRow.push_back(1); //inserting the 1st element

    //calculate the rest of the elements:
    for (int col = 1; col < row; col++) {
        ans = ans * (row - col);
        ans = ans / col;
        ansRow.push_back(ans);
    }
    return ansRow;
}

vector<vector<int>> pascalTriangle(int n) {
    vector<vector<int>> ans;

    //store the entire pascal's triangle:
    for (int row = 1; row <= n; row++) {
        ans.push_back(generateRow(row));
    }
    return ans;
}
