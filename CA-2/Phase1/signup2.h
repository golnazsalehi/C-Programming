void signup2(struct signup** Signup, int members, char* Uname2, char* Pword2, char* Role2) {
    Signup[members - 1]->goods_num = 0;
    Signup[members - 1]->budget = 0;
    strcpy(Signup[members - 1]->username, Uname2);
    strcpy(Signup[members - 1]->password, Pword2);
    strcpy(Signup[members - 1]->role, Role2);
    printf("u have signed up successfully\n");
}