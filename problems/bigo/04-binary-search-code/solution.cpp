// Study 8 — Binary search (referans çözüm)
int binarySearch(int arr[], int n, int target, int& comparisons) {
    comparisons = 0;
    int first = 0, last = n - 1;
    while (first <= last) {
        int mid = first + (last - first) / 2;   // taşmayı önleyen orta nokta
        comparisons++;                          // ortadaki elemanla bir karşılaştırma
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            first = mid + 1;                    // sağ yarıda ara
        else
            last = mid - 1;                     // sol yarıda ara
    }
    return -1;                                  // bulunamadı
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int c;
    cout << binarySearch(arr, 8, 11, c) << " (" << c << " karsilastirma)" << endl;
    cout << binarySearch(arr, 8, 100, c) << " (" << c << " karsilastirma)" << endl;
    return 0;
}
