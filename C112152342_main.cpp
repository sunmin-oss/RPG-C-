#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>
#include <cmath>

#include "C112152342_Login.h" //登入功能
#include "C112152342_map.h"   //地圖功能
#include "C112152342_shop.h"  //商店功能
#include "C112152342_logic.h" //邏輯功能
#include "C112152342_fight.h"
using namespace std;
/*
修復資料錯誤
*/
int main()
{
    bool game_c = true;
    SetConsoleOutputCP(CP_UTF8);
    ifstream file("dungeon.txt");
    if (!file.is_open())
    {
        cout << "無法開啟檔案: " << "dungeon.txt" << endl;
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        Sleep(3000);
    }
    file.close();
    while (game_c)
    {
        GameLogin login; // 登入功能
        login.ReadUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
        role_data_init role_data; // 使用者角色資料
        struct player_init
        {
            string name;
            int id;
            role_data_init role_data;
        };
        player_init player;
        /*
        login.ShowAllUserData();
        login.ShowUserInfo("sunmin");//顯示使用者資訊
        login.ShowRoleSkill("sunmin", 1);//顯示角色技能
        login.ShowRolePet("sunmin", 1);//顯示角色寵物
        login.ShowRoleBag("sunmin", 1);//顯示角色背包
        login.CreateRole("sunmin");//創建角色
        login.DeleteRole("tt", 1);//刪除角色
        login.DeleteAccount("sss", "123456");//刪除帳號
        login.CreateAccount("sunmin", "123456");//創建帳號
        login.ForgetPassword("sunmin");//忘記密碼
        login.Login("sunmin", "123456");//登入
        login.ModifyUserData("sunmin", "sunmin", "123456");//修改使用者資料
        role_data_init role_data = login.GetRoleData("sunmin", 1);//傳出使用者角色資料
        login.CreateAccount("sss", "123456");//創建帳號
        login.ShowAllUserData();
        cout<<role_data.hand.name<<endl;
        cout<<role_data.body.name<<endl;
        cout<<role_data.foot.name<<endl;
        cout<<role_data.head.name<<endl;
        role_data.head.price = 900;
        login.ModifyRoleData("sunmin", 1, role_data);//修改角色資料
        */

        // 載入地圖資料
        // 載入地圖資料
        vector<map_init> map_data; // 1. 初始化地圖資料
        GameMap map(map_data);     // 2. 建立GameMap物件並讀取地圖
        map.readFile_map("map.txt", map_data);
        int x = 5, y = 5, now_map = 0, role_num; // 3. 玩家初始位置
        string move_input;
        // 草原     城堡      神廟   沙漠
        int monster_l[4][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        // int crates_l[2] = {1, 1};//寶箱
        // 載入商店資料
        Shop shop(login);
        shop.LoadItems("shop.txt");
        shop.LoadSkill("skill.txt");
        // shop.ShowAllSkill();
        // system("pause");
        // shop.ShowItems(5);
        // system("pause");

        // 載入邏輯資料
        logic logic(login);

        // 載入戰鬥資料
        FIGHT fight(login);
        fight.Read_monster_Data("monster.txt");
        // fight.show_all_monster();

        bool game_start = false;
        while (true) // 遊戲登入
        {
            system("cls"); // 清除畫面
            string username, password;
            int option;
            cout << string(40, '-') << endl;
            cout << string(15, ' ') << left << setw(20) << "1.登入" << endl;
            cout << string(15, ' ') << left << setw(20) << "2.忘記密碼" << endl;
            cout << string(15, ' ') << left << setw(20) << "3.創建帳號" << endl;
            cout << string(15, ' ') << left << setw(20) << "4.刪除帳號" << endl;
            cout << string(15, ' ') << left << setw(20) << "5.管理員登入" << endl;
            cout << string(40, '-') << endl;
            cout << string(15, ' ') << left << "請輸入選項:";
            cin >> option;
            if (option == 1) // 登入
            {
                system("cls"); // 清除畫面
                cout << string(25, '=') << " 登入 " << string(25, '=') << endl;
                cout << string(15, ' ') << left << setw(20) << "請輸入帳號:";
                cin >> username;
                cout << string(15, ' ') << left << setw(20) << "請輸入密碼:";
                cin >> password;
                system("cls");                       // 清除畫面
                if (login.Login(username, password)) // 登入成功
                {
                    cout << string(25, '=') << " 登入成功 " << string(25, '=') << endl;
                    cout << string(25, ' ') << "1.繼續遊戲" << endl;
                    cout << string(25, ' ') << "2.創建新角色" << endl;
                    cout << string(25, ' ') << "3.刪除角色" << endl;
                    int option;
                    cout << string(25, ' ') << "請輸入選項:";
                    cin >> option;
                    if (option == 1)
                    {
                        login.ShowUserInfo(username); // 顯示使用者資訊
                        int role;
                        cout << string(20, ' ') << setw(20) << "請選擇角色:";
                        cin >> role;
                        role_data = login.GetRoleData(username, role); // 傳出使用者角色資料
                        player.name = username;
                        player.id = role;
                        player.role_data = role_data;
                        x = player.role_data.role_x;
                        y = player.role_data.role_y;
                        now_map = player.role_data.role_area;
                        for (int i = 0; i < 101; i++)
                        {
                            system("cls"); // 清除畫面
                            cout << string(20, ' ') << left << setw(20) << "登入成功!" << endl;
                            cout << string(20, '-') << left << "資料載入中..." << string(20, '-') << endl;
                            cout << string(i / 2, '#') << " " << i << "% ";
                            if (i > 80)
                                Sleep(10);
                            else if (rand() % 5 == 0)
                                Sleep(60);
                            else
                                Sleep(10);
                        }
                        cout << endl;
                        system("cls"); // 清除畫面
                        cout << string(20, ' ') << "載入完成" << endl;
                        Sleep(300);
                        game_start = true;
                        break;
                    }
                    else if (option == 2)
                    {
                        system("cls"); // 清除畫面
                        login.CreateRole(username);
                        login.ShowUserInfo(username); // 顯示使用者資訊
                        int role;
                        cout << string(20, ' ') << setw(20) << "請選擇角色:";
                        cin >> role;
                        role_data = login.GetRoleData(username, role); // 傳出使用者角色資料
                        player.name = username;
                        player.id = role;
                        player.role_data = role_data;
                        for (int i = 0; i < 101; i++)
                        {
                            system("cls"); // 清除畫面
                            cout << string(20, ' ') << left << setw(20) << "登入成功!" << endl;
                            cout << string(20, '-') << left << "資料載入中..." << string(20, '-') << endl;
                            cout << string(i / 2, '#') << " " << i << "% ";
                            if (i > 80)
                                Sleep(10);
                            else if (rand() % 5 == 0)
                                Sleep(60);
                            else
                                Sleep(10);
                        }
                        cout << endl;
                        system("cls"); // 清除畫面
                        cout << string(20, ' ') << "載入完成" << endl;
                        Sleep(300);
                        game_start = true;
                        break;
                    }
                    else if (option == 3)
                    {
                        system("cls");                // 清除畫面
                        login.ShowUserInfo(username); // 顯示使用者資訊
                        int role;
                        cout << string(20, ' ') << setw(20) << "請選擇角色:";
                        cin >> role;
                        login.DeleteRole(username, role);
                    }
                }
                else
                {
                    cout << string(15, ' ') << left << setw(20) << "帳號或密碼錯誤!" << endl;
                    system("pause");
                }
            }
            else if (option == 2) // 忘記密碼
            {
                system("cls"); // 清除畫面
                cout << string(15, ' ') << left << setw(20) << "請輸入管理員帳號:";
                cin >> username;
                cout << string(15, ' ') << left << setw(20) << "請輸入管理員密碼:";
                cin >> password;
                if (username != "admin" || password != "admin")
                {
                    cout << string(15, ' ') << left << setw(20) << "帳號或密碼錯誤!" << endl;
                    continue;
                }
                cout << string(15, ' ') << left << setw(20) << "請輸入帳號:";
                cin >> username;
                login.ForgetPassword(username);
                system("pause");
            }
            else if (option == 3) // 創建帳號
            {
                system("cls"); // 清除畫面
                cout << string(15, ' ') << left << setw(20) << "請輸入帳號:";
                cin >> username;
                cout << string(15, ' ') << left << setw(20) << "請輸入密碼:";
                cin >> password;
                if (login.CreateAccount(username, password)) // 創建帳號
                {
                    role_data = login.GetRoleData(username, 1); // 傳出使用者角色資料
                    player.name = username;
                    player.id = 1;
                    player.role_data = role_data;
                    for (int i = 0; i < 101; i++)
                    {
                        system("cls"); // 清除畫面
                        cout << string(20, ' ') << left << setw(20) << "登入成功!" << endl;
                        cout << string(20, '-') << left << "資料載入中..." << string(20, '-') << endl;
                        cout << string(i / 2, '#') << " " << i << "% ";
                        if (i > 80)
                            Sleep(10);
                        else if (rand() % 5 == 0)
                            Sleep(60);
                        else
                            Sleep(10);
                    }
                    cout << endl;
                    system("cls"); // 清除畫面
                    cout << string(20, ' ') << "載入完成" << endl;
                    Sleep(300);
                    game_start = true;
                    break;
                }
                else
                {
                    cout << string(15, ' ') << left << setw(20) << "帳號已存在!" << endl;
                }
            }
            else if (option == 4) // 刪除帳號
            {
                system("cls"); // 清除畫面
                cout << string(15, ' ') << left << setw(20) << "請輸入帳號:";
                cin >> username;
                cout << string(15, ' ') << left << setw(20) << "請輸入密碼:";
                cin >> password;
                login.DeleteAccount(username, password);
            }
            else if (option == 5) // 管理員登入
            {
                system("cls"); // 清除畫面
                cout << string(15, ' ') << left << setw(20) << "請輸入帳號:";
                cin >> username;
                cout << string(15, ' ') << left << setw(20) << "請輸入密碼:";
                cin >> password;
                if (username == "admin" && password == "admin")
                {
                    cout << string(15, ' ') << left << setw(20) << "管理員登入成功!" << endl;
                    cout << string(15, ' ') << left << setw(20) << "1.查看所有使用者資料" << endl;
                    cout << string(15, ' ') << left << setw(20) << "2.查看所有技能" << endl;
                    cout << string(15, ' ') << left << setw(20) << "3.查看所有商品" << endl;
                    cout << string(15, ' ') << left << setw(20) << "4.查看所有怪物" << endl;

                    cout << string(15, ' ') << left << setw(20) << "7.離開" << endl;
                    cout << string(15, ' ') << left << setw(20) << "請輸入選項:";
                    cin >> option;
                    if (option == 1)
                    {
                        login.ShowAllUserData();
                        system("pause");
                    }
                    else if (option == 2)
                    {
                        shop.ShowAllSkill();
                        system("pause");
                    }
                    else if (option == 3)
                    {
                        shop.ShowAllItems();
                        system("pause");
                    }
                    else if (option == 4)
                    {
                        fight.show_all_monster();
                        system("pause");
                    }
                    else if (option == 7)
                    {
                        break;
                    }
                }
                else
                {
                    cout << string(15, ' ') << left << setw(20) << "帳號或密碼錯誤!" << endl;
                }
            }
            else
            {
                cout << string(15, ' ') << left << setw(20) << "輸入錯誤!" << endl;
            }
        }
        // game_start = true;
        int m1 = 0, m2 = 0, m3 = 0;
        int move_legal;
        while (game_start) // 遊戲開始
        {
            // 顯示當前地圖
            if (now_map > 1)
                m1 = monster_l[now_map - 2][0], m2 = monster_l[now_map - 2][1], m3 = monster_l[now_map - 2][2];
            else
                m1 = m2 = m3 = 0;
            map.show_map(now_map, x, y, m1, m2, m3);
            // cout <<now_map<<endl;
            // cout << monster_l[0][0] << monster_l[0][1] << monster_l[0][2] << endl;
            // cout << monster_l[1][0] << monster_l[1][1] << monster_l[1][2] << endl;
            // cout << monster_l[2][0] << monster_l[2][1] << monster_l[2][2] << endl;
            // cout << monster_l[3][0] << monster_l[3][1] << monster_l[3][2] << endl;
            // 顯示目前座標
            cout << "現在位置: (" << x << "," << y << ")" << endl;
            cout << "請輸入移動方向 (w/s/a/d), p寵物, b背包/狀態, m地圖, e顯示角色狀態, u升級, k技能列表, q離開: ";
            cin >> move_input;

            // 判斷移動方向
            int new_x = x, new_y = y;
            if (move_input == "w")
                new_y--;
            else if (move_input == "s")
                new_y++;
            else if (move_input == "a")
                new_x--;
            else if (move_input == "d")
                new_x++;
            else if (move_input == "e") // 顯示角色狀態
            {
                system("cls");                   // 清除畫面
                login.ShowUserInfo(player.name); // 顯示使用者資訊
                cout << "e離開:";
                cin >> move_input;
                while (move_input != "e")
                    cin >> move_input;
            }
            else if (move_input == "b") // 背包
            {
                player.role_data = logic.Use_items(player.role_data);
                login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                /*
                do
                {
                    system("cls"); // 清除畫面
                    // login.ShowRoleBag(player.name, player.id); // 顯示角色背包
                    cout << string(50, '=') << " 角色狀態 " << string(50, '=') << endl;
                    cout <<string(5, ' ')<< "角色血量:" << player.role_data.role_hp << "/" << player.role_data.role_hp_max << " "
                         << "角色魔法值:" << player.role_data.role_mp << "/" << player.role_data.role_mp_max <<" "
                         <<"金幣:"<<player.role_data.role_money<< endl;
                    cout << string(50, '=') << " 角色裝備 " << string(50, '=') << endl;
                    cout << string(5, ' ')<< "頭部 " << "名稱:" << player.role_data.head.name << " "
                         << "傷害值:" << player.role_data.head.damage << " "
                         << "防禦力:" << player.role_data.head.defense << " "
                         << "回復值:" << player.role_data.head.recovery << " "
                         << "火屬性:" << player.role_data.head.fire_attr << " "
                         << "水屬性:" << player.role_data.head.water_attr << " "
                         << "木屬性:" << player.role_data.head.wood_attr << " "
                         << "價格:" << player.role_data.head.price << endl;
                    cout << string(5, ' ')<< "身體 " << "名稱:" << player.role_data.body.name << " "
                         << "傷害值:" << player.role_data.body.damage << " "
                         << "防禦力:" << player.role_data.body.defense << " "
                         << "回復值:" << player.role_data.body.recovery << " "
                         << "火屬性:" << player.role_data.body.fire_attr << " "
                         << "水屬性:" << player.role_data.body.water_attr << " "
                         << "木屬性:" << player.role_data.body.wood_attr << " "
                         << "價格:" << player.role_data.body.price << endl;
                    cout << string(5, ' ')<< "手部 " << "名稱:" << player.role_data.hand.name << " "
                         << "傷害值:" << player.role_data.hand.damage << " "
                         << "防禦力:" << player.role_data.hand.defense << " "
                         << "回復值:" << player.role_data.hand.recovery << " "
                         << "火屬性:" << player.role_data.hand.fire_attr << " "
                         << "水屬性:" << player.role_data.hand.water_attr << " "
                         << "木屬性:" << player.role_data.hand.wood_attr << " "
                         << "價格:" << player.role_data.hand.price << endl;
                    cout << string(5, ' ')<< "腳部 " << "名稱:" << player.role_data.foot.name << " "
                         << "傷害值:" << player.role_data.foot.damage << " "
                         << "防禦力:" << player.role_data.foot.defense << " " << "回復值:" << player.role_data.foot.recovery << " "
                         << "火屬性:" << player.role_data.foot.fire_attr << " " << "水屬性:" << player.role_data.foot.water_attr << " "
                          << "木屬性:" << player.role_data.foot.wood_attr << " " << "價格:" << player.role_data.foot.price << endl;

                    cout << string(50, '=') << " 角色背包 " << string(50, '=') << endl;
                    for (int i = 0; i < player.role_data.bag.size(); i++)
                    {
                        cout << string(2, ' ')<< left << "編號:" << i << " "
                             << left << "適用職業:" << player.role_data.bag[i].job << " "
                             << left << "類型:" << player.role_data.bag[i].type << " "
                             << left << "名稱:" << player.role_data.bag[i].name << " "
                             << left << "部位:" << player.role_data.bag[i].part << " "
                             << left << "傷害:" << player.role_data.bag[i].damage << " "
                             << left << "防禦:" << player.role_data.bag[i].defense << " "
                             << left << "回復:" << player.role_data.bag[i].recovery << " "
                             << left << "火屬性:" << player.role_data.bag[i].fire_attr << " "
                             << left << "水屬性:" << player.role_data.bag[i].water_attr << " "
                             << left << "木屬性:" << player.role_data.bag[i].wood_attr << " "
                             << left << "價格:" << player.role_data.bag[i].price << endl;
                    }
                    cout << "b背包離開背包 輸入編號可使用物品:";
                    cin >> move_input;

                } while (move_input != "b");*/
            }
            else if (move_input == "p") // 寵物
            {
                // 寵物編號|寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
                // int now_pet_id = player.role_data.role_pet_id;
                // cout<<"當前所使用寵物"<<player.role_data.role_pet.pet_data[now_pet_id-1].name<<endl;
                // for (int i = 0; i <player.role_data.role_pet.pet_data.size(); i++)
                // {
                //     cout << string(2, ' ') << left
                //          << "編號:" << i << " " << player.role_data.role_pet.pet_data[i].id
                //          << "名稱:" << player.role_data.role_pet.pet_data[i].name
                //          << "血量:" << player.role_data.role_pet.pet_data[i].hp << "/" << player.role_data.role_pet.pet_data[i].hp_max
                //          << "攻擊力:" << player.role_data.role_pet.pet_data[i].atk
                //          << "防禦力:" << player.role_data.role_pet.pet_data[i].def
                //          << "等級:" << player.role_data.role_pet.pet_data[i].level
                //          << "經驗值:" << player.role_data.role_pet.pet_data[i].exp
                //          << "升級所需經驗值:" << player.role_data.role_pet.pet_data[i].exp_up
                //          << "火屬性值:" << player.role_data.role_pet.pet_data[i].attr_fire
                //          << "水屬性值:" << player.role_data.role_pet.pet_data[i].attr_water
                //          << "木屬性值:" << player.role_data.role_pet.pet_data[i].attr_wood
                //          << endl;
                // }
                player.role_data = logic.Use_pet(player.role_data);
                login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                // system("pause");
            }
            else if (move_input == "m") // 小地圖 傳送
            {
                system("cls"); // 清除畫面
                map.showmap_name(now_map);
                map.show_map(6, 0, 0, 0, 0, 0);
                cout << "m地圖離開地圖 t可進行傳送:";
                cin >> move_input;
                if (move_input == "t")
                {
                    cout << "請輸入地圖名稱(0 初始城鎮 1 市集 2 草原 3 城堡 4 神廟 5 沙漠):";
                    cin >> move_input;
                    if (move_input == "0")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 0;
                    }
                    else if (move_input == "1")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 1;
                    }
                    else if (move_input == "2")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 2;
                    }
                    else if (move_input == "3")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 3;
                    }
                    else if (move_input == "4")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 4;
                    }
                    else if (move_input == "5")
                    {
                        new_x = 9;
                        new_y = 6;
                        now_map = 5;
                    }
                }
                else if (move_input == "m")
                {
                    while (move_input != "m")
                        cin >> move_input;
                }
            }
            else if (move_input == "k") // 技能列表
            {
                system("cls");                               // 清除畫面
                login.ShowRoleSkill(player.name, player.id); // 顯示角色技能
                cout << "k離開:";
                cin >> move_input;
                while (move_input != "k")
                    cin >> move_input;
            }
            else if (move_input == "u") // 升級
            {
                system("cls"); // 清除畫面
                player.role_data = logic.Use_Up(player.role_data);
                login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                // system("pause");
            }
            else if (move_input == "q")
            {
                player.role_data.role_x = x;
                player.role_data.role_y = y;
                player.role_data.role_area = now_map;
                login.ModifyRoleData(player.name, player.id, player.role_data);
                login.SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
                cout << "遊戲已儲存" << endl;
                cout << "是否回到登入畫面 1.是 2.否:";
                int option;
                cin >> option;
                if (option == 1)
                {
                    game_c = true;
                    break;
                }
                else
                {
                    game_c = false;
                    break;
                }
            }
            // 檢查移動是否合法
            move_legal = map.move_player(new_x, new_y, now_map, m1, m2, m3);
            if (move_legal != 0)
            {
                // 移動成功
                system("cls");       // 清除畫面
                if (move_legal == 1) // 可通行
                {
                    x = new_x;
                    y = new_y;
                    // cout << "移動成功!" << endl;
                }
                else if (move_legal == 2) // 門
                {
                    if (now_map == 0) // 初始城鎮
                    {
                        x = new_x;
                        y = new_y;
                        if (x == 19 && y == 6)
                        {
                            now_map = 1; // 市集
                            x = 1;
                            y = 6;
                        }
                        else if (x == 0 && y == 6)
                        {
                            now_map = 2; // 草原
                            x = 18;
                            y = 6;
                        }
                        else if (x == 9 && y == 10)
                        {
                            now_map = 3; // 城堡
                            x = 9;
                            y = 2;
                        }
                        else if (x == 9 && y == 1)
                        {
                            now_map = 5; // 沙漠
                            x = 9;
                            y = 9;
                        }
                    }
                    else if (now_map == 1) // 市集
                    {
                        x = new_x;
                        y = new_y;
                        if (x == 0 && y == 6)
                        {
                            now_map = 0; // 初始城鎮
                            x = 18;
                            y = 6;
                        }
                    }
                    else if (now_map == 2) // 草原
                    {
                        monster_l[now_map - 2][0] = 1;
                        monster_l[now_map - 2][1] = 1;
                        monster_l[now_map - 2][2] = 1;
                        // cout << "刷新怪物" << endl;
                        x = new_x;
                        y = new_y;
                        if (x == 19 && y == 6)
                        {
                            now_map = 0; // 初始城鎮
                            x = 1;
                            y = 6;
                        }
                        else if (x == 0 && y == 6)
                        {
                            now_map = 4; // 神廟
                            x = 18;
                            y = 6;
                        }
                    }
                    else if (now_map == 3) // 城堡
                    {
                        monster_l[now_map - 2][0] = 1;
                        monster_l[now_map - 2][1] = 1;
                        monster_l[now_map - 2][2] = 1;
                        // cout << "刷新怪物" << endl;
                        x = new_x;
                        y = new_y;
                        if (x == 9 && y == 1)
                        {
                            now_map = 0; // 初始城鎮
                            x = 9;
                            y = 9;
                        }
                    }
                    else if (now_map == 4) // 神廟
                    {
                        monster_l[now_map - 2][0] = 1;
                        monster_l[now_map - 2][1] = 1;
                        monster_l[now_map - 2][2] = 1;
                        // cout<<"刷新怪物"<<endl;
                        x = new_x;
                        y = new_y;
                        if (x == 19 && y == 6)
                        {
                            now_map = 2; // 草原
                            x = 1;
                            y = 6;
                        }
                    }
                    else if (now_map == 5) // 沙漠
                    {
                        monster_l[now_map - 2][0] = 1;
                        monster_l[now_map - 2][1] = 1;
                        monster_l[now_map - 2][2] = 1;
                        // cout << "刷新怪物" << endl;
                        x = new_x;
                        y = new_y;
                        if (x == 9 && y == 10)
                        {
                            now_map = 0; // 初始城鎮
                            x = 9;
                            y = 2;
                        }
                    }
                }
                else if (move_legal == 3) // 商人
                {
                    // cout << "商人" << endl;
                    if (move_input == "w")
                        new_y++;
                    else if (move_input == "s")
                        new_y--;
                    else if (move_input == "a")
                        new_x++;
                    else if (move_input == "d")
                        new_x--;
                    x = new_x;
                    y = new_y;
                    system("cls");
                    cout << "遇到商人 1.購買 2.出售 3.離開" << endl;
                    cout << "請輸入選項:";
                    int option;
                    cin >> option;
                    if (option == 1)
                    {

                        player.role_data = shop.BuyItem(player.role_data);
                        login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                        system("cls");
                    }
                    else if (option == 2)
                    {
                        player.role_data = shop.SellItem(player.role_data);
                        login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                        system("cls");
                    }
                    else
                    {
                        cout << "離開" << endl;
                    }
                }
                else if (move_legal == 4) // 寶箱
                {
                    cout << string(50, ' ') << "寶箱" << endl;
                    if (move_input == "w")
                        new_y++;
                    else if (move_input == "s")
                        new_y--;
                    else if (move_input == "a")
                        new_x++;
                    else if (move_input == "d")
                        new_x--;
                    x = new_x;
                    y = new_y;
                    cout << string(50, ' ') << "是否開啟寶箱?(y/n)" << endl;
                    cout << string(50, ' ') << "請輸入選項:";
                    string option;
                    cin >> option;
                    if (option == "y")
                    {
                        player.role_data = shop.crates(player.role_data);
                        system("pause");
                        login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                    }
                    else
                    {
                        cout << "不開啟" << endl;
                    }
                    system("cls");
                }
                else if (move_legal == 5) // 怪物
                {
                    x = new_x;
                    y = new_y;
                    if (move_input == "w")
                        new_y++;
                    else if (move_input == "s")
                        new_y--;
                    else if (move_input == "a")
                        new_x++;
                    else if (move_input == "d")
                        new_x--;
                    cout << "怪物" << endl;
                    system("cls"); // 清除畫面
                    // map.show_map(now_map, x, y, monster_location[now_map - 2][0], monster_location[now_map - 2][1], monster_location[now_map - 2][2]);
                    cout << string(20, '=') << "遇到怪物" << string(20, '=') << endl;
                    cout << string(20, ' ') << "1.戰鬥" << endl;
                    cout << string(20, ' ') << "2.逃跑" << endl;
                    cout << string(20, ' ') << "請輸入選項:";
                    // cout << "x" << x << "y" << y << endl;
                    int option;
                    cin >> option;
                    if (option == 1) // 戰鬥
                    {
                        system("cls"); // 清除畫面
                        if (y == 3 && x == 3)
                        {
                            player.role_data = fight.fight(player.role_data, monster_l[now_map - 2][0]);
                            login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                            if (player.role_data.role_hp <= 0)                              // 死亡
                            {
                                system("cls");
                                cout << string(50, ' ') << "你已經死亡" << endl;
                                player.role_data.role_hp = player.role_data.role_hp_max;
                                player.role_data.role_mp = player.role_data.role_mp_max;
                                player.role_data.role_money = player.role_data.role_money / 2;
                                player.role_data.role_x = 9;
                                player.role_data.role_y = 6;
                                player.role_data.role_area = 0;
                                cout << string(50, ' ') << "HP:" << role_data.role_hp << endl;
                                cout << string(50, ' ') << "重生!!" << endl;
                                x = player.role_data.role_x;
                                y = player.role_data.role_y;
                                now_map = player.role_data.role_area;
                                // system("pause");
                                Sleep(1000);
                                system("cls");
                                continue;
                            }
                             else if( monster_l[now_map - 2][0] == 0)
                            {
                                cout << string(100, '=') << endl;
                                cout << string(50, ' ') << "獲得寶箱!!" << endl;
                                cout << string(100, '=') << endl;
                                Sleep(1000);
                                player.role_data = shop.crates(player.role_data);
                                if (player.role_data.role_exp >= player.role_data.role_exp_up) // 升級
                                {
                                    player.role_data.role_exp = 0;                           // 經驗值歸零
                                    player.role_data.role_exp_up += 10;                      // 升級所需經驗值增加
                                    player.role_data.role_level += 1;                        // 等級增加
                                    player.role_data.role_hp_max += 10;                      // 血量上限增加
                                    player.role_data.role_hp = player.role_data.role_hp_max; // 血量回滿
                                    player.role_data.role_mp_max += 10;                      // 魔法值上限增加
                                    player.role_data.role_mp = player.role_data.role_mp_max; // 魔法值回滿
                                    player.role_data.role_money += 100;                      // 獲得金幣
                                    player.role_data.role_atk += 5;                          // 攻擊力增加
                                    player.role_data.role_def += 5;                          // 防禦力增加
                                    player.role_data.role_skill += 10;                       // 技能點數增加
                                    player.role_data.role_attr += 5;                         // 屬性點數增加
                                    cout << string(30, ' ') << "升級" << endl;
                                    cout << string(30, ' ') << "等級+1:" << player.role_data.role_level << endl;
                                    cout << string(30, ' ') << "血量+10:" << player.role_data.role_hp_max << endl;
                                    cout << string(30, ' ') << "魔法值+10:" << player.role_data.role_mp_max << endl;
                                    cout << string(30, ' ') << "金幣+100:" << player.role_data.role_money << endl;
                                    cout << string(30, ' ') << "攻擊力+5:" << player.role_data.role_atk << endl;
                                    cout << string(30, ' ') << "防禦力+5:" << player.role_data.role_def << endl;
                                    cout << string(30, ' ') << "技能點數+10:" << player.role_data.role_skill << endl;
                                    cout << string(30, ' ') << "屬性點數+5:" << player.role_data.role_attr << endl;
                                    system("pause");
                                }
                                for (int i = 0; i < player.role_data.role_pet.pet_data.size(); i++) // 寵物升級
                                {
                                    if (player.role_data.role_pet.pet_data[i].exp >= player.role_data.role_pet.pet_data[i].exp_up)
                                    {
                                        cout << string(30, ' ') << "寵物" << player.role_data.role_pet.pet_data[i].name << "升級" << endl;
                                        player.role_data.role_pet.pet_data[i].exp = 0;                                           // 經驗值歸零
                                        player.role_data.role_pet.pet_data[i].exp_up += 10;                                      // 升級所需經驗值增加
                                        player.role_data.role_pet.pet_data[i].level += 1;                                        // 等級增加
                                        player.role_data.role_pet.pet_data[i].hp_max += 10;                                      // 血量上限增加
                                        player.role_data.role_pet.pet_data[i].hp = player.role_data.role_pet.pet_data[i].hp_max; // 血量回滿
                                        player.role_data.role_pet.pet_data[i].atk += 5;                                          // 攻擊力增加
                                        player.role_data.role_pet.pet_data[i].def += 5;                                          // 防禦力增加
                                        player.role_data.role_pet.pet_data[i].attr_fire += 5;                                    // 火屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_water += 5;                                   // 水屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_wood += 5;                                    // 木屬性增加
                                    }
                                }
                                // system("pause");
                            }
                        }
                        else if (y == 8 && x == 16)
                        {
                            // cout << "怪物" << y << " " << x << endl;
                            player.role_data = fight.fight(player.role_data, monster_l[now_map - 2][1]);
                            login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                            if (player.role_data.role_hp <= 0)                              // 死亡
                            {
                                system("cls");
                                cout << string(50, ' ') << "你已經死亡" << endl;
                                player.role_data.role_hp = player.role_data.role_hp_max;
                                player.role_data.role_mp = player.role_data.role_mp_max;
                                player.role_data.role_money = player.role_data.role_money / 2;
                                player.role_data.role_x = 9;
                                player.role_data.role_y = 6;
                                player.role_data.role_area = 0;
                                cout << string(50, ' ') << "HP:" << role_data.role_hp << endl;
                                cout << string(50, ' ') << "重生!!" << endl;
                                x = player.role_data.role_x;
                                y = player.role_data.role_y;
                                now_map = player.role_data.role_area;
                                // system("pause");
                                Sleep(1000);
                                system("cls");
                                continue;
                            }
                             else if( monster_l[now_map - 2][1] == 0)
                            {
                                cout << string(100, '=') << endl;
                                cout << string(50, ' ') << "獲得寶箱!!" << endl;
                                cout << string(100, '=') << endl;
                                Sleep(1000);
                                player.role_data = shop.crates(player.role_data);
                                if (player.role_data.role_exp >= player.role_data.role_exp_up) // 升級
                                {
                                    player.role_data.role_exp = 0;                           // 經驗值歸零
                                    player.role_data.role_exp_up += 10;                      // 升級所需經驗值增加
                                    player.role_data.role_level += 1;                        // 等級增加
                                    player.role_data.role_hp_max += 10;                      // 血量上限增加
                                    player.role_data.role_hp = player.role_data.role_hp_max; // 血量回滿
                                    player.role_data.role_mp_max += 10;                      // 魔法值上限增加
                                    player.role_data.role_mp = player.role_data.role_mp_max; // 魔法值回滿
                                    player.role_data.role_money += 100;                      // 獲得金幣
                                    player.role_data.role_atk += 5;                          // 攻擊力增加
                                    player.role_data.role_def += 5;                          // 防禦力增加
                                    player.role_data.role_skill += 10;                       // 技能點數增加
                                    player.role_data.role_attr += 5;                         // 屬性點數增加
                                    cout << string(30, ' ') << "升級" << endl;
                                    cout << string(30, ' ') << "等級+1:" << player.role_data.role_level << endl;
                                    cout << string(30, ' ') << "血量+10:" << player.role_data.role_hp_max << endl;
                                    cout << string(30, ' ') << "魔法值+10:" << player.role_data.role_mp_max << endl;
                                    cout << string(30, ' ') << "金幣+100:" << player.role_data.role_money << endl;
                                    cout << string(30, ' ') << "攻擊力+5:" << player.role_data.role_atk << endl;
                                    cout << string(30, ' ') << "防禦力+5:" << player.role_data.role_def << endl;
                                    cout << string(30, ' ') << "技能點數+10:" << player.role_data.role_skill << endl;
                                    cout << string(30, ' ') << "屬性點數+5:" << player.role_data.role_attr << endl;
                                    system("pause");
                                }
                                for (int i = 0; i < player.role_data.role_pet.pet_data.size(); i++) // 寵物升級
                                {
                                    if (player.role_data.role_pet.pet_data[i].exp >= player.role_data.role_pet.pet_data[i].exp_up)
                                    {
                                        cout << string(30, ' ') << "寵物" << player.role_data.role_pet.pet_data[i].name << "升級" << endl;
                                        player.role_data.role_pet.pet_data[i].exp = 0;                                           // 經驗值歸零
                                        player.role_data.role_pet.pet_data[i].exp_up += 10;                                      // 升級所需經驗值增加
                                        player.role_data.role_pet.pet_data[i].level += 1;                                        // 等級增加
                                        player.role_data.role_pet.pet_data[i].hp_max += 10;                                      // 血量上限增加
                                        player.role_data.role_pet.pet_data[i].hp = player.role_data.role_pet.pet_data[i].hp_max; // 血量回滿
                                        player.role_data.role_pet.pet_data[i].atk += 5;                                          // 攻擊力增加
                                        player.role_data.role_pet.pet_data[i].def += 5;                                          // 防禦力增加
                                        player.role_data.role_pet.pet_data[i].attr_fire += 5;                                    // 火屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_water += 5;                                   // 水屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_wood += 5;                                    // 木屬性增加
                                    }
                                }
                                // system("pause");
                            }
                        }
                        else if (y == 8 && x == 4)
                        {
                            // cout << "怪物" << y << " " << x << endl;
                            player.role_data = fight.fight(player.role_data, monster_l[now_map - 2][2]);

                            login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                            if (player.role_data.role_hp <= 0)                              // 死亡
                            {
                                system("cls");
                                cout << string(50, ' ') << "你已經死亡" << endl;
                                player.role_data.role_hp = player.role_data.role_hp_max;
                                player.role_data.role_mp = player.role_data.role_mp_max;
                                player.role_data.role_money = player.role_data.role_money / 2;
                                player.role_data.role_x = 9;
                                player.role_data.role_y = 6;
                                player.role_data.role_area = 0;
                                cout << string(50, ' ') << "HP:" << role_data.role_hp << endl;
                                cout << string(50, ' ') << "重生!!" << endl;
                                x = player.role_data.role_x;
                                y = player.role_data.role_y;
                                now_map = player.role_data.role_area;
                                // system("pause");
                                Sleep(1000);
                                system("cls");
                                continue;
                            }
                            else if( monster_l[now_map - 2][2] == 0)
                            {
                                cout << string(100, '=') << endl;
                                cout << string(50, ' ') << "獲得寶箱!!" << endl;
                                cout << string(100, '=') << endl;
                                Sleep(1000);
                                player.role_data = shop.crates(player.role_data);
                                if (player.role_data.role_exp >= player.role_data.role_exp_up) // 升級
                                {
                                    player.role_data.role_exp = 0;                           // 經驗值歸零
                                    player.role_data.role_exp_up += 10;                      // 升級所需經驗值增加
                                    player.role_data.role_level += 1;                        // 等級增加
                                    player.role_data.role_hp_max += 10;                      // 血量上限增加
                                    player.role_data.role_hp = player.role_data.role_hp_max; // 血量回滿
                                    player.role_data.role_mp_max += 10;                      // 魔法值上限增加
                                    player.role_data.role_mp = player.role_data.role_mp_max; // 魔法值回滿
                                    player.role_data.role_money += 100;                      // 獲得金幣
                                    player.role_data.role_atk += 5;                          // 攻擊力增加
                                    player.role_data.role_def += 5;                          // 防禦力增加
                                    player.role_data.role_skill += 10;                       // 技能點數增加
                                    player.role_data.role_attr += 5;                         // 屬性點數增加
                                    cout << string(30, ' ') << "升級" << endl;
                                    cout << string(30, ' ') << "等級+1:" << player.role_data.role_level << endl;
                                    cout << string(30, ' ') << "血量+10:" << player.role_data.role_hp_max << endl;
                                    cout << string(30, ' ') << "魔法值+10:" << player.role_data.role_mp_max << endl;
                                    cout << string(30, ' ') << "金幣+100:" << player.role_data.role_money << endl;
                                    cout << string(30, ' ') << "攻擊力+5:" << player.role_data.role_atk << endl;
                                    cout << string(30, ' ') << "防禦力+5:" << player.role_data.role_def << endl;
                                    cout << string(30, ' ') << "技能點數+10:" << player.role_data.role_skill << endl;
                                    cout << string(30, ' ') << "屬性點數+5:" << player.role_data.role_attr << endl;
                                    system("pause");
                                }
                                for (int i = 0; i < player.role_data.role_pet.pet_data.size(); i++) // 寵物升級
                                {
                                    if (player.role_data.role_pet.pet_data[i].exp >= player.role_data.role_pet.pet_data[i].exp_up)
                                    {
                                        cout << string(30, ' ') << "寵物" << player.role_data.role_pet.pet_data[i].name << "升級" << endl;
                                        player.role_data.role_pet.pet_data[i].exp = 0;                                           // 經驗值歸零
                                        player.role_data.role_pet.pet_data[i].exp_up += 10;                                      // 升級所需經驗值增加
                                        player.role_data.role_pet.pet_data[i].level += 1;                                        // 等級增加
                                        player.role_data.role_pet.pet_data[i].hp_max += 10;                                      // 血量上限增加
                                        player.role_data.role_pet.pet_data[i].hp = player.role_data.role_pet.pet_data[i].hp_max; // 血量回滿
                                        player.role_data.role_pet.pet_data[i].atk += 5;                                          // 攻擊力增加
                                        player.role_data.role_pet.pet_data[i].def += 5;                                          // 防禦力增加
                                        player.role_data.role_pet.pet_data[i].attr_fire += 5;                                    // 火屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_water += 5;                                   // 水屬性增加
                                        player.role_data.role_pet.pet_data[i].attr_wood += 5;                                    // 木屬性增加
                                        // system("pause");
                                    }
                                }
                                // system("pause");
                            }
                        }

                        if (monster_l[now_map - 2][0] == 0 && monster_l[now_map - 2][1] == 0 && monster_l[now_map - 2][2] == 0)
                        {
                            cout << string(20, ' ') << "怪物已全被打敗" << endl;
                        }
                        system("cls");
                    }
                    else
                    {
                        system("cls"); // 清除畫面
                        cout << "逃跑" << endl;
                    }
                    x = new_x;
                    y = new_y;
                }
                else if (move_legal == 6) // 技能商店
                {
                    if (move_input == "w")
                        new_y++;
                    else if (move_input == "s")
                        new_y--;
                    else if (move_input == "a")
                        new_x++;
                    else if (move_input == "d")
                        new_x--;
                    x = new_x;
                    y = new_y;
                    system("cls");
                    cout << "遇到技能商人 1.購買 2.離開" << endl;
                    cout << "請輸入選項:";
                    int option;
                    cin >> option;
                    if (option == 1)
                    {
                        system("cls");
                        player.role_data = shop.BuySkill(player.role_data);
                        login.ModifyRoleData(player.name, player.id, player.role_data); // 修改角色資料
                        system("cls");
                    }
                    else
                    {
                        cout << "離開" << endl;
                    }
                }
            }
            else
            {
                system("cls"); // 清除畫面
                cout << "無法移動到該位置!" << endl;
                if (move_input == "w")
                    new_y++;
                else if (move_input == "s")
                    new_y--;
                else if (move_input == "a")
                    new_x++;
                else if (move_input == "d")
                    new_x--;
            }
        }
        if (game_c == false)
        {
            break;
        }
    }
    return 0;
}
