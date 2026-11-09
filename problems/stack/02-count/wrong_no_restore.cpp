// YANLIŞ: sayıyor ama stack'i boşaltıp bırakıyor
int countItem(Stack& myStack, int targetItem) {
    int count = 0;
    while (!myStack.isEmpty()) {
        if (myStack.peek() == targetItem) count++;
        myStack.pop();
    }
    return count;
}
