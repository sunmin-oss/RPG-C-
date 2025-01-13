#ifndef FIGHT_H
#define FIGHT_H

#include <string>
#include <vector>
#include "C112152342_Login.h"
#include "C112152342_logic.h"
#include "C112152342_shop.h"
using namespace std;

class FIGHT
{
private:
    GameLogin &login; // 登入系統參考
public:
    FIGHT(GameLogin &login);
    //怪物資料
    vector <pet_init> monster;
    //讀取怪物資料
    void Read_monster_Data(const string filename);
    //顯示所有怪物
    void show_all_monster();
    role_data_init fight(role_data_init role_data, int &monster_l);  // 戰鬥
};

#endif