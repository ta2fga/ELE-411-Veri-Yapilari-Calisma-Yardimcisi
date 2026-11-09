// YANLIŞ: sadece ileri tarama, ve dış döngü bir tur eksik
void cocktailSort(int arr[], int N) {
    for (int p = 0; p < N / 2; p++)
        for (int i = 0; i < N - 1 - p; i++)
            if (arr[i] > arr[i + 1]) { int t = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = t; }
}
