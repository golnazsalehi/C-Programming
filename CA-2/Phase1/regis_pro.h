void regis_pro(struct signup** Signup, int* finding, struct goods** GOODS, int goods_count, int goods_price, char* pro) {
    GOODS[0]->number = goods_count;
    GOODS[0]->price = goods_price;
    strcpy(GOODS[0]->name, pro);
    strcpy(GOODS[0]->seller_name, Signup[*finding]->username);
    strcpy(Signup[*finding]->Goods[0]->seller_name, Signup[*finding]->username);
    strcpy(Signup[*finding]->Goods[0]->name, pro);
    Signup[*finding]->Goods[0]->number = goods_count;
    Signup[*finding]->Goods[0]->price = goods_price;
    printf("|_$_| <Successfully registered> |_$_|\n");
}