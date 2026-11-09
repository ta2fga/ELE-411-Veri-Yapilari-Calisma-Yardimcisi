// =====================================================================
//  ele411.h  —  ELE411 çalışma sitesi ortak başlık dosyası
//
//  Bu dosya her derlemede OTOMATİK olarak include edilir
//  (g++ -include ele411.h). Kodunuzda tekrar tanımlamayın:
//
//    Stack      : isEmpty(), push(int), pop() -> bool, peek() -> int
//    Queue      : isEmpty(), enqueue(int), dequeue() -> bool, peekFront() -> int
//    Node       : int tutan bağlı liste düğümü   (item, next + get/set)
//    StringNode : string tutan bağlı liste düğümü (Midterm2019 Q2)
//    TreeNode   : int item; TreeNode* left; TreeNode* right;  (BST)
//
//  Arayüzler sınavlardaki UML ile birebir aynıdır. Özellikle:
//    * pop() / dequeue() DEĞER DÖNDÜRMEZ, sadece başarılı olup olmadığını
//      (bool) döndürür. Değeri almak için önce peek()/peekFront() çağırın.
//    * Boş yapı üzerinde peek()/peekFront() çağırmak programı bir hata
//      mesajıyla durdurur (sınavda bu tanımsız davranıştır!).
//
//  Yardımcılar (kendi denemeleriniz ve testler için):
//    makeStack({1,2,3})    -> alttan üste 1,2,3 (3 en üstte)
//    makeQueue({1,2,3})    -> önden arkaya 1,2,3 (1 en önde)
//    makeList({1,2,3})     -> 1 -> 2 -> 3 -> nullptr, head pointer döner
//    makeStringList({"a","b"})
//    makeBST({5,3,8})      -> sırayla BST'ye ekler, kök döner
//    printStack(s), printQueue(q), printList(head)
//    stackToString(s), queueToString(q), listToString(head)
//    deleteList(head), deleteTree(root)
// =====================================================================
#ifndef ELE411_H
#define ELE411_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <initializer_list>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <io.h>
#define ELE411_DUP _dup
#define ELE411_DUP2 _dup2
#define ELE411_CLOSE _close
#define ELE411_FILENO _fileno
#else
#include <unistd.h>
#define ELE411_DUP dup
#define ELE411_DUP2 dup2
#define ELE411_CLOSE close
#define ELE411_FILENO fileno
#endif

using namespace std;

namespace ele411 {
inline void fatal(const char* msg) {
    std::cout.flush();
    std::fflush(stdout);
    std::fprintf(stderr, "\n[ELE411 HATA] %s\n", msg);
    std::fflush(stderr);
    std::exit(70);
}
}  // namespace ele411

// ---------------------------------------------------------------------
//  Stack (int) — link-based gerçekleme. UML:
//    + isEmpty(): boolean
//    + push(item: int): boolean
//    + pop(): boolean        (değer döndürmez!)
//    + peek(): int
// ---------------------------------------------------------------------
class Stack {
private:
    struct SNode { int item; SNode* next; };
    SNode* topPtr;

    void copyFrom(const Stack& other) {
        topPtr = nullptr;
        SNode* tail = nullptr;
        for (SNode* cur = other.topPtr; cur != nullptr; cur = cur->next) {
            SNode* n = new SNode{cur->item, nullptr};
            if (tail == nullptr) topPtr = n; else tail->next = n;
            tail = n;
        }
    }
    void clearAll() { while (pop()) {} }

public:
    Stack() : topPtr(nullptr) {}
    Stack(const Stack& other) { copyFrom(other); }
    Stack& operator=(const Stack& other) {
        if (this != &other) { clearAll(); copyFrom(other); }
        return *this;
    }
    ~Stack() { clearAll(); }

    bool isEmpty() const { return topPtr == nullptr; }

    bool push(int newItem) {
        topPtr = new SNode{newItem, topPtr};
        return true;
    }

    bool pop() {
        if (isEmpty()) return false;
        SNode* old = topPtr;
        topPtr = topPtr->next;
        delete old;
        return true;
    }

    int peek() const {
        if (isEmpty()) ele411::fatal("Bos Stack uzerinde peek() cagrildi. Once isEmpty() ile kontrol edin.");
        return topPtr->item;
    }
};

// ---------------------------------------------------------------------
//  Queue (int) — link-based gerçekleme. UML:
//    + isEmpty(): boolean
//    + enqueue(item: int): boolean
//    + dequeue(): boolean    (değer döndürmez!)
//    + peekFront(): int
// ---------------------------------------------------------------------
class Queue {
private:
    struct QNode { int item; QNode* next; };
    QNode* frontPtr;
    QNode* backPtr;

    void copyFrom(const Queue& other) {
        frontPtr = backPtr = nullptr;
        for (QNode* cur = other.frontPtr; cur != nullptr; cur = cur->next) enqueue(cur->item);
    }
    void clearAll() { while (dequeue()) {} }

public:
    Queue() : frontPtr(nullptr), backPtr(nullptr) {}
    Queue(const Queue& other) { copyFrom(other); }
    Queue& operator=(const Queue& other) {
        if (this != &other) { clearAll(); copyFrom(other); }
        return *this;
    }
    ~Queue() { clearAll(); }

    bool isEmpty() const { return frontPtr == nullptr; }

    bool enqueue(int newItem) {
        QNode* n = new QNode{newItem, nullptr};
        if (isEmpty()) frontPtr = n; else backPtr->next = n;
        backPtr = n;
        return true;
    }

    bool dequeue() {
        if (isEmpty()) return false;
        QNode* old = frontPtr;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) backPtr = nullptr;
        delete old;
        return true;
    }

    int peekFront() const {
        if (isEmpty()) ele411::fatal("Bos Queue uzerinde peekFront() cagrildi. Once isEmpty() ile kontrol edin.");
        return frontPtr->item;
    }
};

// ---------------------------------------------------------------------
//  Bağlı liste düğümü. Hem public alanlar (Lecture 4: item, next) hem de
//  get/set metotları (Midterm UML) kullanılabilir.
//    Node       -> int
//    StringNode -> string
// ---------------------------------------------------------------------
template <class T>
class BasicNode {
public:
    T item;
    BasicNode* next;

    BasicNode() : item(), next(nullptr) {}
    BasicNode(const T& anItem) : item(anItem), next(nullptr) {}
    BasicNode(const T& anItem, BasicNode* nextNodePtr) : item(anItem), next(nextNodePtr) {}

    T getItem() const { return item; }
    BasicNode* getNext() const { return next; }
    void setItem(const T& anItem) { item = anItem; }
    void setNext(BasicNode* nextNodePtr) { next = nextNodePtr; }
};
typedef BasicNode<int> Node;
typedef BasicNode<std::string> StringNode;

// ---------------------------------------------------------------------
//  İkili ağaç düğümü (midterm.pdf BST sorusu): root->item, root->left, root->right
// ---------------------------------------------------------------------
class TreeNode {
public:
    int item;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int anItem) : item(anItem), left(nullptr), right(nullptr) {}
};

// =====================================================================
//  Yardımcı fonksiyonlar
// =====================================================================
inline Stack makeStack(std::initializer_list<int> bottomToTop) {
    Stack s;
    for (int x : bottomToTop) s.push(x);
    return s;
}
inline Queue makeQueue(std::initializer_list<int> frontToBack) {
    Queue q;
    for (int x : frontToBack) q.enqueue(x);
    return q;
}
inline Node* makeList(std::initializer_list<int> items) {
    Node* head = nullptr; Node* tail = nullptr;
    for (int x : items) {
        Node* n = new Node(x);
        if (head == nullptr) head = n; else tail->next = n;
        tail = n;
    }
    return head;
}
inline StringNode* makeStringList(std::initializer_list<std::string> items) {
    StringNode* head = nullptr; StringNode* tail = nullptr;
    for (const std::string& x : items) {
        StringNode* n = new StringNode(x);
        if (head == nullptr) head = n; else tail->next = n;
        tail = n;
    }
    return head;
}
template <class T>
inline void deleteList(BasicNode<T>* head) {
    while (head != nullptr) { BasicNode<T>* nx = head->next; delete head; head = nx; }
}
inline TreeNode* bstInsert(TreeNode* root, int x) {
    if (root == nullptr) return new TreeNode(x);
    if (x < root->item) root->left = bstInsert(root->left, x);
    else root->right = bstInsert(root->right, x);
    return root;
}
inline TreeNode* makeBST(std::initializer_list<int> insertOrder) {
    TreeNode* root = nullptr;
    for (int x : insertOrder) root = bstInsert(root, x);
    return root;
}
inline void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left); deleteTree(root->right); delete root;
}

// Stack içeriği: alttan üste, ör. "[1, 2, 3] (üst: 3)". Orijinal stack değişmez.
inline std::string stackToString(const Stack& s) {
    Stack copy = s;
    std::vector<int> v;
    while (!copy.isEmpty()) { v.push_back(copy.peek()); copy.pop(); }
    std::ostringstream os;
    os << "[";
    for (int i = (int)v.size() - 1; i >= 0; --i) { os << v[i]; if (i > 0) os << ", "; }
    os << "]";
    return os.str();
}
// Queue içeriği: önden arkaya, ör. "[1, 2, 3]" (1 en önde). Orijinal queue değişmez.
inline std::string queueToString(const Queue& q) {
    Queue copy = q;
    std::ostringstream os;
    os << "[";
    bool first = true;
    while (!copy.isEmpty()) {
        if (!first) os << ", ";
        os << copy.peekFront(); copy.dequeue(); first = false;
    }
    os << "]";
    return os.str();
}
template <class T>
inline std::string listToString(const BasicNode<T>* head) {
    std::ostringstream os;
    int guard = 0;
    for (const BasicNode<T>* cur = head; cur != nullptr; cur = cur->next) {
        os << cur->item << " -> ";
        if (++guard > 100000) { os << "... (dongu?) "; break; }
    }
    os << "nullptr";
    return os.str();
}
// Dizi içeriği, ör. "[1, 2, 3]"
inline std::string arrToString(const int* a, int n) {
    std::ostringstream os;
    os << "[";
    for (int i = 0; i < n; ++i) { os << a[i]; if (i + 1 < n) os << ", "; }
    os << "]";
    return os.str();
}
inline std::string vecToString(const std::vector<int>& v) { return arrToString(v.data(), (int)v.size()); }
inline void printArray(const int* a, int n) { std::cout << arrToString(a, n) << std::endl; }

inline void printStack(const Stack& s) { std::cout << "Stack (alt->ust): " << stackToString(s) << std::endl; }
inline void printQueue(const Queue& q) { std::cout << "Queue (on->arka): " << queueToString(q) << std::endl; }
template <class T>
inline void printList(const BasicNode<T>* head) { std::cout << listToString(head) << std::endl; }

// =====================================================================
//  Test altyapısı (harness.cpp dosyaları kullanır)
// =====================================================================
namespace ele411 {

struct TestInfo { std::string name; std::string input; void (*fn)(); };
inline std::vector<TestInfo>& registry() { static std::vector<TestInfo> r; return r; }
inline int& currentTest() { static int t = -1; return t; }
struct Registrar {
    Registrar(const char* name, const char* input, void (*fn)()) { registry().push_back({name, input, fn}); }
};

inline std::string esc(const std::string& s) {
    std::string o;
    for (char c : s) {
        if (c == '\\') o += "\\\\";
        else if (c == '\n') o += "\\n";
        else if (c == '\r') {}
        else if (c == '\x1f') o += ' ';
        else o += c;
    }
    return o;
}
inline void emit(const std::vector<std::string>& fields) {
    std::cout.flush();
    std::fflush(stdout);
    std::string line = "\n@@E411";
    for (const std::string& f : fields) { line += '\x1f'; line += esc(f); }
    line += "\n";
    std::fputs(line.c_str(), stdout);
    std::fflush(stdout);
}

inline std::string str(bool b) { return b ? "true" : "false"; }
inline std::string str(int x) { return std::to_string(x); }
inline std::string str(long x) { return std::to_string(x); }
inline std::string str(long long x) { return std::to_string(x); }
inline std::string str(unsigned x) { return std::to_string(x); }
inline std::string str(double x) { std::ostringstream o; o << x; return o.str(); }
inline std::string str(char c) { return std::string("'") + c + "'"; }
inline std::string str(const std::string& s) { return "\"" + s + "\""; }
inline std::string str(const char* s) { return str(std::string(s)); }

// Gerçek ve beklenen değeri karşılaştırır, sonucu sunucuya bildirir.
template <class A, class B>
inline bool check(const std::string& label, const A& actual, const B& expected) {
    std::string a = str(actual), e = str(expected);
    bool ok = (a == e);
    emit({"CHECK", label, e, a, ok ? "1" : "0"});
    return ok;
}
// Ham metin karşılaştırması (tırnak eklemeden), ör. stack içerikleri.
inline bool checkText(const std::string& label, const std::string& actual, const std::string& expected) {
    bool ok = (actual == expected);
    emit({"CHECK", label, expected, actual, ok ? "1" : "0"});
    return ok;
}
// Testte gösterilecek ek bilgi notu.
inline void note(const std::string& text) { emit({"NOTE", text}); }

// fn() çalışırken ekrana (cout veya printf) yazılanları yakalar ve döndürür.
inline std::string capture(const std::function<void()>& fn) {
    std::cout.flush();
    std::fflush(stdout);
    char fname[64];
    std::snprintf(fname, sizeof fname, "ele411_cap_%d.tmp", currentTest());
    FILE* f = std::fopen(fname, "w+b");
    if (f == nullptr) { fn(); return "(cikti yakalanamadi)"; }
    int saved = ELE411_DUP(1);
    ELE411_DUP2(ELE411_FILENO(f), 1);
    fn();
    std::cout.flush();
    std::fflush(stdout);
    ELE411_DUP2(saved, 1);
    ELE411_CLOSE(saved);
    std::fseek(f, 0, SEEK_SET);
    std::string out;
    char buf[4096];
    size_t n;
    while ((n = std::fread(buf, 1, sizeof buf, f)) > 0 && out.size() < 65536) out.append(buf, n);
    std::fclose(f);
    std::remove(fname);
    return out;
}
// Satır sonu boşluklarını ve sondaki boş satırları temizler (çıktı karşılaştırma için).
inline std::string trimOutput(const std::string& s) {
    std::istringstream in(s);
    std::string line, out;
    std::vector<std::string> lines;
    while (std::getline(in, line)) {
        while (!line.empty() && (line.back() == ' ' || line.back() == '\t' || line.back() == '\r')) line.pop_back();
        lines.push_back(line);
    }
    while (!lines.empty() && lines.back().empty()) lines.pop_back();
    size_t start = 0;
    while (start < lines.size() && lines[start].empty()) start++;
    for (size_t i = start; i < lines.size(); ++i) { out += lines[i]; if (i + 1 < lines.size()) out += "\n"; }
    return out;
}

inline int runTests(int argc, char** argv) {
    std::vector<TestInfo>& r = registry();
    if (argc >= 2 && std::strcmp(argv[1], "--list") == 0) {
        emit({"COUNT", std::to_string(r.size())});
        for (size_t i = 0; i < r.size(); ++i) emit({"TEST", std::to_string(i), r[i].name, r[i].input});
        return 0;
    }
    if (argc >= 3 && std::strcmp(argv[1], "--run") == 0) {
        int i = std::atoi(argv[2]);
        if (i < 0 || i >= (int)r.size()) return 2;
        currentTest() = i;
        emit({"BEGIN", std::to_string(i)});
        r[i].fn();
        emit({"END", std::to_string(i)});
        return 0;
    }
    std::fprintf(stderr, "Kullanim: --list | --run <i>\n");
    return 2;
}

}  // namespace ele411

#define ELE411_CAT2(a, b) a##b
#define ELE411_CAT(a, b) ELE411_CAT2(a, b)
// TEST("ad", "girdi açıklaması") { ... CHECK(...); }
#define TEST(name, input)                                                         \
    static void ELE411_CAT(ele411_test_, __LINE__)();                             \
    static ele411::Registrar ELE411_CAT(ele411_reg_, __LINE__)(name, input,       \
                                                    ELE411_CAT(ele411_test_, __LINE__)); \
    static void ELE411_CAT(ele411_test_, __LINE__)()
#define CHECK(label, actual, expected) ele411::check(label, actual, expected)
#define CHECK_TEXT(label, actual, expected) ele411::checkText(label, actual, expected)

#endif  // ELE411_H
