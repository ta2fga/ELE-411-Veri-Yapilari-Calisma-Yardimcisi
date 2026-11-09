// Lecture 4 — LinkedBag (int, sıralı)
// TODO: add, remove, contains metotlarını yazın. Diğerleri hazır.

class LinkedBag {
private:
    Node* headPtr;
    int itemCount;

    // target'ı içeren düğümü, yoksa nullptr döndürür
    Node* getPointerTo(const int target) const {
        Node* cur = headPtr;
        while (cur != nullptr) {
            if (target == cur->item) break;
            cur = cur->next;
        }
        return cur;
    }

public:
    LinkedBag() : headPtr(nullptr), itemCount(0) {}
    ~LinkedBag() { clear(); }
    int getCurrentSize() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
    int getFrequencyOf(const int anEntry) const {
        int frequency = 0;
        for (Node* cur = headPtr; cur != nullptr; cur = cur->next)
            if (anEntry == cur->item) frequency++;
        return frequency;
    }
    void clear() {
        while (headPtr != nullptr) {
            Node* nodeToBeDeleted = headPtr;
            headPtr = headPtr->next;
            delete nodeToBeDeleted;
        }
        itemCount = 0;
    }
    string toString() const { return listToString(headPtr); }   // test ve deneme için

    // Sıralı (küçükten büyüğe) ekler, true döner
    bool add(const int newItem) {
        // TODO
        return false;
    }

    // İlk eşleşen düğümü çıkarıp delete eder; yoksa false
    bool remove(const int anEntry) {
        // TODO
        return false;
    }

    bool contains(const int anEntry) const {
        // TODO
        return false;
    }
};

int main() {
    LinkedBag bag;
    bag.add(5); bag.add(1); bag.add(3);
    cout << bag.toString() << endl;   // 1 -> 3 -> 5 -> nullptr
    bag.remove(3);
    cout << bag.toString() << endl;   // 1 -> 5 -> nullptr
    return 0;
}
