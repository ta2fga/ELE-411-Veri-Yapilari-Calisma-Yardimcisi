// Study 1 — Sırasız dizide tekrarları silme (referans çözüm)
// Karmaşıklık: O(N^2) zaman, O(1) ek bellek
int removeDuplicates(int arr[], int n) {
    int newLen = 0;                          // arr[0..newLen-1]: şimdiye kadarki tekrarsız elemanlar
    for (int i = 0; i < n; i++) {
        bool seen = false;
        for (int j = 0; j < newLen; j++) {   // arr[i] daha önce alındı mı?
            if (arr[j] == arr[i]) { seen = true; break; }
        }
        if (!seen)
            arr[newLen++] = arr[i];          // ilk kez görüldü: tekrarsız kısma ekle
    }
    return newLen;
}

int main() {
    int arr[] = {3, 1, 3, 2, 1};
    int n = removeDuplicates(arr, 5);
    printArray(arr, n);
    return 0;
}
