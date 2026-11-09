// Midterm2019 Q6 — Stack'ten hedefin tüm geçişlerini silme (referans çözüm)

void removeAll(Stack& myStack, int targetItem) {
    Stack temp;   // sadece bir yardımcı stack

    // 1) Tüm elemanları çıkar; hedef olmayanları temp'e sakla
    while (!myStack.isEmpty()) {
        int topItem = myStack.peek();
        myStack.pop();
        if (topItem != targetItem)
            temp.push(topItem);     // hedefler push edilmediği için silinmiş olur
    }

    // 2) temp'tekileri geri koy: ters sıra tekrar düzelir
    while (!temp.isEmpty()) {
        myStack.push(temp.peek());
        temp.pop();
    }
}

int main() {
    Stack s = makeStack({7, 1, 7, 2, 7});
    removeAll(s, 7);
    printStack(s);
    return 0;
}
