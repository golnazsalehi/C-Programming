void signup1(struct signup** Signup, char* Uname2, char* Pword2, char* Role2) {
    Signup[0]->goods_num = 0;
    Signup[0]->budget = 0;
    strcpy(Signup[0]->username, Uname2);
    strcpy(Signup[0]->password, Pword2);
    strcpy(Signup[0]->role, Role2);
    printf("u have signed up successfully\n");
}