// Midterm2020 — Bağlı listede bubble sort
// Girdi : headPtr (Node*)     Çıktı: yok (void)
// Node UML: getNext(): Node*, getItem(): int, setNext(Node*), setItem(int)
// Başka veri yapısı YOK; değişiklikler doğrudan liste üzerinde.

void bubbleSortList(Node* headPtr) {
    // Kodunuzu buraya yazın

}

int main() {
    Node* head = makeList({5, 1, 4, 2, 8});
    bubbleSortList(head);
    printList(head);   // 1 -> 2 -> 4 -> 5 -> 8 -> nullptr
    deleteList(head);
    return 0;
}
