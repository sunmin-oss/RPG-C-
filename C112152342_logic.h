#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include "C112152342_Login.h"
using namespace std;

class logic
{
private:
    GameLogin &login; // 登入系統參考
public:
    logic(GameLogin &login);
    role_data_init Use_items(role_data_init role_data); // 角色資料
    role_data_init Use_pet(role_data_init role_data);//角色寵物
    role_data_init Use_Up(role_data_init role_data);//角色升級
    
};

#endif