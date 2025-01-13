#include "C112152342_map.h"
#include <iostream>
#include <fstream>

// 讀取地圖資料
void GameMap::readFile_map(const string &filename, vector<map_init> &map_data)
{
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        map_init temp;
        int i = 0;
        while (getline(file, line))
        {
            // cout<<line<<i<<endl;
            if (i < 10)
            {
                temp.map[i] = line;
                i++;
            }
            else
            {
                temp.map[i] = line;
                i = 0;
                map_data.push_back(temp);
            }
        }
        file.close();

        // for(int i = 0; i < map_data.size(); i++) {
        //     for(int j = 0; j <= 10; j++) {
        //         cout << map_data[i].map[j] << endl;
        //     }
        // }
    }
    else
    {
        cout << "無法開啟檔案" << endl;
    }
}

// 顯示地圖
void GameMap::show_map(int map_name, int x, int y, int m1, int m2, int m3)
{
    for (int i = 0; i < map_data.size(); i++)
    {
        if (int(map_data[i].map[0][0] - '0') == map_name)
        {
            cout << map_data[i].map_name[map_name] << endl;
            for (int j = 1; j <= 10; j++)
            {
                for (int k = 0; k < map_data[i].map[j].size(); k++)
                {
                    if (j == y && k == x)
                    {
                        cout << "@";
                    }
                    else
                    {
                        // m1(3 3) m2(8 16) m3(8 4)
                        if (m1 && (j == 3 && k == 3) && (map_name > 1))
                        {
                            if (m1 == 1)
                            {
                                cout << "M";
                            }
                            else
                            {
                                cout << ".";
                            }
                        }
                        else if (m2 && (j == 8 && k == 16) && (map_name > 1))
                        {
                            if (m2 == 1)
                            {
                                cout << "M";
                            }
                            else
                            {
                                cout << ".";
                            }
                        }
                        else if (m3 && (j == 8 && k == 4) && (map_name > 1))
                        {
                            if (m3 == 1)
                            {
                                cout << "M";
                            }
                            else
                            {
                                cout << ".";
                            }
                        }
                        else
                        {
                            cout << map_data[i].map[j][k];
                        }
                    }
                }
                cout << endl;
            }
        }
    }
}

// 移動判斷
int GameMap::move_player(int x, int y, int map_name, int m1, int m2, int m3)
{
    /*0牆壁 1可通行 2門 3商人*/
    for (int i = 0; i < map_data.size(); i++)
    {
        if (int(map_data[i].map[0][0] - '0') == map_name)
        {
            if (map_data[i].map[y][x] == '#')
            {
                return 0; // 牆壁
            }
            else if (map_data[i].map[y][x] == 'D')
            {
                return 2; // 門
            }
            else if (map_data[i].map[y][x] == 'P')
            {
                return 3; // 商人
            }
            else if (map_data[i].map[y][x] == 'C')
            {
                return 4; // 寶箱
            }
            else if(map_data[i].map[y][x] == 'S')//技能商店
            {
                return 6;
            }
            else if ((map_name > 1) && ((y == 3 && x == 3 && m1) || (y == 8 && x == 16 && m2) || (y == 8 && x == 4 && m3))) // 怪物
            {
                return 5; // 怪物
            }
            else if (map_data[i].map[y][x] == '.')
            {
                return 1; // 可通行
            }
        }
    }
    return false;
}

// 地圖名稱
void GameMap::showmap_name(int name_num)
{
    cout << "當前位置" << map_data[name_num].map_name[name_num] << endl;
}