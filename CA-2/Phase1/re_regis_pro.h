void re_regis_pro(struct signup** Signup, int* finding, char* pro, int goods_count, struct goods** GOODS, int* i) {
    int k = 0;
    for (k = 0; k < Signup[*finding]->goods_num; k++) {
        if (strcmp(Signup[*finding]->Goods[k]->name, pro) == 0) {
            Signup[*finding]->Goods[k]->number += goods_count;
            GOODS[*i]->number += goods_count;
            printf("|_$_| <Successfully registered again> |_$_|\n");
            break;
        }
    }
}