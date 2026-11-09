// Study 13 — Queue'da minimum (referans çözüm)
int findMin(Queue& q) {
    Queue temp;                      // yardımcı queue: FIFO sırayı korur
    int minVal = q.peekFront();      // q boş değil
    while (!q.isEmpty()) {
        int x = q.peekFront();       // dequeue değer döndürmez: önce peekFront
        q.dequeue();
        if (x < minVal) minVal = x;
        temp.enqueue(x);
    }
    while (!temp.isEmpty()) {        // aynı sırayla geri aktar
        q.enqueue(temp.peekFront());
        temp.dequeue();
    }
    return minVal;
}

int main() {
    Queue q = makeQueue({7, 3, 9, 1, 4});
    cout << findMin(q) << endl;
    printQueue(q);
    return 0;
}
