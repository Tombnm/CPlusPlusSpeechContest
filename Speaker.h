#pragma once
#include <iostream>
using namespace std;
#include <string>

class Speaker{
public:
    Speaker();
    
    //姓名
    string m_name;
    //两轮得分
    double m_score[2];

    ~Speaker();
};