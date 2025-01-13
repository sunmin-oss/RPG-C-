#include "C112152342_fight.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>

FIGHT::FIGHT(GameLogin &login) : login(login) {}

// 讀取怪物資料
void FIGHT::Read_monster_Data(const string filename)
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
        // cout << line << endl;
        // system("pause");
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }

        if (tokens.size() == 11)
        {
            // 寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
            pet_init pet;
            pet.name = tokens[0];
            pet.hp = atoi(tokens[1].c_str());
            pet.hp_max = atoi(tokens[2].c_str());
            pet.atk = atoi(tokens[3].c_str());
            pet.def = atoi(tokens[4].c_str());
            pet.level = atoi(tokens[5].c_str());
            pet.exp = atoi(tokens[6].c_str());
            pet.exp_up = atoi(tokens[7].c_str());
            pet.attr_fire = atoi(tokens[8].c_str());
            pet.attr_water = atoi(tokens[9].c_str());
            pet.attr_wood = atoi(tokens[10].c_str());
            monster.push_back(pet);
        }
    }
    file.close();
}

// 顯示所有怪物
void FIGHT::show_all_monster()
{
    for (int i = 0; i < monster.size(); i++)
    {
        cout << "名稱:" << monster[i].name << endl;
        cout << "血量:" << monster[i].hp << endl;
        cout << "最大血量:" << monster[i].hp_max << endl;
        cout << "攻擊力:" << monster[i].atk << endl;
        cout << "防禦力:" << monster[i].def << endl;
        cout << "等級:" << monster[i].level << endl;
        cout << "經驗值:" << monster[i].exp << endl;
        cout << "升級所需經驗值:" << monster[i].exp_up << endl;
        cout << "火屬性值:" << monster[i].attr_fire << endl;
        cout << "水屬性值:" << monster[i].attr_water << endl;
        cout << "木屬性值:" << monster[i].attr_wood << endl;
        cout << endl;
    }
    system("pause");
}

// 戰鬥
role_data_init FIGHT::fight(role_data_init role_data, int &monster_l)
{
    srand(time(0));
    int l = 90;
    // for (int i = 0; i <= l; i++)
    // {
    //     system("cls");
    //     cout << string(l + 2, '#') << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << "#" << string(i, '*') << string(l - i, ' ') << "#" << endl;
    //     cout << string(l + 2, '#') << endl;
    //     Sleep(10);
    // }
    l = 100;
    int monster_index = rand() % monster.size();
    pet_init monster_data = monster[monster_index];
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        Sleep(200);
        cout << string(l + 2, '#') << endl;
        cout << string(40, ' ') << "遇到了" << monster_data.name << endl;
        cout << string(l + 2, '#') << endl;
        Sleep(200);
    }
    int option, skill_index;
    int player_damage = 0, monster_damage = 0;
    l = 40;
    do
    {
        system("cls");
        cout << string(50, '=') << "戰鬥進行中" << string(50, '=') << endl;
        cout << string(l, ' ') << "你的HP:" << role_data.role_hp << "/" << role_data.role_hp_max
             << " 你的MP:" << role_data.role_mp << "/" << role_data.role_mp_max << endl;
        cout << string(l, ' ') << monster_data.name << " Level:" << monster_data.level << " HP:" << monster_data.hp << endl;
        cout << string(l, ' ') << "1.攻擊 2.背包 3.逃跑 :";
        cin >> option;
        if (option == 1)
        {
            system("cls");
            // 我的攻擊
            //  適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
            cout << string(50, '=') << "戰鬥進行中" << string(50, '=') << endl;
            cout << string(l, ' ') << "你的HP:" << role_data.role_hp << "/" << role_data.role_hp_max
                 << " 你的MP:" << role_data.role_mp << "/" << role_data.role_mp_max << endl;
            cout << string(l, ' ') << monster_data.name << " Level:" << monster_data.level << " HP:" << monster_data.hp << endl;
            cout << string(l, ' ') << "選擇技能" << endl;
            for (int i = 0; i < role_data.role_skill_data.size(); i++)
            {
                cout << string(l, ' ') << i + 1 << "." << role_data.role_skill_data[i].name << " "
                     << "傷害:" << role_data.role_skill_data[i].damage << " "
                     << "消耗MP:" << role_data.role_skill_data[i].mp << endl;
            }
            cout << string(l, ' ') << "輸入技能編號:";
            cin >> skill_index;
            skill_index--;
            if (role_data.role_mp - role_data.role_skill_data[skill_index].mp >= 0)
            {
                system("cls");
                cout << string(l, ' ') << "你使用了" << role_data.role_skill_data[skill_index].name << endl;
                cout << string(l, ' ') << "技能傷害:" << role_data.role_skill_data[skill_index].damage << " 消耗MP:" << role_data.role_skill_data[skill_index].mp << endl;
                cout << string(l, ' ') << "角色傷害:" << role_data.role_atk << endl;
                cout << string(l, ' ') << "武器傷害:" << role_data.hand.damage << endl;
                player_damage = role_data.role_skill_data[skill_index].damage // 技能傷害
                                + role_data.role_atk                          // 角色傷害
                                + role_data.hand.damage;                      // 武器傷害
                cout << string(l, ' ') << "總傷害:" << player_damage << endl;
                cout << string(l, ' ') << monster_data.name << " HP:" << monster_data.hp << " 防禦值:" << monster_data.def << endl;
                system("pause");
                system("cls");
                if (player_damage < monster_data.def && rand() % 2 == 0)
                {
                    cout << string(l, ' ') << monster_data.name << " 閃避了攻擊" << endl;
                    player_damage = 1;
                    Sleep(600);
                }
                // monster_data.hp -= player_damage;
                monster_data.hp = (monster_data.hp < player_damage) ? 0 : monster_data.hp - player_damage;
                for (int i = 0; i < 5; i++) //
                {
                    system("cls");
                    Sleep(100);
                    cout << string(50, '=') << "攻擊成功" << string(50, '=') << endl;
                    cout << string(l, ' ') << monster_data.name << " 受到了" << player_damage << "點傷害" << endl;
                    role_data.role_mp = role_data.role_mp - role_data.role_skill_data[skill_index].mp;
                    if (role_data.role_mp < 0)
                    {
                        role_data.role_mp = 0;
                    }
                    Sleep(200);
                }
            }
            else
            {
                cout << string(l, ' ') << "MP不足" << endl;
                system("pause");
                continue;
            }
            // 怪物攻擊
            if (monster_data.hp > 0)
            {
                system("cls");
                cout << string(l, '=') << monster_data.name << " 攻擊" << string(l, '=') << endl;
                cout << string(l, ' ') << "你的HP:" << role_data.role_hp << "/" << role_data.role_hp_max
                     << " 你的MP:" << role_data.role_mp << "/" << role_data.role_mp_max << endl;
                cout << string(l, ' ') << monster_data.name << " Level:" << monster_data.level << "HP:" << monster_data.hp << endl;
                monster_damage = monster_data.atk + rand() % 10 * monster_data.level;
                cout << string(l, ' ') << monster_data.name << "攻擊:" << monster_damage << endl;
                system("pause");
                if (role_data.role_def > monster_damage)
                {
                    cout << string(l, ' ') << "你閃避了攻擊" << endl;
                    monster_damage = 1;
                    Sleep(600);
                }
                role_data.role_hp -= monster_damage;
                for (int i = 0; i < 5; i++) //
                {
                    system("cls");
                    Sleep(100);
                    cout << string(50, '=') << "受到攻擊" << string(50, '=') << endl;
                    cout << string(l, ' ') << "你擋下 " << role_data.role_def * 0.5 << "點傷害" << endl;
                    cout << string(l, ' ') << "你受到了" << monster_data.atk - role_data.role_def * 0.5 << "點傷害" << endl;
                    Sleep(200);
                }
                Sleep(1000);
                // system("pause");
                // if (role_data.role_hp <= 0)
                // {
                //     system("cls");
                //     cout << string(l, ' ') << "你已經死亡!" << endl;
                //     role_data.role_hp = role_data.role_hp_max;
                //     role_data.role_mp = role_data.role_mp_max;
                //     role_data.role_money = role_data.role_money / 2;
                //     role_data.role_x = 9;
                //     role_data.role_y = 6;
                //     role_data.role_area = 0;
                //     cout << string(l, ' ') << "HP:" << role_data.role_hp << endl;
                //     cout << string(l, ' ') << "重生!!" << endl;
                //     system("pause");
                //     monster_l = 1;
                //     return role_data;
                // }
                if (rand() % 2 == 0 && role_data.role_hp > 0)
                {
                    system("cls");
                    cout << string(l, '=') << "寵物攻擊" << string(l, '=') << endl;
                    cout << string(l, ' ') << "寵物Level:" << role_data.role_pet.pet_data[role_data.role_id].level
                         << " HP:" << role_data.role_pet.pet_data[role_data.role_id].hp << endl;
                    cout << string(l, ' ') << monster_data.name << " Level:" << monster_data.level << " HP:" << monster_data.hp << endl;
                    player_damage = role_data.role_pet.pet_data[role_data.role_id].atk + rand() % 10 * role_data.role_pet.pet_data[role_data.role_id].level;
                    cout << string(l, ' ') << "寵物攻擊:" << player_damage << endl;
                    monster_data.hp = (monster_data.hp < player_damage) ? 0 : monster_data.hp - player_damage;
                    // system("pause");
                    Sleep(1000);
                    system("cls");
                }
            }
        }
        else if (option == 2) // 背包
        {
            string move_input;
            system("cls"); // 清除畫面
            // login.ShowRoleBag(player.name, player.id); // 顯示角色背包
            cout << string(50, '=') << " 角色狀態 " << string(50, '=') << endl;
            cout << string(5, ' ') << "Level:" << role_data.role_level << " "
                 << "角色血量:" << role_data.role_hp << "/" << role_data.role_hp_max << " "
                 << "角色魔法值:" << role_data.role_mp << "/" << role_data.role_mp_max << " "
                 << "金幣:" << role_data.role_money << endl;
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
            cout << string(30, ' ') << "輸入編號可使用物品:";
            cin >> move_input;
            if (move_input != "b")
            {
                // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
                int item_id = stoi(move_input);
                cout << string(30, ' ') << "使用物品:" << role_data.bag[item_id].name << endl;
                cout << string(30, ' ') << "適用職業:" << role_data.bag[item_id].job << endl;
                // cout << (role_data.bag[item_id].job == "all") << endl;
                if (role_data.bag[item_id].job == role_data.role_job || role_data.bag[item_id].job == "all")
                {
                    if (role_data.bag[item_id].part == "all") // 使用物品
                    {
                        role_data.role_hp += role_data.bag[item_id].recovery; // 回復血量
                        if (role_data.role_hp > role_data.role_hp_max)
                        {
                            role_data.role_hp = role_data.role_hp_max;
                            cout << string(30, ' ') << "血量已滿!" << endl;
                        }
                        else
                        {
                            cout << string(30, ' ') << "回復" << role_data.bag[item_id].recovery << "血量" << endl;
                        }
                        role_data.role_mp += role_data.bag[item_id].recovery; // 回復魔法值
                        if (role_data.role_mp > role_data.role_mp_max)
                        {
                            role_data.role_mp = role_data.role_mp_max;
                            cout << string(20, ' ') << "魔法值已滿!" << endl;
                        }
                        else
                        {
                            cout << string(20, ' ') << "回復" << role_data.bag[item_id].recovery << "魔法值" << endl;
                        }
                        if (role_data.bag[item_id].damage > 0) // 增加攻擊力
                        {
                            cout << string(20, ' ') << "增加攻擊力:" << role_data.bag[item_id].damage << "->" << role_data.role_atk + role_data.bag[item_id].damage << endl;
                            role_data.role_atk += role_data.bag[item_id].damage; // 增加攻擊力
                        }
                        if (role_data.bag[item_id].defense > 0) // 增加防禦力
                        {
                            cout << string(20, ' ') << "增加防禦力:" << role_data.bag[item_id].defense << "->" << role_data.role_def + role_data.bag[item_id].defense << endl;
                            role_data.role_def += role_data.bag[item_id].defense; // 增加防禦力
                        }

                        role_data.bag.erase(role_data.bag.begin() + item_id);
                    }
                    else if (role_data.bag[item_id].part == "head")
                    {
                        cout << string(20, ' ') << "更換頭部裝備";
                        cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                        item_init temp = role_data.head;
                        role_data.head = role_data.bag[item_id];
                        role_data.bag[item_id] = temp;
                    }
                    else if (role_data.bag[item_id].part == "body")
                    {
                        cout << string(20, ' ') << "更換身體裝備";
                        cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                        item_init temp = role_data.body;
                        role_data.body = role_data.bag[item_id];
                        role_data.bag[item_id] = temp;
                    }
                    else if (role_data.bag[item_id].part == "hand")
                    {
                        cout << string(20, ' ') << "更換手部裝備";
                        cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                        item_init temp = role_data.hand;
                        role_data.hand = role_data.bag[item_id];
                        role_data.bag[item_id] = temp;
                    }
                    else if (role_data.bag[item_id].part == "foot")
                    {
                        cout << string(20, ' ') << "更換腳部裝備";
                        cout << role_data.hand.name << "->" << role_data.bag[item_id].name << endl;
                        item_init temp = role_data.foot;
                        role_data.foot = role_data.bag[item_id];
                        role_data.bag[item_id] = temp;
                    }
                }
                else
                {
                    cout << "職業不符合!" << endl;
                    system("pause");
                }
            }
            system("pause");
        }

        if (monster_data.hp <= 0)
        {
            system("cls");
            cout << string(l, ' ') << monster_data.name << " 已經被打敗!" << endl;
            cout << string(l, ' ') << "獲得經驗值:" << monster_data.exp << " "
                 << role_data.role_exp << "->" << role_data.role_exp + monster_data.exp << endl;
            role_data.role_exp += monster_data.exp;
            cout << string(l, ' ') << "獲得金幣:" << monster_data.level * 10 << " "
                 << role_data.role_money << "->" << role_data.role_money + monster_data.level * 10 << endl;
            role_data.role_money += monster_data.level * 10;
            if (1)
            {
                cout << string(l, ' ') << "寵物獲得經驗值:" << monster_data.exp * 0.8 << " "
                     << role_data.role_pet.pet_data[role_data.role_id].exp << "->" << role_data.role_pet.pet_data[role_data.role_id].exp + monster_data.exp * 0.8 << endl;
                role_data.role_pet.pet_data[role_data.role_id].exp += monster_data.exp;
            }
            if (1)
            {
                cout << string(l, ' ') << "獲得" << monster_data.name << endl;
                monster_data.hp = monster_data.hp_max;
                pet_init new_pet;
                new_pet.id = role_data.role_pet.pet_data.size() + 1;
                new_pet.name = monster_data.name;
                new_pet.hp = monster_data.hp;
                new_pet.hp_max = monster_data.hp_max;
                new_pet.atk = monster_data.atk;
                new_pet.def = monster_data.def;
                new_pet.level = monster_data.level;
                new_pet.exp = monster_data.exp;
                new_pet.exp_up = monster_data.exp_up;
                new_pet.attr_fire = monster_data.attr_fire;
                new_pet.attr_water = monster_data.attr_water;
                new_pet.attr_wood = monster_data.attr_wood;
                role_data.role_pet.pet_data.push_back(new_pet);
            }
            system("pause");
            monster_l = 0;
            return role_data;
        }
        else if (role_data.role_hp <= 0)
        {
            // system("cls");
            // cout << string(l, ' ') << "你已經死亡!" << endl;
            role_data.role_hp = 0;
            // system("pause");
            monster_l = 1;
            return role_data;
        }
    } while (option != 3);

    monster_l = 1;
    return role_data;
}
