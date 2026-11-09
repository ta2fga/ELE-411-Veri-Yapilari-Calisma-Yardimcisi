// YANLIŞ: karşılaştırma yapmadan arka arkaya kopyalıyor
void mergeArrays(int arr1[], int arr2[], int n1, int n2, int arr3[]) {
    int k = 0;
    for (int i = 0; i < n1; i++) arr3[k++] = arr1[i];
    for (int j = 0; j < n2; j++) arr3[k++] = arr2[j];
}
