// Lecture 6 — Merge sort (referans çözüm)
void merge(int arr[], int first, int mid, int last) {
    int size = last - first + 1;
    int* temp = new int[size];                  // geçici dizi
    int i = first, j = mid + 1, k = 0;
    while (i <= mid && j <= last)               // küçük olanı al
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid)  temp[k++] = arr[i++];     // kalanlar
    while (j <= last) temp[k++] = arr[j++];
    for (k = 0; k < size; k++)                  // geri kopyala
        arr[first + k] = temp[k];
    delete[] temp;
}

void mergeSort(int arr[], int first, int last) {
    if (first < last) {
        int mid = first + (last - first) / 2;
        mergeSort(arr, first, mid);             // sol yarı
        mergeSort(arr, mid + 1, last);          // sağ yarı
        merge(arr, first, mid, last);           // birleştir
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    mergeSort(arr, 0, 6);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
