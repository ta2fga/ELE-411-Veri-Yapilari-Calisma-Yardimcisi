// Midterm2020 — Stack'te hedefi sayma
// Girdiler:
//   1. myStack   : int stack'i
//   2. targetItem: tüm geçişleri sayılacak tamsayı
// Çıktı:
//   count: hedefin kaç kez geçtiği (int)
//
// Kurallar: Stack'in sırası KORUNMALI. Dizi/Queue/vector YOK — sadece bir yardımcı Stack.
// Stack UML: isEmpty(), push(int), pop() -> bool (değer döndürmez!), peek() -> int

int countItem(Stack& myStack, int targetItem) {
    // Kodunuzu buraya yazın

    return 0;
}

int main() {
    Stack s = makeStack({2, 5, 2, 7, 2});   // alttan üste
    cout << "2 sayisi: " << countItem(s, 2) << endl;   // 3
    printStack(s);                                     // [2, 5, 2, 7, 2] kalmalı
    return 0;
}
