// midterm.pdf — Stack'te hedef arama
// Stack, Queue, Node... ele411.h'den otomatik gelir (iostream + using namespace std dahil).
//
// Girdiler:
//   1. myStack   : int stack'i
//   2. targetItem: aranacak tamsayı
// Çıktı:
//   result: hedef bulunduysa true, bulunmadıysa false
//
// Kurallar: Fonksiyondan çıkarken stack'in sırası KORUNMALI.
//           Dizi, Queue, vector vb. YOK — sadece bir yardımcı Stack kullanılabilir.
// Stack UML: isEmpty(): bool, push(int): bool, pop(): bool (değer döndürmez!), peek(): int

bool searchStack(Stack& myStack, int targetItem) {
    // Kodunuzu buraya yazın

    return false;
}

// "Çalıştır" bu main'i kullanır; "Test et" ise kendi testlerini çalıştırır.
int main() {
    Stack s = makeStack({4, 7, 1, 9});   // alttan üste 4 7 1 9 (9 en üstte)
    cout << boolalpha;
    cout << "1 var mi?  " << searchStack(s, 1) << endl;   // true
    cout << "5 var mi?  " << searchStack(s, 5) << endl;   // false
    printStack(s);                                        // [4, 7, 1, 9] kalmalı
    return 0;
}
