// Study 1 — Sırasız dizide tekrarları silme
// Girdi : arr, n      Çıktı: yeni uzunluk; arr'ın başında tekrarsız elemanlar (ilk geçiş sırasıyla)
// Örnek : [3, 1, 3, 2, 1] -> 3 döner, arr = [3, 1, 2, ...]

int removeDuplicates(int arr[], int n) {
    // Kodunuzu buraya yazın

    return n;
}

int main() {
    int arr[] = {3, 1, 3, 2, 1};
    int n = removeDuplicates(arr, 5);
    printArray(arr, n);   // [3, 1, 2]
    return 0;
}
