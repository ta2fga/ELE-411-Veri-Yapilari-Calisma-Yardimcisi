// YANLIŞ: iç döngü last'ı kontrol etmiyor (i < last)
void selectionSort(int arr[], int n) {
    for (int last = n - 1; last >= 1; last--) {
        int largest = 0;
        for (int i = 1; i < last; i++) if (arr[i] > arr[largest]) largest = i;
        int t = arr[largest]; arr[largest] = arr[last]; arr[last] = t;
    }
}
