// Lecture 2 — ArrayBag (string)
// TODO: add, remove, contains, getFrequencyOf metotlarını yazın. Diğerleri hazır.

class ArrayBag {
private:
    static const int DEFAULT_CAPACITY = 6;   // dolu torbayı test etmek için küçük
    string items[DEFAULT_CAPACITY];          // torbadaki elemanlar
    int itemCount;                           // şu anki eleman sayısı
    int maxItems;                            // kapasite

    // target'ın indeksini, yoksa -1 döndürür
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
        // TODO
        return false;
    }

    bool remove(const string& anEntry) {
        // TODO
        return false;
    }

    bool contains(const string& anEntry) const {
        // TODO
        return false;
    }

    int getFrequencyOf(const string& anEntry) const {
        // TODO
        return 0;
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
