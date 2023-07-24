#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
#include "goods.h"
#include "signup.h"
#include"get_input.h"
#include"view.h"
#include"s_goods.h"
#include"login.h"
#include"regis_pro.h"
#include"re_regis_pro.h"
#include"Rgis_pro.h"
#include"deposit.h"
#include"buy_one.h"
#include"signup1.h"
#include"signup2.h"
#include"check_pro.h"
int main() {
    int members = 0;//in case of knowing the number of members
    int pro_total_num = 0;//in case of knowing the number of all goods
    struct signup** Signup;//saving members's data
    Signup = (struct signup**)malloc(sizeof(struct signup*));
    struct goods** GOODS;
    GOODS = (struct goods**)malloc(sizeof(struct goods*) * pro_total_num);
    int Case1 = 0;//login or signup
    int Case2 = 0;//other commands like view,buy...
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int finding = 0;
    char* action2 = NULL;
    char* Uname2 = NULL;
    char* Pword2 = NULL;
    char* Role2 = NULL;
    if (Signup == NULL) {
        printf("Malloc failed!\n");
        return 0;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~#WELCOME ^-^ 2 ^-^ UT ^-^ KALA#~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~#IF U STILL DONT HAVE AN ACCOUNT,SIGNUP#~~~~~~~~~~~~~~~~~**@@**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while (1) {
        fseek(stdin, 0, SEEK_END);
        fflush(stdin);
        Case1 = 0;
        Case2 = 0;
        flag1 = 0;
        flag2 = 0;
        finding = 0;
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
            finding = 0;
            login(&finding, Signup, members, &flag1, Uname2, Pword2, Role2);
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
                        else
                            Case2 = 6;
                        switch (Case2) {
                        case 1: {//logout
                            flag2 = 2;
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 2: {//view
                            view(Signup, finding);
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
                                        Signup[finding]->goods_num = 1;
                                        pro_total_num = 1;
                                        GOODS = (struct goods**)realloc(GOODS, sizeof(struct goods*) * 1);
                                        GOODS[0] = (struct goods*)malloc(sizeof(struct goods));
                                        GOODS[0]->name = (char*)malloc(sizeof(char) * strlen(pro));
                                        GOODS[0]->seller_name = (char*)malloc(sizeof(char) * strlen(Signup[finding]->username));
                                        Signup[finding]->Goods = (struct goods**)realloc(Signup[finding]->Goods, sizeof(struct goods*));
                                        Signup[finding]->Goods[0] = (struct goods*)malloc(sizeof(struct goods));
                                        Signup[finding]->Goods[0]->name = (char*)malloc(sizeof(char) * strlen(pro));
                                        Signup[finding]->Goods[0]->seller_name = (char*)malloc(sizeof(char) * strlen(Signup[finding]->username));
                                        regis_pro(Signup, &finding, GOODS, co, pri, pro);
                                        free(pro);
                                        free(goods_price);
                                        free(goods_count);
                                        free(action2);
                                    }
                                    else {
                                        int i = 0;
                                        check_pro(Signup, finding, &i, &flag1, GOODS, pro_total_num, pro);
                                        if (flag1 == 5) {
                                            free(action2);
                                            free(pro);
                                            free(goods_price);
                                            free(goods_count);
                                            fseek(stdin, 0, SEEK_END);
                                            break;
                                        }
                                        else if (flag1 == 3) {
                                            re_regis_pro(Signup, &finding, pro, co, GOODS, &i);
                                            free(action2);
                                            free(pro);
                                            free(goods_price);
                                            free(goods_count);
                                            fseek(stdin, 0, SEEK_END);
                                            fflush(stdin);
                                            break;
                                        }
                                        else {
                                            Signup[finding]->goods_num++;
                                            pro_total_num++;
                                            GOODS = (struct goods**)realloc(GOODS, sizeof(struct goods*) * pro_total_num);
                                            GOODS[pro_total_num - 1] = (struct goods*)malloc(sizeof(struct goods));
                                            GOODS[pro_total_num - 1]->name = (char*)malloc(sizeof(char) * strlen(pro));
                                            GOODS[pro_total_num - 1]->seller_name = (char*)malloc(sizeof(char) * strlen(Signup[finding]->username));
                                            Signup[finding]->Goods = (struct goods**)realloc(Signup[finding]->Goods, Signup[finding]->goods_num * sizeof(struct goods*));
                                            Signup[finding]->Goods[Signup[finding]->goods_num - 1] = (struct goods*)malloc(sizeof(struct goods));
                                            Signup[finding]->Goods[Signup[finding]->goods_num - 1]->name = (char*)malloc(sizeof(char) * strlen(pro));
                                            Signup[finding]->Goods[Signup[finding]->goods_num - 1]->seller_name = (char*)malloc(sizeof(char) * strlen(Signup[finding]->username));
                                            Regis_pro(GOODS, pro_total_num, co, pri, pro, Signup, finding);
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
                            s_goods(GOODS, pro_total_num);
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
                        case 6: {//else
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
                        else
                            Case2 = 7;
                        int find = 0;
                        switch (Case2) {
                        case 1: {
                            flag2 = 2;
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 2: {
                            view(Signup, finding);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 3: {
                            s_goods(GOODS, pro_total_num);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 4: {
                            printf("!-! U must logout first!this isn't acceptble !-!\n");
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 5: {
                            deposit(Signup, finding);
                            free(action2);
                            fseek(stdin, 0, SEEK_END);
                            fflush(stdin);
                            break; }
                        case 6: {//buy
                            int gc = 0;
                            char* goods_name = (char*)malloc(sizeof(char));
                            char* goods_count = (char*)malloc(sizeof(char));
                            char* seller_username = (char*)malloc(sizeof(char));
                            goods_name = get_input(goods_name);
                            goods_count = get_input(goods_count);
                            seller_username = get_input(seller_username);
                            int i = buy_one(members, Signup, &find, seller_username);
                            for (int h = 0; h < strlen(goods_count);h++) {
                                if (!isdigit(goods_count[h])) {
                                    gc = 1;
                                    break;
                                }
                            }
                            if (gc == 1) {
                                printf("invalid count of the pro\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            if (find == 0) {
                                printf("This seller doesn't exist\n");
                                free(action2);
                                fseek(stdin, 0, SEEK_END);
                                fflush(stdin);
                                break;
                            }
                            else {
                                int j = 0;
                                for (j = 0; j < Signup[i]->goods_num; j++) {
                                    if (strcmp(Signup[i]->Goods[j]->name, goods_name) == 0) {
                                        find = 2;
                                        break;
                                    }
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
                                    if (Signup[i]->Goods[j]->number >= gcc) {
                                        if ((Signup[i]->Goods[j]->price) * (gcc) <= Signup[finding]->budget) {
                                            for (int i = 0;i < Signup[finding]->goods_num;i++) {
                                                if (strcmp(Signup[finding]->Goods[i]->name, goods_name) == 0) {
                                                    flag3 = 1;
                                                    Signup[finding]->Goods[i]->number += gcc;
                                                }
                                            }
                                            Signup[i]->Goods[j]->number -= gcc;
                                            int gf = 0;
                                            for (gf = 0;gf < pro_total_num;gf++) {
                                                if (strcmp(GOODS[gf]->name, Signup[i]->Goods[j]->name) == 0)
                                                    break;
                                            }
                                            GOODS[gf]->number -= gcc;
                                            Signup[finding]->budget -= (Signup[i]->Goods[j]->price) * (gcc);
                                            Signup[i]->budget += (Signup[i]->Goods[j]->price) * (gcc);
                                            if (flag3 != 1) {
                                                Signup[finding]->goods_num++;
                                                Signup[finding]->Goods = (struct goods**)realloc(Signup[finding]->Goods, sizeof(struct goods*) * Signup[finding]->goods_num);
                                                Signup[finding]->Goods[Signup[finding]->goods_num - 1] = (struct goods*)malloc(sizeof(struct goods));
                                                Signup[finding]->Goods[Signup[finding]->goods_num - 1]->name = (char*)malloc(sizeof(char) * strlen(Signup[i]->Goods[j]->name));
                                                Signup[finding]->Goods[Signup[finding]->goods_num - 1]->seller_name = (char*)malloc(sizeof(char) * strlen(seller_username));
                                                Signup[finding]->Goods[Signup[finding]->goods_num - 1]->number = gcc;
                                                Signup[finding]->Goods[Signup[finding]->goods_num - 1]->price = Signup[i]->Goods[j]->price;
                                                strcpy(Signup[finding]->Goods[Signup[finding]->goods_num - 1]->name, Signup[i]->Goods[j]->name);
                                                strcpy(Signup[finding]->Goods[Signup[finding]->goods_num - 1]->seller_name, seller_username);
                                                printf("done\n");
                                                free(action2);
                                                fseek(stdin, 0, SEEK_END);
                                                fflush(stdin);
                                                break;
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
                        case 7: {
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
                    Signup = (struct signup**)realloc(Signup, sizeof(struct signup*));
                    Signup[0] = (struct signup*)malloc(sizeof(struct signup));
                    Signup[0]->username = (char*)malloc(sizeof(char) * strlen(Uname2));
                    Signup[0]->password = (char*)malloc(sizeof(char) * strlen(Pword2));
                    Signup[0]->role = (char*)malloc(sizeof(char) * strlen(Role2));
                    Signup[0]->Goods = (struct goods**)malloc(sizeof(struct goods*) * Signup[0]->goods_num);
                    signup1(Signup, Uname2, Pword2, Role2);
                    free(action2);
                    free(Uname2);
                    free(Pword2);
                    free(Role2);
                    fseek(stdin, 0, SEEK_END);
                    fflush(stdin);
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
                for (int i = 0; i < members; i++) {
                    if (strcmp(Signup[i]->username, Uname2) == 0 && strcmp(Signup[i]->role, Role2) == 0) {
                        printf("this username is already taken\n");
                        flag1 = 1;
                        break;
                    }
                }
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
                        Signup = (struct signup**)realloc(Signup, members * sizeof(struct signup*));
                        Signup[members - 1] = (struct signup*)malloc(sizeof(struct signup));
                        Signup[members - 1]->username = (char*)malloc(sizeof(char) * strlen(Uname2));
                        Signup[members - 1]->password = (char*)malloc(sizeof(char) * strlen(Pword2));
                        Signup[members - 1]->role = (char*)malloc(sizeof(char) * strlen(Role2));
                        Signup[members - 1]->Goods = (struct goods**)malloc(sizeof(struct goods*) * Signup[members - 1]->goods_num);
                        signup2(Signup, members, Uname2, Pword2, Role2);
                        free(action2);
                        free(Uname2);
                        free(Pword2);
                        free(Role2);
                        fseek(stdin, 0, SEEK_END);
                        fflush(stdin);
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