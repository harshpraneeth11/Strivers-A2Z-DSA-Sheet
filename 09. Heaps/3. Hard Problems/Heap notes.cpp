#include <bits/stdc++.h>
using namespace std;

priority_queue<int> pq; // max heap by default
priority_queue<int, vector<int>, greater<int>> pq;

In heap questions, always draw the PQ

pq.push(x)
pq.pop()
pq.top()
pq.empty()
pq.size()

struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.second > b.second; // min-heap on second
    }
};

priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;

auto cmp = [](pair<int,int> a, pair<int,int> b) {
    return a.second < b.second; // max heap by second
};

priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
