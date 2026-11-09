// Study 13 — Queue'da minimum (sırayı koru)
// Başka bir Queue veya Stack kullanılabilir; dizi/vector YOK. q boş değil.
// Queue UML: isEmpty(), enqueue(int), dequeue() -> bool, peekFront() -> int

int findMin(Queue& q) {
    // Kodunuzu buraya yazın

    return 0;
}

int main() {
    Queue q = makeQueue({7, 3, 9, 1, 4});   // önden arkaya
    cout << findMin(q) << endl;             // 1
    printQueue(q);                          // [7, 3, 9, 1, 4] kalmalı
    return 0;
}
