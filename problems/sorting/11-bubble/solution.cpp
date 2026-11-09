// Lecture 6 — Bubble sort, erken durmalı (referans çözüm)
void bubbleSort(int arr[], int n) {
    bool sorted = false;
    int pass = 1;
    while (!sorted && pass < n) {
        sorted = true;                            // bu geçişte takas olmazsa biter
        for (int i = 0; i < n - pass; i++) {      // son pass-1 eleman zaten yerinde
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = temp;
                sorted = false;
            }
        }
        pass++;
    }
}

int main() {
    int arr[] = {7, 2, 12, 5, 6, 4, 9};
    bubbleSort(arr, 7);
    printArray(arr, 7);   // [2, 4, 5, 6, 7, 9, 12]
    return 0;
}
