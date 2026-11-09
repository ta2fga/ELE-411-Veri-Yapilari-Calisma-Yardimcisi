// Midterm2019 Q7 — Cocktail sort (referans çözüm)
void swapItems(int& a, int& b) { int t = a; a = b; b = t; }

void cocktailSort(int arr[], int N) {
    int left = 0, right = N - 1;      // sıralanmamış kısım: arr[left..right]
    bool swapped = true;
    while (swapped && left < right) {
        swapped = false;
        // 1) soldan sağa: maksimumu sağa taşı
        for (int i = left; i < right; i++)
            if (arr[i] > arr[i + 1]) { swapItems(arr[i], arr[i + 1]); swapped = true; }
        right--;                      // en büyük yerine oturdu
        // 2) sağdan sola: minimumu sola taşı
        for (int i = right; i > left; i--)
            if (arr[i - 1] > arr[i]) { swapItems(arr[i - 1], arr[i]); swapped = true; }
        left++;                       // en küçük yerine oturdu
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    cocktailSort(arr, 7);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
