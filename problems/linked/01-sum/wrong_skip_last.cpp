// YANLIŞ: son düğümü atlıyor
int sumList(Node* head) {
    int s = 0;
    if (head == nullptr) return 0;
    for (Node* c = head; c->next != nullptr; c = c->next) s += c->item;
    return s;
}
