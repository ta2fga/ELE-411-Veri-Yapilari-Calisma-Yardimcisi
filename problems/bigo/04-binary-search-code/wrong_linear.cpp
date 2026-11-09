// YANLIŞ: lineer arama (karşılaştırma sınırını aşar)
int binarySearch(int arr[], int n, int target, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) { comparisons++; if (arr[i] == target) return i; }
    return -1;
}
