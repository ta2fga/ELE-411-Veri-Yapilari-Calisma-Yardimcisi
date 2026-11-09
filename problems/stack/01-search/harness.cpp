// Test kodu: searchStack
static void h_case(std::initializer_list<int> items, int target, bool expected) {
    Stack s = makeStack(items);
    std::string before = stackToString(s);
    bool r = searchStack(s, target);
    CHECK("dönüş değeri", r, expected);
    CHECK_TEXT("çağrıdan sonra stack (alt→üst)", stackToString(s), before);
}
TEST("Boş stack", "myStack = [] (alt→üst), targetItem = 5") { h_case({}, 5, false); }
TEST("Tek eleman, var", "myStack = [5], targetItem = 5") { h_case({5}, 5, true); }
TEST("Tek eleman, yok", "myStack = [5], targetItem = 3") { h_case({5}, 3, false); }
TEST("Hedef en üstte", "myStack = [3, 8, 2, 6], targetItem = 6") { h_case({3, 8, 2, 6}, 6, true); }
TEST("Hedef en altta", "myStack = [3, 8, 2, 6], targetItem = 3") { h_case({3, 8, 2, 6}, 3, true); }
TEST("Hedef yok (sıra korunmalı)", "myStack = [3, 8, 2, 6], targetItem = 10") { h_case({3, 8, 2, 6}, 10, false); }
TEST("Tekrarlı elemanlar", "myStack = [1, 2, 1, 2, 1], targetItem = 2") { h_case({1, 2, 1, 2, 1}, 2, true); }
TEST("Negatif sayılar", "myStack = [-1, 0, -5, 4], targetItem = -5") { h_case({-1, 0, -5, 4}, -5, true); }
