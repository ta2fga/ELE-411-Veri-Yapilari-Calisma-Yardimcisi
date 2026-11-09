// YANLIŞ (sd.pdf'teki hata): stack DEĞERLE geçiriliyor; fonksiyon kopyayı ters çevirir,
// çağıranın stack'i değişmez.
void reverseStack(Stack st) {
    Queue q;
    while (!st.isEmpty()) { q.enqueue(st.peek()); st.pop(); }
    while (!q.isEmpty()) { st.push(q.peekFront()); q.dequeue(); }
}
