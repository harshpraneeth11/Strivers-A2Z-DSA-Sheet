Here is your **clean, interview-ready, neatly formatted Sliding Window cheat sheet**:

---

# 🔥 Sliding Window Master Templates

---

# 1. Fixed Size Window (Window Size = K)

### Used in:

* Maximum sum subarray of size K
* First negative in every window
* Count distinct in every window
* Maximum / minimum in every window

### Template:

```cpp
int l = 0, r = 0;

while (r < n) {
    // include arr[r]

    if (r - l + 1 < k) {
        r++;
    }
    else if (r - l + 1 == k) {
        // process answer

        // remove arr[l]
        l++;
        r++;
    }
}
```

### Key Idea:

Expand until size K → Process window → Remove left → Continue

---

# 2. Longest Valid Window

### Used in:

* Longest substring without repeating characters
* Max consecutive ones
* Fruit into baskets
* Longest subarray satisfying condition

### Template:

```cpp
int l = 0;

for (int r = 0; r < n; r++) {
    // include arr[r]

    while (window_invalid) {
        // remove arr[l]
        l++;
    }

    ans = max(ans, r - l + 1);
}
```

### Key Idea:

Expand → If invalid, shrink → Update maximum length

---

# 3. Minimum Valid Window

### Used in:

* Minimum Window Substring
* Smallest subarray with sum ≥ K
* Minimum size valid window

### Template:

```cpp
int l = 0;
int ans = INT_MAX;

for (int r = 0; r < n; r++) {
    // include arr[r]

    while (window_valid) {
        ans = min(ans, r - l + 1);

        // remove arr[l]
        l++;
    }
}
```

### Key Idea:

Expand → Window becomes valid → Update answer → Shrink as much as possible

---

# 4. Count Subarrays with At Most K

### Used in:

* At most K distinct elements
* At most K odd numbers
* Count valid subarrays

### Template:

```cpp
int l = 0;
long long ans = 0;

for (int r = 0; r < n; r++) {
    // include arr[r]

    while (condition > K) {
        // remove arr[l]
        l++;
    }

    ans += (r - l + 1);
}
```

### Why this works:

After shrinking:

```
[l........r]
```

All subarrays ending at r are valid:

```
[l,r]
[l+1,r]
[l+2,r]
...
[r,r]
```

Count = `r - l + 1`

---

# 5. Count Subarrays with Exactly K

### Used in:

* Exactly K distinct integers
* Exactly K odd numbers
* Binary subarrays with sum = goal

### Formula:

```
Exactly(K) = AtMost(K) - AtMost(K - 1)
```

### Template:

```cpp
long long exactK(...) {
    return atMost(K) - atMost(K - 1);
}
```

---

# 📊 Recognition Table

| Problem Type                       | Template                |
| ---------------------------------- | ----------------------- |
| Every window of size K             | Fixed Window            |
| Longest valid window               | Longest Valid           |
| Smallest valid window              | Minimum Valid           |
| Count subarrays with condition ≤ K | At Most K               |
| Count subarrays with condition = K | AtMost(K) - AtMost(K-1) |

---

# 6. Fixed Window with Data Structure (Monotonic Deque)

### Used in:

* Sliding Window Maximum
* Min in every window
* Next greater/previous greater style window problems

### Template:

```cpp

[ 8 6 2 -1 ] and arr[i] = 3
Then -1 and 2 will be removed and 3 is added at back
And it becomes [ 8 6 3 ]
Now, we check if the left most value in queue or the maximum
is from the left most value in current window, then we remove the left most
in queue and do l++

deque<int> dq;
int l = 0;

for (int r = 0; r < n; r++) {

    // maintain monotonic decreasing deque
    while (!dq.empty() && dq.back() < arr[r])
        dq.pop_back();

    dq.push_back(arr[r]);

    if (r - l + 1 == k) {

        // answer is front of deque
        ans.push_back(dq.front());

        // remove left element if it leaves window
        if (dq.front() == arr[l])
            dq.pop_front();

        l++;
    }
}
```

### Key Idea:

Maintain a structure that gives max/min in O(1)

---

#  7. Frequency / HashMap Window

### Used in:

* Longest substring with K distinct
* Anagram search
* Permutation in string
* Substring with all characters

### Template:

```cpp
unordered_map<char,int> mp;
int l = 0;

for (int r = 0; r < n; r++) {

    mp[s[r]]++;

    while (mp.size() > K) {
        mp[s[l]]--;
        if (mp[s[l]] == 0)
            mp.erase(s[l]);
        l++;
    }

    ans = max(ans, r - l + 1);
}
```
### Key Idea:

Window validity depends on frequency structure
---

# Template 1: Count by fixing r (end index)

```cpp
for (int r = 0; r < n; r++) {
    add(s[r]);

    while (valid()) {
        remove(s[l++]);
    }

    ans += l;
}
```

### Key Idea:

l = first invalid start

Valid starts:
0 ... l-1

Count = l

* 1st : we add count before moving l : this is there in inside while loop during shrinking
* 2nd : we add count before moving r : this is there at the end of block

# Template 2: Count by fixing l (start index)

```cpp
for (int r = 0; r < n; r++) {
    add(s[r]);

    while (valid()) {
        ans += (n - r);
        remove(s[l++]);
    }
}
```

### Key Idea:
[l..r] is valid
All extensions are valid: [l..r], [l..r+1], ..., [l..n-1]
Count = n - r

* 1st : we add count before moving l : this is there in inside while loop during shrinking
* 2nd : we add count before moving r : this is there at the end of block
---
