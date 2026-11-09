// YANLIŞ: geri doldurmuyor -> sıra bozuluyor
bool searchStack(Stack& myStack, int targetItem) {
    while (!myStack.isEmpty()) {
        if (myStack.peek() == targetItem) return true;
        myStack.pop();
    }
    return false;
}
