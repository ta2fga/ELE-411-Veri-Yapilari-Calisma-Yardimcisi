// Test kodu: infixToPostfix
static void h_case(const char* infix, const char* expected) {
    CHECK(std::string("infixToPostfix(\"") + infix + "\")", infixToPostfix(infix), std::string(expected));
}
TEST("Tek operand", "infix = \"a\"") { h_case("a", "a"); }
TEST("Basit", "infix = \"a+b\"") { h_case("a+b", "ab+"); }
TEST("Öncelik", "infix = \"a+b*c\", \"a*b+c\"") { h_case("a+b*c", "abc*+"); h_case("a*b+c", "ab*c+"); }
TEST("Parantez", "infix = \"(a+b)*c\"") { h_case("(a+b)*c", "ab+c*"); }
TEST("Soldan birleşme", "infix = \"a-b-c\", \"a/b*c\"") { h_case("a-b-c", "ab-c-"); h_case("a/b*c", "ab/c*"); }
TEST("Ders örneği (Figure 6-5)", "infix = \"a - (b + c * d) / e\"") { h_case("a - (b + c * d) / e", "abcd*+e/-"); }
TEST("İç içe parantez", "infix = \"((a+b)*(c-d))/e\"") { h_case("((a+b)*(c-d))/e", "ab+cd-*e/"); }
TEST("Rakam operandlar", "infix = \"2*(3+4)\"") { h_case("2*(3+4)", "234+*"); }
