// Midterm2019 Q8 — 0/1 dizisini sıralama (referans çözüm)
// Karmaşıklık: O(N) zaman, O(1) ek bellek
void sortBinaryArray(int arr[], int N) {
    int zeros = 0;
    for (int i = 0; i < N; i++)          // 1. geçiş: 0'ları say
        if (arr[i] == 0) zeros++;
    for (int i = 0; i < N; i++)          // 2. geçiş: önce 0'lar, sonra 1'ler
        arr[i] = (i < zeros) ? 0 : 1;
}

int main() {
    int arr[] = {1, 0, 1, 1, 0, 0, 1, 0};
    sortBinaryArray(arr, 8);
    printArray(arr, 8);
    return 0;
}
