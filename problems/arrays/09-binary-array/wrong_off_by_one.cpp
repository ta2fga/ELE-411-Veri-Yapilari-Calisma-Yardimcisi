// YANLIŞ: sınır bir kaymış
void sortBinaryArray(int arr[], int N) {
    int zeros = 0;
    for (int i = 0; i < N; i++) if (arr[i] == 0) zeros++;
    for (int i = 0; i < N; i++) arr[i] = (i <= zeros) ? 0 : 1;
}
