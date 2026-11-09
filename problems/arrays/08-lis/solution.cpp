// Study 15 — LIS (referans çözüm, dinamik programlama O(N^2))
int lengthOfLIS(int arr[], int n) {
    if (n == 0) return 0;
    int* lis = new int[n];        // lis[i]: arr[i] ile biten en uzun artan alt dizi
    int best = 1;
    for (int i = 0; i < n; i++) {
        lis[i] = 1;               // tek başına arr[i]
        for (int j = 0; j < i; j++)
            if (arr[j] < arr[i] && lis[j] + 1 > lis[i])
                lis[i] = lis[j] + 1;   // arr[j]'de biten diziye arr[i]'yi ekle
        if (lis[i] > best) best = lis[i];
    }
    delete[] lis;
    return best;
}

int main() {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lengthOfLIS(arr, 8) << endl;
    return 0;
}
