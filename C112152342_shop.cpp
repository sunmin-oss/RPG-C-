#include "C112152342_shop.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
Shop::Shop(GameLogin &login) : login(login) {}

// 讀取商店商品資料
void Shop::LoadItems(const string &filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << "無法開啟商店檔案!" << endl;
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string data;
        vector<string> tokens;
        // cout<<line<<endl;
        // system("pause");
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }

        if (tokens.size() == 11)
        {
            item_init item;
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
            item.job = tokens[0];              // 適用職業
            item.type = tokens[1];             // 類型
            item.part = tokens[2];             // 部位
            item.name = tokens[3];             // 名稱
            item.damage = stoi(tokens[4]);     // 傷害
            item.defense = stoi(tokens[5]);    // 防禦
            item.recovery = stoi(tokens[6]);   // 回復
            item.fire_attr = stoi(tokens[7]);  // 火屬性
            item.water_attr = stoi(tokens[8]); // 水屬性
            item.wood_attr = stoi(tokens[9]);  // 木屬性
            item.price = stoi(tokens[10]);     // 價格
            items.push_back(item);             // 將商品加入列表
        }
    }
    file.close();
}

// 顯示商品列表
void Shop::ShowAllItems()
{ // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
    cout << string(20, '=') << "商店商品列表" << string(20, '=') << endl;
    cout << setw(5) << "編號"
         << setw(12) << "職業"
         << setw(12) << "類型"
         << setw(12) << "部位"
         << setw(12) << "名稱"
         << setw(8) << "傷害"
         << setw(8) << "防禦"
         << setw(8) << "回復"
         << setw(8) << "火"
         << setw(8) << "水"
         << setw(8) << "木"
         << setw(8) << "價格" << endl;

    for (int i = 0; i < items.size(); i++)
    {
        cout << setw(5) << i + 1
             << setw(12) << items[i].job       // 適用職業
             << setw(12) << items[i].type      // 類型
             << setw(12) << items[i].part      // 部位
             << setw(12) << items[i].name      // 名稱
             << setw(8) << items[i].damage     // 傷害值
             << setw(8) << items[i].defense    // 防禦力
             << setw(8) << items[i].recovery   // 回復值
             << setw(8) << items[i].fire_attr  // 火屬性
             << setw(8) << items[i].water_attr // 水屬性
             << setw(8) << items[i].wood_attr  // 木屬性
             << setw(8) << items[i].price << endl;
    }
}

// 隨機顯示指定數量的商品
void Shop::ShowItems(int n)
{ // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
    srand(time(0));
    cout << string(20, '=') << "商店商品列表" << string(20, '=') << endl;
    for (int i = 0; i < n; i++)
    {
        int index = rand() % items.size(), x = 8;
        cout << setw(x) << left << "編號: " << i + 1
             << setw(x) << left << " 職業: " << items[index].job            // 適用職業
             << setw(x) << left << " 類型: " << items[index].type           // 類型
             << setw(x) << left << " 部位: " << items[index].part           // 部位
             << setw(x) << left << " 名稱: " << items[index].name           // 名稱
             << setw(x) << left << " 傷害: " << items[index].damage         // 傷害值
             << setw(x) << left << " 防禦: " << items[index].defense        // 防禦力
             << setw(6) << left << " 回復: " << items[index].recovery       // 回復值
             << setw(6) << left << " 火: " << items[index].fire_attr        // 火屬性
             << setw(6) << left << " 水: " << items[index].water_attr       // 水屬性
             << setw(6) << left << " 木: " << items[index].wood_attr        // 木屬性
             << setw(6) << left << " 價格: " << items[index].price << endl; // 價格
    }
}

// 購買商品
role_data_init Shop::BuyItem(role_data_init role_data)
{
    string item_id;
    item_init item[5];
    srand(time(0));
    for (int i = 0; i < 5; i++)
    {
        item[i] = items[rand() % items.size()];
    }
    do
    {
        system("cls");
        cout << string(50, '=');
        cout << setw(12) << "擁有金幣:" << role_data.role_money << string(50, '=') << endl;
        cout << string(50, '=') << "商店商品列表" << string(50, '=') << endl;
        for (int i = 0; i < 5; i++)
        {
            int x = 8;
            cout << setw(x) << left << "編號: " << i + 1
                 << setw(x) << left << " 職業: " << item[i].job            // 適用職業
                 << setw(x) << left << " 類型: " << item[i].type           // 類型
                 << setw(x) << left << " 部位: " << item[i].part           // 部位
                 << setw(x) << left << " 名稱: " << item[i].name           // 名稱
                 << setw(x) << left << " 傷害: " << item[i].damage         // 傷害值
                 << setw(x) << left << " 防禦: " << item[i].defense        // 防禦力
                 << setw(6) << left << " 回復: " << item[i].recovery       // 回復值
                 << setw(6) << left << " 火: " << item[i].fire_attr        // 火屬性
                 << setw(6) << left << " 水: " << item[i].water_attr       // 水屬性
                 << setw(6) << left << " 木: " << item[i].wood_attr        // 木屬性
                 << setw(6) << left << " 價格: " << item[i].price << endl; // 價格
        }
        cout << string(5, ' ') << "e離開 輸入要購買的商品編號:";
        cin >> item_id;
        if (item_id != "e")
        {
            int index = stoi(item_id) - 1;
            if (role_data.role_money >= item[index].price)
            {
                role_data.role_money -= item[index].price;
                role_data.bag.push_back(item[index]);
                cout << "購買成功!" << endl;
                system("pause");
            }
            else
            {
                cout << "金幣不足!" << endl;
                system("pause");
            }
        }
    } while (item_id != "e");

    return role_data;
}

// 賣出商品
role_data_init Shop::SellItem(role_data_init role_data)
{
    string item_id;
    do
    {
        system("cls");
        cout << string(50, '=');
        cout << setw(12) << "擁有金幣:" << role_data.role_money << string(50, '=') << endl;
        cout << string(50, '=') << "商店商品列表" << string(50, '=') << endl;
        for (int i = 0; i < role_data.bag.size(); i++)
        {
            int x = 8;
            cout << setw(x) << left << "編號: " << i + 1
                 << setw(x) << left << " 職業: " << role_data.bag[i].job            // 適用職業
                 << setw(x) << left << " 類型: " << role_data.bag[i].type           // 類型
                 << setw(x) << left << " 部位: " << role_data.bag[i].part           // 部位
                 << setw(x) << left << " 名稱: " << role_data.bag[i].name           // 名稱
                 << setw(x) << left << " 傷害: " << role_data.bag[i].damage         // 傷害值
                 << setw(x) << left << " 防禦: " << role_data.bag[i].defense        // 防禦力
                 << setw(6) << left << " 回復: " << role_data.bag[i].recovery       // 回復值
                 << setw(6) << left << " 火: " << role_data.bag[i].fire_attr        // 火屬性
                 << setw(6) << left << " 水: " << role_data.bag[i].water_attr       // 水屬性
                 << setw(6) << left << " 木: " << role_data.bag[i].wood_attr        // 木屬性
                 << setw(6) << left << " 價格: " << role_data.bag[i].price << endl; // 價格
        }
        cout << string(5, ' ') << "e離開 輸入要售出的商品編號:";
        cin >> item_id;
        if (item_id != "e")
        {
            int index = stoi(item_id) - 1;
            role_data.role_money += role_data.bag[index].price;
            role_data.bag.erase(role_data.bag.begin() + index);
            cout << "賣出成功!" << endl;
            system("pause");
        }
    } while (item_id != "e");

    return role_data;
}

// 寶相
role_data_init Shop::crates(role_data_init role_data)
{
    system("cls");
    srand(time(0));
    int index = rand() % items.size(), x = 8;
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        Sleep(200);
        cout << string(50, ' ') << "恭喜獲得道具:" << items[index].job << items[index].name << endl;
        Sleep(200);
    }
    role_data.bag.push_back(items[index]);
    return role_data;
}

// 載入技能
void Shop::LoadSkill(const string &filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << "無法開啟商店檔案!" << endl;
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string data;
        vector<string> tokens;
        // cout<<line<<endl;
        // system("pause");
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }

        if (tokens.size() == 12)
        {
            skill_init skill;
            // 適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
            skill.job = tokens[0];              // 適用職業
            skill.name = tokens[1];             // 名稱
            skill.level = stoi(tokens[2]);      // 等級
            skill.level_up = stoi(tokens[3]);   // 升級所需技能點
            skill.damage = stoi(tokens[4]);     // 傷害值
            skill.defense = stoi(tokens[5]);    // 防禦值
            skill.recovery = stoi(tokens[6]);   // 回復值
            skill.mp = stoi(tokens[7]);         // 消耗魔法值
            skill.fire_attr = stoi(tokens[8]);  // 火屬性
            skill.water_attr = stoi(tokens[9]); // 水屬性
            skill.wood_attr = stoi(tokens[10]); // 木屬性
            skill.price = stoi(tokens[11]);     // 價格
            skills.push_back(skill);            // 將技能加入列表
        }
    }
    file.close();
}

// 顯示技能列表
void Shop::ShowAllSkill()
{
    cout << string(20, '=') << "商店技能列表" << string(20, '=') << endl;
    cout << setw(5) << "編號"
         << setw(12) << "職業"
         << setw(12) << "名稱"
         << setw(5) << "等級"
         << setw(14) << "升級所需技能點"
         << setw(7) << "傷害值"
         << setw(7) << "防禦力"
         << setw(7) << "回復值"
         << setw(7) << "消耗魔法值"
         << setw(7) << "火"
         << setw(7) << "水"
         << setw(7) << "木"
         << setw(7) << "價格" << endl;

    for (int i = 0; i < skills.size(); i++)
    {
        cout << setw(5) << i + 1
             << setw(12) << skills[i].job           // 適用職業
             << setw(12) << skills[i].name          // 名稱
             << setw(5) << skills[i].level          // 等級
             << setw(14) << skills[i].level_up      // 升級所需技能點
             << setw(7) << skills[i].damage         // 傷害值
             << setw(7) << skills[i].defense        // 防禦力
             << setw(7) << skills[i].recovery       // 回復值
             << setw(7) << skills[i].mp             // 消耗魔法值
             << setw(7) << skills[i].fire_attr      // 火屬性
             << setw(7) << skills[i].water_attr     // 水屬性
             << setw(7) << skills[i].wood_attr      // 木屬性
             << setw(7) << skills[i].price << endl; // 價格
    }
}

role_data_init Shop::BuySkill(role_data_init role_data) // 購買技能
{
    string skill_id;
    skill_init skill[5];
    srand(time(0));
    for (int i = 0; i < 5; i++)
    {
        skill[i] = skills[rand() % skills.size()];
    }
    do
    {
        system("cls");
        cout << string(50, '=');
        cout << setw(12) << "擁有金幣:" << role_data.role_money << string(50, '=') << endl;
        cout << string(50, '=') << "商店技能列表" << string(50, '=') << endl;
        for (int i = 0; i < 5; i++)
        {
            //適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
            int x = 8;
            cout<<setw(x)<<left <<"編號: "<<i+1
                <<setw(x)<<left <<"職業: "<<skill[i].job
                <<setw(x)<<left <<"名稱: "<<skill[i].name
                <<setw(x)<<left <<"等級: "<<skill[i].level
                <<setw(x)<<left <<"傷害值: "<<skill[i].damage
                <<setw(x)<<left <<"防禦力: "<<skill[i].defense
                <<setw(x)<<left <<"回復值: "<<skill[i].recovery
                <<setw(x)<<left <<"消耗魔法值: "<<skill[i].mp
                <<setw(x)<<left <<"火屬性: "<<skill[i].fire_attr
                <<setw(x)<<left <<"水屬性: "<<skill[i].water_attr
                <<setw(x)<<left <<"木屬性: "<<skill[i].wood_attr
                <<setw(x)<<left <<"價格: "<<skill[i].price<<endl;
        }
        cout << string(5, ' ') << "e離開 輸入要購買的商品編號:";
        cin >> skill_id;
        if (skill_id != "e")
        {
            int index = stoi(skill_id) - 1;
            if (role_data.role_money >= skill[index].price)
            {
                if(role_data.role_job != skill[index].job)
                {
                    cout<<"職業不符"<<endl;
                    system("pause");
                    continue;
                }
                role_data.role_money -= skill[index].price;
                role_data.role_skill_data.push_back(skill[index]);
                cout << "購買成功!" << endl;
                system("pause");
            }
            else
            {
                cout << "金幣不足!" << endl;
                system("pause");
            }
        }
    } while (skill_id != "e");

    return role_data;
}