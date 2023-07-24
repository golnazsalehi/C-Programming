void check_pro(struct signup** Signup, int finding, int* i, int* flag1, struct goods** GOODS, int pro_total_num, char* pro) {
    for (*i = 0; *i < pro_total_num; *i += 1) {
        if (strcmp(GOODS[*i]->name, pro) == 0 && strcmp(Signup[finding]->username, GOODS[*i]->seller_name) != 0) {
            printf("~~ -.- This product is already existed by another seller -.- ~~\n");
            *flag1 = 5;
            break;
        }
        else if (strcmp(GOODS[*i]->name, pro) == 0 && strcmp(Signup[finding]->username, GOODS[*i]->seller_name) == 0) {
            *flag1 = 3;
            fseek(stdin, 0, SEEK_END);
            fflush(stdin);
            break;
        }
    }
}