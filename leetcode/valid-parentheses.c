bool isValid(char* s) {
    int n = strlen(s);
    if (n == 1) {
        return false;
    }

    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else {
            if (top == -1) {
                free(stack);
                return false;
            }

            char topChar = stack[top];

            if ((topChar == '(' && c == ')') ||
                (topChar == '[' && c == ']') ||
                (topChar == '{' && c == '}')) {
                top--; 
            } else {
                free(stack);
                return false;
            }
        }
    }

    bool ans = (top == -1);
    free(stack);
    stack = NULL;
    return ans;
}