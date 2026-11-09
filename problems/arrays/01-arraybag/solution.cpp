// Lecture 2 — ArrayBag (referans çözüm, ders koduna göre)
class ArrayBag {
private:
    static const int DEFAULT_CAPACITY = 6;
    string items[DEFAULT_CAPACITY];
    int itemCount;
    int maxItems;

    int getIndexOf(const string& target) const {
        for (int i = 0; i < itemCount; i++)
            if (items[i] == target) return i;
        return -1;
    }

public:
    ArrayBag() : itemCount(0), maxItems(DEFAULT_CAPACITY) {}
    int getCurrentSize() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
    void clear() { itemCount = 0; }
    void displayContent() const {
        for (int i = 0; i < itemCount; i++) cout << items[i] << endl;
    }

    bool add(const string& newEntry) {
        bool hasRoomToAdd = itemCount < maxItems;   // kapasite kontrolü
        if (hasRoomToAdd) {
            items[itemCount] = newEntry;            // ilk boş yere koy
            itemCount++;
        }
        return hasRoomToAdd;
    }

    bool remove(const string& anEntry) {
        int itemLocation = getIndexOf(anEntry);
        bool canRemoveItem = itemLocation > -1;
        if (canRemoveItem) {
            itemCount--;
            items[itemLocation] = items[itemCount];  // boşluğu son elemanla doldur
        }
        return canRemoveItem;
    }

    bool contains(const string& anEntry) const {
        return getIndexOf(anEntry) > -1;
    }

    int getFrequencyOf(const string& anEntry) const {
        int frequency = 0;
        for (int i = 0; i < itemCount; i++)
            if (items[i] == anEntry) frequency++;
        return frequency;
    }
};

int main() {
    ArrayBag mybag;
    mybag.add("Pen");
    mybag.add("Notebook");
    cout << "The bag contains " << mybag.getCurrentSize() << " items" << endl;
    mybag.displayContent();
    return 0;
}
