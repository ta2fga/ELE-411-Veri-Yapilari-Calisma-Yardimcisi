int lengthIterative(Node* head) { int c = 0; while (head) { c++; head = head->next; } return c; }
// YANLIŞ: recursive base case 1 döndürüyor
int lengthRecursive(Node* head) {
    if (head == nullptr) return 1;
    return 1 + lengthRecursive(head->next);
}
