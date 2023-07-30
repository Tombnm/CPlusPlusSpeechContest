#include <iostream>
using namespace std;
#include "SpeechManager.h"
#include "Speaker.h"

int main(){

    //测试代码
    // for(map<int,Speaker>::iterator it=sm.m_speaker.begin();it!=sm.m_speaker.end();it++){
    //     cout<<"Speaker id: "<<it->first<<" |  Speaker name: "<<it->second.m_name<<" |  Score: "<<it->second.m_score[0]<<endl;
    // }

    //创建对象
    SpeechManager sm;
    sm.ShowMenu();

    
while(true){
    int choice = 0;
    cout<<"Input your choice"<<endl;
    cin>>choice;

    switch(choice){
        //开始比赛
        case 1:
        sm.startspeech();
        break;
        //查看往届比赛记录
        case 2:
        sm.showscore();
        break;
        //清空比赛记录
        case 3:
        break;
        //退出系统
        case 4:
        sm.QuitSystem();
        break;
        default:
        system("cls");
        break;
    }
}
    system ("pause");
    return 0;
}