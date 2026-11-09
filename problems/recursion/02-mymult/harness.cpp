TEST("Ders örneği", "myMult(21, 6)") { CHECK("myMult(21, 6)", myMult(21, 6), 126); }
TEST("a = 1", "myMult(1, 9)") { CHECK("myMult(1, 9)", myMult(1, 9), 9); }
TEST("b = 0", "myMult(4, 0)") { CHECK("myMult(4, 0)", myMult(4, 0), 0); }
TEST("Negatif b", "myMult(3, -5)") { CHECK("myMult(3, -5)", myMult(3, -5), -15); }
TEST("Kare", "myMult(7, 7)") { CHECK("myMult(7, 7)", myMult(7, 7), 49); }
