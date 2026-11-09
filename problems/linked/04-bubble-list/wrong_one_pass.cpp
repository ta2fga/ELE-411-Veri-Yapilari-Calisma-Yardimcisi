// YANLIŞ: sadece tek geçiş yapıyor
void bubbleSortList(Node* headPtr) {
    if (!headPtr) return;
    for (Node* c = headPtr; c->getNext() != nullptr; c = c->getNext())
        if (c->getItem() > c->getNext()->getItem()) { int t = c->getItem(); c->setItem(c->getNext()->getItem()); c->getNext()->setItem(t); }
}
