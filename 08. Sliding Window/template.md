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

If you want, I can also convert this into:

* 📄 One-page PDF cheat sheet (interview revision sheet)
* 🧠 Anki flashcards for revision
* 💻 VS Code snippet template (auto-expand typing shortcuts)

Just tell 👍
