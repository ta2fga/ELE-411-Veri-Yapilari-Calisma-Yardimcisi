static void h_ref(int n, char s, char d, char a, std::string& out) {
    if (n == 1) { out += std::string("Move the top disk from ") + s + " to " + d + "\n"; return; }
    h_ref(n - 1, s, a, d, out);
    out += std::string("Move the top disk from ") + s + " to " + d + "\n";
    h_ref(n - 1, a, d, s, out);
}
static void h_case(int n, char s, char d, char a) {
    std::string exp; h_ref(n, s, d, a, exp);
    std::string got = ele411::capture([&] { hanoi(n, s, d, a); });
    CHECK_TEXT("hamleler", ele411::trimOutput(got), ele411::trimOutput(exp));
}
TEST("n = 1", "hanoi(1, 'A', 'C', 'B')") { h_case(1, 'A', 'C', 'B'); }
TEST("n = 2", "hanoi(2, 'A', 'C', 'B')") { h_case(2, 'A', 'C', 'B'); }
TEST("n = 3 (7 hamle)", "hanoi(3, 'A', 'C', 'B')") { h_case(3, 'A', 'C', 'B'); }
TEST("Farklı çubuk adları", "hanoi(3, 'X', 'Y', 'Z')") { h_case(3, 'X', 'Y', 'Z'); }
TEST("n = 5 (31 hamle)", "hanoi(5, 'A', 'C', 'B')") { h_case(5, 'A', 'C', 'B'); }
