// YANLIŞ: iki kez döküyor -> sıra eski haline dönüyor (ters çevrilmiyor)
void reverseStack(Stack& st) {
    Stack t;
    while (!st.isEmpty()) { t.push(st.peek()); st.pop(); }
    while (!t.isEmpty()) { st.push(t.peek()); t.pop(); }
}
