// Midterm2020 — Bağlı listede bubble sort (referans çözüm)
// headPtr değerle geldiği için düğümleri değil, item'ları takas ediyoruz.
void bubbleSortList(Node* headPtr) {
    if (headPtr == nullptr) return;              // boş liste
    Node* end = nullptr;                         // end'den sonrası sıralı
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Node* cur = headPtr;
        while (cur->getNext() != end) {          // sıralı kısma kadar
            Node* nextNode = cur->getNext();
            if (cur->getItem() > nextNode->getItem()) {
                int temp = cur->getItem();       // komşuların item'larını takas et
                cur->setItem(nextNode->getItem());
                nextNode->setItem(temp);
                swapped = true;
            }
            cur = nextNode;
        }
        end = cur;                               // en büyük eleman cur'a yerleşti
    }
}

int main() {
    Node* head = makeList({5, 1, 4, 2, 8});
    bubbleSortList(head);
    printList(head);
    deleteList(head);
    return 0;
}
