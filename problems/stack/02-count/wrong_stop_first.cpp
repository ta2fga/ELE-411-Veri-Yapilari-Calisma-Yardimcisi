// YANLIŞ: ilk eşleşmede duruyor (en fazla 1 döndürür)
int countItem(Stack& myStack, int targetItem) {
    Stack temp;
    int count = 0;
    while (!myStack.isEmpty()) {
        int x = myStack.peek();
        if (x == targetItem) { count++; break; }
        myStack.pop(); temp.push(x);
    }
    while (!temp.isEmpty()) { myStack.push(temp.peek()); temp.pop(); }
    return count;
}
