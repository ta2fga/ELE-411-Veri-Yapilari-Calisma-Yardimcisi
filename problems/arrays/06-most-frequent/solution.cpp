// Study 11 — En sık geçen eleman (referans çözüm)
// Karmaşıklık: O(N^2) zaman, O(1) ek bellek
int mostFrequent(int arr[], int n) {
    int best = arr[0], bestCount = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++)          // arr[i] kaç kez geçiyor?
            if (arr[j] == arr[i]) count++;
        if (count > bestCount) {             // sadece kesin büyükse: eşitlikte önceki kalır
            bestCount = count;
            best = arr[i];
        }
    }
    return best;
}

int main() {
    int arr[] = {1, 3, 2, 3, 1, 3};
    cout << mostFrequent(arr, 6) << endl;
    return 0;
}
