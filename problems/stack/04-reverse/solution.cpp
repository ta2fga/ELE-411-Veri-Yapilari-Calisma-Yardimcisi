// Study 7 — Stack'i ters çevirme (referans çözüm, sd.pdf'in DÜZELTİLMİŞ hali)
//
// sd.pdf'teki hatalar:
//   * "int st = st.top()"   -> stack ile aynı isimde değişken; x tanımsız
//   * insert_at_bottom(x)   -> stack argümanı unutulmuş
//   * stack DEĞERLE geçiriliyor -> fonksiyonun yaptığı değişiklik kayboluyor
// Aşağıda hepsi düzeltildi: stack her yerde referansla (Stack&) geçiriliyor.

// x'i stack'in EN ALTINA yerleştirir.
void insertAtBottom(Stack& st, int x) {
    if (st.isEmpty()) {
        st.push(x);                 // base case: boş stack'te en alt = en üst
    } else {
        int topItem = st.peek();    // üsttekini geçici olarak al (çağrı yığınında saklanır)
        st.pop();
        insertAtBottom(st, x);      // x'i kalan kısmın altına koy
        st.push(topItem);           // aldığımızı geri koy
    }
}

// Stack'i recursive olarak ters çevirir.
void reverseStack(Stack& st) {
    if (!st.isEmpty()) {
        int x = st.peek();          // üsttekini al
        st.pop();
        reverseStack(st);           // geri kalanını ters çevir
        insertAtBottom(st, x);      // eski üst elemanı en alta koy
    }
}
// Karmaşıklık: O(N^2) — her insertAtBottom O(N), N kez çağrılıyor.

/* ---------------- ALTERNATİF 1: bir Queue ile, O(N) ----------------
void reverseStack(Stack& st) {
    Queue q;
    while (!st.isEmpty()) {         // üstten başlayarak queue'ya at
        q.enqueue(st.peek());
        st.pop();
    }
    while (!q.isEmpty()) {          // queue'nun önündeki (eski üst) ilk push edilir
        st.push(q.peekFront());     // -> en alta iner
        q.dequeue();
    }
}

   ---------------- ALTERNATİF 2: iki yardımcı Stack ile, O(N) ----------------
void pour(Stack& from, Stack& to) {   // from'u to'ya döker (sırayı ters çevirir)
    while (!from.isEmpty()) { to.push(from.peek()); from.pop(); }
}
void reverseStack(Stack& st) {
    Stack t1, t2;
    pour(st, t1);    // ters
    pour(t1, t2);    // tekrar orijinal
    pour(t2, st);    // st'de ters
}
------------------------------------------------------------------- */

int main() {
    Stack s = makeStack({1, 2, 3, 4});
    reverseStack(s);
    printStack(s);
    return 0;
}
