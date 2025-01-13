#include "C112152342_Login.h"
#include <fstream>
#include <iostream>
#include <iomanip>

GameLogin::GameLogin()
{
    // 建構子初始化
}

// 讀取帳號資料
void GameLogin::ReadUserData(const string filename, const string bag_name, const string skill_name, const string pet_name, const string now_item)
{
    // 讀取 user_role_now_item.txt
    // 讀取 user_role_pet.txt
    // 讀取 user_role_skill.txt
    // 讀取 user_bag.txt
    // 讀取 user.txt
    vector<user_data_init> user_data_temp; // 使用者資料
    vector<role_data_init> role_data_temp; // 角色資料
    vector<role_pet_init> role_pet_temp;   // 寵物資料
    vector<skill_init> skill_data_temp;    // 技能資料
    // 讀取帳號資料
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "無法開啟檔案: " << filename << endl;
        return;
    }

    string line;
    user_data_init current_user;

    // 讀取並處理每一行
    while (getline(file, line))
    {
        stringstream ss(line);
        string data;
        vector<string> tokens;
        // cout<<  line << endl;
        // 分割資料
        while (getline(ss, data, '|'))
        {
            // cout<<  data << endl;
            tokens.push_back(data);
        }
        if (tokens.size() == 2) // 處理帳號資料
        {
            if (!current_user.username.empty())
            {
                user_data.push_back(current_user);
                current_user = user_data_init();
            }
            current_user.username = tokens[0];

            current_user.password =Decrypt( tokens[1]);

            // 輸出帳號資訊
            // cout << "\n=== 帳號資訊 ===" << endl;
            // cout << "帳號: " << tokens[0] << endl;
            // cout << "密碼: " << tokens[1] << endl;
            // cout<< "解密後密碼: "<<Decrypt( tokens[1])<<endl;
            // system("pause");
        }
        // 處理角色資料
        else if (tokens.size() == 21)
        { // 角色id|角色職業 |當前寵物id| 角色血量| 角色最大血量| 角色魔法值| 角色最大魔法值| 角色經驗值| 升級所需經驗值| 角色等級| 角色攻擊力| 角色防禦力| 角色屬性點| 角色火屬性值| 角色水屬性值| 角色木屬性值| 角色技能點| 角色金錢| 角色x座標| 角色y座標| 角色所在地區
            role_data_init role_data_temp;
            /*
            // cout<<tokens.size()<<endl;
            // cout<<"角色id:"<<tokens[0]<<endl;
            // cout<<"角色職業: "<<tokens[1]<<endl;
            // cout<<"當前寵物id: "<<tokens[2]<<endl;
            // cout<<"角色血量: "<<tokens[3]<<endl;
            // cout<<"角色最大血量: "<<tokens[4]<<endl;
            // cout<<"角色魔法值: "<<tokens[5]<<endl;
            // cout<<"角色最大魔法值: "<<tokens[6]<<endl;
            // cout<<"角色經驗值: "<<tokens[7]<<endl;
            // cout<<"升級所需經驗值: "<<tokens[8]<<endl;
            // cout<<"角色等級: "<<tokens[9]<<endl;
            // cout<<"角色攻擊力: "<<tokens[10]<<endl;
            // cout<<"角色防禦力: "<<tokens[11]<<endl;
            // cout<<"角色屬性點: "<<tokens[12]<<endl;
            // cout<<"角色火屬性值: "<<tokens[13]<<endl;
            // cout<<"角色水屬性值: "<<tokens[14]<<endl;
            // cout<<"角色木屬性值: "<<tokens[15]<<endl;
            // cout<<"角色技能點: "<<tokens[16]<<endl;
            // cout<<"角色金錢: "<<tokens[17]<<endl;
            // cout<<"角色x座標: "<<tokens[18]<<endl;
            // cout<<"角色y座標: "<<tokens[19]<<endl;
            // cout<<"角色所在地區: "<<tokens[20]<<endl;*/
            role_data_temp.role_id = stoi(tokens[0]);          // 角色id
            role_data_temp.role_job = tokens[1];               // 角色職業
            role_data_temp.role_pet_id = stoi(tokens[2]);      // 當前寵物id
            role_data_temp.role_hp = stoi(tokens[3]);          // 角色血量
            role_data_temp.role_hp_max = stoi(tokens[4]);      // 角色最大血量
            role_data_temp.role_mp = stoi(tokens[5]);          // 角色魔法值
            role_data_temp.role_mp_max = stoi(tokens[6]);      // 角色最大魔法值
            role_data_temp.role_exp = stoi(tokens[7]);         // 角色經驗值
            role_data_temp.role_exp_up = stoi(tokens[8]);      // 升級所需經驗值
            role_data_temp.role_level = stoi(tokens[9]);       // 角色等級
            role_data_temp.role_atk = stoi(tokens[10]);        // 角色攻擊力
            role_data_temp.role_def = stoi(tokens[11]);        // 角色防禦力
            role_data_temp.role_attr = stoi(tokens[12]);       // 角色屬性點
            role_data_temp.role_attr_fire = stoi(tokens[13]);  // 角色火屬性值
            role_data_temp.role_attr_water = stoi(tokens[14]); // 角色水屬性值
            role_data_temp.role_attr_wood = stoi(tokens[15]);  // 角色木屬性值
            role_data_temp.role_skill = stoi(tokens[16]);      // 角色技能點
            role_data_temp.role_money = stoi(tokens[17]);      // 角色金錢
            role_data_temp.role_x = stoi(tokens[18]);          // 角色x座標
            role_data_temp.role_y = stoi(tokens[19]);          // 角色y座標
            role_data_temp.role_area = stoi(tokens[20]);       // 角色所在地區
            current_user.role.push_back(role_data_temp);
        }
    }
    if (!current_user.username.empty())
    {
        user_data.push_back(current_user);
    }
    file.close();
    // cout << "\n資料讀取完成!" << endl;

    // 讀取背包資料
    ifstream file_bag(bag_name);
    if (!file_bag.is_open())
    {
        cout << "無法開啟檔案: " << bag_name << endl;
        return;
    }
    string line_bag;
    string account;
    int role_id;
    // 讀取並處理每一行
    while (getline(file_bag, line_bag))
    {
        stringstream ss(line_bag);
        string data;
        vector<string> tokens;
        // cout << line_bag << endl;
        // 分割資料
        while (getline(ss, data, '|'))
        {
            // cout << data << endl;
            tokens.push_back(data);
        }

        if (tokens.size() == 2)
        {
            account = tokens[0];
            role_id = stoi(tokens[1]);
        }
        else if (tokens.size() == 11)
        { // 適用職業|類型   |部位(頭部/身體/手部/腳部)|名稱   |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性 |價格

            item_init item_temp;
            item_temp.job = tokens[0];              // 適用職業
            item_temp.type = tokens[1];             // 類型
            item_temp.part = tokens[2];             // 部位
            item_temp.name = tokens[3];             // 名稱
            item_temp.damage = stoi(tokens[4]);     // 傷害值
            item_temp.defense = stoi(tokens[5]);    // 防禦值
            item_temp.recovery = stoi(tokens[6]);   // 回復值
            item_temp.fire_attr = stoi(tokens[7]);  // 火屬性
            item_temp.water_attr = stoi(tokens[8]); // 水屬性
            item_temp.wood_attr = stoi(tokens[9]);  // 木屬性
            item_temp.price = stoi(tokens[10]);     // 價格
            for (int i = 0; i < user_data.size(); i++)
            {
                if (user_data[i].username == account)
                {
                    for (int j = 0; j < user_data[i].role.size(); j++)
                    {
                        if (user_data[i].role[j].role_id == role_id)
                        {
                            user_data[i].role[j].bag.push_back(item_temp);
                        }
                    }
                }
            }
        }
    }
    file_bag.close();
    // cout << "\n背包資料讀取完成!" << endl;

    // 讀取技能資料
    ifstream file_skill(skill_name);
    if (!file_skill.is_open())
    {
        cout << "無法開啟檔案: " << skill_name << endl;
        return;
    }
    string line_skill;
    while (getline(file_skill, line_skill))
    {
        stringstream ss(line_skill);
        string data;
        vector<string> tokens;
        // cout<<  line_skill << endl;
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }
        // cout<<tokens.size()<<endl;
        if (tokens.size() == 2) // 帳號|角色ID
        {
            account = tokens[0];
            role_id = stoi(tokens[1]);
            // cout<<"技能"<<account<<role_id<<endl;
        }
        else if (tokens.size() == 12) // 適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
        {
            skill_init skill_temp;
            skill_temp.job = tokens[0];              // 適用職業
            skill_temp.name = tokens[1];             // 名稱
            skill_temp.level = stoi(tokens[2]);      // 等級
            skill_temp.level_up = stoi(tokens[3]);   // 升級所需技能點
            skill_temp.damage = stoi(tokens[4]);     // 傷害值
            skill_temp.defense = stoi(tokens[5]);    // 防禦值
            skill_temp.recovery = stoi(tokens[6]);   // 回復值
            skill_temp.mp = stoi(tokens[7]);         // 消耗魔法值
            skill_temp.fire_attr = stoi(tokens[8]);  // 火屬性
            skill_temp.water_attr = stoi(tokens[9]); // 水屬性
            skill_temp.wood_attr = stoi(tokens[10]); // 木屬性
            skill_temp.price = stoi(tokens[11]);     // 價格
            for (int i = 0; i < user_data.size(); i++)
            {
                if (user_data[i].username == account)
                {
                    for (int j = 0; j < user_data[i].role.size(); j++)
                    {
                        if (user_data[i].role[j].role_id == role_id)
                        {
                            user_data[i].role[j].role_skill_data.push_back(skill_temp);
                        }
                    }
                }
            }
        }
    }
    file_skill.close();
    // cout << "\n技能資料讀取完成!" << endl;
    // 讀取寵物資料
    ifstream file_pet(pet_name);
    if (!file_pet.is_open())
    {
        cout << "無法開啟檔案: " << pet_name << endl;
        return;
    }
    string line_pet;
    while (getline(file_pet, line_pet))
    {
        stringstream ss(line_pet);
        string data;
        vector<string> tokens;
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }

        if (tokens.size() == 2) // 帳號|角色ID
        {
            account = tokens[0];
            role_id = stoi(tokens[1]);
        }
        else if (tokens.size() == 12)
        // 寵物編號|寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
        {
            pet_init pet_temp;
            pet_temp.id = stoi(tokens[0]);          // 寵物編號
            pet_temp.name = tokens[1];              // 寵物名稱
            pet_temp.hp = stoi(tokens[2]);          // 寵物血量
            pet_temp.hp_max = stoi(tokens[3]);      // 寵物最大血量
            pet_temp.atk = stoi(tokens[4]);         // 寵物攻擊力
            pet_temp.def = stoi(tokens[5]);         // 寵物防禦力
            pet_temp.level = stoi(tokens[6]);       // 寵物等級
            pet_temp.exp = stoi(tokens[7]);         // 寵物經驗值
            pet_temp.exp_up = stoi(tokens[8]);      // 寵物升級所需經驗值
            pet_temp.attr_fire = stoi(tokens[9]);   // 寵物火屬性值
            pet_temp.attr_water = stoi(tokens[10]); // 寵物水屬性值
            pet_temp.attr_wood = stoi(tokens[11]);  // 寵物木屬性值

            for (auto &user : user_data)
            {
                if (user.username == account)
                {
                    for (auto &role : user.role)
                    {
                        if (role.role_id == role_id)
                        {
                            role.role_pet.pet_data.push_back(pet_temp);
                        }
                    }
                }
            }
        }
    }
    file_pet.close();
    // cout << "\n寵物資料讀取完成!" << endl;

    // 讀取當前裝備資料
    ifstream file_now_item(now_item);
    if (!file_now_item.is_open())
    {
        cout << "無法開啟檔案: " << now_item << endl;
        return;
    }
    string line_now_item;
    while (getline(file_now_item, line_now_item))
    {
        stringstream ss(line_now_item);
        string data;
        vector<string> tokens;
        // cout << line_now_item << endl;
        while (getline(ss, data, '|'))
        {
            tokens.push_back(data);
        }
        // cout << tokens.size() << endl;
        // system("pause");
        if (tokens.size() == 2) // 帳號|角色ID
        {
            account = tokens[0];
            role_id = stoi(tokens[1]);
        }
        else if (tokens.size() == 11) //  //適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
        {
            item_init item_temp;
            cout << tokens[2] << tokens[3] << endl;
            item_temp.job = tokens[0];              // 適用職業
            item_temp.type = tokens[1];             // 類型
            item_temp.part = tokens[2];             // 部位
            item_temp.name = tokens[3];             // 名稱
            item_temp.damage = stoi(tokens[4]);     // 傷害值
            item_temp.defense = stoi(tokens[5]);    // 防禦值
            item_temp.recovery = stoi(tokens[6]);   // 回復值
            item_temp.fire_attr = stoi(tokens[7]);  // 火屬性
            item_temp.water_attr = stoi(tokens[8]); // 水屬性
            item_temp.wood_attr = stoi(tokens[9]);  // 木屬性
            item_temp.price = stoi(tokens[10]);     // 價格
            cout << item_temp.part << endl;
            string trimmed = item_temp.part;
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
            //  trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
            //  trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
            cout << trimmed << endl;
            cout << (trimmed == "head") << endl;

            for (auto &user : user_data)
            {
                if (user.username == account)
                {
                    for (auto &role : user.role)
                    {
                        if (role.role_id == role_id)
                        {
                            // Update equipment based on part
                            if (trimmed == "head")
                                role.head = item_temp;
                            else if (trimmed == "body")
                                role.body = item_temp;
                            else if (trimmed == "hand")
                                role.hand = item_temp;
                            else if (trimmed == "foot")
                                role.foot = item_temp;
                            else
                                cout << "Invalid part" << endl;
                            // system("pause");
                        }
                    }
                }
            }
        }
    }
    file_now_item.close();

    // cout << "\n當前裝備資料讀取完成!" << endl;
}

// 儲存帳號資料
void GameLogin::SaveUserData(const string filename, const string bag_name, const string skill_name, const string pet_name, const string now_item)
{
    // 保存主要資料
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "無法開啟檔案: " << filename << endl;
        return;
    }

    for (const auto &user : user_data)
    {
        // 寫入帳號密碼
        file << user.username << "|" << Encrypt(user.password) << endl;

        // 寫入角色資料
        for (const auto &role : user.role)
        {
            file << role.role_id << "|"         // 角色id
                 << role.role_job << "|"        // 角色職業
                 << role.role_pet_id << "|"     // 當前寵物id
                 << role.role_hp << "|"         // 角色血量
                 << role.role_hp_max << "|"     // 角色最大血量
                 << role.role_mp << "|"         // 角色魔法值
                 << role.role_mp_max << "|"     // 角色最大魔法值
                 << role.role_exp << "|"        // 角色經驗值
                 << role.role_exp_up << "|"     // 升級所需經驗值
                 << role.role_level << "|"      // 角色等級
                 << role.role_atk << "|"        // 角色攻擊力
                 << role.role_def << "|"        // 角色防禦力
                 << role.role_attr << "|"       // 角色屬性點
                 << role.role_attr_fire << "|"  // 角色火屬性值
                 << role.role_attr_water << "|" // 角色水屬性值
                 << role.role_attr_wood << "|"  // 角色木屬性值
                 << role.role_skill << "|"      // 角色技能點
                 << role.role_money << "|"      // 角色金錢
                 << role.role_x << "|"          // 角色x座標
                 << role.role_y << "|"          // 角色y座標
                 << role.role_area << endl;     // 角色所在地區
        }
    }
    file.close();
    // 保存背包資料
    ofstream file_bag(bag_name);
    if (!file_bag.is_open())
    {
        cout << "無法開啟檔案: " << bag_name << endl;
        return;
    }

    for (const auto &user : user_data)
    {
        for (const auto &role : user.role)
        {
            // 寫入帳號和角色ID
            file_bag << user.username << "|" << role.role_id << endl;
            // 寫入背包物品
            for (const auto &item : role.bag)
            {
                file_bag << item.job << "|"
                         << item.type << "|"
                         << item.part << "|"
                         << item.name << "|"
                         << item.damage << "|"
                         << item.defense << "|"
                         << item.recovery << "|"
                         << item.fire_attr << "|"
                         << item.water_attr << "|"
                         << item.wood_attr
                         << "|" << item.price << endl;
            }
        }
    }
    file_bag.close();

    // 保存技能資料
    ofstream file_skill(skill_name);
    if (!file_skill.is_open())
    {
        cout << "無法開啟檔案: " << skill_name << endl;
        return;
    }

    for (const auto &user : user_data)
    {
        for (const auto &role : user.role)
        {
            file_skill << user.username << "|" << role.role_id << endl;
            for (const auto &skill : role.role_skill_data)
            {
                // 適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
                file_skill << skill.job << "|" << skill.name << "|"                 // 適用職業|名稱
                           << skill.level << "|" << skill.level_up << "|"           // 等級|升級所需技能點
                           << skill.damage << "|" << skill.defense << "|"           // 傷害值|防禦力
                           << skill.recovery << "|" << skill.mp << "|"              // 回復值|消耗魔法值
                           << skill.fire_attr << "|" << skill.water_attr            // 火屬性|水屬性
                           << "|" << skill.wood_attr << "|" << skill.price << endl; // 木屬性|價格
            }
        }
    }
    file_skill.close();

    // 保存寵物資料
    ofstream file_pet(pet_name);
    if (!file_pet.is_open())
    {
        cout << "無法開啟檔案: " << pet_name << endl;
        return;
    }

    for (const auto &user : user_data)
    {
        for (const auto &role : user.role)
        {
            file_pet << user.username << "|" << role.role_id << endl;
            for (const auto &pet : role.role_pet.pet_data)
            {
                // 寵物編號|寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
                file_pet << pet.id << "|" << pet.name << "|"                // 寵物編號|寵物名稱
                         << pet.hp << "|" << pet.hp_max << "|"              // 寵物血量|寵物最大血量
                         << pet.atk << "|" << pet.def << "|"                // 寵物攻擊力|寵物防禦力
                         << pet.level << "|" << pet.exp << "|"              // 寵物等級|寵物經驗值
                         << pet.exp_up << "|" << pet.attr_fire << "|"       // 寵物升級所需經驗值|寵物火屬性值
                         << pet.attr_water << "|" << pet.attr_wood << endl; // 寵物水屬性值|寵物木屬性值
            }
        }
    }
    file_pet.close();

    // 保存當前裝備資料
    ofstream file_now_item(now_item);
    if (!file_now_item.is_open())
    {
        cout << "無法開啟檔案: " << now_item << endl;
        return;
    }

    for (const auto &user : user_data)
    {
        for (const auto &role : user.role)
        {
            file_now_item << user.username << "|" << role.role_id << endl; // 帳號|角色id
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱     |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性 |價格
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
            file_now_item << role.head.job << "|" << role.head.type << "|" << role.head.part << "|"                 // 適用職業|類型|部位
                          << role.head.name << "|" << role.head.damage << "|" << role.head.defense << "|"           // 名稱|傷害值|防禦值
                          << role.head.recovery << "|" << role.head.fire_attr << "|" << role.head.water_attr << "|" // 回復值|火屬性|水屬性
                          << role.head.wood_attr << "|" << role.head.price << endl;                                 // 木屬性|價格

            file_now_item << role.hand.job << "|" << role.hand.type << "|" << role.hand.part << "|"                 // 適用職業|類型|部位
                          << role.hand.name << "|" << role.hand.damage << "|" << role.hand.defense << "|"           // 名稱|傷害值|防禦值
                          << role.hand.recovery << "|" << role.hand.fire_attr << "|" << role.hand.water_attr << "|" // 回復值|火屬性|水屬性
                          << role.hand.wood_attr << "|" << role.hand.price << endl;                                 // 木屬性|價格

            file_now_item << role.body.job << "|" << role.body.type << "|" << role.body.part << "|"                 // 適用職業|類型|部位
                          << role.body.name << "|" << role.body.damage << "|" << role.body.defense << "|"           // 名稱|傷害值|防禦值
                          << role.body.recovery << "|" << role.body.fire_attr << "|" << role.body.water_attr << "|" // 回復值|火屬性|水屬性
                          << role.body.wood_attr << "|" << role.body.price << endl;                                 // 木屬性|價格

            file_now_item << role.foot.job << "|" << role.foot.type << "|" << role.foot.part << "|"                 // 適用職業|類型|部位
                          << role.foot.name << "|" << role.foot.damage << "|" << role.foot.defense << "|"           // 名稱|傷害值|防禦值
                          << role.foot.recovery << "|" << role.foot.fire_attr << "|" << role.foot.water_attr << "|" // 回復值|火屬性|水屬性
                          << role.foot.wood_attr << "|" << role.foot.price << endl;                                 // 木屬性|價格
        }
    }
    file_now_item.close();

    // cout << "所有資料保存完成!" << endl;
}

// 登入功能(帳號, 密碼)
bool GameLogin::Login(const string &username, const string &password)
{
    // 搜尋帳號
    for (const auto &user : user_data)
    {
        // 驗證帳號密碼
        if (user.username == username && user.password ==password)
        {   
            // cout<< string(15, ' ') << left << setw(20) << "=== 登入成功 ===" << endl;
            // cout << string(15, ' ') << left << setw(20)<< "帳號：" << username << endl;
            // cout << string(15, ' ') << left << setw(20)<< "角色數量：" << user.role.size() << endl;
            // 顯示角色列表
            // for (const auto &role : user.role)
            // {
            //     cout << "\n角色 " << role.role_id << "：" << endl;
            //     cout << "職業：" << role.role_job << endl;
            //     cout << "等級：" << role.role_level << endl;
            //     cout << "HP：" << role.role_hp << "/" << role.role_hp_max << endl;
            //     cout << "MP：" << role.role_mp << "/" << role.role_mp_max << endl;
            // }

            return true;
        }
    }

    // cout << "帳號或密碼錯誤！" << endl;
    return false;
}

// 忘記密碼功能(帳號)
bool GameLogin::ForgetPassword(const string &username)
{
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            cout << string(15, ' ') << left << setw(20) << "舊密碼: " << user.password << endl;
            cout << string(15, ' ') << left << setw(20) << "請輸入新密碼: ";
            string new_password;
            cin >> new_password;
            cout << string(15, ' ') << left << setw(20) << "請再次輸入新密碼: ";
            string new_password2;
            cin >> new_password2;
            if (new_password == new_password2)
            {
                user.password = new_password;
                // cout << "密碼修改成功!" << endl;
                SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
                return true;
            }
            else
            {
                cout << string(15, ' ') << left << setw(20) << "兩次輸入密碼不一致!" << endl;
                return false;
            }
            return true;
        }
    }
    cout << string(15, ' ') << left << setw(20) << "找不到指定帳號: " << username << endl;
    return false;
}

// 創建帳號(帳號, 密碼)
bool GameLogin::CreateAccount(const string &username, const string &password)
{
    // 檢查帳號是否已存在
    for (const auto &user : user_data)
    {
        if (user.username == username)
        {
            cout << "帳號已存在！" << endl;
            system("pause");
            return false;
        }
    }

    // 建立新帳號
    user_data_init new_user;
    new_user.username = username;
    new_user.password = password;
    // 輸入角色資料
    role_data_init new_role;
    new_role.role_id = 1; // 角色id
    // 選擇職業
    cout << "請選擇職業 (1.戰士 2.法師 3.射手): ";
    int job_choice;
    cin >> job_choice;
    if (job_choice == 1)
    {
        new_role.role_job = "戰士"; // 角色職業
    }
    else if (job_choice == 2)
    {
        new_role.role_job = "法師"; // 角色職業
    }
    else if (job_choice == 3)
    {
        new_role.role_job = "射手"; // 角色職業
    }

    // 初始化基本屬性
    // 角色id|角色職業 |當前寵物id| 角色血量| 角色最大血量| 角色魔法值| 角色最大魔法值| 角色經驗值| 升級所需經驗值| 角色等級| 角色攻擊力| 角色防禦力| 角色屬性點| 角色火屬性值| 角色水屬性值| 角色木屬性值| 角色技能點| 角色金錢| 角色x座標| 角色y座標| 角色所在地區

    // 根據職業設定初始屬性
    if (job_choice == 1) // 戰士
    {
        new_role.role_hp = 100;     // 角色血量
        new_role.role_hp_max = 100; // 角色最大血量
        new_role.role_mp = 50;      // 角色魔法值
        new_role.role_mp_max = 50;  // 角色最大魔法值
        new_role.role_atk = 10;     // 角色攻擊力
        new_role.role_def = 8;      // 角色防禦力
        // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱     |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性 |價格
        /*
        戰士|防具|head|青銅頭盔|0|10|0|0|0|0|100
        戰士|防具|body|青銅盔甲|0|10|0|0|0|0|100
        戰士|武器|hand|青銅劍|10|0|0|0|0|0|100
        戰士|防具|foot|青銅靴子|0|10|0|0|0|0|100*/
        new_role.head.job = "戰士";
        new_role.head.type = "防具";
        new_role.head.part = "head";
        new_role.head.name = "青銅頭盔";
        new_role.head.damage = 0;
        new_role.head.defense = 10;
        new_role.head.recovery = 0;
        new_role.head.fire_attr = 0;
        new_role.head.water_attr = 0;
        new_role.head.wood_attr = 0;
        new_role.head.price = 100;

        new_role.body.job = "戰士";
        new_role.body.type = "防具";
        new_role.body.part = "body";
        new_role.body.name = "青銅盔甲";
        new_role.body.damage = 0;
        new_role.body.defense = 10;
        new_role.body.recovery = 0;
        new_role.body.fire_attr = 0;
        new_role.body.water_attr = 0;
        new_role.body.wood_attr = 0;
        new_role.body.price = 100;

        new_role.hand.job = "戰士";
        new_role.hand.type = "武器";
        new_role.hand.part = "hand";
        new_role.hand.name = "青銅劍";
        new_role.hand.damage = 10;
        new_role.hand.defense = 0;
        new_role.hand.recovery = 0;
        new_role.hand.fire_attr = 0;
        new_role.hand.water_attr = 0;
        new_role.hand.wood_attr = 0;
        new_role.hand.price = 100;

        new_role.foot.job = "戰士";
        new_role.foot.type = "防具";
        new_role.foot.part = "foot";
        new_role.foot.name = "青銅靴子";
        new_role.foot.damage = 0;
        new_role.foot.defense = 10;
        new_role.foot.recovery = 0;
        new_role.foot.fire_attr = 0;
        new_role.foot.water_attr = 0;
        new_role.foot.wood_attr = 0;
        new_role.foot.price = 100;

        // 適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
        // 戰士    |突擊|1   |10           |10    |0     |0      |0        |0     |0     |0     |100
        new_role.role_skill_data.push_back({"戰士", "突擊", 1, 10, 10, 0, 0, 0, 0, 0, 0, 100});

        // 戰士|寵物編號|寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
        //  1   |小火龍  |100     |100        |20        |10        |1       |0        |100               |5          |0           |0
        new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
    }
    else if (job_choice == 2) // 法師
    {
        new_role.role_hp = 80;
        new_role.role_hp_max = 80;
        new_role.role_mp = 100;
        new_role.role_mp_max = 100;
        new_role.role_atk = 12;
        new_role.role_def = 5;

        new_role.head.job = "法師";
        new_role.head.type = "防具";
        new_role.head.part = "head";
        new_role.head.name = "布帽";
        new_role.head.damage = 0;
        new_role.head.defense = 5;
        new_role.head.recovery = 0;
        new_role.head.fire_attr = 0;
        new_role.head.water_attr = 0;
        new_role.head.wood_attr = 0;
        new_role.head.price = 100;

        new_role.body.job = "法師";
        new_role.body.type = "防具";
        new_role.body.part = "body";
        new_role.body.name = "布袍";
        new_role.body.damage = 0;
        new_role.body.defense = 5;
        new_role.body.recovery = 0;
        new_role.body.fire_attr = 0;
        new_role.body.water_attr = 0;
        new_role.body.wood_attr = 0;
        new_role.body.price = 100;

        new_role.hand.job = "法師";
        new_role.hand.type = "武器";
        new_role.hand.part = "hand";
        new_role.hand.name = "木杖";
        new_role.hand.damage = 12;
        new_role.hand.defense = 0;
        new_role.hand.recovery = 0;
        new_role.hand.fire_attr = 0;
        new_role.hand.water_attr = 0;
        new_role.hand.wood_attr = 0;
        new_role.hand.price = 100;

        new_role.foot.job = "法師";
        new_role.foot.type = "防具";
        new_role.foot.part = "foot";
        new_role.foot.name = "布鞋";
        new_role.foot.damage = 0;
        new_role.foot.defense = 5;
        new_role.foot.recovery = 0;
        new_role.foot.fire_attr = 0;
        new_role.foot.water_attr = 0;
        new_role.foot.wood_attr = 0;
        new_role.foot.price = 100;

        new_role.role_skill_data.push_back({"法師", "火球", 1, 10, 10, 0, 0, 10, 10, 0, 0, 100});

        new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
    }
    else if (job_choice == 3) // 射手
    {
        new_role.role_hp = 80;
        new_role.role_hp_max = 80;
        new_role.role_mp = 100;
        new_role.role_mp_max = 100;
        new_role.role_atk = 12;
        new_role.role_def = 5;
        new_role.head.job = "射手";
        new_role.head.type = "防具";
        new_role.head.part = "head";
        new_role.head.name = "布帽";
        new_role.head.damage = 0;
        new_role.head.defense = 5;
        new_role.head.recovery = 0;
        new_role.head.fire_attr = 0;
        new_role.head.water_attr = 0;
        new_role.head.wood_attr = 0;
        new_role.head.price = 100;

        new_role.body.job = "射手";
        new_role.body.type = "防具";
        new_role.body.part = "body";
        new_role.body.name = "布袍";
        new_role.body.damage = 0;
        new_role.body.defense = 5;
        new_role.body.recovery = 0;
        new_role.body.fire_attr = 0;
        new_role.body.water_attr = 0;
        new_role.body.wood_attr = 0;
        new_role.body.price = 100;

        new_role.hand.job = "射手";
        new_role.hand.type = "武器";
        new_role.hand.part = "hand";
        new_role.hand.name = "弓";
        new_role.hand.damage = 12;
        new_role.hand.defense = 0;
        new_role.hand.recovery = 0;
        new_role.hand.fire_attr = 0;
        new_role.hand.water_attr = 0;
        new_role.hand.wood_attr = 0;
        new_role.hand.price = 100;

        new_role.foot.job = "射手";
        new_role.foot.type = "防具";
        new_role.foot.part = "foot";
        new_role.foot.name = "布鞋";
        new_role.foot.damage = 0;
        new_role.foot.defense = 5;
        new_role.foot.recovery = 0;
        new_role.foot.fire_attr = 0;
        new_role.foot.water_attr = 0;
        new_role.foot.wood_attr = 0;
        new_role.foot.price = 100;

        new_role.role_skill_data.push_back({"射手", "射擊", 1, 10, 10, 0, 0, 10, 10, 0, 0, 100});

        new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
    }

    new_role.role_pet_id = 1;     // 當前寵物id
    new_role.role_exp = 0;        // 角色經驗值
    new_role.role_exp_up = 100;   // 升級所需經驗值
    new_role.role_level = 1;      // 角色等級
    new_role.role_attr = 0;       // 角色屬性點
    new_role.role_attr_fire = 0;  // 角色火屬性值
    new_role.role_attr_water = 0; // 角色水屬性值
    new_role.role_attr_wood = 0;  // 角色木屬性值
    new_role.role_skill = 0;      // 角色技能點
    new_role.role_money = 100;    // 角色金錢
    new_role.role_x = 5;          // 角色x座標
    new_role.role_y = 5;          // 角色y座標
    new_role.role_area = 0;       // 角色所在地區
    // 適用職業|類型   |部位(頭部/身體/手部/腳部)|名稱|傷害值|防禦力|回復值 |火屬性|水屬性|木屬性|價格
    // all     |消耗品|all                     |小藥水|0    |30    |0    |0     |0      |50
    new_role.bag.push_back({"all", "消耗品", "all", "小藥水", 0, 0, 30, 0, 0, 0, 50});

    // 添加角色到帳號
    new_user.role.push_back(new_role);
    cout << "角色創建成功!" << endl;
    // 加入到使用者資料中
    user_data.push_back(new_user);

    // 儲存資料
    SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");

    cout << "帳號建立成功！" << endl;
    return true;
}

// 刪除帳號(帳號, 密碼)
bool GameLogin::DeleteAccount(const string &username, const string &password)
{
    // 尋找帳號
    for (auto it = user_data.begin(); it != user_data.end(); ++it)
    {
        if (it->username == username && it->password == password)
        {
            // 確認是否要刪除
            cout << "確定要刪除帳號嗎？(Y/N): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                // 刪除帳號
                user_data.erase(it);
                cout << "帳號已刪除！" << endl;

                // 儲存更新後的資料
                SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt",
                             "user_role_pet.txt", "user_role_now_item.txt");
                return true;
            }
            else
            {
                cout << "取消刪除帳號！" << endl;
                return false;
            }
        }
    }

    cout << "帳號或密碼錯誤！" << endl;
    return false;
}

// 傳出使用者角色資料(帳號, 角色id)
role_data_init GameLogin::GetRoleData(const string &username, int roleId)
{
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            for (auto &role : user.role)
            {
                if (role.role_id == roleId)
                {
                    return role;
                }
            }
        }
    }
    cout << "找不到指定帳號: " << username << endl;
    return role_data_init();
}

// 修改使用者資料(帳號, 舊密碼, 新密碼)
bool GameLogin::ModifyUserData(const string &username, const string &old_password, const string &new_password)
{
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            if (user.password == old_password)
            {
                user.password = new_password;
                cout << "密碼修改成功!" << endl;
                SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
                return true;
            }
            cout << "密碼錯誤!" << endl;
            return false;
        }
    }
    cout << "找不到指定帳號: " << username << endl;
    return false;
}

// 修改角色資料(帳號, 角色id, 新角色資料)
bool GameLogin::ModifyRoleData(const string &username, int roleId, const role_data_init &new_role_data)
{
    // 尋找帳號
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            // 尋找角色
            for (auto &role : user.role)
            {
                if (role.role_id == roleId)
                {
                    // 更新角色資料
                    role = new_role_data;
                    role.role_id = roleId; // 保持原有ID不變
                    // role.role_mp = 87;
                    cout << "角色資料修改成功!" << endl;
                    SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
                    return true;
                }
            }
            cout << "找不到指定角色ID: " << roleId << endl;
            return false;
        }
    }
    cout << "找不到指定帳號: " << username << endl;
    return false;
}

// 創建角色(帳號)
void GameLogin::CreateRole(const string &username)
{
    // 檢查帳號是否存在
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            // 檢查角色數量限制
            if (user.role.size() >= 3)
            {
                cout << "角色數量已達上限!" << endl;
                return;
            }

            // 輸入角色資料
            role_data_init new_role;
            new_role.role_id = user.role.size() + 1; // 角色id

            // 選擇職業
            cout << "請選擇職業 (1.戰士 2.法師 3.射手): ";
            int job_choice;
            cin >> job_choice;
            if (job_choice == 1)
            {
                new_role.role_job = "戰士"; // 角色職業
            }
            else if (job_choice == 2)
            {
                new_role.role_job = "法師"; // 角色職業
            }
            else if (job_choice == 3)
            {
                new_role.role_job = "射手"; // 角色職業
            }
            else
            {
                cout << "輸入錯誤!" << endl;
                return;
            }

            // 初始化基本屬性
            // 角色id|角色職業 |當前寵物id| 角色血量| 角色最大血量| 角色魔法值| 角色最大魔法值| 角色經驗值| 升級所需經驗值| 角色等級| 角色攻擊力| 角色防禦力| 角色屬性點| 角色火屬性值| 角色水屬性值| 角色木屬性值| 角色技能點| 角色金錢| 角色x座標| 角色y座標| 角色所在地區

            // 根據職業設定初始屬性
            if (job_choice == 1) // 戰士
            {
                new_role.role_hp = 100;     // 角色血量
                new_role.role_hp_max = 100; // 角色最大血量
                new_role.role_mp = 50;      // 角色魔法值
                new_role.role_mp_max = 50;  // 角色最大魔法值
                new_role.role_atk = 10;     // 角色攻擊力
                new_role.role_def = 8;      // 角色防禦力
                                            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱     |傷害值|防禦力|回復值 |火屬性|水屬性|木屬性 |價格
                new_role.head.job = "戰士";
                new_role.head.type = "防具";
                new_role.head.part = "head";
                new_role.head.name = "青銅頭盔";
                new_role.head.damage = 0;
                new_role.head.defense = 10;
                new_role.head.recovery = 0;
                new_role.head.fire_attr = 0;
                new_role.head.water_attr = 0;
                new_role.head.wood_attr = 0;
                new_role.head.price = 100;

                new_role.body.job = "戰士";
                new_role.body.type = "防具";
                new_role.body.part = "body";
                new_role.body.name = "青銅盔甲";
                new_role.body.damage = 0;
                new_role.body.defense = 10;
                new_role.body.recovery = 0;
                new_role.body.fire_attr = 0;
                new_role.body.water_attr = 0;
                new_role.body.wood_attr = 0;
                new_role.body.price = 100;

                new_role.hand.job = "戰士";
                new_role.hand.type = "武器";
                new_role.hand.part = "hand";
                new_role.hand.name = "青銅劍";
                new_role.hand.damage = 10;
                new_role.hand.defense = 0;
                new_role.hand.recovery = 0;
                new_role.hand.fire_attr = 0;
                new_role.hand.water_attr = 0;
                new_role.hand.wood_attr = 0;
                new_role.hand.price = 100;

                new_role.foot.job = "戰士";
                new_role.foot.type = "防具";
                new_role.foot.part = "foot";
                new_role.foot.name = "青銅靴子";
                new_role.foot.damage = 0;
                new_role.foot.defense = 10;
                new_role.foot.recovery = 0;
                new_role.foot.fire_attr = 0;
                new_role.foot.water_attr = 0;
                new_role.foot.wood_attr = 0;
                new_role.foot.price = 100;
                // 適用職業|名稱|等級|升級所需技能點|傷害值|防禦力|回復值|消耗魔法值|火屬性|水屬性|木屬性|價格
                // 戰士    |突擊|1   |10           |10    |0     |0      |0        |0     |0     |0     |100
                new_role.role_skill_data.push_back({"戰士", "突擊", 1, 10, 10, 0, 0, 0, 0, 0, 0, 100});

                // 戰士|寵物編號|寵物名稱|寵物血量|寵物最大血量|寵物攻擊力|寵物防禦力|寵物等級|寵物經驗值|寵物升級所需經驗值|寵物火屬性值|寵物水屬性值|寵物木屬性值
                //  1   |小火龍  |100     |100        |20        |10        |1       |0        |100               |5          |0           |0
                new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
            }
            else if (job_choice == 2) // 法師
            {
                new_role.role_hp = 80;
                new_role.role_hp_max = 80;
                new_role.role_mp = 100;
                new_role.role_mp_max = 100;
                new_role.role_atk = 12;
                new_role.role_def = 5;
                new_role.head.job = "法師";
                new_role.head.type = "防具";
                new_role.head.part = "head";
                new_role.head.name = "布帽";
                new_role.head.damage = 0;
                new_role.head.defense = 5;
                new_role.head.recovery = 0;
                new_role.head.fire_attr = 0;
                new_role.head.water_attr = 0;
                new_role.head.wood_attr = 0;
                new_role.head.price = 100;

                new_role.body.job = "法師";
                new_role.body.type = "防具";
                new_role.body.part = "body";
                new_role.body.name = "布袍";
                new_role.body.damage = 0;
                new_role.body.defense = 5;
                new_role.body.recovery = 0;
                new_role.body.fire_attr = 0;
                new_role.body.water_attr = 0;
                new_role.body.wood_attr = 0;
                new_role.body.price = 100;

                new_role.hand.job = "法師";
                new_role.hand.type = "武器";
                new_role.hand.part = "hand";
                new_role.hand.name = "木杖";
                new_role.hand.damage = 12;
                new_role.hand.defense = 0;
                new_role.hand.recovery = 0;
                new_role.hand.fire_attr = 0;
                new_role.hand.water_attr = 0;
                new_role.hand.wood_attr = 0;
                new_role.hand.price = 100;

                new_role.foot.job = "法師";
                new_role.foot.type = "防具";
                new_role.foot.part = "foot";
                new_role.foot.name = "布鞋";
                new_role.foot.damage = 0;
                new_role.foot.defense = 5;
                new_role.foot.recovery = 0;
                new_role.foot.fire_attr = 0;
                new_role.foot.water_attr = 0;
                new_role.foot.wood_attr = 0;
                new_role.foot.price = 100;
                new_role.role_skill_data.push_back({"法師", "火球", 1, 10, 10, 0, 0, 10, 10, 0, 0, 100});

                new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
            }
            else if (job_choice == 3) // 射手
            {
                new_role.role_hp = 80;
                new_role.role_hp_max = 80;
                new_role.role_mp = 100;
                new_role.role_mp_max = 100;
                new_role.role_atk = 12;
                new_role.role_def = 5;
                new_role.head.job = "射手";
                new_role.head.type = "防具";
                new_role.head.part = "head";
                new_role.head.name = "布帽";
                new_role.head.damage = 0;
                new_role.head.defense = 5;
                new_role.head.recovery = 0;
                new_role.head.fire_attr = 0;
                new_role.head.water_attr = 0;
                new_role.head.wood_attr = 0;
                new_role.head.price = 100;

                new_role.body.job = "射手";
                new_role.body.type = "防具";
                new_role.body.part = "body";
                new_role.body.name = "布袍";
                new_role.body.damage = 0;
                new_role.body.defense = 5;
                new_role.body.recovery = 0;
                new_role.body.fire_attr = 0;
                new_role.body.water_attr = 0;
                new_role.body.wood_attr = 0;
                new_role.body.price = 100;

                new_role.hand.job = "射手";
                new_role.hand.type = "武器";
                new_role.hand.part = "hand";
                new_role.hand.name = "弓";
                new_role.hand.damage = 12;
                new_role.hand.defense = 0;
                new_role.hand.recovery = 0;
                new_role.hand.fire_attr = 0;
                new_role.hand.water_attr = 0;
                new_role.hand.wood_attr = 0;
                new_role.hand.price = 100;

                new_role.foot.job = "射手";
                new_role.foot.type = "防具";
                new_role.foot.part = "foot";
                new_role.foot.name = "布鞋";
                new_role.foot.damage = 0;
                new_role.foot.defense = 5;
                new_role.foot.recovery = 0;
                new_role.foot.fire_attr = 0;
                new_role.foot.water_attr = 0;
                new_role.foot.wood_attr = 0;
                new_role.foot.price = 100;

                new_role.role_skill_data.push_back({"射手", "射擊", 1, 10, 10, 0, 0, 10, 10, 0, 0, 100});

                new_role.role_pet.pet_data.push_back({1, "小火龍", 100, 100, 20, 10, 1, 0, 100, 5, 0, 0});
            }
            else
            {
                cout << "輸入錯誤!" << endl;
                return;
            }

            new_role.role_pet_id = 1;     // 當前寵物id
            new_role.role_exp = 0;        // 角色經驗值
            new_role.role_exp_up = 100;   // 升級所需經驗值
            new_role.role_level = 1;      // 角色等級
            new_role.role_attr = 0;       // 角色屬性點
            new_role.role_attr_fire = 0;  // 角色火屬性值
            new_role.role_attr_water = 0; // 角色水屬性值
            new_role.role_attr_wood = 0;  // 角色木屬性值
            new_role.role_skill = 0;      // 角色技能點
            new_role.role_money = 100;    // 角色金錢
            new_role.role_x = 5;          // 角色x座標
            new_role.role_y = 5;          // 角色y座標
            new_role.role_area = 0;       // 角色所在地區
            // 適用職業|類型  |部位(頭部/身體/手部/腳部)|名稱  |傷害值 |回復值|火屬性|水屬性|木屬性 |價格
            // all     |消耗品|all                     |小藥水 |0     |30    |0     |0     | 0     |50
            new_role.bag.push_back({"all", "消耗品", "all", "小藥水", 0, 0, 30, 0, 0, 0, 50});

            // 添加角色到帳號
            user.role.push_back(new_role);
            cout << "角色創建成功!" << endl;

            // 儲存資料
            SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt", "user_role_pet.txt", "user_role_now_item.txt");
            return;
        }
    }
    cout << "找不到指定帳號: " << username << endl;
}

// 刪除角色(帳號, 角色id)
void GameLogin::DeleteRole(const string &username, int roleId)
{
    // 尋找帳號
    for (auto &user : user_data)
    {
        if (user.username == username)
        {
            // 尋找角色
            for (auto it = user.role.begin(); it != user.role.end(); ++it)
            {
                if (it->role_id == roleId)
                {
                    // 確認刪除
                    cout << "確定要刪除角色嗎？(Y/N): ";
                    char confirm;
                    cin >> confirm;

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        // 刪除角色
                        user.role.erase(it);

                        // 重新調整剩餘角色的ID
                        for (size_t i = 0; i < user.role.size(); i++)
                        {
                            user.role[i].role_id = i + 1;
                        }

                        cout << "角色已刪除！" << endl;

                        // 儲存更新後的資料
                        SaveUserData("user.txt", "user_bag.txt", "user_role_skill.txt",
                                     "user_role_pet.txt", "user_role_now_item.txt");
                        return;
                    }
                    else
                    {
                        cout << "取消刪除角色！" << endl;
                        return;
                    }
                }
            }
            cout << "找不到指定角色ID！" << endl;
            return;
        }
    }
    cout << "找不到指定帳號！" << endl;
}

// 顯示當前所有帳號資料
void GameLogin::ShowAllUserData()
{
    cout << "帳號資料:" << endl;
    for (int i = 0; i < user_data.size(); i++)
    {
        cout << "帳號:" << user_data[i].username << " 密碼:" << user_data[i].password << endl;
        // cout << user_data[i].role.size() << endl;
        for (int j = 0; j < user_data[i].role.size(); j++)
        {
            cout << "角色id:" << user_data[i].role[j].role_id << " 角色職業:" << user_data[i].role[j].role_job << endl;
            cout << "背包物品:" << user_data[i].role[j].bag.size() << endl;
            cout << "技能數量:" << user_data[i].role[j].role_skill_data.size() << endl;
            cout << "寵物數量:" << user_data[i].role[j].role_pet.pet_data.size() << endl;
            cout << "當前裝備:" << endl;
            cout << "頭部:" << user_data[i].role[j].head.name << endl;
            cout << "身體:" << user_data[i].role[j].body.name << endl;
            cout << "手部:" << user_data[i].role[j].hand.name << endl;
            cout << "腳部:" << user_data[i].role[j].foot.name << endl;
        }
    }
}

// 顯示使用者資訊(帳號)
void GameLogin::ShowUserInfo(const string &username)
{
    string map_name[7] = {"初始城鎮"," 市集"," 草原","城堡" ,"神廟" ,"沙漠" ,"小地圖"};//地圖名稱
    for (int i = 0; i < user_data.size(); i++)
    {
        if (user_data[i].username == username)
        {
            cout << string(20, ' ') << "帳號:" << user_data[i].username << " 密碼:" << user_data[i].password << endl;

            for (int j = 0; j < user_data[i].role.size(); j++)
            {   

                cout << string(10, ' ');
                cout << "角色id:" << user_data[i].role[j].role_id << " 職業:" << user_data[i].role[j].role_job;
                cout << " 等級:" << user_data[i].role[j].role_level << " HP:" << user_data[i].role[j].role_hp << "/" << user_data[i].role[j].role_hp_max
                     << " MP:" << user_data[i].role[j].role_mp << "/" << user_data[i].role[j].role_mp_max 
                     <<" 所在地圖:" <<map_name[user_data[i].role[j].role_area ]<<endl;//地圖名稱<< user_data[i].role[j].role_area << endl;
            }
        }
    }
}

// 顯示角色技能(帳號, 角色id)
void GameLogin::ShowRoleSkill(const string &username, int roleId)
{
    for (int i = 0; i < user_data.size(); i++)
    {
        if (user_data[i].username == username)
        {
            for (int j = 0; j < user_data[i].role.size(); j++)
            {
                if (user_data[i].role[j].role_id == roleId)
                {
                    cout << "角色id:" << user_data[i].role[j].role_id << " 角色職業:" << user_data[i].role[j].role_job << endl;
                    cout << "技能數量:" << user_data[i].role[j].role_skill_data.size() << endl;
                    cout << setw(10) << "適用職業" << "|" << setw(10) << "名稱" << "|" << setw(5) << "等級" << "|"
                         << setw(10) << "升級所需技能點" << "|" << setw(10) << "傷害值" << "|" << setw(10) << "防禦力" << "|"
                         << setw(10) << "回復值" << "|" << setw(10) << "消耗魔法值" << "|" << setw(10) << "火屬性" << "|"
                         << setw(10) << "水屬性" << "|" << setw(10) << "木屬性" << "|" << setw(10) << "價格" << endl;
                    for (const auto &skill : user_data[i].role[j].role_skill_data)
                    {
                        cout << setw(10) << skill.job << "|"
                             << setw(10) << skill.name << "|"
                             << setw(4) << skill.level << "|"
                             << setw(14) << skill.level_up << "|"
                             << setw(7) << skill.damage << "|"
                             << setw(7) << skill.defense << "|"
                             << setw(7) << skill.recovery << "|"
                             << setw(10) << skill.mp << "|"
                             << setw(7) << skill.fire_attr << "|"
                             << setw(7) << skill.water_attr << "|"
                             << setw(7) << skill.wood_attr << "|"
                             << setw(7) << skill.price << endl;
                    }
                }
            }
        }
    }
}

// 顯示角色背包(帳號, 角色id)
void GameLogin::ShowRoleBag(const string &username, int roleId)
{
    for (int i = 0; i < user_data.size(); i++)
    {
        if (user_data[i].username == username)
        {
            for (int j = 0; j < user_data[i].role.size(); j++)
            {
                if (user_data[i].role[j].role_id == roleId)
                {
                    cout << "角色id:" << user_data[i].role[j].role_id << " 角色職業:" << user_data[i].role[j].role_job << endl;
                    cout << "背包物品:" << user_data[i].role[j].bag.size() << endl;
                    cout << setw(12) << "適用職業" << "|" << setw(12) << "類型" << "|" << setw(12) << "名稱" << "|"
                         << setw(12) << "部位" << "|" << setw(12) << "傷害值" << "|" << setw(12) << "防禦力" << "|"
                         << setw(12) << "回復值" << "|" << setw(12) << "火屬性" << "|" << setw(12) << "水屬性" << "|"
                         << setw(12) << "木屬性" << "|" << setw(12) << "價格" << endl;
                    for (const auto &item : user_data[i].role[j].bag)
                    {
                        cout << setw(10) << item.job << "|"
                             << setw(10) << item.type << "|"
                             << setw(10) << item.name << "|"
                             << setw(10) << item.part << "|"
                             << setw(10) << item.damage << "|"
                             << setw(10) << item.defense << "|"
                             << setw(10) << item.recovery << "|"
                             << setw(10) << item.fire_attr << "|"
                             << setw(10) << item.water_attr << "|"
                             << setw(10) << item.wood_attr << "|"
                             << setw(10) << item.price
                             << endl;
                    }
                    /*
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
                    */
                }
            }
        }
    }
}

// 顯示角色寵物(帳號, 角色id)
void GameLogin::ShowRolePet(const string &username, int roleId)
{
    for (int i = 0; i < user_data.size(); i++)
    {
        if (user_data[i].username == username)
        {
            for (int j = 0; j < user_data[i].role.size(); j++)
            {
                if (user_data[i].role[j].role_id == roleId)
                {
                    cout << "角色id:" << user_data[i].role[j].role_id << " 角色職業:" << user_data[i].role[j].role_job << endl;
                    cout << "寵物數量:" << user_data[i].role[j].role_pet.pet_data.size() << endl;
                    cout << setw(10) << "編號" << "|" << setw(10) << "寵物名稱" << "|"
                         << setw(10) << "血量" << "|" << setw(10) << "最大血量" << "|"
                         << setw(10) << "攻擊力" << "|" << setw(10) << "防禦力" << "|"
                         << setw(10) << "等級" << "|" << setw(10) << "經驗值" << "|"
                         << setw(10) << "升級所需經驗值" << "|" << setw(10) << "火屬性值"
                         << "|" << setw(10) << "水屬性值" << "|" << setw(10) << "木屬性值" << endl;
                    for (const auto &pet : user_data[i].role[j].role_pet.pet_data)
                    {
                        cout << setw(8) << pet.id << "|"
                             << setw(11) << pet.name << "|"
                             << setw(8) << pet.hp << "|"
                             << setw(8) << pet.hp_max << "|"
                             << setw(7) << pet.atk << "|"
                             << setw(7) << pet.def << "|"
                             << setw(8) << pet.level << "|"
                             << setw(7) << pet.exp << "|"
                             << setw(14) << pet.exp_up << "|"
                             << setw(8) << pet.attr_fire << "|"
                             << setw(8) << pet.attr_water << "|"
                             << setw(8) << pet.attr_wood << endl;
                    }
                }
            }
        }
    }
}
