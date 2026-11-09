// YANLIŞ: yardımcı olarak stack kullanıp geri aktarıyor -> sıra ters dönüyor
int findMin(Queue& q) {
    Stack s; int m = q.peekFront();
    while (!q.isEmpty()) { int x = q.peekFront(); q.dequeue(); if (x < m) m = x; s.push(x); }
    while (!s.isEmpty()) { q.enqueue(s.peek()); s.pop(); }
    return m;
}
