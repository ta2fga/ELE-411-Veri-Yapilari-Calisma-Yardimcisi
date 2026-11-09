// Study 2 — İki sıralı diziyi birleştirme (referans çözüm, sd.pdf'in düzeltilmiş hali)
void mergeArrays(int arr1[], int arr2[], int n1, int n2, int arr3[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {          // iki dizide de eleman varken
        if (arr1[i] < arr2[j])          // sd.pdf'te EKSİK olan karşılaştırma
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }
    while (i < n1)                      // arr1'de kalanlar
        arr3[k++] = arr1[i++];
    while (j < n2)                      // arr2'de kalanlar
        arr3[k++] = arr2[j++];
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int arr3[8];
    mergeArrays(arr1, arr2, 4, 4, arr3);
    printArray(arr3, 8);
    return 0;
}
