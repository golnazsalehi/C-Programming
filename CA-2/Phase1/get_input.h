char* get_input(char* str) {
    str = NULL;
    char ch;
    int i = 0;
    str = (char*)malloc(sizeof(char));
    *str = '\0';

    while (1)
    {
        ch = getchar();
        if ((ch != '\n') && (ch != ' ')) {
            *(str + i) = ch;
            i++;
            str = (char*)realloc(str, (2 * sizeof(char)) + i);
        }
        else
            break;
    }
    *(str + i) = '\0';
    return str;
}