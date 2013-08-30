int main(void) {
    char s[] = "12345";
    int number;
    number = atoi(s);
    return 0;
}

int atoi(char *a) {
    char i;
    char c;
    int n;
    n = 0;
    c = *a;
    for(i = 1; ((c>='0') && (c<='9')); i++) {
        n = 10*n + (c - '0');
        c = *(a+i);
    }
    return n;
}
