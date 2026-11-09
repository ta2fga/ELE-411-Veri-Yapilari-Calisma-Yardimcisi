// Study 8 — Binary search ve karşılaştırma sayısı
// Her döngü adımında (ortadaki elemana bakışta) comparisons'ı 1 artırın.

int binarySearch(int arr[], int n, int target, int& comparisons) {
    comparisons = 0;
    // Kodunuzu buraya yazın

    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int c;
    cout << binarySearch(arr, 8, 11, c) << " (" << c << " karsilastirma)" << endl;
    cout << binarySearch(arr, 8, 100, c) << " (" << c << " karsilastirma)" << endl;   // en kotu durum: 4
    return 0;
}
