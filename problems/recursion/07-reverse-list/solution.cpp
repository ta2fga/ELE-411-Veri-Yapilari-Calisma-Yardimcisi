// Midterm2019 Q2 — Bağlı listeyi tersten yazdır (referans çözüm)
void printReverse(StringNode* headPtr) {
    if (headPtr == nullptr)                  // base case: listenin sonu
        return;
    printReverse(headPtr->getNext());        // önce geri kalanını tersten yazdır
    cout << headPtr->getItem() << endl;      // sonra bu düğümü
}

int main() {
    StringNode* head = makeStringList({"ali", "veli", "deli"});
    printReverse(head);
    deleteList(head);
    return 0;
}
