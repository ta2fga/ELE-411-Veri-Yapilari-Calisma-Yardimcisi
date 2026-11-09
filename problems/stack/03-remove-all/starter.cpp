// Midterm2019 Q6 — Stack'ten hedefin tüm geçişlerini silme
// Girdiler:
//   1. myStack   : int stack'i
//   2. targetItem: tüm geçişleri silinecek tamsayı
// Çıktı:
//   myStack: hedefler silinmiş stack (diğer elemanların sırası korunmuş)
//
// Kurallar: Dizi/Queue/vector YOK — sadece bir yardımcı Stack kullanılabilir.
// Stack UML: isEmpty(), push(int), pop() -> bool (değer döndürmez!), peek() -> int

void removeAll(Stack& myStack, int targetItem) {
    // Kodunuzu buraya yazın

}

int main() {
    Stack s = makeStack({7, 1, 7, 2, 7});   // alttan üste
    removeAll(s, 7);
    printStack(s);                          // [1, 2] olmalı
    return 0;
}
