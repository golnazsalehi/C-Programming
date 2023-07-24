void Regis_pro(struct goods** GOODS, int pro_total_num, int goods_count, int goods_price, char* pro, struct signup** Signup, int finding) {
    GOODS[pro_total_num - 1]->number = goods_count;
    GOODS[pro_total_num - 1]->price = goods_price;
    strcpy(GOODS[pro_total_num - 1]->name, pro);
    strcpy(GOODS[pro_total_num - 1]->seller_name, Signup[finding]->username);
    strcpy(Signup[finding]->Goods[Signup[finding]->goods_num - 1]->seller_name, Signup[finding]->username);
    strcpy(Signup[finding]->Goods[Signup[finding]->goods_num - 1]->name, pro);
    Signup[finding]->Goods[Signup[finding]->goods_num - 1]->number = goods_count;
    Signup[finding]->Goods[Signup[finding]->goods_num - 1]->price = goods_price;
    printf("|_$_| <Successfully registered> |_$_|\n");
}