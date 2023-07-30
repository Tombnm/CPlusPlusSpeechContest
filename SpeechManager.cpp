#include "SpeechManager.h"

SpeechManager::SpeechManager(){
    //初始化属性
    this->initSpeechManager();
    //创建12名选手
    this->creatspeaker();
}

//显示界面
void SpeechManager::ShowMenu(){
    cout<<"******************************************************"<<endl;
    cout<<"********** Welcome to speech contest *****************"<<endl;
    cout<<"********** 1 Begin the speech contest ****************"<<endl;
    cout<<"********** 2 View record of speech contest ***********"<<endl;
    cout<<"********** 3 Clear record of speech contest **********"<<endl;
    cout<<"********** 4 Quit system *****************************"<<endl;
    cout<<"******************************************************"<<endl;
}

//初始化容器和属性
void SpeechManager::initSpeechManager(){
    //保证容器为空
    this->v1.clear();
    this->v2.clear();
    this->vectory.clear();
    this->m_speaker.clear();

    //初始化比赛轮数
    this->m_index=1;
}

//退出系统
void SpeechManager::QuitSystem(){
    cout<<"Welcom next use"<<endl;
    system("pause");
    exit(0);
}

//创建12名选手
void SpeechManager::creatspeaker(){
    string nameseed = "ABCDEFGHIJKL";
    for(int i = 0;i < nameseed.size();i++){
        string name = "Speaker";
        name = name + nameseed[i];

        Speaker sp;
        sp.m_name = name;
        for(int j = 0;j < 2;j++){
            sp.m_score[j] = 0;
        }
        //创建选手编号，并且放入到v1容器中
        this->v1.push_back(i+10001);
        //选手编号及对应选手放入到map容器中
        this->m_speaker.insert(make_pair(i+10001,sp));
    }
}

//开始比赛 - 控制流程
void SpeechManager::startspeech(){
    //第一轮比赛
    //1.抽签
    this->speechdraw();

    //2.比赛
    this->speechcontest();

    //3.显示晋级结果
    this->showscore();

    //第二轮比赛
    this->m_index++;

    //1.抽签
    this->speechdraw();

    //2.比赛
    this->speechcontest();

    //3.显示最终结果
    this->showscore();

    //4.保存结果到文件中
    
}

void SpeechManager::speechdraw(){
    cout<<"The draw fot the "<<this->m_index<<" round"<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"The result for the draw"<<endl;

    if(this->m_index == 1){
        //第一轮抽签
        shuffle(v1.begin(),v1.end(),default_random_engine(time(0)));
        for(vector<int>::iterator it = v1.begin();it != v1.end();it++){
            cout<<*it<<"  ";
        }
        cout<<endl;
    }
    else{
        //第二轮抽签
        shuffle(v2.begin(),v2.end(),default_random_engine(time(0)));
        for(vector<int>::iterator it = v2.begin();it != v2.end();it++){
            cout<<*it<<"  ";
        }
        cout<<endl;
    }
    cout<<"------------------------------------------"<<endl;
    system("pause");
    cout<<endl;
}

void SpeechManager::speechcontest(){
    cout<<"-----------Speechcontest round : "<<this->m_index<<"----------"<<endl;

    //准备临时容器，存放小组成绩
    multimap<double,int,greater<double>> groupscore;
    //记录人员个数，6人一组
    int num = 0;

    //比赛选手的容器
    vector<int> v_src;

    if(this->m_index == 1){
        v_src = this->v1;
    }
    else{
        v_src = this->v2;
    }

    //遍历所有的选手进行比赛
    for(vector<int>::iterator it = v_src.begin();it != v_src.end();it++){
        num++;
        //评委打分
        deque<double> d;
        for(int i = 0;i < 10;i++){
            double score = (rand()%401+600)/10.f; //600~1000
            //cout<<score<<"  ";
            d.push_back(score);
        }
        //cout<<endl;
        //将分数进行降序排列，去除最高分最低分
        sort(d.begin(),d.end(),greater<double>());
        d.pop_front();
        d.pop_back();

        //累加总分，算出平均分
        double sum = accumulate(d.begin(),d.end(),0.0f);
        double avg = sum/(double)d.size();

        //将平均分放入到map容器中
        this->m_speaker[*it].m_score[this->m_index-1] = avg;

        //将打分成绩放入临时小组成绩容器
        groupscore.insert(make_pair(avg,*it));

        //每6人取出前三名
        if(num%6 == 0){
            cout<<"group "<<num/6<<endl;
            for(multimap<double,int,greater<double>>::iterator it = groupscore.begin();it != groupscore.end();it++){
                cout<<"Number "<<it->second<<" Nmae "<<m_speaker[it->second].m_name<<" score "
                <<m_speaker[it->second].m_score[m_index-1]<<endl;
            }
            //取走前三名，放入到下一个容器中
            int count = 0;
            for(multimap<double,int,greater<double>>::iterator it = groupscore.begin();it != groupscore.end();it++,count++){
                if(this->m_index == 1){
                    v2.push_back((*it).second);
                }
                else{
                    vectory.push_back((*it).second);
                }
            }
            //小组容器清空
            groupscore.clear();
        }
    }
    cout<<"----------Round "<<m_index<<" speech contest finished----------"<<endl;
    system("pause");
}

//显示比赛结果
void SpeechManager::showscore(){
    cout<<"----------Speaker information of round "<<m_index<<" speech contest----------"<<endl;

    vector<int> v;
    if(m_index == 1){
        v = v2;
    }
    else{
        v = vectory;
    }

    for(vector<int>::iterator it = v.begin();it != v.end();it++){
        cout<<"Number "<<*it<<" Name "<<this->m_speaker[*it].m_name<<" Score "<<this->m_speaker[*it].m_score[this->m_index-1]<<endl;
    }
    cout<<endl;

    system("pause");
}

//保存记录
void SpeechManager::saverecord(){
    ofstream ofs;
    ofs.open("speech.csv",ios::out | ios ::app);//用输出的方式打开文件

    //将每个人的数据写入文件中
    for(vector<int>::iterator it = vectory.begin();it != vectory.end();it++){
        ofs<<*it<<","
        <<m_speaker[*it].m_score[1]<<",";
    }
    ofs<<endl;
    ofs.close();

    cout<<"Save record successful"<<endl;
}

SpeechManager::~SpeechManager(){}