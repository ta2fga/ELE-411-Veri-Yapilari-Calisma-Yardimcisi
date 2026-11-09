// YANLIŞ: remove son elemanı boşluğa taşımıyor -> son eleman kayboluyor, silinen kalıyor
class ArrayBag {
    static const int DEFAULT_CAPACITY = 6;
    string items[DEFAULT_CAPACITY];
    int itemCount = 0, maxItems = DEFAULT_CAPACITY;
    int getIndexOf(const string& t) const { for (int i = 0; i < itemCount; i++) if (items[i] == t) return i; return -1; }
public:
    int getCurrentSize() const { return itemCount; }
    bool add(const string& e) { if (itemCount >= maxItems) return false; items[itemCount++] = e; return true; }
    bool remove(const string& e) { int i = getIndexOf(e); if (i < 0) return false; itemCount--; return true; }
    bool contains(const string& e) const { return getIndexOf(e) > -1; }
    int getFrequencyOf(const string& e) const { int f = 0; for (int i = 0; i < itemCount; i++) if (items[i] == e) f++; return f; }
};
