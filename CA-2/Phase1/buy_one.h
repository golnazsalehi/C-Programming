int buy_one(int members, struct signup** Signup, int* find, char* seller_username) {
    int i = 0;
    for (i = 0; i < members; i++) {
        if (strcmp(seller_username, Signup[i]->username) == 0 && strcmp(Signup[i]->role, "seller") == 0) {
            *find = 1;
            break;
        }
    }
    return i;
}