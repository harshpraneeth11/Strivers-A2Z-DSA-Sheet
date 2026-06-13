// Given an integer, K. Generate all binary strings of size k without consecutive 1’s.

// Examples: 

// Input : K = 3  
// Output : 000 , 001 , 010 , 100 , 101 
// Input : K  = 4 
// Output :0000 0001 0010 0100 0101 1000 1001 1010

void solve(int n, string str, vector<string>& ans) {

    if (str.size() == n) {
        ans.push_back(str);
        return;
    }

    solve(n, str + "1", ans);

    if (str.empty() || str.back() == '1')
        solve(n, str + "0", ans);
}
