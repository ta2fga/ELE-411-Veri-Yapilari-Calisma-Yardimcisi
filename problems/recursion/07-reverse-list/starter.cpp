// Midterm2019 Q2 — Bağlı listeyi recursive olarak tersten yazdır
// Girdi : headPtr — ilk düğüm (StringNode*), son düğüm nullptr'ı gösterir
// Çıktı : yok (void); her öğeyi ayrı satıra yazdırın
// Node UML: getNext(): Node*, getItem(): string

void printReverse(StringNode* headPtr) {
    // Kodunuzu buraya yazın

}

int main() {
    StringNode* head = makeStringList({"ali", "veli", "deli"});
    printReverse(head);   // deli / veli / ali
    deleteList(head);
    return 0;
}
