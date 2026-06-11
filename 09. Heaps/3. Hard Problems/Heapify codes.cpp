// left : 2i+1, right : 2i+2, parent : i-1/2 
// In the heap, n/2-1 is last non leaf, because 2(n/2)+1, 2(n/2)+2 are out of bounds if it is a non leaf node

// MaxHeapify and MinHeapify : O(logN)
// Build MaxHeap : O(N)
// Insert : O(logN)
// Delete : O(logN)
// Increase key : O(logN)
// Heap Sort : O(NlogN)

// Max-Heapify

// Heapify ensures that the subtree rooted at the given index "only" satisfies the heap property.

void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest); // Recursively heapify the affected sub-tree
    }
}

// ________________________________________

// Min-Heapify

void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is smaller than root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest); // Recursively heapify the affected sub-tree
    }
}

// ________________________________________

// Build Max-Heap

void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Build Min-Heap

void buildMinHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// ________________________________________

// Insert into Heap

// Inserting an element into a heap involves adding the element at the end and then fixing the heap property by moving up.

void insertToMaxHeap(vector<int>& arr, int key) {
    arr.push_back(key);
    int i = arr.size() - 1;

    // Fix the max-heap property if it's violated
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// ________________________________________

// Delete from Heap (Max-Heap Example)

// Deleting the root from a max-heap involves swapping the root with the last element, removing the last element, and then restoring the heap property.
// Deletion and extracting the Max from maxHeap and Min from minHeap are same
// We do using void for delete generally and int for extract

int deleteRoot(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return -1; // Empty heap

    int root = arr[0];
    arr[0] = arr[n - 1];
    arr.pop_back();

    maxHeapify(arr, arr.size(), 0);

    return root;
}

// ________________________________________

// Increase Key (For Max-Heap)

// Increasing the value of an element and then maintaining the heap property by moving up.
// We do decrease key for check the property is valid or not with children
// For minHeap, decreasing key makes moving up and increasing key makes moving down

void increaseKey(vector<int>& arr, int i, int new_val) {
    arr[i] = new_val;
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void decreaseKey(vector<int>& arr, int i, int new_val) {
    arr[i] = new_val;
    heapify(arr, arr.size(), i);
}
// ________________________________________

// Heap Sort (Using Max-Heap)

// Heap sort is performed by building a max-heap and then repeatedly moving the root to the end of the array.

// last line is the main step
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max heap
    buildMaxHeap(arr);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // Call maxHeapify on the reduced heap
        maxHeapify(arr, i, 0);          // ** In general i=n, but here we used i=n-1, so it won't consider the last element during maxHeap
    }
}
