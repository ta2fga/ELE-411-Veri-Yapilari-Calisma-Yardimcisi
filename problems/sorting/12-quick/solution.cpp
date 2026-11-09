// Lecture 6 — Quick sort, son eleman pivot / Lomuto bölümleme (referans çözüm)
void swapItems(int& a, int& b) { int t = a; a = b; b = t; }

// arr[first..last]'ı arr[last] etrafında bölümler, pivotun son indeksini döndürür
int partition(int arr[], int first, int last) {
    int pivot = arr[last];
    int i = first - 1;                      // arr[first..i] <= pivot
    for (int j = first; j < last; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapItems(arr[i], arr[j]);
        }
    }
    swapItems(arr[i + 1], arr[last]);       // pivot kesin yerine
    return i + 1;
}

void quickSort(int arr[], int first, int last) {
    if (first < last) {                     // en az 2 eleman
        int p = partition(arr, first, last);
        quickSort(arr, first, p - 1);       // pivotun solu
        quickSort(arr, p + 1, last);        // pivotun sağı
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    quickSort(arr, 0, 6);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
