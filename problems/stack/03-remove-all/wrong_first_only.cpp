// YANLIŞ: sadece üstten ilk geçişi siliyor
void removeAll(Stack& myStack, int targetItem) {
    Stack temp;
    bool removed = false;
    while (!myStack.isEmpty()) {
        int x = myStack.peek(); myStack.pop();
        if (x == targetItem && !removed) { removed = true; continue; }
        temp.push(x);
    }
    while (!temp.isEmpty()) { myStack.push(temp.peek()); temp.pop(); }
}
