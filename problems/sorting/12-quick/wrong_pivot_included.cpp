// YANLIŞ: recursive çağrılarda pivot hariç tutulmuyor ve takas unutulmuş
void quickSort(int arr[], int first, int last) {
    if (first >= last) return;
    int pivot = arr[last], i = first - 1;
    for (int j = first; j < last; j++) if (arr[j] < pivot) { i++; int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }
    quickSort(arr, first, i);
    quickSort(arr, i + 2, last);
}
