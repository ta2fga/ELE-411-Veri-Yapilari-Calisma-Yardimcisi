// Lecture 6 — Selection sort, maksimumu seçen sürüm (referans çözüm)
void selectionSort(int arr[], int n) {
    for (int last = n - 1; last >= 1; last--) {     // arr[last+1..n-1] sıralı
        int largest = 0;
        for (int i = 1; i <= last; i++)             // arr[0..last] içindeki en büyük
            if (arr[i] > arr[largest]) largest = i;
        int temp = arr[largest];                    // en büyüğü sona taşı
        arr[largest] = arr[last];
        arr[last] = temp;
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    selectionSort(arr, 7);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
