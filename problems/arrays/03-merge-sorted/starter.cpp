// Study 2 — İki sıralı diziyi birleştirme
// arr3'ün boyutu n1 + n2. Sonuç sıralı olmalı.

void mergeArrays(int arr1[], int arr2[], int n1, int n2, int arr3[]) {
    // Kodunuzu buraya yazın

}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int arr3[8];
    mergeArrays(arr1, arr2, 4, 4, arr3);
    printArray(arr3, 8);   // [1, 2, 3, 4, 5, 6, 7, 8]
    return 0;
}
