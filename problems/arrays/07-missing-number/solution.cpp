// Study 14 — Eksik sayı (referans çözüm), O(N)
int findMissing(int arr[], int n) {
    long long expected = (long long)n * (n + 1) / 2;   // 0 + 1 + ... + n
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return (int)(expected - sum);                      // aradaki fark eksik sayıdır
}

int main() {
    int arr[] = {3, 0, 1};
    cout << findMissing(arr, 3) << endl;
    return 0;
}
