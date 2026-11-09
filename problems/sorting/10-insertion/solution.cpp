// Lecture 6 — Insertion sort (referans çözüm)
void insertionSort(int arr[], int n) {
    for (int unsorted = 1; unsorted < n; unsorted++) {    // arr[0..unsorted-1] sıralı
        int nextItem = arr[unsorted];
        int loc = unsorted;
        while (loc > 0 && arr[loc - 1] > nextItem) {      // büyükleri sağa kaydır
            arr[loc] = arr[loc - 1];
            loc--;
        }
        arr[loc] = nextItem;                              // boşluğa yerleştir
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    insertionSort(arr, 7);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
