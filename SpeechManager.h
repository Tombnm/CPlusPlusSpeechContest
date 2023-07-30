#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "Speaker.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <deque>
#include <numeric>
#include <string>
#include <fstream>

class SpeechManager{
public:
    //构造函数
    SpeechManager();

    //初始化属性和容器
    void initSpeechManager();

    //显示界面
    void ShowMenu();

    //退出系统
    void QuitSystem();

    //创建12名选手
    void creatspeaker();

    //开始比赛 — 控制流程
    void startspeech();

    //抽签
    void speechdraw();

    //开始比赛
    void speechcontest();

    //显示比赛结果
    void showscore();

    //保存记录
    void saverecord();



    //成员属性
    //比赛选手,12人
    vector<int> v1;

    //第一轮晋级选手，6人
    vector<int> v2;

    //胜利前3名选手容器，3人
    vector<int> vectory;

    //存放编号以及对应选手的容器
    map<int,Speaker> m_speaker;

    //存放比赛轮数
    int m_index;



    //析构函数
    ~SpeechManager();
};