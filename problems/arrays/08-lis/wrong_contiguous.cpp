// YANLIŞ: sadece ardışık (yan yana) artan parçaya bakıyor
int lengthOfLIS(int arr[], int n) {
    if (n == 0) return 0;
    int best = 1, cur = 1;
    for (int i = 1; i < n; i++) { cur = (arr[i] > arr[i - 1]) ? cur + 1 : 1; if (cur > best) best = cur; }
    return best;
}
