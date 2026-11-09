// YANLIŞ: sadece sayaç tutuyor; türü ve sırayı kontrol etmiyor
bool isBalanced(string expr) {
    int open = 0;
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') open++;
        else if (ch == ')' || ch == ']' || ch == '}') open--;
    }
    return open == 0;
}
