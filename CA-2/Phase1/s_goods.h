void s_goods(struct goods** GOODS, int pro_total_num) {
    if (pro_total_num != 0) {
        printf("**************************************************************\n");
        for (int i = 0; i < pro_total_num; i++) {
            printf("name:%s\t   price:%d\t    count:%d\t   seller_name:%s\n", GOODS[i]->name, GOODS[i]->price, GOODS[i]->number, GOODS[i]->seller_name);
        }
        printf("**************************************************************\n");
    }
    else {
        printf("/ / / /The inventory is empty/ / / / \n");
    }
}