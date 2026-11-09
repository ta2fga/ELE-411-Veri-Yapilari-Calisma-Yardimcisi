// YANLIŞ: dersteki add birebir — baştakine eşit değer eklenince prev == nullptr -> çökme

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
        Node* n = new Node(newItem);
        if (itemCount == 0) headPtr = n;
        else if (headPtr->item > newItem) { n->next = headPtr; headPtr = n; }
        else {
            Node* prev = nullptr; Node* cur = headPtr;
            while (cur != nullptr && cur->item < newItem) { prev = cur; cur = cur->next; }
            n->next = cur; prev->next = n;
        }
        itemCount++; return true;
    }
    bool remove(const int anEntry) {
        Node* d = getPointerTo(anEntry);
        if (!d) return false;
        if (d == headPtr) headPtr = headPtr->next;
        else { Node* p = headPtr; while (p->next != d) p = p->next; p->next = d->next; }
        delete d; itemCount--; return true;
    }
    bool contains(const int anEntry) const { return getPointerTo(anEntry) != nullptr; }
};
