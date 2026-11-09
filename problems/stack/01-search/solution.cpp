// midterm.pdf — Stack'te hedef arama (referans çözüm)
// Fikir: Elemanları tek tek yardımcı stack'e taşıyarak hedefi ara,
//        sonra hepsini geri taşıyarak orijinal sırayı geri kur.

bool searchStack(Stack& myStack, int targetItem) {
    Stack temp;              // izin verilen tek yardımcı yapı
    bool found = false;

    // 1) Hedefi bulana kadar ya da stack boşalana kadar üstten bak
    while (!myStack.isEmpty()) {
        int topItem = myStack.peek();   // pop() değer döndürmez: önce peek
        if (topItem == targetItem) {
            found = true;               // bulduk; hedefi yerinde bırakıp çık
            break;
        }
        myStack.pop();
        temp.push(topItem);             // temp'te sıra ters
    }

    // 2) temp'tekileri geri koy -> sıra eski haline döner
    while (!temp.isEmpty()) {
        myStack.push(temp.peek());
        temp.pop();
    }
    return found;                       // return, geri doldurmadan SONRA
}

int main() {
    Stack s = makeStack({4, 7, 1, 9});
    cout << boolalpha;
    cout << "1 var mi?  " << searchStack(s, 1) << endl;
    cout << "5 var mi?  " << searchStack(s, 5) << endl;
    printStack(s);
    return 0;
}
