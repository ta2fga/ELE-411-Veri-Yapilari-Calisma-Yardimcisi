// Lecture 4 — LinkedBag (referans çözüm; dersteki add'in eşitlik hatası düzeltildi)

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

    bool add(const int newItem) {
        Node* nodeToBeAdded = new Node(newItem);
        if (headPtr == nullptr || headPtr->item >= newItem) {
            // boş liste ya da en başa gelmeli (>=: eşitlikte de başa ekle, derste '>' idi)
            nodeToBeAdded->next = headPtr;
            headPtr = nodeToBeAdded;
        } else {
            Node* prev = nullptr;
            Node* cur = headPtr;
            while (cur != nullptr && cur->item < newItem) {   // doğru yeri bul
                prev = cur;
                cur = cur->next;
            }
            nodeToBeAdded->next = cur;     // prev ile cur arasına ekle
            prev->next = nodeToBeAdded;
        }
        itemCount++;
        return true;
    }

    bool remove(const int anEntry) {
        Node* nodeToBeDeleted = getPointerTo(anEntry);
        bool canRemoveItem = (nodeToBeDeleted != nullptr);
        if (canRemoveItem) {
            if (nodeToBeDeleted == headPtr) {
                headPtr = headPtr->next;               // baştaki düğüm
            } else {
                Node* prev = headPtr;                  // öncekini bul
                while (prev->next != nodeToBeDeleted)
                    prev = prev->next;
                prev->next = nodeToBeDeleted->next;    // aradan çıkar
            }
            nodeToBeDeleted->next = nullptr;           // güvenli silme
            delete nodeToBeDeleted;
            itemCount--;
        }
        return canRemoveItem;
    }

    bool contains(const int anEntry) const {
        return getPointerTo(anEntry) != nullptr;
    }
};

int main() {
    LinkedBag bag;
    bag.add(5); bag.add(1); bag.add(3);
    cout << bag.toString() << endl;
    bag.remove(3);
    cout << bag.toString() << endl;
    return 0;
}
