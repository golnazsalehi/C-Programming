void view(struct signup** Signup, int finding) {
    printf("#################### user info #####################\n");
    printf("username:%s\t", Signup[finding]->username);
    printf("password:%s\t", Signup[finding]->password);
    printf("role:%s\t", Signup[finding]->role);
    printf("budget:%d\n", Signup[finding]->budget);
    printf("#################### goods info ####################\n");
    if (Signup[finding]->goods_num != 0) {
        for (int i = 0; i < Signup[finding]->goods_num; i++) {
            printf("name:%s\t   inventory:%d\t   price:%d\n", Signup[finding]->Goods[i]->name, Signup[finding]->Goods[i]->number, Signup[finding]->Goods[i]->price);
        }
        printf("####################################################\n");
    }
}