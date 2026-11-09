// YANLIŞ: geri dökmek yerine temp'i kopyalıyor -> sıra ters kalıyor
void removeAll(Stack& myStack, int targetItem) {
    Stack temp;
    while (!myStack.isEmpty()) {
        int x = myStack.peek(); myStack.pop();
        if (x != targetItem) temp.push(x);
    }
    myStack = temp;
}
