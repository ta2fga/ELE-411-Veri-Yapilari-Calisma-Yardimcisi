TEST("Sıralı ekleme", "add 5, 1, 3, 9, 4") {
    LinkedBag b; b.add(5); b.add(1); b.add(3); b.add(9); b.add(4);
    CHECK_TEXT("liste", b.toString(), "1 -> 3 -> 4 -> 5 -> 9 -> nullptr");
    CHECK("getCurrentSize()", b.getCurrentSize(), 5);
}
TEST("Baştakine eşit ekleme (ders kodundaki hata)", "add 2, 2, 7, 2") {
    LinkedBag b; b.add(2); b.add(2); b.add(7); b.add(2);
    CHECK_TEXT("liste", b.toString(), "2 -> 2 -> 2 -> 7 -> nullptr");
}
TEST("contains", "add 4, 8; contains 8, 5") {
    LinkedBag b;
    CHECK("boş torbada contains(1)", b.contains(1), false);
    b.add(4); b.add(8);
    CHECK("contains(8)", b.contains(8), true);
    CHECK("contains(5)", b.contains(5), false);
}
TEST("Baştan silme", "1 3 5; remove 1") {
    LinkedBag b; b.add(1); b.add(3); b.add(5);
    CHECK("remove(1)", b.remove(1), true);
    CHECK_TEXT("liste", b.toString(), "3 -> 5 -> nullptr");
}
TEST("Ortadan ve sondan silme", "1 3 5 7; remove 3, remove 7") {
    LinkedBag b; b.add(7); b.add(5); b.add(3); b.add(1);
    CHECK("remove(3)", b.remove(3), true);
    CHECK("remove(7)", b.remove(7), true);
    CHECK_TEXT("liste", b.toString(), "1 -> 5 -> nullptr");
    CHECK("getCurrentSize()", b.getCurrentSize(), 2);
}
TEST("Olmayanı silme", "2 4; remove 3, boş torbada remove") {
    LinkedBag e;
    CHECK("boş torbada remove(1)", e.remove(1), false);
    LinkedBag b; b.add(2); b.add(4);
    CHECK("remove(3)", b.remove(3), false);
    CHECK_TEXT("liste", b.toString(), "2 -> 4 -> nullptr");
}
TEST("Tekrarlı silme", "5 5 5; remove 5 iki kez") {
    LinkedBag b; b.add(5); b.add(5); b.add(5);
    b.remove(5); b.remove(5);
    CHECK("getFrequencyOf(5)", b.getFrequencyOf(5), 1);
    CHECK_TEXT("liste", b.toString(), "5 -> nullptr");
}
