void deposit(struct signup** Signup, int finding) {
    int pool = 0;
    char* amount = (char*)malloc(sizeof(char));
    amount = get_input(amount);
    for (int h = 0; h < strlen(amount);h++) {
        if (!isdigit(amount[h])) {
            pool = 1;
            break;
        }
    }
    if (pool == 1)
        printf("invalid amount of money\n");
    else {
        int money = atoi(amount);
        Signup[finding]->budget += money;
        printf("$<->$ DEPOSIT SUCCESSFULL $<->$\n");
    }
}