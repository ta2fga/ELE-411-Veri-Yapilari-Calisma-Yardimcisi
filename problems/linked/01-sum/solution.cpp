// Study 3 — Bağlı liste toplamı (referans çözüm)
int sumList(Node* head) {
    int sum = 0;
    Node* cur = head;
    while (cur != nullptr) {     // listenin sonuna kadar yürü
        sum += cur->item;
        cur = cur->next;
    }
    return sum;
}

int main() {
    Node* head = makeList({7, 6, 8, 4, 1});
    cout << "Sum of nodes = " << sumList(head) << endl;
    deleteList(head);
    return 0;
}
