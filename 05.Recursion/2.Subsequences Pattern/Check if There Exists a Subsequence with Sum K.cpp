bool solve(int idx, int sum, int arr[]) {
    if (sum == 0) return true; 
    if (idx == 0) return arr[0] == sum;

    bool pick = false;
    if (arr[idx] <= sum) pick = solve(idx - 1, sum - arr[idx], arr);

    bool notPick = solve(idx - 1, sum, arr);
    return pick || notPick;
}

bool isSubsetSum(int arr[], int n, int k) {
    return solve(n - 1, k, arr);
}
