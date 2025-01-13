#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "C112152342_Login.h"

using namespace std;

class Shop
{
private:
    GameLogin &login; // 登入系統參考
public:
    Shop(GameLogin &login);
    vector<item_init> items;                           // 商店商品列表
    vector<skill_init> skills;                         // 商店技能列表
    void LoadItems(const string &filename);            // 讀取商店商品資料
    void ShowItems(int n);                             // 顯示商店商品
    void ShowAllItems();                               // 顯示所有商品
    role_data_init BuyItem(role_data_init role_data);  // 購買商品
    role_data_init SellItem(role_data_init role_data); // 賣出商品
    role_data_init crates(role_data_init role_data);   // 寶箱

    void LoadSkill(const string &filename);            // 讀取技能資料
    void ShowAllSkill();                               // 顯示所有技能
    role_data_init BuySkill(role_data_init role_data); // 購買技能
};

#endif