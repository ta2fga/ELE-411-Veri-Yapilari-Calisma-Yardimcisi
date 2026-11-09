// Study 7 — Stack'i ters çevirme
// Girdi : st — int stack'i (REFERANSLA geçirin, yoksa değişiklik çağırana ulaşmaz!)
// Çıktı : yok (void). st yerinde ters çevrilir.
//
// Kurallar: Başka bir Stack veya Queue kullanılabilir. Dizi / vector / başka yapı YOK.
// Stack UML: isEmpty(), push(int), pop() -> bool, peek() -> int
// Queue UML: isEmpty(), enqueue(int), dequeue() -> bool, peekFront() -> int

void reverseStack(Stack& st) {
    // Kodunuzu buraya yazın

}

int main() {
    Stack s = makeStack({1, 2, 3, 4});   // alttan üste: 1 2 3 4 (4 en üstte)
    reverseStack(s);
    printStack(s);                       // [4, 3, 2, 1] olmalı (1 en üstte)
    return 0;
}
