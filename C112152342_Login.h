// 登入
#ifndef GAMELOGIN_H
#define GAMELOGIN_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct item_init // 道具資料
{
    string job;     // 適用職業
    string type;    // 類型
    string name;    // 名稱
    string part;    // 部位(頭部/身體/手部/腳部)
    int damage;     // 傷害值
    int defense;    // 防禦值
    int recovery;   // 回復值
    int fire_attr;  // 火屬性
    int water_attr; // 水屬性
    int wood_attr;  // 木屬性
    int price;      // 價格
};

struct skill_init // 技能資料
{
    string job;     // 適用職業
    string name;    // 名稱
    int level;      // 等級
    int level_up;   // 升級所需技能點
    int damage;     // 傷害值
    int defense;    // 防禦值
    int recovery;   // 回復值
    int mp;         // 消耗魔法值
    int fire_attr;  // 火屬性
    int water_attr; // 水屬性
    int wood_attr;  // 木屬性
    int price;      // 價格
};

struct pet_init // 寵物資料
{
    int id;         // 寵物編號
    string name;    // 寵物名稱
    int hp;         // 寵物血量
    int hp_max;     // 寵物最大血量
    int level;      // 寵物等級
    int exp;        // 寵物經驗值
    int exp_up;     // 寵物升級所需經驗值
    int atk;        // 寵物攻擊力
    int def;        // 寵物防禦力
    int attr_fire;  // 寵物火屬性值
    int attr_water; // 寵物水屬性值
    int attr_wood;  // 寵物木屬性值
};

struct role_pet_init // 角色寵物資料
{
    vector<pet_init> pet_data; // 寵物資料
};

struct role_data_init // 角色資料
{
    int role_id;      // 角色id
    string role_job;  // 角色職業

    item_init head; // 頭部裝備
    item_init body; // 身體裝備
    item_init hand; // 手部裝備
    item_init foot; // 腳部裝備

    vector<item_init> bag;        // 角色背包

    int role_pet_id;                     // 角色寵物id
    role_pet_init role_pet;              // 當前角色寵物資料
    vector<role_pet_init> role_pet_data; // 角色所有寵物資料

    int role_hp;     // 角色血量
    int role_hp_max; // 角色最大血量

    int role_mp;     // 角色魔法直
    int role_mp_max; // 角色最大魔法直

    int role_exp;    // 角色經驗值
    int role_exp_up; // 升級所需經驗值
    int role_level;  // 角色等級

    int role_atk;        // 角色攻擊力
    int role_def;        // 角色防禦力
    int role_attr;       // 角色屬性點
    int role_attr_fire;  // 角色火屬性值
    int role_attr_water; // 角色水屬性值
    int role_attr_wood;  // 角色木屬性值

    int role_skill;                     // 角色技能點
    vector<skill_init> role_skill_data; // 角色技能

    int role_money; // 角色金錢

    int role_x;    // 角色x座標
    int role_y;    // 角色y座標
    int role_area; // 角色所在地區
};

struct user_data_init // 使用者資料
{
    string username;             // 帳號
    string password;             // 密碼
    vector<role_data_init> role; // 角色資料
};

class GameLogin
{
private:
    vector<user_data_init> user_data;          // 使用者資料
    //加密
    string Encrypt(string str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            str[i] = str[i] + 1;
        }
        return str;
    }
    //解密
    string Decrypt(string str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            str[i] = str[i] - 1;
        }
        return str;
    }
public:
    GameLogin(); // 建構子
    // 讀取帳號資料(使用者檔案名稱, 背包檔案名稱, 技能檔案名稱, 寵物檔案名稱)
    void ReadUserData(const string filename, const string bag_name, const string skill_name, const string pet_name, const string now_item);
    // 儲存帳號資料(使用者檔案名稱, 背包檔案名稱, 技能檔案名稱, 寵物檔案名稱)
    void SaveUserData(const string filename, const string bag_name, const string skill_name, const string pet_name, const string now_item);
    // 登入功能(帳號, 密碼)
    bool Login(const string &username, const string &password);
    // 忘記密碼功能(帳號)
    bool ForgetPassword(const string &username);
    // 創建帳號(帳號, 密碼)
    bool CreateAccount(const string &username, const string &password);
    // 刪除帳號(帳號, 密碼)
    bool DeleteAccount(const string &username, const string &password);

    // 顯示當前所有帳號資料
    void ShowAllUserData();
    // 顯示使用者資訊(帳號)
    void ShowUserInfo(const string &username);
    // 顯示角色背包(帳號, 角色id)
    void ShowRoleBag(const string &username, int roleId);
    // 顯示角色技能(帳號, 角色id)
    void ShowRoleSkill(const string &username, int roleId);
    // 顯示角色寵物(帳號, 角色id)
    void ShowRolePet(const string &username, int roleId);
    // 傳出使用者角色資料(帳號, 角色id)
    role_data_init GetRoleData(const string &username, int roleId);
    // 修改使用者資料(帳號, 舊密碼, 新密碼)
    bool ModifyUserData(const string &username, const string &old_password, const string &new_password);
    // 修改角色資料(帳號, 角色id, 新角色資料)
    bool ModifyRoleData(const string &username, int roleId, const role_data_init &new_role_data);
    // 創建角色(帳號)
    void CreateRole(const string &username);
    // 刪除角色(帳號, 角色id)
    void DeleteRole(const string &username, int roleId);
};

#endif