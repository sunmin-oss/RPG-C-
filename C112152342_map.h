#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <string>
#include <vector>
using namespace std;

struct map_init {
    /*map[0] 名稱*/
    string map[11];//地圖
    string map_name[7] = {"初始城鎮"," 市集"," 草原","城堡" ,"神廟" ,"沙漠" ,"小地圖"};//地圖名稱
    /*
    初始城鎮 市集 草原 城堡 神廟 沙漠 小地圖
    */
};


class GameMap {
private:
    vector<map_init>& map_data;//地圖資料
public:
    GameMap(vector<map_init>& data) : map_data(data) {}//建構子
    void readFile_map(const string& filename, vector<map_init>& map_data);//讀取地圖資料
    void show_map(int map_name,int x,int y,int m1,int m2,int m3);//顯示地圖
    int move_player(int x, int y, int map_name,int m1,int m2,int m3);//移動判斷
    void showmap_name(int name_num);//地圖名稱
};

#endif