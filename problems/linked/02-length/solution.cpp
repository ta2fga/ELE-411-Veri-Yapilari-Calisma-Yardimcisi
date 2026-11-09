// Study 16 — Bağlı liste uzunluğu (referans çözüm)
int lengthIterative(Node* head) {
    int count = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        count++;
    return count;
}

int lengthRecursive(Node* head) {
    if (head == nullptr)                      // base case: boş liste
        return 0;
    return 1 + lengthRecursive(head->next);   // bu düğüm + geri kalanı
}

int main() {
    Node* head = makeList({3, 1, 4, 1, 5});
    cout << lengthIterative(head) << " " << lengthRecursive(head) << endl;
    deleteList(head);
    return 0;
}
