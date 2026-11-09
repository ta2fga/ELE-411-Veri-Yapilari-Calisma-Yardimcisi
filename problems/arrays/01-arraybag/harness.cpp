TEST("Boş torba", "yeni ArrayBag") {
    ArrayBag b;
    CHECK("contains(\"Pen\")", b.contains("Pen"), false);
    CHECK("getFrequencyOf(\"Pen\")", b.getFrequencyOf("Pen"), 0);
    CHECK("remove(\"Pen\")", b.remove("Pen"), false);
}
TEST("Ekleme", "add Pen, Notebook") {
    ArrayBag b;
    CHECK("add(\"Pen\")", b.add("Pen"), true);
    CHECK("add(\"Notebook\")", b.add("Notebook"), true);
    CHECK("getCurrentSize()", b.getCurrentSize(), 2);
    CHECK("contains(\"Notebook\")", b.contains("Notebook"), true);
}
TEST("Dolu torba (kapasite 6)", "7 kez add") {
    ArrayBag b;
    for (int i = 0; i < 6; i++) CHECK("add #" + std::to_string(i + 1), b.add("x" + std::to_string(i)), true);
    CHECK("7. add (dolu)", b.add("fazla"), false);
    CHECK("getCurrentSize()", b.getCurrentSize(), 6);
}
TEST("Frekans", "Pen, Book, Pen, Pen, Ink") {
    ArrayBag b; b.add("Pen"); b.add("Book"); b.add("Pen"); b.add("Pen"); b.add("Ink");
    CHECK("getFrequencyOf(\"Pen\")", b.getFrequencyOf("Pen"), 3);
    CHECK("getFrequencyOf(\"Ink\")", b.getFrequencyOf("Ink"), 1);
    CHECK("getFrequencyOf(\"Cup\")", b.getFrequencyOf("Cup"), 0);
}
TEST("Silme", "Pen, Notebook, Pen, Book; remove Pen, remove Eraser") {
    ArrayBag b; b.add("Pen"); b.add("Notebook"); b.add("Pen"); b.add("Book");
    CHECK("remove(\"Pen\")", b.remove("Pen"), true);
    CHECK("getCurrentSize()", b.getCurrentSize(), 3);
    CHECK("getFrequencyOf(\"Pen\")", b.getFrequencyOf("Pen"), 1);
    CHECK("contains(\"Book\")", b.contains("Book"), true);
    CHECK("contains(\"Notebook\")", b.contains("Notebook"), true);
    CHECK("remove(\"Eraser\")", b.remove("Eraser"), false);
    CHECK("getCurrentSize()", b.getCurrentSize(), 3);
}
TEST("Sil ve tekrar ekle", "dolu torbadan sil, sonra ekle") {
    ArrayBag b; for (int i = 0; i < 6; i++) b.add("x" + std::to_string(i));
    CHECK("remove(\"x0\")", b.remove("x0"), true);
    CHECK("add(\"y\")", b.add("y"), true);
    CHECK("contains(\"x5\")", b.contains("x5"), true);
    CHECK("contains(\"x0\")", b.contains("x0"), false);
}
