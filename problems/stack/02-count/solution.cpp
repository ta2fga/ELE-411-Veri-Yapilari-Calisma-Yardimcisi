// Midterm2020 — Stack'te hedefi sayma (referans çözüm)

int countItem(Stack& myStack, int targetItem) {
    Stack temp;          // sadece bir yardımcı stack
    int count = 0;

    // 1) Tüm elemanları gez: say ve temp'e taşı
    while (!myStack.isEmpty()) {
        int topItem = myStack.peek();   // önce değeri al
        myStack.pop();                  // sonra çıkar
        if (topItem == targetItem)
            count++;
        temp.push(topItem);
    }

    // 2) Geri doldur: temp'teki ters sıra tekrar orijinal sıraya döner
    while (!temp.isEmpty()) {
        myStack.push(temp.peek());
        temp.pop();
    }
    return count;
}

int main() {
    Stack s = makeStack({2, 5, 2, 7, 2});
    cout << "2 sayisi: " << countItem(s, 2) << endl;
    printStack(s);
    return 0;
}
