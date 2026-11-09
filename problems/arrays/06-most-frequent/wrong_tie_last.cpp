// YANLIŞ: >= kullanıyor -> eşitlikte sonrakini seçiyor
int mostFrequent(int arr[], int n) {
    int best = arr[0], bestCount = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) if (arr[j] == arr[i]) c++;
        if (c >= bestCount) { bestCount = c; best = arr[i]; }
    }
    return best;
}
