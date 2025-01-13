#include "C112152342_logic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
logic::logic(GameLogin &login) : login(login) {}
// 此函數允許玩家使用他們背包中的物品。
// 它顯示玩家的當前狀態、裝備和背包物品。
// 玩家可以選擇一個物品來使用，這將會：
// - 恢復生命值或魔法值。
// - 增加攻擊或防禦屬性。
// - 裝備新裝備（頭部、身體、手部或腳部）。
// 該函數檢查物品是否適用於玩家的職業，並相應地更新玩家的屬性或裝備。

role_data_init logic::Use_items(role_data_init role_data)
{
    string move_input;
    do
    {
        system("cls"); // 清除畫面
        // login.ShowRoleBag(player.name, player.id); // 顯示角色背包
        cout << string(50, '=') << " 角色狀態 " << string(50, '=') << endl;
        cout << string(5, ' ') << "Level:" << role_data.role_level << " "
            <<string(5, ' ')<< "EXP:" << role_data.role_exp << "/" << role_data.role_exp_up << " "
             << "角色血量:" << role_data.role_hp << "/" << role_data.role_hp_max << " "
             << "角色魔法值:" << role_data.role_mp << "/" << role_data.role_mp_max << " "
             << "金幣:" << role_data.role_money
             << " 火屬性:" << role_data.role_attr_fire
             << " 水屬性:" << role_data.role_attr_water
             << " 木屬性:" << role_data.role_attr_wood << endl;

        cout << string(50, '=') << " 角色裝備 " << string(50, '=') << endl;
        cout << string(5, ' ') << "頭部 " << "名稱:" << role_data.head.name << " "
             << "傷害值:" << role_data.head.damage << " "
             << "防禦力:" << role_data.head.defense << " "
             << "回復值:" << role_data.head.recovery << " "
             << "火屬性:" << role_data.head.fire_attr << " "
             << "水屬性:" << role_data.head.water_attr << " "
             << "木屬性:" << role_data.head.wood_attr << " "
             << "價格:" << role_data.head.price << endl;
        cout << string(5, ' ') << "身體 " << "名稱:" << role_data.body.name << " "
             << "傷害值:" << role_data.body.damage << " "
             << "防禦力:" << role_data.body.defense << " "
             << "回復值:" << role_data.body.recovery << " "
             << "火屬性:" << role_data.body.fire_attr << " "
             << "水屬性:" << role_data.body.water_attr << " "
             << "木屬性:" << role_data.body.wood_attr << " "
             << "價格:" << role_data.body.price << endl;
        cout << string(5, ' ') << "手部 " << "名稱:" << role_data.hand.name << " "
             << "傷害值:" << role_data.hand.damage << " "
             << "防禦力:" << role_data.hand.defense << " "
             << "回復值:" << role_data.hand.recovery << " "
             << "火屬性:" << role_data.hand.fire_attr << " "
             << "水屬性:" << role_data.hand.water_attr << " "
             << "木屬性:" << role_data.hand.wood_attr << " "
             << "價格:" << role_data.hand.price << endl;
        cout << string(5, ' ') << "腳部 " << "名稱:" << role_data.foot.name << " "
             << "傷害值:" << role_data.foot.damage << " "
             << "防禦力:" << role_data.foot.defense << " " << "回復值:" << role_data.foot.recovery << " "
             << "火屬性:" << role_data.foot.fire_attr << " " << "水屬性:" << role_data.foot.water_attr << " "
             << "木屬性:" << role_data.foot.wood_attr << " " << "價格:" << role_data.foot.price << endl;

        cout << string(50, '=') << " 角色背包 " << string(50, '=') << endl;
        for (int i = 0; i < role_data.bag.size(); i++)
        {
            cout << string(2, ' ') << left << "編號:" << i << " "
                 << left << "適用職業:" << role_data.bag[i].job << " "
                 << left << "類型:" << role_data.bag[i].type << " "
                 << left << "名稱:" << role_data.bag[i].name << " "
                 << left << "部位:" << role_data.bag[i].part << " "
                 << left << "傷害:" << role_data.bag[i].damage << " "
                 << left << "防禦:" << role_data.bag[i].defense << " "
                 << left << "回復:" << role_data.bag[i].recovery << " "
                 << left << "火屬性:" << role_data.bag[i].fire_attr << " "
                 << left << "水屬性:" << role_data.bag[i].water_attr << " "
                 << left << "木屬性:" << role_data.bag[i].wood_attr << " "
                 << left << "價格:" << role_data.bag[i].price << endl;
        }
        cout << string(5, ' ') << "b背包離開背包 輸入編號可使用物品:";
        cin >> move_input;
        if (move_input != "b")
        {
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
            int item_id = stoi(move_input);
            cout << string(50, ' ') << "使用物品:" << role_data.bag[item_id].name << endl;
            cout << string(50, ' ') << "適用職業:" << role_data.bag[item_id].job << endl;
            // cout << (role_data.bag[item_id].job == "all") << endl;
            if (role_data.bag[item_id].job == role_data.role_job || role_data.bag[item_id].job == "all")
            {
                if (role_data.bag[item_id].part == "all") // 使用物品
                {
                    role_data.role_hp += role_data.bag[item_id].recovery; // 回復血量
                    if (role_data.role_hp > role_data.role_hp_max)
                    {
                        role_data.role_hp = role_data.role_hp_max;
                        cout << string(50, ' ') << "血量已滿!" << endl;
                    }
                    else
                    {
                        cout << string(50, ' ') << "回復" << role_data.bag[item_id].recovery << "血量" << endl;
                    }
                    role_data.role_mp += role_data.bag[item_id].recovery; // 回復魔法值
                    if (role_data.role_mp > role_data.role_mp_max)
                    {
                        role_data.role_mp = role_data.role_mp_max;
                        cout << string(50, ' ') << "魔法值已滿!" << endl;
                    }
                    else
                    {
                        cout << string(50, ' ') << "回復" << role_data.bag[item_id].recovery << "魔法值" << endl;
                    }
                    if (role_data.bag[item_id].damage > 0) // 增加攻擊力
                    {
                        cout << string(50, ' ') << "增加攻擊力:" << role_data.bag[item_id].damage << "->" << role_data.role_atk + role_data.bag[item_id].damage << endl;
                        role_data.role_atk += role_data.bag[item_id].damage; // 增加攻擊力
                    }
                    if (role_data.bag[item_id].defense > 0) // 增加防禦力
                    {
                        cout << string(50, ' ') << "增加防禦力:" << role_data.bag[item_id].defense << "->" << role_data.role_def + role_data.bag[item_id].defense << endl;
                        role_data.role_def += role_data.bag[item_id].defense; // 增加防禦力
                    }

                    role_data.bag.erase(role_data.bag.begin() + item_id);
                }
                else if (role_data.bag[item_id].part == "head")
                {
                    cout << string(50, ' ') << "更換頭部裝備";
                    cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                    item_init temp = role_data.head;
                    role_data.head = role_data.bag[item_id];
                    role_data.bag[item_id] = temp;
                }
                else if (role_data.bag[item_id].part == "body")
                {
                    cout << string(50, ' ') << "更換身體裝備";
                    cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                    item_init temp = role_data.body;
                    role_data.body = role_data.bag[item_id];
                    role_data.bag[item_id] = temp;
                }
                else if (role_data.bag[item_id].part == "hand")
                {
                    cout << string(50, ' ') << "更換手部裝備";
                    cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                    item_init temp = role_data.hand;
                    role_data.hand = role_data.bag[item_id];
                    role_data.bag[item_id] = temp;
                }
                else if (role_data.bag[item_id].part == "foot")
                {
                    cout << string(50, ' ') << "更換腳部裝備";
                    cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                    item_init temp = role_data.foot;
                    role_data.foot = role_data.bag[item_id];
                    role_data.bag[item_id] = temp;
                }
            }
            else
            {
                cout << string(50, ' ') << "職業不符合!" << endl;
                Sleep(1000);
                // system("pause");
            }
            system("pause");
        }

    } while (move_input != "b");
    return role_data;
}

// 角色寵物
role_data_init logic::Use_pet(role_data_init role_data)
{
    string select;
    cout << string(50, '=') << "寵物" << string(50, '=') << endl;
    do
    {
        system("cls");
        int now_pet_id = role_data.role_pet_id;
        cout << string(5, ' ') << "當前所使用寵物" << role_data.role_pet.pet_data[now_pet_id - 1].name << endl;
        for (int i = 0; i < role_data.role_pet.pet_data.size(); i++)
        {
            cout << string(5, ' ') << left
                 << "編號:" << role_data.role_pet.pet_data[i].id
                 << "名稱:" << role_data.role_pet.pet_data[i].name
                 << "血量:" << role_data.role_pet.pet_data[i].hp << "/" << role_data.role_pet.pet_data[i].hp_max
                 << "攻擊力:" << role_data.role_pet.pet_data[i].atk
                 << "防禦力:" << role_data.role_pet.pet_data[i].def
                 << "等級:" << role_data.role_pet.pet_data[i].level
                 << "經驗值:" << role_data.role_pet.pet_data[i].exp
                 << "升級所需經驗值:" << role_data.role_pet.pet_data[i].exp_up
                 << "火屬性值:" << role_data.role_pet.pet_data[i].attr_fire
                 << "水屬性值:" << role_data.role_pet.pet_data[i].attr_water
                 << "木屬性值:" << role_data.role_pet.pet_data[i].attr_wood
                 << endl;
        }
        cout << string(5, ' ') << "p離開 請輸入要使用的寵物編號:";
        cin >> select;
        if (select != "p")
        {

            role_data.role_pet_id = atoi(select.c_str());
            cout << string(5, ' ') << "使用" << role_data.role_pet.pet_data[role_data.role_pet_id - 1].name << endl;
            system("pause");
        }
    } while (select != "p");
    return role_data;
}

role_data_init logic::Use_Up(role_data_init role_data)
{
    while (true)
    {
        system("cls");
        cout << string(40, '=') << "升級" << string(40, '=') << endl;
        cout << string(30, ' ') << "選擇升級 1.技能 2.屬性 3.離開" << endl;
        int select;
        cout << string(30, ' ') << "請輸入選項:";
        cin >> select;
        system("cls");
        if (select == 1)
        {
            cout << string(40, '=') << "技能升級" << string(40, '=') << endl;
            cout << string(30, ' ') << "技能點數:" << role_data.role_skill << endl;
            for (int i = 0; i < role_data.role_skill_data.size(); i++)
            {
                cout << string(5, ' ') << "編號:" << i << " "
                     << "名稱:" << role_data.role_skill_data[i].name << " "
                     << "職業:" << role_data.role_skill_data[i].job << " "
                     << "等級:" << role_data.role_skill_data[i].level << " "
                     << "升級所需技能點:" << role_data.role_skill_data[i].level_up << " "
                     << "傷害:" << role_data.role_skill_data[i].damage << " "
                     << "防禦:" << role_data.role_skill_data[i].defense << " "
                     << "回復:" << role_data.role_skill_data[i].recovery << " "
                     << "火屬性:" << role_data.role_skill_data[i].fire_attr << " "
                     << "水屬性:" << role_data.role_skill_data[i].water_attr << " "
                     << "木屬性:" << role_data.role_skill_data[i].wood_attr
                     << endl;
            }
            cout << string(30, ' ') << "輸入技能編號:";
            cin >> select;
            if (role_data.role_skill_data[select].level_up <= role_data.role_skill)
            {
                role_data.role_skill -= role_data.role_skill_data[select].level_up;
                role_data.role_skill_data[select].level_up += 5;
                role_data.role_skill_data[select].damage += 5;
                role_data.role_skill_data[select].defense += 5;
                role_data.role_skill_data[select].recovery += 5;
                role_data.role_skill_data[select].fire_attr += 5;
                role_data.role_skill_data[select].water_attr += 5;
                role_data.role_skill_data[select].wood_attr += 5;
                for (int i = 0; i < 5; i++)
                {
                    system("cls");
                    Sleep(200);
                    cout << string(30, ' ') << "升級成功" << endl;
                    cout << string(30, ' ') << role_data.role_skill_data[select].name
                         << role_data.role_skill_data[select].level << "->" << role_data.role_skill_data[select].level + 1 << endl;
                    Sleep(200);
                }
                role_data.role_skill_data[select].level += 1;
                system("pause");
            }
            else
            {
                cout << string(30, ' ') << "技能點數不足" << endl;
            }
        }
        else if (select == 2)
        {
            cout << string(40, '=') << "屬性升級" << string(40, '=') << endl;
            cout << string(30, ' ') << "屬性點數:" << role_data.role_attr << endl;
            cout << string(30, ' ') << "火屬性:" << role_data.role_attr_fire << endl;
            cout << string(30, ' ') << "水屬性:" << role_data.role_attr_water << endl;
            cout << string(30, ' ') << "木屬性:" << role_data.role_attr_wood << endl;
            cout << string(30, ' ') << "1.火屬性 2.水屬性 3.木屬性" << endl;
            cout << string(30, ' ') << "請輸入選項:";
            cin >> select;
            if (select == 1)
            {
                if (role_data.role_attr > 0)
                {
                    role_data.role_attr -= 1;
                    for (int i = 0; i < 5; i++)
                    {
                        system("cls");
                        Sleep(200);
                        cout << string(30, ' ') << "升級成功" << endl;
                        cout << string(30, ' ') << "火屬性:"
                             << role_data.role_attr_fire << "->" << role_data.role_attr_fire + 5 << endl;
                        Sleep(200);
                    }
                    role_data.role_attr_fire += 5;
                }
                else
                {
                    cout << string(30, ' ') << "屬性點數不足" << endl;
                }
            }
            else if (select == 2)
            {
                if (role_data.role_attr > 0)
                {
                    role_data.role_attr -= 1;
                    for (int i = 0; i < 5; i++)
                    {
                        system("cls");
                        Sleep(200);
                        cout << string(30, ' ') << "升級成功" << endl;
                        cout << string(30, ' ') << "水屬性:"
                             << role_data.role_attr_water << "->" << role_data.role_attr_water + 5 << endl;
                        Sleep(200);
                    }
                    role_data.role_attr_water += 5;
                }
                else
                {
                    cout << string(30, ' ') << "屬性點數不足" << endl;
                }
            }
            else if (select == 3)
            {
                if (role_data.role_attr > 0)
                {
                    role_data.role_attr -= 1;
                    for (int i = 0; i < 5; i++)
                    {
                        system("cls");
                        Sleep(200);
                        cout << string(30, ' ') << "升級成功" << endl;
                        cout << string(30, ' ') << "木屬性:"
                             << role_data.role_attr_wood << "->" << role_data.role_attr_wood + 5 << endl;
                        Sleep(200);
                    }
                    role_data.role_attr_wood += 5;
                }
                else
                {
                    cout << string(30, ' ') << "屬性點數不足" << endl;
                }
            }
            system("pause");
        }
        else
        {
            break;
        }
    }
    return role_data;
}