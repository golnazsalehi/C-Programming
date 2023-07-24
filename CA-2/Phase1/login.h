void login(int* finding, struct signup** Signup, int members, int* flag1, char* Uname2, char* Pword2, char* Role2) {
    *finding = 0;
    while (!(!strcmp(Signup[*finding]->username, Uname2) && !strcmp(Signup[*finding]->password, Pword2) && !strcmp(Signup[*finding]->role, Role2))) {
        if (*finding < members - 1)
            *finding += 1;
        else {
            *flag1 = 1;
            break;
        }
    }
}