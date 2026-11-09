// YANLIŞ (verimsiz): lineer tarama O(N) -> büyük testte zaman aşımı
int countOccurrences(int arr[], int N, int target) {
    int c = 0;
    for (int i = 0; i < N; i++) if (arr[i] == target) c++;
    return c;
}
