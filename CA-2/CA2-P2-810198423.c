#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
struct signup {
    int goods_num;
    char* username;
    char* password;
    struct goods* Goods;
    char* role;
    int budget;
    struct signup* right;
    struct signup* left;
};
struct goods {
    char* seller_name;
    char* name;
    int price;
    int number;
    float rate;
    int sellers_ranking;
    struct goods* right;
    struct goods* left;
};
struct goods* Goods(int* total_good_num);
void file_to_tree(struct signup** head, int* members);
struct signup* member_node_maker(FILE* user);
struct goods* good_node_maker(FILE* user);
char* read_line_from_input_file(FILE* input);
void save_good_data_in_file(struct goods* GOODS, int total_good_num);
void print_good_tree(struct goods* GOOD, FILE* user);
void save_personal_data_in_file(struct signup* head, int members);
void print_users_tree(struct signup* head, FILE* user);
void deleteTree(struct goods* node);
void search_print(struct goods* GOODS) {
    /*this function print those nodes which has the Specific condition */
    if (GOODS == NULL)
        return;
    search_print(GOODS->left);
    if (0 < GOODS->price) {
        if (5 <= GOODS->sellers_ranking) {
            if (2 <= GOODS->rate)
                printf("name:%s\t      price:%d\t       count:%d\t     seller_name:%s\t     rating:%f      buyer_rate:%d\n", GOODS->name, GOODS->price, GOODS->number, GOODS->seller_name, GOODS->rate, GOODS->sellers_ranking);
        }
        else {
            printf("name:%s\t      price:%d\t       count:%d\t     seller_name:%s\t     rating:%f      buyer_rate:%d\n", GOODS->name, GOODS->price, GOODS->number, GOODS->seller_name, GOODS->rate, GOODS->sellers_ranking);
        }
    }
    search_print(GOODS->right);
}
void remove_goods(struct goods* head, char* goods_name, int* num_of_goods, int* flag);
void remove_left(struct goods* head, char* goods_name, int* flag, int* num_of_goods);
void remove_right(struct goods* head, char* goods_name, int* flag, int* num_of_goods);
void rate_account(char* goods_name, char* seller_username, struct goods* head, int* flag, int rating) {
    struct goods* temp_head = head;
    while (1) {
        if (strcmp(temp_head->name, goods_name) == 0) {
            if (strcmp(temp_head->seller_name, seller_username) == 0) {
                if (temp_head->rate == 0) {//check if the buyer has rated b4
                    temp_head->rate = rating;
                    temp_head->sellers_ranking += 1;
                    printf("u have rated successfully\n");
                    return;
                }
                else {
                    *flag = 1;
                    printf("u have rated B4\n");
                    return;
                }
            }
            else {
                *flag = 1;
                printf("this seller doesnt sell this pro\n");
                return;
            }
        }
        else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left == NULL) {//means the good doent exist
            *flag = 1;
            printf("this pro doesnt exist\n");
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left != NULL)
            temp_head = temp_head->left;
        else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right == NULL) {//means the good doent exist
            *flag = 1;
            printf("this pro doesnt exist\n");
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right != NULL)
            temp_head = temp_head->right;
    }
}
void rate_GOODS(char* goods_name, struct goods* head, int rating) {
    struct goods* temp_head = head;
    while (1) {
        if (strcmp(temp_head->name, goods_name) == 0) {
            int total_rate = temp_head->rate * temp_head->sellers_ranking;//sum of the Previous ratings
            temp_head->sellers_ranking += 1;//add the num of buyers who have rated
            total_rate += rating;//add the new rating
            total_rate = total_rate / temp_head->sellers_ranking;//calculate the average
            temp_head->rate = total_rate;//register the new average
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left != NULL)
            temp_head = temp_head->left;
        else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right != NULL)
            temp_head = temp_head->right;
    }
}
void rate_in_seller_account(char* goods_name, char* seller_username, struct signup* head, int rating) {
    struct signup* temp_head = head;
    while (1) {
        if (strcmp(temp_head->username, seller_username) == 0) {//searching
            rate_GOODS(goods_name, head->Goods->left, rating);
            return;
        }
        else if (strcmp(temp_head->username, seller_username) == 1 && temp_head->left != NULL)
            temp_head = temp_head->left;
        else if (strcmp(temp_head->username, seller_username) == -1 && temp_head->right != NULL)
            temp_head = temp_head->right;
    }
}
void rate_goods(struct goods* GOODS_head, struct signup* head, char* goods_name, char* seller_username, int rating, struct signup* finding) {
    /*its the main function for rating*/
    int flag = 0;//this flag show if the selected good exsits or not
    rate_account(goods_name, seller_username, finding->Goods->left, &flag, rating);
    if (flag == 1)
        return;
    rate_in_seller_account(goods_name, seller_username, head, rating);//this goes to the seller account to register the rating there as well
    rate_GOODS(goods_name, GOODS_head->left, rating);//this goes to the main tree of goods to register the rating there as well
    return;
}
void change_price(struct goods* head, char* goods_name, int* flag, int new_price) {
    struct goods* temp_head = head;
    while (1) {
        if (strcmp(temp_head->name, goods_name) == 0) {//searching the tree to find the pro
            temp_head->price = new_price;//chang the price
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left == NULL) {//means the pro doesnt exsit
            *flag = 1;
            printf("this pro doesnt exist\n");
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left != NULL)
            temp_head = temp_head->left;
        else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right == NULL) {//means the pro doesnt exsit
            *flag = 1;
            printf("this pro doesnt exist\n");
            return;
        }
        else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right != NULL)
            temp_head = temp_head->right;
    }
}
void change_goods_price(struct signup* head, struct goods* GOODS_head, char* goods_name, int new_price) {
    int flag = 0;//this shows if the pro exists or not
    change_price(head->Goods->left, goods_name, &flag, new_price);
    if (flag == 1)
        return;
    change_price(GOODS_head->left, goods_name, &flag, new_price);
    printf("|_$_| <Successfully changed> |_$_|\n");
    return;
}

void insert(struct goods* G, char* pro, char* seller, int price, int count) {
    /*this function just make a good_node and register the info*/
    struct goods* curr = G;
    curr->name = (char*)malloc(sizeof(char) * strlen(pro));
    curr->seller_name = (char*)malloc(sizeof(char) * strlen(seller));
    strcpy(curr->name, pro);
    strcpy(curr->seller_name, seller);
    curr->number = count;
    curr->price = price;
    curr->rate = 0;
    curr->sellers_ranking = 0;
    curr->left = NULL;
    curr->right = NULL;
    return;
}
void insert_good_finder(struct goods* good, char* pro, char* seller, int price, int count) {
    /*this function search the main tree of goods to find the proper position*/
    struct goods* curr = good;
    while (curr != NULL) {
        if (strcmp(curr->name, pro) == 1)
            if (curr->left == NULL) {
                curr->left = (struct goods*)malloc(sizeof(struct goods));
                insert(curr->left, pro, seller, price, count);
                return;
            }
            else
                curr = curr->left;
        else if (strcmp(curr->name, pro) == -1)
            if (curr->right == NULL) {
                curr->right = (struct goods*)malloc(sizeof(struct goods));
                insert(curr->right, pro, seller, price, count);
                return;
            }
            else
                curr = curr->right;
    }
}
void insert_finder_in_account(struct signup* finding, char* pro, char* seller, int price, int count) {
    /*this function search the  tree of goods in the account to find the proper position*/
    if (finding->goods_num == 0) {//if its the first pro
        finding->Goods->left = (struct goods*)malloc(sizeof(struct goods));
        finding->Goods->left->name = (char*)malloc(sizeof(char) * strlen(pro));
        finding->Goods->left->seller_name = (char*)malloc(sizeof(char) * strlen(seller));
        strcpy(finding->Goods->left->name, pro);
        strcpy(finding->Goods->left->seller_name, seller);
        finding->Goods->left->number = count;
        finding->Goods->left->price = price;
        finding->Goods->left->rate = 0;
        finding->Goods->left->sellers_ranking = 0;
        finding->Goods->left->left = NULL;
        finding->Goods->left->right = NULL;
        return;
    }
    insert_good_finder(finding->Goods->left, pro, seller, price, count);//if its not the first pro
}
void printTree(struct goods* good_printer) {
    if (good_printer == NULL)
        return;
    printTree(good_printer->left);
    printf("name:%s\t          inventory:%d\t         price:%d\t          rateing:%f\n", good_printer->name, good_printer->number, good_printer->price, good_printer->rate);
    printTree(good_printer->right);
}
void view(struct signup* finding) {
    printf("######################## user info #########################\n");
    printf("username:%s\t", finding->username);
    printf("password:%s\t", finding->password);
    printf("role:%s\t", finding->role);
    printf("budget:%d\n", finding->budget);
    printf("######################## goods info ########################\n");
    if (finding->goods_num != 0) {
        printTree(finding->Goods->left);
        printf("########################################################\n");
    }
}
void user_checker(struct signup* head, char* Uname2, char* Role2, int* flag1) {
    /*this function checks the usernames to figure out if entered username exists or not*/
    struct signup* user_finder = head;
    while (1) {
        if (strcmp(user_finder->username, Uname2) == 0 && strcmp(user_finder->role, Role2) == 0) {
            printf("this username is already taken\n");
            *flag1 = 1;
            break;
        }
        else if (strcmp(user_finder->username, Uname2) == 1 || strcmp(user_finder->username, Uname2) == 0) {
            if (user_finder->left != NULL)
                user_finder = user_finder->left;
            else
                break;
        }
        else if (strcmp(user_finder->username, Uname2) == -1) {
            if (user_finder->right != NULL)
                user_finder = user_finder->right;
            else
                break;
        }
    }
}
void signup2_part1(struct signup* head, char* Uname2, char* Pword2, char* Role2) {
    /*this finction search the tree of users to find the proper place for the new one*/
    struct signup* find_location = head;
    while (1) {
        if (strcmp(find_location->username, Uname2) == 1 || strcmp(find_location->username, Uname2) == 0) {
            if (find_location->left == NULL) {
                find_location->left = (struct signup*)malloc(sizeof(struct signup));
                find_location->left->username = (char*)malloc(sizeof(char) * strlen(Uname2));
                find_location->left->password = (char*)malloc(sizeof(char) * strlen(Pword2));
                find_location->left->role = (char*)malloc(sizeof(char) * strlen(Role2));
                find_location->left->goods_num = 0;
                find_location->left->budget = 0;
                find_location->left->left = NULL;
                find_location->left->right = NULL;
                find_location->left->Goods = (struct goods*)malloc(sizeof(struct goods));
                strcpy(find_location->left->username, Uname2);
                strcpy(find_location->left->password, Pword2);
                strcpy(find_location->left->role, Role2);
                printf("u have signed up successfully\n");
                break;
            }
            else
                find_location = find_location->left;
        }
        else if (strcmp(find_location->username, Uname2) == -1) {
            if (find_location->right == NULL) {
                find_location->right = (struct signup*)malloc(sizeof(struct signup));
                find_location->right->username = (char*)malloc(sizeof(char) * strlen(Uname2));
                find_location->right->password = (char*)malloc(sizeof(char) * strlen(Pword2));
                find_location->right->role = (char*)malloc(sizeof(char) * strlen(Role2));
                find_location->right->goods_num = 0;
                find_location->right->budget = 0;
                find_location->right->left = NULL;
                find_location->right->right = NULL;
                find_location->right->Goods = (struct goods*)malloc(sizeof(struct goods));
                strcpy(find_location->right->username, Uname2);
                strcpy(find_location->right->password, Pword2);
                strcpy(find_location->right->role, Role2);
                printf("u have signed up successfully\n");
                break;
            }
            else
                find_location = find_location->right;
        }
    }
}
void signup1(struct signup* head, char* Uname2, char* Pword2, char* Role2) {
    /*this functiokn is for the first member to register*/
    head->username = (char*)malloc(sizeof(char) * strlen(Uname2));
    head->password = (char*)malloc(sizeof(char) * strlen(Pword2));
    head->role = (char*)malloc(sizeof(char) * strlen(Role2));
    head->goods_num = 0;
    head->budget = 0;
    strcpy(head->username, Uname2);
    strcpy(head->password, Pword2);
    strcpy(head->role, Role2);
    head->left = NULL;
    head->right = NULL;
    head->Goods = (struct goods*)malloc(sizeof(struct goods));
    printf("u have signed up successfully\n");
}
struct signup* login(struct signup* head, int* flag1, char* Uname2, char* Pword2, char* Role2) {
    /*well i this the way this function works is obvious but i must say the flag1 shows if the data is correct or not*/
    struct signup* current = head;
    while (!(!strcmp(current->username, Uname2) && !strcmp(current->password, Pword2) && !strcmp(current->role, Role2))) {
        if (strcmp(current->username, Uname2) == 1 || strcmp(current->username, Uname2) == 0) {
            if (current->left == NULL) {
                *flag1 = 1;
                return NULL;
            }
            current = current->left;
        }
        else if (strcmp(current->username, Uname2) == -1) {
            if (current->right == NULL) {
                *flag1 = 1;
                return NULL;
            }
            current = current->right;
        }
        else if (current->left == NULL && current->right == NULL) {
            *flag1 = 1;
            return NULL;
        }
    }
    return current;
}
void check_pro(struct signup* finding, int* flag1, struct goods* GOODS, char* pro, int goods_count) {
    struct goods* current_good = GOODS;
    while (1) {
        if (strcmp(current_good->name, pro) == 0 && strcmp(finding->username, current_good->seller_name) != 0) {//check if the pro is already existed by another seller
            printf("~~ -.- This product is already existed by another seller -.- ~~\n");
            *flag1 = 5;//this is a flag which works in main function
            return;
        }
        else if (strcmp(current_good->name, pro) == 0 && strcmp(finding->username, current_good->seller_name) == 0) {//check if the pro is already existed before by the seller,itself
            struct goods* find_good = finding->Goods->left;
            while (1) {
                if (strcmp(find_good->name, pro) == 0) {
                    find_good->number += goods_count;
                    current_good->number += goods_count;
                    *flag1 = 3;
                    printf("|_$_| <Successfully registered again> |_$_|\n");
                    return;
                }
                else {
                    if (strcmp(find_good->name, pro) == 1) {
                        if (find_good->left != NULL)
                            find_good = find_good->left;
                        else
                            return;
                    }
                    else if (strcmp(find_good->name, pro) == -1) {
                        if (find_good->right != NULL)
                            find_good = find_good->right;
                        else
                            return;
                    }
                }
            }
            *flag1 = 3;
            fseek(stdin, 0, SEEK_END);
            fflush(stdin);
            return;
        }
        else {
            if (strcmp(current_good->name, pro) == 1) {//search to find the proper position
                if (current_good->left != NULL)
                    current_good = current_good->left;
                else
                    return;
            }
            else if (strcmp(current_good->name, pro) == -1) {
                if (current_good->right != NULL)
                    current_good = current_good->right;
                else
                    return;
            }
        }
    }
}
void regis_pro(struct signup* finding, struct goods* GOODS, int goods_count, int goods_price, char* pro) {//register a new pro
    GOODS->name = (char*)malloc(sizeof(char) * strlen(pro));
    GOODS->seller_name = (char*)malloc(sizeof(char) * strlen(finding->username));
    GOODS->left = NULL;
    GOODS->right = NULL;
    GOODS->rate = 0;
    GOODS->sellers_ranking = 0;
    finding->goods_num = 1;
    finding->Goods->left = (struct goods*)malloc(sizeof(struct goods));
    finding->Goods->left->left = NULL;
    finding->Goods->left->right = NULL;
    finding->Goods->left->name = (char*)malloc(sizeof(char) * strlen(pro));
    finding->Goods->left->seller_name = (char*)malloc(sizeof(char) * strlen(finding->username));
    GOODS->number = goods_count;
    GOODS->price = goods_price;
    strcpy(GOODS->name, pro);
    strcpy(GOODS->seller_name, finding->username);
    strcpy(finding->Goods->left->seller_name, finding->username);
    strcpy(finding->Goods->left->name, pro);
    finding->Goods->left->number = goods_count;
    finding->Goods->left->price = goods_price;
    finding->Goods->left->rate = 0;
    finding->Goods->left->sellers_ranking = 0;
    printf("|_$_| <Successfully registered> |_$_|\n");
}
void s_goods(struct goods* GOODS) {
    if (GOODS == NULL)
        return;
    s_goods(GOODS->left);
    if (5 <= GOODS->sellers_ranking) {
        if (2 <= GOODS->rate)
            printf("name:%s\t         price:%d\t          count:%d\t        seller_name:%s\t        rating:%f       num of buyers who have rated:%d\n", GOODS->name, GOODS->price, GOODS->number, GOODS->seller_name, GOODS->rate, GOODS->sellers_ranking);
    }
    else {
        if (GOODS->sellers_ranking != 0)
            printf("name:%s\t         price:%d\t          count:%d\t        seller_name:%s\t        rating:%f       num of buyers who have rated:%d\n", GOODS->name, GOODS->price, GOODS->number, GOODS->seller_name, GOODS->rate, GOODS->sellers_ranking);
        else {
            printf("name:%s\t         price:%d\t          count:%d\t        seller_name:%s\t", GOODS->name, GOODS->price, GOODS->number, GOODS->seller_name);
            printf(" rating:NaN      num of buyers who have rated:%d\n", GOODS->sellers_ranking);
        }
    }
    s_goods(GOODS->right);
}
char* get_input(char* str) {
    str = NULL;
    char ch;
    int i = 0;
    str = (char*)malloc(sizeof(char));
    *str = '\0';
    while (1)
    {
        ch = getchar();
        if ((ch != '\n') && (ch != ' ')) {
            *(str + i) = ch;
            i++;
            str = (char*)realloc(str, (2 * sizeof(char)) + i);
        }
        else
            break;
    }
    *(str + i) = '\0';
    return str;
}
void deposit(struct signup* finding) {
    int pool = 0;
    char* amount = (char*)malloc(sizeof(char));
    amount = get_input(amount);
    for (int h = 0; h < strlen(amount);h++) {
        if (!isdigit(amount[h])) {
            pool = 1;
            break;
        }
    }
    if (pool == 1)
        printf("invalid amount of money\n");
    else {
        int money = atoi(amount);
        finding->budget += money;
        printf("$<->$ DEPOSIT SUCCESSFULL $<->$\n");
    }
}
struct signup* seller_finder(struct signup* head, int* find, char* seller_username) {//this function search for seller if its exist or not
    struct signup* seller_finder = head;
    while (1) {
        if (strcmp(seller_username, seller_finder->username) == 0 && strcmp(seller_finder->role, "seller") == 0) {

            *find = 1;
            return seller_finder;
        }
        else if (strcmp(seller_username, seller_finder->username) == 1) {
            if (seller_finder->left == NULL)
                return NULL;
            else
                seller_finder = seller_finder->left;
        }
        else if (strcmp(seller_username, seller_finder->username) == -1) {
            if (seller_finder->right == NULL)
                return NULL;
            else
                seller_finder = seller_finder->right;
        }
    }
}
struct goods* pro_finder(struct signup* seller_saver, char* goods_name, int* find) {//this function search in seller_goods_tree to figure out if the selected pro exists 
    if (seller_saver->goods_num == 0)
        return NULL;
    struct goods* pro_saver = seller_saver->Goods->left;
    if (pro_saver == NULL)
        return NULL;
    while (1) {
        if (strcmp(pro_saver->name, goods_name) == 0) {
            if (pro_saver->sellers_ranking < 5) {
                *find = 2;
                return pro_saver;
                break;
            }
            else if (2 <= pro_saver->rate) {
                *find = 2;
                return pro_saver;
                break;
            }
            else {
                *find = 10;
                return NULL;
                break;
            }
        }
        else if (strcmp(pro_saver->name, goods_name) == 1) {
            if (pro_saver->left == NULL)
                return NULL;
            else
                pro_saver = pro_saver->left;
        }
        else if (strcmp(pro_saver->name, goods_name) == -1) {
            if (pro_saver->right == NULL)
                return NULL;
            else
                pro_saver = pro_saver->right;
        }
    }
}
void buied_pro(struct signup* finding, char* goods_name, int gcc, int* flag3) {//this function is fore buied pro to just raise the count not anything else
    if (finding->goods_num == 0)
        return;
    struct goods* pro = finding->Goods->left;
    while (1) {
        if (strcmp(pro->name, goods_name) == 0) {
            *flag3 = 1;
            pro->number += gcc;
            pro->rate = 0;
            break;
        }
        else if (strcmp(pro->name, goods_name) == 1) {
            if (pro->left == NULL)
                return;
            else
                pro = pro->left;
        }
        else if (strcmp(pro->name, goods_name) == -1) {
            if (pro->right == NULL)
                return;
            else
                pro = pro->right;
        }
    }
    return;
}
void pro_finder_in_GOODS(struct goods* GOODS, char* goods_name, int gcc) {//find the pro in the main goods tree and decrease the count of the selected pro
    struct goods* pro = GOODS;
    while (1) {
        if (strcmp(pro->name, goods_name) == 0) {
            pro->number -= gcc;
            break;
        }
        else if (strcmp(pro->name, goods_name) == 1)
            pro = pro->left;
        else if (strcmp(pro->name, goods_name) == -1)
            pro = pro->right;
    }
}
void find_pro_location(struct goods* pro, char* goods_name, char* seller_name, int gcc, int price) {//insert a new pro in tree
    struct goods* temp_good = pro;
    if ((strcmp(temp_good->name, goods_name) == 1 || strcmp(temp_good->name, goods_name) == 0) && temp_good->left == NULL) {
        temp_good->left = (struct goods*)malloc(sizeof(struct goods));
        temp_good->left->name = (char*)malloc(sizeof(char) * strlen(goods_name));
        temp_good->left->seller_name = (char*)malloc(sizeof(char) * strlen(seller_name));
        temp_good->left->left = NULL;
        temp_good->left->right = NULL;
        temp_good->left->number = gcc;
        temp_good->left->price = price;
        strcpy(temp_good->left->name, goods_name);
        strcpy(temp_good->left->seller_name, seller_name);
        temp_good->left->rate = 0;
        temp_good->left->sellers_ranking = 0;
        printf("done\n");
    }
    else if (strcmp(temp_good->name, goods_name) == 1 && temp_good->left != NULL)
        find_pro_location(temp_good->left, goods_name, seller_name, gcc, price);
    else if (strcmp(temp_good->name, goods_name) == -1 && temp_good->right == NULL) {
        temp_good->right = (struct goods*)malloc(sizeof(struct goods));
        temp_good->right->name = (char*)malloc(sizeof(char) * strlen(goods_name));
        temp_good->right->seller_name = (char*)malloc(sizeof(char) * strlen(seller_name));
        temp_good->right->left = NULL;
        temp_good->right->right = NULL;
        temp_good->right->number = gcc;
        temp_good->right->price = price;
        temp_good->right->rate = 0;
        temp_good->right->sellers_ranking = 0;
        strcpy(temp_good->right->name, goods_name);
        strcpy(temp_good->right->seller_name, seller_name);
        printf("done\n");
    }
    else
        find_pro_location(temp_good->right, goods_name, seller_name, gcc, price);

}
void sub_copy(struct goods* copy, struct goods* main) {//this function just copy a node in a tree
    copy->name = (char*)malloc(sizeof(char) * strlen(main->name));
    copy->seller_name = (char*)malloc(sizeof(char) * strlen(main->seller_name));
    strcpy(copy->seller_name, main->seller_name);
    strcpy(copy->name, main->name);
    copy->number = main->number;
    copy->price = main->price;
    copy->rate = main->rate;
    copy->sellers_ranking = main->sellers_ranking;
}
struct goods* copytree(struct goods* root) {//this function copy the main tree of goods in case of filtering them for search
    struct goods* new_root;
    if (root != NULL) {
        new_root = (struct goods*)malloc(sizeof(struct goods));
        sub_copy(new_root, root);
        new_root->left = copytree(root->left);
        new_root->right = copytree(root->right);
    }
    else
        return NULL;
    return new_root;

}
void initialize(struct goods* temp, struct goods* tem, struct goods* pro);
void remove_based_on_max_price(struct goods* copy, int max_price) {//if the price of one good is higher than the max_price,its price changes to -1
    if (copy != NULL) {
        if (copy->price > max_price)
            copy->price = -1;
        remove_based_on_max_price(copy->left, max_price);
        remove_based_on_max_price(copy->right, max_price);
    }
    return;
}

void remove_based_on_min_price(struct goods* copy, int min_price) {//if the price of one good is lower than the min_price,its price changes to -1
    if (copy != NULL) {
        if (copy->price < min_price)
            copy->price = -1;
        remove_based_on_min_price(copy->left, min_price);
        remove_based_on_min_price(copy->right, min_price);
    }
    return;
}

void remove_based_on_name(struct goods* copy, char* name) {//if the name of one of the goods is not matched with the good_name,its price changes to -1
    if (copy != NULL) {
        if (strcmp(copy->name, name) != 0)
            copy->price = -1;
        remove_based_on_name(copy->left, name);
        remove_based_on_name(copy->right, name);
    }
    return;
}
void remove_based_on_seller_username(struct goods* copy, char* seller_username) {//if the seller_username of one of the goods is not matched with the seller_username,its price changes to -1
    if (copy != NULL) {
        if (strcmp(copy->seller_name, seller_username) != 0)
            copy->price = -1;
        remove_based_on_seller_username(copy->left, seller_username);
        remove_based_on_seller_username(copy->right, seller_username);
    }
    return;
}
int main() {
    int members = 0;//in case of knowing the number of members
    int pro_total_num = 0;//in case of knowing the number of all goods
    struct signup* head;//head of the members(linked list)
    head = (struct signup*)malloc(sizeof(struct signup));
    head->right = NULL;
    head->left = NULL;
    struct goods* GOODS_head;
    GOODS_head = (struct goods*)malloc(sizeof(struct goods));
    GOODS_head->right = NULL;
    GOODS_head->left = NULL;
    int Case1 = 0;//login or signup
    int Case2 = 0;//other commands like view,buy...
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    struct signup* finding = NULL;
    char* action2 = NULL;
    char* Uname2 = NULL;
    char* Pword2 = NULL;
    char* Role2 = NULL;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~#WELCOME ^-^ 2 ^-^ UT ^-^ KALA#~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~#IF U STILL DONT HAVE AN ACCOUNT,SIGNUP#~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    file_to_tree(&head, &members);
    GOODS_head = Goods(&pro_total_num);
    while (1) {
        fseek(stdin, 0, SEEK_END);
        fflush(stdin);
        Case1 = 0;
        Case2 = 0;
        flag1 = 0;
        flag2 = 0;
        action2 = NULL;
        Uname2 = NULL;
        Pword2 = NULL;
        Role2 = NULL;
        action2 = (char*)malloc(sizeof(char));
        Uname2 = (char*)malloc(sizeof(char));
        Pword2 = (char*)malloc(sizeof(char));
        Role2 = (char*)malloc(sizeof(char));
        action2 = get_input(action2);
        Uname2 = get_input(Uname2);
        Pword2 = get_input(Pword2);
        Role2 = get_input(Role2);
        if (!strcmp("login", action2)) {
            Case1 = 1;
        }
        else if (!strcmp("signup", action2)) {
            Case1 = 2;
        }
        else {
            printf("invalid input :(\n");
            free(action2); //free all the allocated memory->
            free(Uname2);
            free(Pword2);
            free(Role2);
            continue;
        }
        switch (Case1) {//login
        case 1:
            if (members == 0) {
                printf("No one has registered yet!\n");
                free(action2); //free all the allocated memory->
                free(Uname2);
                free(Pword2);
                free(Role2);
                break;
            }
            finding = NULL;
            finding = login(head, &flag1, Uname2, Pword2, Role2);
            if (flag1 == 1) {
                printf("?-? U may have entered wrong data,please try again ?-?\n");
                free(action2);
                free(Uname2);
                free(Pword2);
                free(Role2);
                break;
            }
            else {
                printf("*-* you've logged in successfully *-*\n");
                free(action2);
                free(Uname2);
                free(Pword2);
                if (strcmp("seller", Role2) == 0) {//seller
                    free(Role2);
                    char* pro;
                    while (1) {
                        save_personal_data_in_file(head, members);
                        save_good_data_in_file(GOODS_head->left, pro_total_num);
                        flag1 = 0;
                        flag2 = 0;
                        action2 = NULL;
                        fseek(stdin, 0, SEEK_END);
                        fflush(stdin);
                        action2 = get_input(action2);
                        if (strcmp(action2, "logout") == 0)
                            Case2 = 1;
                        else if (strcmp(action2, "view") == 0)
                            Case2 = 2;
                        else if (strcmp(action2, "add_goods") == 0)
                            Case2 = 3;
                        else if (strcmp(action2, "show_goods") == 0)
                            Case2 = 4;
                        else if (strcmp(action2, "login") == 0 || strcmp(action2, "signup") == 0)
                            Case2 = 5;
                        else if (strcmp(action2, "remove_goods") == 0)
                            Case2 = 6;
                        else if (strcmp(action2, "change_goods_price") == 0)
                            Case2 = 7;
                        else if (strcmp(action2, "search") == 0)
                            Case2 = 8;
                        else
                            Case2 = 9;
                        switch (Case2) {
                        case 1: {//logout
                            flag2 = 2;
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            save_personal_data_in_file(head, members);
                            save_good_data_in_file(GOODS_head->left, pro_total_num);
                            break; }
                        case 2: {//view
                            view(finding);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 3: {//add_goods
                            int gp = 0;
                            int gc = 0;
                            char* goods_price;
                            char* goods_count;
                            pro = NULL;
                            goods_price = NULL;
                            goods_count = NULL;
                            pro = get_input(pro);
                            goods_price = get_input(goods_price);
                            goods_count = get_input(goods_count);
                            for (int h = 0; h < strlen(goods_price);h++) {
                                if (!isdigit(goods_price[h])) {
                                    gp = 1;
                                    break;
                                }
                            }
                            for (int h = 0; h < strlen(goods_count);h++) {
                                if (!isdigit(goods_count[h])) {
                                    gc = 1;
                                    break;
                                }
                            }
                            if (gp == 0 && gc == 0) {
                                int pri = atoi(goods_price);
                                int co = atoi(goods_count);
                                if (pri > 0 && co > 0) {
                                    if (pro_total_num == 0) {
                                        pro_total_num = 1;
                                        GOODS_head->left = (struct goods*)malloc(sizeof(struct goods));
                                        regis_pro(finding, GOODS_head->left, co, pri, pro);
                                        free(pro);
                                        free(goods_price);
                                        free(goods_count);
                                        free(action2);
                                    }
                                    else {
                                        check_pro(finding, &flag1, GOODS_head->left, pro, co);
                                        if (flag1 == 5) {
                                            free(action2);
                                            free(pro);
                                            free(goods_price);
                                            free(goods_count);
                                            fseek(stdin, 0, SEEK_END);
                                            break;
                                        }
                                        else if (flag1 == 3) {
                                            free(action2);
                                            free(pro);
                                            free(goods_price);
                                            free(goods_count);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        else {
                                            insert_good_finder(GOODS_head->left, pro, finding->username, pri, co);
                                            insert_finder_in_account(finding, pro, finding->username, pri, co);
                                            finding->goods_num++;
                                            pro_total_num++;
                                            printf("|_$_| <Successfully registered> |_$_|\n");
                                            free(action2);
                                            free(pro);
                                            free(goods_price);
                                            free(goods_count);
                                        }
                                        fseek(stdin, 0, SEEK_END);
                                        fflush(stdin);
                                        break;
                                    }
                                }
                                else {
                                    printf("$$$$$=The goods_price or goods_count is invalid=$$$$$\n");
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                            }
                            else {
                                printf("$$$$$=The goods_price or goods_count is invalid=$$$$$\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            break;
                        }
                        case 4: {//show_goods
                            if (pro_total_num == 0) {
                                printf("/ / / /The inventory is empty/ / / / \n");
                                break;
                            }
                            printf("********************************************************************************\n");
                            s_goods(GOODS_head->left);
                            printf("********************************************************************************\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 5: {//login or logout
                            printf("!-! U must logout first!this isn't acceptble !-!\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 6: {//remove goods
                            if (finding->goods_num == 0)
                            {
                                printf("u have nothing to remove\n");
                                break;
                            }
                            char* remove = (char*)malloc(sizeof(char));
                            remove = get_input(remove);
                            int flag = 0;
                            remove_goods(finding->Goods, remove, &finding->goods_num, &flag);
                            if (flag == 1) {
                                free(remove);
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            remove_goods(GOODS_head, remove, &pro_total_num, &flag);
                            printf("successfully removed\n");
                            break; }
                        case 7: {
                            char* change_goods_name = NULL;
                            change_goods_name = get_input(change_goods_name);
                            char* change_new_price = NULL;
                            change_new_price = get_input(change_new_price);
                            int gc = 0;
                            for (int h = 0; h < strlen(change_new_price);h++) {
                                if (!isdigit(change_new_price[h])) {
                                    gc = 1;
                                    break;
                                }
                            }
                            if (gc == 1) {
                                printf("invalid amount of money\n");
                                break;
                            }
                            int new_price = atoi(change_new_price);
                            change_goods_price(finding, GOODS_head, change_goods_name, new_price);
                            break;}
                        case 8: {
                            if (pro_total_num == 0) {
                                printf("there is nothing to search\n");
                                break;
                            }
                            char* number_of_conditions = NULL;
                            number_of_conditions = get_input(number_of_conditions);
                            int r = 0;
                            for (int h = 0; h < strlen(number_of_conditions);h++) {
                                if (!isdigit(number_of_conditions[h])) {
                                    r = 1;
                                    break;
                                }
                            }
                            if (r == 1) {
                                printf("invalid number of conditions\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            int num_of_con = atoi(number_of_conditions);
                            if (1 <= num_of_con && num_of_con <= 4) {
                                struct goods* total_condition = (struct goods*)malloc(sizeof(struct goods));
                                total_condition->right = NULL;
                                total_condition->left = copytree(GOODS_head->left); //copy the tree of goods in case of filtering
                                int Case3 = 0;
                                int invalid_flag = 0;
                                for (int i = 0;i < num_of_con;i++) {
                                    char* command = NULL;
                                    command = get_input(command);
                                    char* attribute_value = NULL;
                                    if (strcmp(command, "max_price") == 0)
                                        Case3 = 1;
                                    else if (strcmp(command, "min_price") == 0)
                                        Case3 = 2;
                                    else if (strcmp(command, "name") == 0)
                                        Case3 = 3;
                                    else if (strcmp(command, "seller_username") == 0)
                                        Case3 = 4;
                                    else
                                        Case3 = 5;
                                    switch (Case3) {
                                    case 1: {
                                        attribute_value = get_input(attribute_value);
                                        int s = 0;
                                        for (int h = 0; h < strlen(attribute_value);h++) {
                                            if (!isdigit(attribute_value[h])) {
                                                s = 1;
                                                break;
                                            }
                                        }
                                        if (s == 1) {
                                            printf("invalid attribute value\n");
                                            invalid_flag = 1;
                                            free(action2);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        int max_price = atoi(attribute_value);
                                        remove_based_on_max_price(total_condition->left, max_price);
                                        break;}
                                    case 2: {
                                        attribute_value = get_input(attribute_value);
                                        int s = 0;
                                        for (int h = 0; h < strlen(attribute_value);h++) {
                                            if (!isdigit(attribute_value[h])) {
                                                s = 1;
                                                break;
                                            }
                                        }
                                        if (s == 1) {
                                            printf("invalid attribute value\n");
                                            invalid_flag = 1;
                                            free(action2);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        int min_price = atoi(attribute_value);
                                        remove_based_on_min_price(total_condition->left, min_price);
                                        break;}
                                    case 3: {
                                        attribute_value = get_input(attribute_value);//as name of the pro
                                        remove_based_on_name(total_condition->left, attribute_value);
                                        break;}
                                    case 4: {
                                        attribute_value = get_input(attribute_value);//as name of the seller
                                        remove_based_on_seller_username(total_condition->left, attribute_value);
                                        break;}
                                    case 5: {
                                        printf("invalid goods attribute\n");
                                        invalid_flag = 1;
                                        break;}
                                    }
                                    if (invalid_flag == 1)
                                        break;
                                }
                                if (invalid_flag == 1) {
                                    free(total_condition);
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                                else {
                                    printf("###################################################################\n");
                                    search_print(total_condition->left);
                                    printf("###################################################################\n");
                                    free(total_condition);
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                            }
                            else {
                                printf("it must be on scale of one to four\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            break;}
                        case 9: {//else
                            printf("invalid command,try again\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break;
                        }
                        }
                        if (flag2 == 2) {
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            printf("logout successfull :)\n");
                            break;
                        }
                    }
                }
                else {//buyer
                    free(Role2);
                    while (1) {
                        save_personal_data_in_file(head, members);
                        save_good_data_in_file(GOODS_head->left, pro_total_num);
                        flag2 = 0;
                        flag1 = 0;
                        flag3 = 0;
                        action2 = NULL;
                        fseek(stdin, 0, SEEK_END);
                        fflush(stdin);
                        action2 = get_input(action2);
                        if (strcmp(action2, "logout") == 0)
                            Case2 = 1;
                        else if (strcmp(action2, "view") == 0)
                            Case2 = 2;
                        else if (strcmp(action2, "show_goods") == 0)
                            Case2 = 3;
                        else if (strcmp(action2, "login") == 0 || strcmp(action2, "signup") == 0)
                            Case2 = 4;
                        else if (strcmp(action2, "deposit") == 0)
                            Case2 = 5;
                        else if (strcmp(action2, "buy") == 0)
                            Case2 = 6;
                        else if (strcmp(action2, "rate_goods") == 0)
                            Case2 = 7;
                        else if (strcmp(action2, "search") == 0)
                            Case2 = 8;
                        else
                            Case2 = 9;
                        int find = 0;
                        switch (Case2) {
                        case 1: {//logout
                            flag2 = 2;
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            save_personal_data_in_file(head, members);
                            save_good_data_in_file(GOODS_head->left, pro_total_num);
                            break; }
                        case 2: {//view
                            view(finding);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 3: {//show_goods
                            if (pro_total_num == 0) {
                                printf("/ / / /The inventory is empty/ / / / \n");
                                break;
                            }
                            printf("********************************************************************************\n");
                            s_goods(GOODS_head->left);
                            printf("********************************************************************************\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 4: {//login || signup
                            printf("!-! U must logout first!this isn't acceptble !-!\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 5: {//deposit
                            deposit(finding);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 6: {//buy
                            int gc = 0;
                            struct signup* seller_saver = NULL;
                            char* goods_name = (char*)malloc(sizeof(char));
                            char* goods_count = (char*)malloc(sizeof(char));
                            char* seller_username = (char*)malloc(sizeof(char));
                            goods_name = get_input(goods_name);
                            goods_count = get_input(goods_count);
                            seller_username = get_input(seller_username);
                            seller_saver = seller_finder(head, &find, seller_username);
                            for (int h = 0; h < strlen(goods_count);h++) {
                                if (!isdigit(goods_count[h])) {
                                    gc = 1;
                                    break;
                                }
                            }
                            if (find == 0) {
                                printf("This seller doesn't exist\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            if (gc == 1) {
                                printf("invalid count of the pro\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            else {
                                struct goods* pro_saver = NULL;
                                pro_saver = pro_finder(seller_saver, goods_name, &find);
                                if (find == 10) {
                                    printf("this pro is inavailable right now\n");
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                                if (find != 2) {
                                    printf("This seller doesn't sell this pro\n");
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                                else {
                                    int gcc = atoi(goods_count);
                                    if (pro_saver->number >= gcc) {
                                        if ((pro_saver->price) * (gcc) <= finding->budget) {
                                            buied_pro(finding, goods_name, gcc, &flag3);
                                            pro_saver->number -= gcc;
                                            pro_finder_in_GOODS(GOODS_head->left, goods_name, gcc);
                                            finding->budget -= (pro_saver->price) * (gcc);
                                            seller_saver->budget += (pro_saver->price) * (gcc);
                                            if (flag3 != 1) {
                                                finding->goods_num++;
                                                if (finding->goods_num == 1) {
                                                    finding->Goods = (struct goods*)malloc(sizeof(struct goods));
                                                    finding->Goods->left = (struct goods*)malloc(sizeof(struct goods));
                                                    finding->Goods->right = NULL;
                                                    finding->Goods->left->rate = 0;
                                                    finding->Goods->left->left = NULL;
                                                    finding->Goods->left->right = NULL;
                                                    finding->Goods->left->sellers_ranking = 0;
                                                    finding->Goods->left->name = (char*)malloc(sizeof(char) * strlen(goods_name));
                                                    finding->Goods->left->seller_name = (char*)malloc(sizeof(char) * strlen(seller_username));
                                                    strcpy(finding->Goods->left->name, goods_name);
                                                    strcpy(finding->Goods->left->seller_name, seller_username);
                                                    finding->Goods->left->number = gcc;
                                                    finding->Goods->left->price = (pro_saver->price);
                                                    free(action2);
                                                    fseek(stdin, 0, SEEK_END);
                                                    fflush(stdin);
                                                    printf("done\n");
                                                    break;
                                                }
                                                else {
                                                    struct goods* pro = finding->Goods->left;
                                                    find_pro_location(pro, goods_name, seller_username, gcc, pro_saver->price);
                                                    free(action2);
                                                    fseek(stdin, 0, SEEK_END);
                                                    fflush(stdin);
                                                    break;
                                                }
                                            }
                                            else {
                                                free(action2);
                                                fseek(stdin, 0, SEEK_END);
                                                fflush(stdin);
                                                printf("done again\n");
                                                break;
                                            }
                                        }
                                        else {
                                            printf("($)Your budget is not enough($)\n");
                                            free(action2);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                    }
                                    else {
                                        printf("The inventory is not enough\n");
                                        free(action2);
                                        fseek(stdin, 0, SEEK_END);
                                        fflush(stdin);
                                        break;
                                    }
                                }
                            }}
                        case 7: {//rate
                            if (finding->goods_num == 0)
                            {
                                printf("u have nothing to rate\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            else {
                                char* goods_name = NULL;
                                char* seller_username = NULL;
                                char* rating = NULL;
                                goods_name = get_input(goods_name);
                                seller_username = get_input(seller_username);
                                rating = get_input(rating);
                                int r = 0;
                                for (int h = 0; h < strlen(rating);h++) {
                                    if (!isdigit(rating[h])) {
                                        r = 1;
                                        break;
                                    }
                                }
                                if (r == 1) {
                                    printf("invalid rating\n");
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                                if (r == 0) {
                                    int star = atoi(rating);
                                    if (1 <= star && star <= 5) {
                                        rate_goods(GOODS_head, head, goods_name, seller_username, star, finding);
                                        free(action2);
                                        fseek(stdin, 0, SEEK_END);
                                        fflush(stdin);
                                        break;
                                    }
                                    else {
                                        printf("it must be on scale of 1 to 5\n");
                                        free(action2);
                                        fseek(stdin, 0, SEEK_END);
                                        fflush(stdin);
                                        break;
                                    }
                                }
                            }
                            break;}
                        case 8: {//search
                            if (pro_total_num == 0) {
                                printf("there is nothing to search\n");
                                break;
                            }
                            char* number_of_conditions = NULL;
                            number_of_conditions = get_input(number_of_conditions);
                            int r = 0;
                            for (int h = 0; h < strlen(number_of_conditions);h++) {
                                if (!isdigit(number_of_conditions[h])) {
                                    r = 1;
                                    break;
                                }
                            }
                            if (r == 1) {
                                printf("invalid number of conditions\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            int num_of_con = atoi(number_of_conditions);
                            if (1 <= num_of_con && num_of_con <= 4) {
                                struct goods* total_condition = (struct goods*)malloc(sizeof(struct goods));
                                total_condition->right = NULL;
                                total_condition->left = copytree(GOODS_head->left); //copy the tree of goods in case of filtering
                                int Case3 = 0;
                                int invalid_flag = 0;
                                for (int i = 0;i < num_of_con;i++) {
                                    char* command = NULL;
                                    command = get_input(command);
                                    char* attribute_value = NULL;
                                    if (strcmp(command, "max_price") == 0)
                                        Case3 = 1;
                                    else if (strcmp(command, "min_price") == 0)
                                        Case3 = 2;
                                    else if (strcmp(command, "name") == 0)
                                        Case3 = 3;
                                    else if (strcmp(command, "seller_username") == 0)
                                        Case3 = 4;
                                    else
                                        Case3 = 5;
                                    switch (Case3) {
                                    case 1: {
                                        attribute_value = get_input(attribute_value);
                                        int s = 0;
                                        for (int h = 0; h < strlen(attribute_value);h++) {
                                            if (!isdigit(attribute_value[h])) {
                                                s = 1;
                                                break;
                                            }
                                        }
                                        if (s == 1) {
                                            printf("invalid attribute value\n");
                                            invalid_flag = 1;
                                            free(action2);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        int max_price = atoi(attribute_value);
                                        remove_based_on_max_price(total_condition->left, max_price);
                                        break;}
                                    case 2: {
                                        attribute_value = get_input(attribute_value);
                                        int s = 0;
                                        for (int h = 0; h < strlen(attribute_value);h++) {
                                            if (!isdigit(attribute_value[h])) {
                                                s = 1;
                                                break;
                                            }
                                        }
                                        if (s == 1) {
                                            printf("invalid attribute value\n");
                                            invalid_flag = 1;
                                            free(action2);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        int min_price = atoi(attribute_value);
                                        remove_based_on_min_price(total_condition->left, min_price);
                                        break;}
                                    case 3: {
                                        attribute_value = get_input(attribute_value);//as name of the pro
                                        remove_based_on_name(total_condition->left, attribute_value);
                                        break;}
                                    case 4: {
                                        attribute_value = get_input(attribute_value);//as name of the seller
                                        remove_based_on_seller_username(total_condition->left, attribute_value);
                                        break;}
                                    case 5: {
                                        printf("invalid goods attribute\n");
                                        invalid_flag = 1;
                                        break;}
                                    }
                                    if (invalid_flag == 1)
                                        break;
                                }
                                if (invalid_flag == 1) {
                                    deleteTree(total_condition->left);
                                    free(total_condition);
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                                else {
                                    printf("###################################################################\n");
                                    search_print(total_condition->left);
                                    printf("###################################################################\n");
                                    deleteTree(total_condition->left);
                                    free(total_condition);
                                    free(action2);
                                    fseek(stdin, 0, SEEK_END);
                                    fflush(stdin);
                                    break;
                                }
                            }
                            else {
                                printf("it must be on scale of one to four\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            break;}
                        case 9: {
                            printf("invalid command,try again\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break;
                        }
                        }
                        if (flag2 == 2) {
                            printf("logout successfull\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break;
                        }
                    }
                }
                break;
        case 2://signup
            flag1 = 0;
            if (members == 0) {
                if (strcmp(Role2, "seller") == 0 || strcmp(Role2, "buyer") == 0) {
                    members = 1;
                    signup1(head, Uname2, Pword2, Role2);
                    free(action2);
                    free(Uname2);
                    free(Pword2);
                    free(Role2);
                    fseek(stdin, 0, SEEK_END);
                    fflush(stdin);
                    save_personal_data_in_file(head, members);
                    break;
                }
                else {
                    printf("the role that u have choosen doesn't exist\n");
                    free(action2);
                    free(Uname2);
                    free(Pword2);
                    free(Role2);
                    fseek(stdin, 0, SEEK_END);
                    fflush(stdin);
                    break;
                }
            }
            else if (members != 0) {
                user_checker(head, Uname2, Role2, &flag1);
                if (flag1 == 1) {
                    free(action2);
                    free(Uname2);
                    free(Pword2);
                    free(Role2);
                    fseek(stdin, 0, SEEK_END);
                    fflush(stdin);
                    break;
                }
                else {
                    if (strcmp(Role2, "seller") == 0 || strcmp(Role2, "buyer") == 0) {
                        members++;
                        struct signup* user_adder = NULL;
                        signup2_part1(head, Uname2, Pword2, Role2);
                        free(action2);
                        free(Uname2);
                        free(Pword2);
                        free(Role2);
                        fseek(stdin, 0, SEEK_END);
                        fflush(stdin);
                        save_personal_data_in_file(head, members);
                        break;
                    }
                    else {
                        printf("the role that u have choosen doesn't exist\n");
                        free(action2);
                        free(Uname2);
                        free(Pword2);
                        free(Role2);
                        fseek(stdin, 0, SEEK_END);
                        fflush(stdin);
                        break;
                    }
                }
                break;
            }
            }
        }
    }
}

void remove_left(struct goods* head, char* goods_name, int* flag, int* num_of_goods) {//this function just remove a node but also if its node is not "the node" it dicides to go left or right
    struct goods* temp_head = head->left;
    if (strcmp(temp_head->name, goods_name) == 0) {
        remove_goods(head, goods_name, num_of_goods, flag);
        return;
    }
    else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left == NULL) {
        printf("this pro doesnt exist");
        *flag = 1;
        return;
    }
    else if (strcmp(temp_head->name, goods_name) == 1 && temp_head->left != NULL) {
        remove_left(temp_head, goods_name, flag, num_of_goods);
        return;
    }
    else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right == NULL) {
        printf("this pro doesnt exist");
        *flag = 1;
        return;
    }
    else if (strcmp(temp_head->name, goods_name) == -1 && temp_head->right != NULL) {
        remove_right(temp_head, goods_name, flag, num_of_goods);
        return;
    }

}
void initialize(struct goods* deletee, struct goods* temp) {//this function make a new node with given data
    deletee->name = (char*)malloc(sizeof(char) * strlen(temp->left->name));
    deletee->seller_name = (char*)malloc(sizeof(char) * strlen(temp->left->seller_name));
    strcpy(deletee->name, temp->left->name);
    strcpy(deletee->seller_name, temp->left->seller_name);
    deletee->price = temp->left->price;
    deletee->number = temp->left->number;
    deletee->rate = temp->left->rate;
    deletee->sellers_ranking = temp->left->sellers_ranking;
}
void remove_right(struct goods* head, char* goods_name, int* flag, int* num_of_goods) {//this function just remove a node but also if its node is not "the node" it dicides to go left or right
    struct goods* deletee = head->right;
    if (strcmp(deletee->name, goods_name) == 0) {
        if (deletee->left == NULL && deletee->right == NULL) {//if its leaf
            deletee = NULL;
        }
        else if (deletee->left == NULL) {//if it has one leaf
            head->right = deletee->right;
            free(deletee);
        }
        else if (deletee->right == NULL) {//if it has one leaf
            head->right = deletee->left;
            free(deletee);
        }
        else {//if it has a sub_tree
            struct goods* temp = deletee;
            int i = 1;
            while (temp->left->left != NULL) {
                temp = temp->left;//finding the smallest node in the sub_tree 
                i++;
            }
            if (i == 1) {
                struct goods* finder = head->right->right;
                if (finder == NULL) {
                    head->right->right = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);
                }
                else if (finder->left == NULL) {
                    finder->left = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);
                }
                else {
                    while (finder->left != NULL)
                        finder = finder->left;
                    finder->left = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);

                }
            }
            else {
                struct goods* pro = temp->left;
                initialize(deletee, temp->left);
                temp->left = temp->left->right;
                free(pro);
            }
        }
        *num_of_goods -= 1;
        return;
    }
    else if (strcmp(deletee->name, goods_name) == 1 && deletee->left == NULL) {
        printf("this pro doesnt exist\n");
        *flag = 1;
        return;
    }
    else if (strcmp(deletee->name, goods_name) == 1 && deletee->left != NULL) {
        remove_left(deletee, goods_name, flag, num_of_goods);
        return;
    }
    else if (strcmp(deletee->name, goods_name) == -1 && deletee->right == NULL) {
        printf("this pro doesnt exist\n");
        *flag = 1;
        return;
    }
    else if (strcmp(deletee->name, goods_name) == -1 && deletee->right != NULL) {
        remove_right(deletee, goods_name, flag, num_of_goods);
        return;
    }
}
void remove_goods(struct goods* head, char* goods_name, int* num_of_goods, int* flag) {
    if (strcmp(head->left->name, goods_name) == 0) {
        struct goods* deletee = head->left;
        if (head->left->left == NULL && head->left->right == NULL) {
            head->left = NULL;
        }
        else if (head->left->left == NULL) {
            head->left = head->left->right;
            free(deletee);
        }
        else if (head->left->right == NULL) {
            head->left = head->left->left;
            free(deletee);
        }
        else {
            struct goods* temp = deletee;
            int i = 1;
            while (temp->left->left != NULL) {
                temp = temp->left;//finding the smallest node in the sub_tree 
                i++;
            }
            if (i == 1) {
                struct goods* finder = head->left->right;
                if (finder == NULL) {
                    head->left->right = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);
                }
                else if (finder->left == NULL) {
                    finder->left = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);
                }
                else {
                    while (finder->left != NULL)
                        finder = finder->left;
                    finder->left = temp->left->right;
                    struct goods* pro = temp->left;
                    initialize(deletee, temp);
                    deletee->left = NULL;
                    free(pro);

                }
            }
            else {
                struct goods* pro = temp->left;
                initialize(deletee, temp->left);
                temp->left = temp->left->right;
                free(pro);
            }
        }
        *num_of_goods -= 1;
        return;
    }
    if (strcmp(head->left->name, goods_name) == -1)
        remove_right(head->left, goods_name, flag, num_of_goods);
    else if ((strcmp(head->left->name, goods_name) == 1))
        remove_left(head->left, goods_name, flag, num_of_goods);
    return;
}


void deleteTree(struct goods* node)
{
    /*  This function traverses tree in post order to
    to delete each and every node of the tree */
    if (node == NULL) return;
    /* first delete both subtrees */
    deleteTree(node->left);
    deleteTree(node->right);
    /* then delete the node */
    free(node);
}

void print_good_tree(struct goods* GOOD, FILE* goods) {//this function print data of goods in given file
    if (GOOD == NULL)
        return;
    else {
        fprintf(goods, "%s %d %d %f %d %s\n", GOOD->name, GOOD->price, GOOD->number, GOOD->rate, GOOD->sellers_ranking, GOOD->seller_name);
        print_good_tree(GOOD->left, goods);
        print_good_tree(GOOD->right, goods);
    }
    return;
}
void print_users_tree(struct signup* head, FILE* user) {//this function print users data in the given file
    if (head == NULL)
        return;
    else {
        fprintf(user, "%s %s %s %d\n", head->username, head->password, head->role, head->budget);
        fprintf(user, "%d\n", head->goods_num);
        if (head->goods_num != 0)
            print_good_tree(head->Goods->left, user);
        print_users_tree(head->left, user);
        print_users_tree(head->right, user);
    }
    return;
}
void save_personal_data_in_file(struct signup* head, int members) {//this function open a file and uses uper functions
    FILE* user;
    user = fopen("user.txt", "w");
    fprintf(user, "%d\n", members);
    if (members != 0)
        print_users_tree(head, user);
    fclose(user);
    return;
}
void save_good_data_in_file(struct goods* GOODS, int total_good_num) {//this function open a file and uses uper functions
    FILE* goods;
    goods = fopen("goods.txt", "w");
    fprintf(goods, "%d\n", total_good_num);
    if (total_good_num != 0)
        print_good_tree(GOODS, goods);
    fclose(goods);
    return;
}
char* read_line_from_input_file(FILE* input) {//this functon read from a given file
    int line_length = 0;
    int flag = 0;
    char* line = (char*)malloc(sizeof(char));
    *(line) = '0';
    char temp_char[1] = { ' ' };
    while (true) {
        fread(temp_char, sizeof(char), 1, input);
        line_length++;
        line = (char*)realloc(line, sizeof(char) * line_length);
        line[line_length - 1] = NULL;
        switch (temp_char[0]) {
        case '\n':
            return line;
            flag = 1;
            break;
        case EOF:
            return line;
            flag = 1;
            break;
        case' ':
            return line;
            flag = 1;
            break;
        default:
            line[line_length - 1] = temp_char[0];
            break;
        }
        if (flag == 1)
            break;
    }
}
struct goods* good_node_maker(FILE* user) {//this function make nodes from given data which is given from a file
    struct goods* product = (struct goods*)malloc(sizeof(struct goods));
    product->name = read_line_from_input_file(user);
    product->price = atoi(read_line_from_input_file(user));
    product->number = atoi(read_line_from_input_file(user));
    product->rate = atof(read_line_from_input_file(user));
    product->sellers_ranking = atoi(read_line_from_input_file(user));
    product->seller_name = read_line_from_input_file(user);
    product->left = NULL;
    product->right = NULL;
    return product;
}
struct signup* member_node_maker(FILE* user) {//this function make nodes from given data which is given from a file
    struct signup* create = (struct signup*)malloc(sizeof(struct signup));
    create->username = read_line_from_input_file(user);
    create->password = read_line_from_input_file(user);
    create->role = read_line_from_input_file(user);
    create->budget = atoi(read_line_from_input_file(user));
    create->goods_num = atoi(read_line_from_input_file(user));
    create->left = NULL;
    create->right = NULL;
    create->Goods = (struct goods*)malloc(sizeof(struct goods));
    if (create->goods_num != 0) {
        create->Goods->left = good_node_maker(user);
        if (create->goods_num != 1) {
            for (int i = 1;i <= create->goods_num - 1;i++) {
                struct goods* new_good = good_node_maker(user);
                struct goods* place = create->Goods->left;
                while (1) {
                    if (strcmp(place->name, new_good->name) == 1) {
                        if (place->left == NULL) {
                            place->left = new_good;
                            break;
                        }
                        else
                            place = place->left;
                    }
                    else if (strcmp(place->name, new_good->name) == -1) {
                        if (place->right == NULL) {
                            place->right = new_good;
                            break;
                        }
                        else
                            place = place->right;
                    }
                }
            }
        }
    }
    return create;
}
void file_to_tree(struct signup** head, int* members) {//this is the main function of reading data from the file of members
    FILE* user;
    user = fopen("user.txt", "r");//opens the file
    *members = atoi(read_line_from_input_file(user));
    if (*members != 0) {
        *head = member_node_maker(user);//make the first node
        if (*members != 1) {//if there is more
            for (int i = 1;i <= *members - 1;i++) {
                struct signup* new_mem = member_node_maker(user);
                while (1) {
                    struct signup* place = *head;
                    if (strcmp(place->username, new_mem->username) == 1) {
                        if (place->left == NULL) {
                            place->left = new_mem;
                            break;
                        }
                        else
                            place = place->left;
                    }
                    else if (strcmp(place->username, new_mem->username) == -1) {
                        if (place->right == NULL) {
                            place->right = new_mem;
                            break;
                        }
                        else
                            place = place->right;
                    }
                }
            }
        }
    }
    fclose(user);//closes the file
    return;
}
struct goods* Goods(int* total_good_num) {//this is the main function of reading data from the file for goods
    FILE* goods;
    goods = fopen("goods.txt", "r");
    struct goods* GOODS_head = (struct goods*)malloc(sizeof(struct goods));
    *total_good_num = atoi(read_line_from_input_file(goods));
    if (*total_good_num != 0) {
        GOODS_head->left = good_node_maker(goods);//make the first node
        if (*total_good_num != 1) {//if there is more
            for (int i = 1;i <= *total_good_num - 1; i++) {
                struct goods* new_good = good_node_maker(goods);
                struct goods* place = GOODS_head->left;
                while (1) {
                    if (strcmp(place->name, new_good->name) == 1) {
                        if (place->left == NULL) {
                            place->left = new_good;
                            break;
                        }
                        else
                            place = place->left;
                    }
                    else if (strcmp(place->name, new_good->name) == -1) {
                        if (place->right == NULL) {
                            place->right = new_good;
                            break;
                        }
                        else
                            place = place->right;
                    }
                }
            }
        }
    }
    fclose(goods);//closes the file
    return GOODS_head;
}