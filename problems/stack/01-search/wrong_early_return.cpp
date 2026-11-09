// YANLIŞ: bulunca hemen return ediyor, temp geri dökülmüyor
bool searchStack(Stack& myStack, int targetItem) {
    Stack temp;
    while (!myStack.isEmpty()) {
        int x = myStack.peek();
        if (x == targetItem) return true;
        myStack.pop();
        temp.push(x);
    }
    while (!temp.isEmpty()) { myStack.push(temp.peek()); temp.pop(); }
    return false;
}
