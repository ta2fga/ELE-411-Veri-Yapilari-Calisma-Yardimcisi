// YANLIŞ: önce yazdırıp sonra recursive çağırıyor -> düz sırada yazar
void printReverse(StringNode* headPtr) {
    if (headPtr == nullptr) return;
    cout << headPtr->getItem() << endl;
    printReverse(headPtr->getNext());
}
