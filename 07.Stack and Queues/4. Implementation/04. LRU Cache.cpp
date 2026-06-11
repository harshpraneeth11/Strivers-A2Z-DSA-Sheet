/*
QUESTION:
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.


Example:
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4

-> lru.splice(lru.begin(), lru, keyPos);

lru.begin(): The position in the list where the element will be moved, which is the front of the list in this case.
lru: The list from which the element is being moved (same list here).
keyPos: The iterator pointing to the element to be moved.

This moves the element pointed to by 'keyPos' to the 'front' of the 'lru' list without copying or creating new elements.
We use it in both put() and get()

-> list means doubly linked list

APPROACH:
To implement the LRU cache, we can use a combination of a hash map and a doubly linked list.
- The hash map will store the key-value pairs, where the key is the cache key and the value is a pointer to the corresponding node in the linked list.
- The doubly linked list will maintain the order of the recently used keys, where the front of the list represents the most recently used key and the back of the list represents the least recently used key.

IMPLEMENTATION:
1. Initialize the LRU cache with the given capacity.
2. Implement the get(key) function:
   - If the key exists in the cache, move the corresponding node to the front of the list (indicating it is the most recently used).
   - Return the value of the key if it exists, otherwise return -1.
3. Implement the put(key, value) function:
   - If the key already exists in the cache, update its value and move the corresponding node to the front of the list.
   - If the key does not exist:
     - If the cache is full, remove the least recently used key (from the back of the list) and remove its entry from the hash map.
     - Add the new key-value pair to the front of the list and insert its entry into the hash map.

CODE:
*/

// the question itself tells to have (key, value), so we have pair<int, int> as nodes in lru list

class LRUCache {
private:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> addr;
    list<pair<int, int>> lru;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (addr.find(key) == addr.end())
            return -1; // Key not found

        auto keyPos = addr[key];
        lru.splice(lru.begin(), lru, keyPos);
        return lru.front().second;
    }

    void put(int key, int value) {
        // If the key already exists, update its value and move it to the front
        if (addr.find(key) != addr.end()) {
            auto keyPos = addr[key];
            lru.splice(lru.begin(), lru, keyPos);
            lru.front().second = value;
            return;
        }

        // If the capacity is full, remove the least recently used key
        if (addr.size() == capacity) {
            int backKey = lru.back().first;
            lru.pop_back();
            addr.erase(backKey);
        }

        lru.push_front({key, value});
        addr[key] = lru.begin();
    }
};

/*
COMPLEXITY ANALYSIS:
- The time complexity of both the get() and put() operations is O(1) since we use a hash map to achieve constant time access and update.
- The space complexity is O(capacity) since the cache can store at most 'capacity' key-value pairs.
*/
__________________________________________________

/*
1. Node Class:
This is a nested class representing a doubly linked list node.
Each node contains an integer key, an integer value, and pointers to the previous and next nodes in the linked list.

2. LRUCache Class:
This is the main LRU Cache class.
It has a fixed capacity (cap) that is specified during its instantiation.
It uses an unordered_map<int, Node*> named m to store key-value pairs, where the key is the integer key, and the value is a pointer to the corresponding Node.

3. head and tail Nodes:
The LRUCache class has two dummy nodes: head and tail.
These nodes act as sentinels in the doubly linked list, helping to simplify the edge cases and avoid dealing with null pointers.
head is the first node in the linked list, and tail is the last node.

4. addNode Function:
This function is used to add a new node to the front of the doubly linked list (right after head).
It takes a Node* newnode as input, representing the node to be added.
The function updates the pointers of the new node, the previous first node, and head to include the new node as the new first node.

5. deleteNode Function:
This function is used to delete a node from the doubly linked list.
It takes a Node* delnode as input, representing the node to be deleted.
The function updates the pointers of the previous and next nodes to exclude the node to be deleted, effectively removing it from the linked list.

6. get Function:
This function is used to retrieve a value from the cache based on the given key.
If the key exists in the cache (m.find(key) != m.end()), it retrieves the corresponding node (resNode), extracts its value (ans), and performs the following steps:
Erase the key-value pair from the m unordered map.
Delete the node from its current position in the linked list using deleteNode.
Add the node to the front of the linked list using addNode, making it the most recently used node.
Update the m map to store the key with the most recently used node.
If the key doesn't exist in the cache, it returns -1.

7. put Function:
This function is used to insert or update a key-value pair in the cache.
If the key already exists in the cache, it updates the value by performing the following steps:
Erase the existing key-value pair from the m unordered map.
Delete the corresponding node from its current position in the linked list using deleteNode.
If the cache is full (i.e., m.size() == cap), it removes the least recently used node from the cache by erasing the key-value pair from the m map and deleting the node from the end of the linked list using deleteNode.
After handling the eviction (if needed), it creates a new node using new Node(key, value) and adds it to the front of the linked list using addNode.
Finally, it updates the m map to store the key with the newly added node.

** list<pair<int, int>>::iterator:
The value type in the map is an iterator pointing to an element in a list of key-value pairs (pair<int, int>).
** Head and tail both are dummy here, so we use head->next, tail->prev for pointing to the correct ones

*/

class LRUCache {
public:
    class Node{
        public: 
            int key;
            int val;
            Node* prev;
            Node* next;

            Node(int key, int val){
                this->key = key;
                this->val = val;
            }
    };

    Node* head = new Node(-1, -1); // Dummy head node
    Node* tail = new Node(-1, -1); // Dummy tail node

    int cap; // Cache capacity
    unordered_map<int, Node*> m; // Hash map to store key-node pairs

    LRUCache(int capacity) {
        cap = capacity;
        head -> next = tail;
        tail -> prev = head;
    }

    // Add a new node right after the head (most recently used position)
    void addNode(Node* newnode){
        Node* temp = head -> next;

        newnode -> next = temp;
        newnode -> prev = head;

        head -> next = newnode;
        temp -> prev = newnode;
    }

    // Remove a node from its current position
    void deleteNode(Node* delnode){
        Node* prevv = delnode -> prev;
        Node* nextt = delnode -> next;

        prevv -> next = nextt;
        nextt -> prev = prevv;
    }
    
    // Retrieve the value of the key if it exists in the cache
    int get(int key) {
        if(m.find(key) != m.end()){
            Node* resNode = m[key];       // find node    
            int ans = resNode -> val;     // find value

            m.erase(key);                 // Remove the current mapping
            deleteNode(resNode);          // Remove the node from the list
            addNode(resNode);             // Move the node to the front (most recently used)
            m[key] = head -> next;        // Update the map with the new position
           
            return ans;
        }
        return -1; // Key not found
    }
    
    // Add or update the value of the key in the cache
    void put(int key, int value) {
        if(m.find(key) != m.end()){       // if it exists
            Node* curr = m[key];      // find node, we don't value as anyways we update it
            m.erase(key); // Remove the existing mapping
            deleteNode(curr); // Remove the node from the list
        }

        // The same 4 lines as above with a condition
        // If the cache is full, remove the least recently used node
        if(m.size() == cap){
            m.erase(tail -> prev -> key); // Remove the least recently used key
            deleteNode(tail -> prev); // Remove the least recently used node
        }

        addNode(new Node(key, value)); // Add the new node to the front
        m[key] = head -> next; // Update the map with the new node
    }
};
