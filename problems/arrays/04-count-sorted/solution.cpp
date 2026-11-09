// Study 4 / midterm.pdf — Sıralı dizide geçiş sayısı (referans çözüm)
// İki değiştirilmiş binary search: hedefin ilk ve son indeksi. Karmaşıklık: O(logN)

// leftmost = true  -> ilk geçişin indeksi
// leftmost = false -> son geçişin indeksi    (bulunamazsa -1)
int findBoundary(int arr[], int N, int target, bool leftmost) {
    int first = 0, last = N - 1, result = -1;
    while (first <= last) {
        int mid = first + (last - first) / 2;
        if (arr[mid] == target) {
            result = mid;                     // adayı kaydet ve aramaya devam et
            if (leftmost) last = mid - 1;     // daha solda var mı?
            else          first = mid + 1;    // daha sağda var mı?
        } else if (arr[mid] < target) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    return result;
}

int countOccurrences(int arr[], int N, int target) {
    int firstIdx = findBoundary(arr, N, target, true);
    if (firstIdx == -1) return 0;                       // hiç yok
    int lastIdx = findBoundary(arr, N, target, false);
    return lastIdx - firstIdx + 1;
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 5, 5, 8};
    cout << countOccurrences(arr, 8, 2) << endl;
    cout << countOccurrences(arr, 8, 4) << endl;
    return 0;
}
