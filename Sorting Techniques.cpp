Types of Sorts

Selection Sort
Bubble Sort
Insertion Sort
Merge Sort
Recursive Bubble Sort
Recursive Insertion Sort
Quick Sort

Counting sort
Shell sort
Radix sort
Bucket sort
Heap sort

// _____________________________________________________________

selection sort :  does not have any recursive approach - select the min and place here
bubble sort : keep the max element at the right most and again call for first n-1 elements
insertion sort : solve first n-1 and then insert last element in correct position
mergesort(total) : mergesort(left), mergesort(right), merge()
quicksort(total) : partition(), quicksort(leftP), quicksort(rightP) - i = low-1 and till i the array is less than arr[p]

Bubble / selection : first the last element is kept in its correct place
Insertion : first the left most element is kept in its correct place

Selection : O(n^2) in all and not stable
Bubble / Insertion : O(n) in best, O(n^2) in average and worst and stable
Merge : O(nlogn) in all and stable
Quick : O(nlogn) in best and average, O(n^2) in worst case (bad pivot) and not stable 

MergeSort : 
n
n/2 + n/2
n/4 + n/4 + n/4 + n/4
it happens logn times : so nlogn

Quicksort : in bad pivot case, n + n-1 + n-2 + ... gives O(n^2
In best case, pivot splits array roughly in half every time
n → n/2 + n/2  
n/2 → n/4 + n/4  
...
and it happens logn times - 
// _____________________________________________________________



Selection Sort
/*
Start with the first element as the current position.
Find the minimum element in the unsorted portion of the array.
Swap the minimum element with the element at the current position.
-> Here, startIndex(j) gets decreased by 1 each time
*/
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i; // Index of the smallest element
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]); // Swap the smallest element with the first unsorted element
    }
}
/*
Time Complexity: O(n^2) (best, worst, and average cases).
Space Complexity: O(1) (in-place sorting).
Stability: Not stable (relative order of equal elements may change).

Index:  0   1   2   3
Array:  4a  4b  3   2

Index:  0   1   2   3
Array:  2   4b  3   4a

Order got changed here
*/
_________________________________________

Bubble Sort
/*
Start at the beginning of the array.
Compare each pair of adjacent elements:
    If the current element is greater than the next, swap them.
After one pass, the largest element "bubbles up" to its correct position at the end of the array.
Repeat for the remaining unsorted portion of the array.
Stop when no swaps are made during a pass (array is sorted).
-> Here, endIndex(j) gets decreased by 1 each time
*/
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) // If no swaps in a pass, array is sorted
            break;
    }
}
/*
Time Complexity: O(n^2) (worst/average), O(n) (best case if already sorted).
Space Complexity: O(1) (in-place sorting).
Stability: Stable (relative order of equal elements remains unchanged).

In Insertion Sort, when an element (the key) is compared to elements on its left, it is only inserted into the position 
where it is smaller than the left elements. Importantly, when equal elements are encountered, no swapping happens.
*/
________________________________

Recursive Bubble Sort :
/*
Perform a single pass through the array, comparing and swapping adjacent elements if needed.
After the pass, the largest element will have moved to its correct position.
Recursively call the function to sort the remaining unsorted part of the array (excluding the last element, as it's already sorted).
SC : O(n) due to recursion stack.
*/
void recursiveBubbleSort(vector<int>& arr, int n) {
    // Base case: If array has one or zero elements, it's already sorted
    if (n == 1)
        return;

    // Perform one pass through the array
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            // Swap if elements are in the wrong order
            swap(arr[i], arr[i + 1]);
        }
    }

    // Recursively call the function for the first n-1 elements
    recursiveBubbleSort(arr, n - 1);
}
________________________________________

Insertion Sort
/*
Start from the second element (index 1) as the key.
Compare the key with the elements in the sorted portion of the array (to its left).
Shift elements larger than the key one position to the right.
Insert the key into its correct position in the sorted portion.
Repeat steps 2-4 for all elements in the array.
*/
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Shift elements of arr[0..i-1] that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key; // Place key in its correct position
    }
}
/*
Time Complexity: O(n^2) (worst/average), O(n) (best case if already sorted).
Space Complexity: O(1) (in-place sorting).
Stability: Stable (relative order of equal elements remains unchanged).

In Bubble Sort, adjacent elements are repeatedly compared, and if the current element is greater than the next, 
they are swapped. However, when two elements are equal, no swap occurs between them.
*/
____________________________________________

Recursive Insertion Sort :
/*
Sort the first n-1 elements recursively.
Insert the nth element into the sorted portion of the array by shifting larger elements to the right.
The base case occurs when the array has one element or no elements.
*/

void recursiveInsertionSort(vector<int>& arr, int n) {
    // Base case: If the array has one or zero elements, it's already sorted
    if (n <= 1)
        return;

    // Recursively sort the first n-1 elements
    recursiveInsertionSort(arr, n - 1);

    // Insert the nth element into its correct position in the sorted portion
    int key = arr[n - 1];
    int j = n - 2;

    // Shift elements of arr[0..n-2] that are greater than key
    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = key;
}
/*
Bubble : first the last element is kept in its correct place
R bubble : same 
Insertion : first the left most element is kept in its correct place
R Insertion : last the last element is placed in its place
*/
_________________________________________

Merge Sort :

/*
Divide and Conquer: Merge Sort follows the divide and conquer paradigm. The array is 
    recursively divided into two halves, sorted, and then merged back together.
Recursive Process: The array is divided into two halves until each sub-array has one element. 
    Then, these sub-arrays are merged back in sorted order.
*/
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays for the left and right halves
    vector<int> leftArr(n1), rightArr(n2);

    // Copy data into temp arrays
    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = arr[mid + 1 + i];

    // Merge the temp arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // Copy any remaining elements from leftArr
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Copy any remaining elements from rightArr
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    mergeSort(arr, 0, n - 1);
}

/*
Stability: Merge Sort is stable, meaning the relative order of equal elements is preserved.
Time Complexity: O(n log n) in all cases (best, worst, and average).
Space Complexity: O(n) because it requires extra space for the temporary arrays during merging.
Not In-Place: Merge Sort requires additional space to store temporary arrays during the merge process.
*/
___________________________________________

Quick Sort :
/*
Choose a Pivot: Select an element from the array (commonly the last element).
Partition: Rearrange the array so that elements less than the pivot are on the left, and elements greater than the pivot are on the right.
Recursion: Recursively apply the same steps to the left and right sub-arrays.
*/
int partition(vector<int>& arr, int low, int high) {
    // Pivot is the last element
    int pivot = arr[high];
    int i = low - 1;

    // Rearrange the elements in the array around the pivot
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {      // swap all the arr[j] which have <= pivot value to left side and keep pivot on i+1 side
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    // Place the pivot element in the correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Recursively sort the left and right sub-arrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    quickSort(arr, 0, n - 1);
}
