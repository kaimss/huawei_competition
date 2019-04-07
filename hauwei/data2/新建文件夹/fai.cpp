//
// Created by Think on 2019/3/24.
//
#include <iostream>
#include <fstream>

using namespace std;
class Car{//车
public:
    int id;
    int speed;
    int planTime,from,to;
    int now_speed;//实际速度
    int now_lane;//车所处车道//3车道，单行道012，双行道id小->大:012id大->小:345
    int distance;//在道路上的行驶距离
    int starttime;//实际开始时间
    bool IswaitState;//是否等待状态
    bool IstoEnd;//是否已到达终点
    Car *backcar,*frontcar;//Road车链表指针
    Car *nextWaitCar,*frontWaitCar;//等待车链表指针
    Car(int id,int from,int to,int speed,int planTime,int route_length);
    void Output_route();//输出路径
    int *route;//路线
    int route_length;
    int now_routeLength;
private:

};
class Road{//道路
public :
    int id,length,speed;
    bool one_way;//是否单行道
    int channel;//车道数
    int from,to;//始末路口
    int carnumx;//车道上车数目//id小到id大
    int carnumd;//id大到id小
    int carnumd2;
    int carnumx2;
    Car *waitheadx;//等待车辆头 //id从小到大
    Car *waitheadd;//id从大到小
    Car **carhead;//链表头数组
    Car **carlast;//链表尾数组
    Road(int id,int length,int speed,int chanel,int from,int to,int isDuplex);
private:

};
class Cross{//路口
public:
    int id;
    int *roads_id;//0-4数组，顺时针道路id
    int *roads_minid;//道路id从小到大排序
    int TothisCrosswaitCarsum;
//		Road **in_roads;//道路对象数组0-4
//		Road **out_roads;//
    Cross *nextcross;//链表指针
    Cross(int id,int l1,int l2,int l3,int l4);
private:

};
class Handle{
public:

    int nowTime;
    int startrun(string crossPath,string roadPath,string carPath);
    void printResult(string path);
    //初始化
    void Initialize(string crossPath,string roadPath,string carPath);
    //模拟篇
    bool Simulation();//按时间进度，车辆情况调度
    //策略篇
    void judgeRoute();//
private:
    //元素储存篇//所有值都用NULL或-1(int)初始化，以判断是否有值
    int cross_base;//根据id查对象，id-cross_base为对象数组下标 //=最小id
    int road_base;
    Cross **crosss;//路口对象数组
    Road **roads;//id-road_base为下标
    Road **query_roads;//道路数组//遍历使用
    int query_roads_length;
    int query_cross_length;
    int crosss_length;//数组大小//等于最大id-最小id+1+10//+10防止溢出
    int roads_length;
    Car *headcar;//等待出发车所有车链表的头
    Car *planheadcar;//计划出发的车的链表头
    Cross *headcross;//路口链表的头//在路口数组填完后填链表，防止路口id过于松散，再遍历路口时遍历这个数组费时//遍历使用
    void SetEleStorage();//填装储存容器-文件操作
    //最短路径篇
    int **shortestPath;//二维数组最短路径，[i][j]存放从i到j第一个要经过的路口的id-cross_base//i,j用路口id-cross_base
    int **cross_road;//两个路口间直接的路真id
    long long **shortestl;//最短路径长
    long long maxlong;//最大路径长//达到表示没有路
    void GetShortestPath();//最短路径计算-弗洛伊德算法
    //模拟篇
    int sumCarsOnRoads;//路上所有车
    int headcarLength;//未出发车数量
    int waitCarsum;//路上等待状态
    bool waitGoCarIsCanGo(int roadId,int startCrossId);  //判断等待出发的车辆是否能够出发
    int  waitGoCarGoTocarChannel(int roadId,int startCrossId); //确定等待出发的车辆会走上相应道路的哪一个车道
    Car* sortById(int time,Car *theadcar);
    void IswaitState(Road * road);
    void driveAllCarJustOnRoadToEndState(Road * road);
    Car * getwaitStatecarsTothisRoad(Road * road);
    // int waitStateCarNum(Road *road);
    int ToCrossWaitStatueNum(Road * road,Cross * cross);
    bool FirOneIsWaitStateAndNoGo_AllTrue(bool FirOneIsWaitStateAndNoGo[],int num);
    int GetNextGoToRoadId(Road * road,Car * car);
    //int[3] GetLeftRightMiddleRoadId_BasethisId(int thisRoadId);
    int ToCrossWaitStatueNum(int crossId);
    Car * getWaitStatecarsTothisCross(Road * road,Cross * cross);
    int getNextDirection(int begin,int end);
    int getthisRoadIndexOnroads_id(int roadId,int crossId);
    int getduimianRoadId(int index,int crossId);
    int getleftRoadId(int index,int crossId);
    int getrightRoadId(int index,int crossId);
    bool AisCanGotoBinOneCross(int aRoadId,int bRoadId,int crossId);
    int NextToRoadIdBaseWaitStateCar(Car * car,int roadId);
    bool IsGoToEnd(Car * car,int roadId);
    void weiWaitheadxOrWaitheadhFUZHI(int roadId);
    Car* getWaitStatecarsTothisCross(int roadId,int crossId);
    bool A(Car * car,int crossId,int roadId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]);
    bool IsChongTu(Car * car,int roadId,int crossId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]);
    bool afterMoveIsWaitState(Car *car,int crossId,int roadId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]);
    bool IsWaitStatetoCross(Car *car, Road *road);
    //other
    int* minmaxid(string str0);
//		void sortById();//等待出发车链表排序
    Car **outputcar;//输出储存车指针数组
    int carsum;//车总数
    int minplanTime,maxplanTime;//文件中车的最大最小planTime
    Car* MergesortBytimeid(Car *head);//链表的归并排序//返回车头
    Car* MergesortByid(Car *head);
    void  OtherInitialize();
    Car* findNowYoucianCar(Car **pCar,int size);
    //策略篇
    int roadsTotalmil;
    int roadcarsum();//容纳车总数
    int threeroadselect(Cross *cur,int i,Car *cur1,int nroad);//3道路选择
    void cardirect(Cross *cur,int i,int i1);//给出车的方向
    int fourroadselect(Car *curcar,int nroad);//4道路选择
    void onrdcarjudge();//已出发车辆判断
    void waitcarjudge();//未出发车辆判断
    //动态变化
    double onroadbs=1.0;
    double notonroadbs=1.0;
    double limitP=0.2;
    int fluRange=200;

//    /////////////////////////////debug///////////////////////////////////
//    Car *debugcars[24];
//Car *c11258;
    ////////////////////////////debug//////////////////////////////////
};
/////
Car::Car(int id,int from,int to,int speed,int planTime,int route_length){
    this->id=id;
    this->from=from;
    this->to=to;
    this->speed=speed;
    this->planTime=planTime;
    now_speed=-1;
    now_lane=-1;
    distance=-1;
    starttime=-1;
    backcar=NULL;
    frontcar=NULL;
    nextWaitCar=NULL;
    frontWaitCar=NULL;
    this->route_length=route_length;
    route=new int[route_length];
    now_routeLength=0;
    IswaitState=false;
    IstoEnd=false;
    for(int i=0;i<route_length;i++){//<更改>
        route[i]=-1;
    }
}
Road::Road(int id,int length,int speed,int channel,int from,int to,int isDuplex){
    this->id=id;
    this->length=length;
    this->speed=speed;
    this->channel=channel;
    this->from=from;
    this->to=to;
    carnumx2=carnumx=0;
    carnumd2=carnumd=0;
    waitheadd=NULL;
    waitheadx=NULL;
    if(isDuplex==0){
        one_way=true;
    }else{
        one_way=false;
    }
    if(one_way){
        carhead=new Car*[channel];//链表头数组
        carlast=new Car*[channel];//链表尾数组
        for(int i=0;i<channel;i++){
            carhead[i]=NULL;
            carlast[i]=NULL;
        }
    }else{
        carhead=new Car*[channel*2];//链表头数组
        carlast=new Car*[channel*2];//链表尾数组
        for(int i=0;i<channel*2;i++){
            carhead[i]=NULL;
            carlast[i]=NULL;
        }
    }

}
Cross::Cross(int id,int l1,int l2,int l3,int l4){
    this->id=id;
    roads_id=new int[4];//0-4数组，顺时针道路id
    roads_id[0]=l1;
    roads_id[1]=l2;
    roads_id[2]=l3;
    roads_id[3]=l4;
    roads_minid=new int[4];//id从小到大排序存放
    TothisCrosswaitCarsum=0;
    for(int i=0;i<4;i++){
        int j=i;
        for(;j>0;j--){
            if(roads_minid[j-1]>roads_id[i]){////<更改>
                roads_minid[j]=roads_minid[j-1];
            }else{
                break;
            }
        }
        roads_minid[j]=roads_id[i];
    }
    nextcross=NULL;//链表指针
}
int Handle::startrun(string crossPath,string roadPath,string carPath){
    Initialize(crossPath,roadPath,carPath);
    this->nowTime=minplanTime;
    while(headcarLength>0||sumCarsOnRoads>0){
        judgeRoute();
        if(nowTime>1141){
            Simulation();
            nowTime++;
            judgeRoute();
        }
        if(Simulation()){
        }else{
//            cout<<"循环次数超过路口数"<<endl;
//            break;
        }
//        if(nowTime%100==1){
//            cout<<"time:"<<nowTime<<endl;////////////////////
//            cout<<"zls>>"<<headcarLength<<">>"<<sumCarsOnRoads<<endl;
//        }
        nowTime++;
    }
    return nowTime;
}
int* Handle::minmaxid(string str0){
    int *minmax=new int[2];
    minmax[0]=200000000,minmax[1]=-2000000000;
    ifstream in_r1(str0);
    string str;
    while(!in_r1.eof()){
        getline(in_r1,str);
        int id=0;
        bool zc1=false,zc2=false;
        for(int i=0;i<str.length();i++){
            if(str[i]=='#'){
                break;
            }else if(str[i]=='('){
                zc1=true;
                id=0;
            }else if(str[i]==','||str[i]==' '){
                if(zc1){
                    zc2=true;
                }
                break;
            }else{
                id=id*10+str[i]-'0';
            }
        }
        if(zc2){
            if(id<minmax[0]){
                minmax[0]=id;
            }else if(id>minmax[1]){
                minmax[1]=id;
            }
        }
    }
    in_r1.close();
    return minmax;
}
void Handle::Initialize(string crossPath,string roadPath,string carPath){
    string str;
    int* minmax;
    //cross
//    char str0[20]="cross.txt";
    minmax=minmaxid(crossPath);
    cross_base=minmax[0];
    int crosssum=minmax[1]-minmax[0]+1;
    crosss_length=crosssum+10;//数组大小//等于最大id-最小id+1+10//+10防止溢出
    crosss=new Cross*[crosss_length];//创建指针数组
    for(int i=0;i<crosss_length;i++){
        crosss[i]=NULL;
    }
    cross_road=new int*[crosss_length];
    for(int i=0;i<crosss_length;i++) {
        cross_road[i] = new int[crosss_length];
        for (int j = 0; j < crosss_length; j++) {
            cross_road[i][j] = -1;//无路
        }
    }
    ifstream in_c(crossPath);
    while(!in_c.eof()){
        getline(in_c,str);
        int sz[8];
        int szl=0;
        int ts=0;
        bool zc=false,sfsz=false;
        for(int i=0;i<str.length();i++){
            if(str[i]=='#'){
                zc=false;
                break;
            }else if(str[i]=='-'){
                if(str[i+1]=='1'){
                    sz[szl++]=-1;
                    ts=0;
                    sfsz=false;
                    i++;
                }
            }else if(str[i]=='('){
                ts=0;
                sfsz=false;
            }else if(str[i]==')'){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
                zc=true;
                break;
            }else if(str[i]==','||str[i]==' '){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
            }else if(str[i]>='0'&&str[i]<='9'){
                ts=ts*10+str[i]-'0';
                sfsz=true;
            }
        }
        if(zc){
            crosss[sz[0]-cross_base]=new Cross(sz[0],sz[1],sz[2],sz[3],sz[4]);
        }
    }

    in_c.close();
//		for(int i=0;i<=minmax[1]-minmax[0];i++){
//			cout<<crosss[i]->id<<" "<<crosss[i]->roads_id[0]<<" "<<crosss[i]->roads_id[1]<<" "<<crosss[i]->roads_id[2]<<" "<<crosss[i]->roads_id[3]<<" "<<endl;
//		}
    //road
//    char str01[]="road.txt";
    minmax=minmaxid(roadPath);
    road_base=minmax[0];
    roads_length=minmax[1]-minmax[0]+1+10;
    roads=new Road*[roads_length];//创建指针数组

    for(int i=0;i<roads_length;i++){
        roads[i]=NULL;
    }
    ifstream in_r(roadPath);
    while(!in_r.eof()){
        getline(in_r,str);
        int sz[10];
        int szl=0;
        int ts=0;
        bool zc=false,sfsz=false;
        for(int i=0;i<str.length();i++){
            if(str[i]=='#'){
                zc=false;
                break;
            }else if(str[i]=='('){
                ts=0;
                sfsz=false;
            }else if(str[i]==')'){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
                zc=true;
                break;
            }else if(str[i]==','||str[i]==' '){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
            }else if(str[i]>='0'&&str[i]<='9'){
                ts=ts*10+str[i]-'0';
                sfsz=true;
            }
        }

        if(zc){
            roads[sz[0]-road_base]=new Road(sz[0],sz[1],sz[2],sz[3],sz[4],sz[5],sz[6]);

            if(sz[6]==1){//双行道
                int jid=cross_road[sz[5]-cross_base][sz[4]-cross_base];
                if(jid==-1||roads[jid-road_base]->length>sz[1]){//两路口间有多条道路存放距离短的
                    cross_road[sz[5]-cross_base][sz[4]-cross_base]=sz[0];
                }
            }
            int jid=cross_road[sz[4]-cross_base][sz[5]-cross_base];
            if(jid==-1||roads[jid-road_base]->length>sz[1]){//两路口间有多条道路存放距离短的
                cross_road[sz[4]-cross_base][sz[5]-cross_base]=sz[0];
            }
        }
    }
    int roadsum=minmax[1]-minmax[0]+1;
    in_r.close();

//	for(int i=0;i<crosssum;i++){
//		for(int j=0;j<crosssum;j++){
//			cout<<i<<"to"<<j<<":"<<cross_road[i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	for(int i=0;i<=minmax[1]-minmax[0];i++){
//		cout<<roads[i]->id<<" "<<roads[i]->length<<" "<<roads[i]->speed<<" "<<roads[i]->channel<<" "<<roads[i]->from<<" "<<roads[i]->to<<" "<<roads[i]->one_way<<endl;
//	}
//	cout<<"<<<<<";

    //car
//    headcarLength=0;
    ifstream in_car(carPath);
    headcar=NULL;
    planheadcar=NULL;
    Car *thecar=NULL;
    Car *frontcar=NULL;//上一辆车
    while(!in_car.eof()){
        getline(in_car,str);
        int sz[8];
        int szl=0;
        int ts=0;
        bool zc=false,sfsz=false;
        for(int i=0;i<str.length();i++){
            if(str[i]=='#'){
                zc=false;
                break;
            }else if(str[i]=='('){
                ts=0;
                sfsz=false;
            }else if(str[i]==')'){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
                zc=true;
                break;
            }else if(str[i]==','||str[i]==' '){
                if(sfsz){
                    sz[szl++]=ts;
                    ts=0;
                    sfsz=false;
                }
            }else if(str[i]>='0'&&str[i]<='9'){
                ts=ts*10+str[i]-'0';
                sfsz=true;
            }
        }
        if(zc){
            if(frontcar!=NULL){
                thecar=new Car(sz[0],sz[1],sz[2],sz[3],sz[4],roadsum);///////////////////////可能改
                frontcar->backcar=thecar;
            }else{
                thecar=headcar=new Car(sz[0],sz[1],sz[2],sz[3],sz[4],roadsum);///////////////////////可能改
            }
            headcarLength++;
            thecar->frontcar=frontcar;
            frontcar=thecar;
        }
    }
    carsum=0;
    outputcar=new Car*[headcarLength];
    if(headcar!=NULL){
        minplanTime=headcar->planTime;
        maxplanTime=headcar->planTime;
    }else{
        minplanTime=-1;
        maxplanTime=-1;
    }
    for(Car *c=headcar;c!=NULL;c=c->backcar){
        outputcar[carsum++]=c;
        if(minplanTime>c->planTime){
            minplanTime=c->planTime;
        }else if(maxplanTime<c->planTime){
            maxplanTime=c->planTime;
        }
    }
//	headcar->backcar->backcar->backcar->backcar->backcar->backcar->backcar->backcar=NULL;///////////////
    headcar= MergesortBytimeid(headcar);
    headcar->frontcar=NULL;
    in_car.close();
    //nowTime=2;///////////
//sortById();
//	Car *carr=headcar;
//	while(carr!=NULL){
//		cout<<carr->id<<" "<<carr->from<<" "<<carr->to<<" "<<carr->speed<<" "<<carr->planTime<<endl;
//		carr=carr->backcar;
//	}

    OtherInitialize();
    GetShortestPath();
}
Car* Handle::sortById(int time,Car *theadcar){//等待出发车链表排序
    Car *i=theadcar;
    for(;i!=NULL&&i->planTime<=time;i=i->backcar){//找到满足出发时间的车部分链表
    }
    if(i!=NULL){//只有i前的要排序
        Car *c=i->backcar;//保留i是因为i的planTime大，不影响结果
        i->backcar=NULL;
        theadcar= MergesortByid(theadcar);
        for(Car *i2=theadcar;i2!=NULL;i2=i2->backcar){//重新连接链表
            if(i2->backcar==NULL){
                i2->backcar=c;
                break;
            }
        }
    }else {//所有链表都要排序
        theadcar = MergesortByid(theadcar);
    }
    theadcar->frontcar=NULL;
    return theadcar;
}
Car* Handle::MergesortBytimeid(Car *head){//归并排序//返回车头
    if(head==NULL||head->backcar==NULL){
        return head;
    }else{
        //快慢指针找到中间节点
        Car *fast=head;
        Car *slow=head;
        while(fast->backcar!=NULL&&fast->backcar->backcar!=NULL){
            fast=fast->backcar->backcar;//最终到末尾
            slow=slow->backcar;//最终到中间
        }
        fast=slow;
        slow=slow->backcar;
        fast->backcar=NULL;//链表中间分割
        fast= MergesortBytimeid(head);//前半段
        slow= MergesortBytimeid(slow);//后半段
        Car *chead,*tc;
        if(slow==NULL){
            return fast;
        }else if(fast==NULL){
            return slow;
        }
        if(fast->planTime<slow->planTime||fast->planTime==slow->planTime&&fast->id<slow->id){//确定链表头
            chead=fast;
            fast=fast->backcar;
        }else{
            chead=slow;
            slow=slow->backcar;
        }
        tc=chead;
        while(slow!=NULL&&fast!=NULL){
            if(fast->planTime<slow->planTime||fast->planTime==slow->planTime&&fast->id<slow->id){
                tc->backcar=fast;
                fast->frontcar=tc;////<更改>
                tc=fast;
                fast=fast->backcar;
            }else{
                tc->backcar=slow;
                slow->frontcar=tc;////<更改>
                tc=slow;
                slow=slow->backcar;
            }
        }
        if(fast!=NULL){
            tc->backcar=fast;
            fast->frontcar=tc;
        }else{
            slow->frontcar=tc;
            tc->backcar=slow;
        }
        chead->frontcar=NULL;
        return chead;
    }
}
Car* Handle::MergesortByid(Car *head){//归并排序//返回车头
    if(head==NULL||head->backcar==NULL){
        return head;
    }else{
        //快慢指针找到中间节点
        Car *fast=head;
        Car *slow=head;
        while(fast->backcar!=NULL&&fast->backcar->backcar!=NULL){
            fast=fast->backcar->backcar;//最终到末尾
            slow=slow->backcar;//最终到中间
        }
        fast=slow;
        slow=slow->backcar;
        fast->backcar=NULL;//链表中间分割
        fast= MergesortByid(head);//前半段
        slow= MergesortByid(slow);//后半段
        Car *chead,*tc;
        if(slow==NULL){
            return fast;
        }else if(fast==NULL){
            return slow;
        }
        if(fast->id<slow->id){//确定链表头
            chead=fast;
            fast=fast->backcar;
        }else{
            chead=slow;
            slow=slow->backcar;
        }
        tc=chead;
        while(slow!=NULL&&fast!=NULL){
            if(fast->id<slow->id){
                tc->backcar=fast;
                fast->frontcar=tc;////<更改>
                tc=fast;
                fast=fast->backcar;
            }else{
                tc->backcar=slow;
                slow->frontcar=tc;////<更改>
                tc=slow;
                slow=slow->backcar;
            }
        }
        if(fast!=NULL){
            tc->backcar=fast;
            fast->frontcar=tc;
        }else{
            slow->frontcar=tc;
            tc->backcar=slow;
        }
        chead->frontcar=NULL;
        return chead;
    }
}
void Handle::OtherInitialize(){
    sumCarsOnRoads=0;
    waitCarsum=0;
    Cross *lastcross=NULL;
    query_cross_length=0;
    this->nowTime=1;
    for(int i=0;i<crosss_length;i++){
        if(crosss[i]){
            if(lastcross){//不为NULL
                lastcross->nextcross=crosss[i];
                lastcross=crosss[i];
            }else{
                lastcross=headcross=crosss[i];
            }
            query_cross_length++;
        }
    }
    query_roads=new Road*[roads_length];
    query_roads_length=0;
    for(int i=0;i<roads_length;i++){
        if(roads[i]){
            query_roads[query_roads_length++]=roads[i];
        }
    }
    roadsTotalmil=0;
    for(int i=0;i<query_roads_length;i++){
        roadsTotalmil+=query_roads[i]->length;
    }
}
void Handle:: GetShortestPath(){
//	int **shortestPath;//二维数组最短路径，[i][j]存放从i到j第一个要经过的路口的id-cross_base//i,j用路口id-cross_base
//	int **cross_road;//两个路口间直接的路
//	int **shortestl;//最短路径长
    //初始化
    maxlong=1000000000;
    shortestPath=new int*[crosss_length];
    shortestl=new long long*[crosss_length];
    int shortroadsum[crosss_length][crosss_length];//记最短路径中道路的数目
    for(int i=0;i<crosss_length;i++){
        shortestPath[i]=new int[crosss_length];
        shortestl[i]=new long long[crosss_length];
        for(int j=0;j<crosss_length;j++){

            if(cross_road[i][j]<0){//无路
                shortestPath[i][j]=-1;
                shortestl[i][j]=maxlong;
                shortroadsum[i][j]=2*crosss_length;
            }else{
//				cout<<i<<" "<<j<<":"<<cross_road[i][j]-road_base<<endl;////////
                shortestl[i][j]=roads[cross_road[i][j]-road_base]->length;
                shortestPath[i][j]=j;//i->j有路，i紧接着要去j
                shortroadsum[i][j]=1;
            }
        }
    }
    //
//	cout<<shortestl[0][1]<<" "<<shortestl[1][0]<<endl;
    for(int k=0;k<crosss_length;k++){
        for(int i=0;i<crosss_length;i++){
            if(i==k){//i->i的结果会有些混乱
                continue;
            }
            for(int j=0;j<crosss_length;j++){
                if(i==j){//i->i的结果会有些混乱
                    continue;
                }
                if(shortestl[i][k]+shortestl[k][j]<shortestl[i][j]){
                    shortestl[i][j]=shortestl[i][k]+shortestl[k][j];
                    shortestPath[i][j]=shortestPath[i][k];
                    shortroadsum[i][j]=shortroadsum[i][k]+shortroadsum[k][j];
                }else if(shortestl[i][k]+shortestl[k][j]==shortestl[i][j]&&shortroadsum[i][k]+shortroadsum[k][j]<shortroadsum[i][j]){
                    //如果最短路一样长，则道路少的路径平均道路更长，道路越长越不容易成为最短路径中路，且车容量也大，不容易堵塞
                    shortestl[i][j]=shortestl[i][k]+shortestl[k][j];
                    shortestPath[i][j]=shortestPath[i][k];
                    shortroadsum[i][j]=shortroadsum[i][k]+shortroadsum[k][j];
                }
//				if(i==1&&j==2)
//				cout<<i+1<<" "<<j+1<<":"<<shortestPath[i][j]+1<<endl;////////
            }
        }
    }
//	cout<<shortestPath[0][1]<<" "<<shortestPath[1][2]<<endl;
//	///////////////////////////////////////////测试
//	for(int i=0;i<crosss_length;i++){
//		for(int j=0;j<crosss_length;j++){
//			cout<<i+cross_base<<"->"<<j+cross_base<<":";
//			if(shortestPath[i][j]==-1){
//				cout<<"NULL"<<endl;
//			}else{
//				cout<<i+cross_base<<",";
//				int ji=shortestPath[i][j];
//				while(ji!=j){
//					cout<<ji+cross_base<<",";
//					ji=shortestPath[ji][j];
//				}
//				cout<<j+cross_base<<endl;
//			}
//		}
//	}
////
    //////////////////////////////////////////////////

}
void Handle::printResult(string path) {
//    ofstream fout(path);
//    for(int i=0;i<carsum;i++){
//        Car *car=outputcar[i];
//        int crossid=car->from;
//        int j=0;
//        for(;j<car->now_routeLength;j++){
//            Road *road=roads[car->route[j]-road_base];
//            if(road->from==crossid){
//                crossid=road->to;
//            }else if(road->to==crossid){
//                if(road->one_way){
//                    cout<<car->id<<":"<<road->id<<"路反向"<<endl;
//                }else{
//                    crossid=road->from;
//                }
//            }else{
//                cout<<car->id<<"路径不连通"<<endl;
//            }
//            if(roads[car->route[j]-road_base]->to==car->to||roads[car->route[j]-road_base]->from==car->to){
//                if(j+1!=car->now_routeLength){
//                    cout<<car->id<<"路径超出"<<endl;
//                }
//            }
//        }
//    }
//    cout<<"over"<<endl;

    ofstream fout(path);
    for(int i=0;i<carsum;i++){
        Car *car=outputcar[i];
        fout<<"("<<car->id<<","<<car->starttime;
        for(int j=0;j<car->now_routeLength;j++){
            fout<<","<<car->route[j];
            if(roads[car->route[j]-road_base]->to==car->to||roads[car->route[j]-road_base]->from==car->to){
                fout<<")"<<endl;
                break;
            }
        }
    }
    fout.close();
}


//傅昊篇
bool aaaa(int i){
    if(i==1){
        return true;
    }
}//////////////19880
//判断到达它出发时间的车辆是否能够出发（走向的那个路口是否满）//done
bool Handle::waitGoCarIsCanGo(int roadId,int startCrossId) {
    Road *pRoad = roads[roadId - road_base];
    int channel = pRoad->channel;
    if(pRoad->one_way){
        Car **carlast = pRoad->carlast;
        int start=0;
        int end=channel-1;
        for (int i = start; i <=end ; ++i) {
            if(carlast[i]==NULL){
                return true;
            } else{
                int distance1 = carlast[i]->distance;
                if(distance1>1){
                    return true;
                }
            }
        }
    } else{
        Car **carlast = pRoad->carlast;
        int toCrossId = pRoad->to;
        int fromCrossId = pRoad->from;
        int duiMianId;
        if(startCrossId==toCrossId){
            duiMianId=fromCrossId;
        } else{
            duiMianId=toCrossId;
        }
        if(startCrossId>duiMianId){
            int start=channel;
            int end=channel+channel-1;
            for (int i = start; i <=end ; ++i) {
                if(carlast[i]==NULL){
                    return true;
                } else{
                    int distance1 = carlast[i]->distance;
                    if(distance1>1){
                        return true;
                    }
                }
            }
        } else{
            int start=0;
            int end=channel-1;
            for (int i = start; i <=end ; ++i) {
                if(carlast[i]==NULL){
                    return true;
                } else{
                    int distance1 = carlast[i]->distance;
                    if(distance1>1){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//在能出发的前提下判断能走哪条车道//done
int Handle::waitGoCarGoTocarChannel(int roadId, int startCrossId) {
    Road *pRoad = roads[roadId - road_base];
    int channel = pRoad->channel;
    if(pRoad->one_way){
        Car **carlast = pRoad->carlast;
        int start=0;
        int end=channel-1;
        for (int i = start; i <=end ; ++i) {
            if(carlast[i]==NULL){
                return i;
            } else{
                int distance1 = carlast[i]->distance;
                if(distance1>1){
                    return i;
                }
            }
        }
    } else{
        Car **carlast = pRoad->carlast;
        int toCrossId = pRoad->to;
        int fromCrossId = pRoad->from;
        int duiMianId;
        if(startCrossId==toCrossId){
            duiMianId=fromCrossId;
        } else{
            duiMianId=toCrossId;
        }
        if(startCrossId>duiMianId){
            int start=channel;
            int end=channel+channel-1;
            for (int i = start; i <=end ; ++i) {
                if(carlast[i]==NULL){
                    return i;
                } else{
                    int distance1 = carlast[i]->distance;
                    if(distance1>1){
                        return i;
                    }
                }
            }
        } else{
            int start=0;
            int end=channel-1;
            for (int i = start; i <=end ; ++i) {
                if(carlast[i]==NULL){
                    return i;
                } else{
                    int distance1 = carlast[i]->distance;
                    if(distance1>1){
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

//为某条道路上所有的车是否为终止态或等待的状态的确定（该方法对来去道均进行了处理）//done
void Handle::IswaitState(Road * road){
    int channel = road->channel;
    int start;
    int end;
    if(road->one_way){
        start=0;
        end=channel-1;
    } else{
        start=0;
        end=2*channel-1;
    }
    for (int i = start; i <=end ; ++i) {
        Car *tpCar = road->carhead[i];
        while(tpCar!=NULL){//<更改>
            Car *pCar=tpCar;
            tpCar=tpCar->backcar;//先储存下一辆车，不然可能丢失
            IsWaitStatetoCross(pCar, road);//不管这辆车是否是等待状态，下一辆车都检查//检测同时就赋了等待属性
        }//<更改>
//        if(pCar!=NULL){
//            int speed=min(road->speed,pCar->speed);
//            int distance1 = pCar->distance;
//            int sumdistance=road->length-distance1;
//            if(sumdistance>=speed*1){//不会出路口
//                pCar->IswaitState= false;
//                Car *car= pCar->backcar;
//                while (car!=NULL){
//                    car->IswaitState= false;
//                    car=car->backcar;
//                }
//            } else{//能到达路口，是否真正出路口，尚待定
//                //判断是否到达终点，如果到达了终点还对route数组遍历，会出问题
//                if(IsGoToEnd(pCar,road->id)){//如果头车到达终点，后面仍然判断等待终止状态
//
//                }
//                if(road->one_way&&pCar->to==road->to){
//                    pCar->IswaitState= true;
//                } else if(!road->one_way&&(pCar->to==road->from||pCar->to==road->to)){
//                    pCar->IswaitState= true;
//                } else{
//                    //不会到达终点
//                    int nextRoadId;
//                    int *routes = pCar->route;
//                    for (int j = pCar->now_routeLength-1; j >=0 ; j--) {
//                        if(routes[j]==road->id){
//                            nextRoadId=routes[j+1];
//                            Road *pRoad = roads[nextRoadId - road_base];
//                            int speed1 = min(pRoad->speed,pCar->speed);
//                            if(sumdistance-speed1*1>=0){
//                                pCar->IswaitState= false;
//                                Car *car= pCar->backcar;
//                                while (car!=NULL){
//                                    car->IswaitState= false;
//                                    car=car->backcar;
//                                }
//                            } else{
//                                pCar->IswaitState= true;
//                                Car *car1=pCar->backcar;
//                                while (car1!=NULL){
//                                    int tmpdistance=pCar->distance-car1->distance;
//                                    int v=min(car1->speed,road->speed);
//                                    if(v*1<tmpdistance){
//                                        car1->IswaitState= false;
//                                        Car * car2=car1->backcar;
//                                        while (car2!=NULL){
//                                            car2->IswaitState= false;
//                                            car2=car2->backcar;
//                                        }
//                                        break;
//                                    } else{
//                                        car1->IswaitState= true;
//                                        pCar=car1;
//                                        car1=car1->backcar;
//                                    }
//                                }
//                            }
//                            break;
//                        }
//                    }
//                }
//
//
//            }
//        }
    }
}

//判断某辆车是否为等待状态的车辆----(如果该车是终止状态，对他的distance进行了改变)//done
bool Handle::IsWaitStatetoCross(Car *car, Road *road) {//等待true终止false终点NULL(NULL==false)
    /////////////////////////////////////////////
//    bool bbb=false;
//    if(nowTime>7653&&car->id==12153&&road->id==5002){
//        bbb=aaaa(1);
//    }


    ////////////////////////////////////////

    int speed=min(road->speed,car->speed);
    int distance1 = car->distance;
    int sumdistance=road->length-distance1;
    if(car->frontcar!=NULL){//车在车道正前方有车阻挡//<更改>
        sumdistance=car->frontcar->distance-distance1;
        if(sumdistance<=speed*1){//受前车影响
            if(car->frontcar->IswaitState){
                car->IswaitState=true;
            }else{
                car->distance=car->frontcar->distance-1;
                car->IswaitState=false;
            }
        }else{
            car->distance+=speed*1;
            car->IswaitState=false;
        }
        return false;//暂时不过路口
    }//<更改>
    //无车阻挡，有机会过路口//


    if(sumdistance>=speed*1){
        car->distance=car->distance+speed*1;
        car->IswaitState=false;
        return false;
    }else{
        //是否到达终点
        if(IsGoToEnd(car,road->id)){//如果到达终点，返回false//<更改>
//        return NULL;//返回NULl和false一样
            return false;
        }
        int nextRoadId;
        int *routes = car->route;
        for (int j = car->now_routeLength-1; j >=0 ; j--) {
            if(routes[j]==road->id){
                nextRoadId=routes[j+1];
                Road *pRoad = roads[nextRoadId - road_base];
                int speed1 = min(pRoad->speed,car->speed);//<更改>
                if(sumdistance-speed1*1>=0){
                    car->distance=road->length;
                    car->IswaitState=false;
                    return false;
                } else{
                    car->IswaitState=true;
                    return true;
                }
            }

        }
    }
    return true;
}


//对某条道路上处于终止状态的车辆进行调度//done
void Handle::driveAllCarJustOnRoadToEndState(Road * road){
    int channel = road->channel;
    int start;
    int end;
    if(road->one_way){
        start=0;
        end=channel-1;
    } else{
        start=0;
        end=2*channel-1;
    }
    for (int i = start; i <=end ; ++i) {
        Car *pCar = road->carhead[i];
        if(pCar!=NULL){
            while (pCar!=NULL&&pCar->IswaitState){
                pCar=pCar->backcar;
            }
            while (pCar!=NULL){
                if(pCar==road->carhead[i]){
                    pCar->distance= min((pCar->distance+min(road->speed,pCar->speed)*1),road->length);
                } else{
                    pCar->distance=min(pCar->frontcar->distance-1,(pCar->distance+min(road->speed,pCar->speed)*1));
                }
                pCar=pCar->backcar;
            }
        }
    }
}

//得到通向该路口的某条道路中处于等待状态的车辆的数目//done
int Handle::ToCrossWaitStatueNum(Road *road, Cross *cross) {
    int sum = 0;
    if (road->one_way && road->to == cross->id) {
        int channel = road->channel;
        for (int i = 0; i < channel; ++i) {
            Car *pCar = road->carhead[i];
            while (pCar && pCar->IswaitState) {
                sum++;
                pCar = pCar->backcar;
            }
        }
    }
    if(!road->one_way) {
        int channel = road->channel;
        int id = cross->id;
        int from = road->from;
        int to = road->to;
        int duimianId;
        if(id==from){
            duimianId=to;
        } else{
            duimianId=from;
        }
        int small;
        int big;
        if(id<duimianId) {
            small=id;
            big=duimianId;
        } else {
            small=duimianId;
            big=id;
        }
        int start;
        int end;
        if(small==id) {
            start=channel;
            end=channel+channel-1;
        } else {
            start=0;
            end=channel-1;
        }
        for (int i = start; i <= end; ++i) {
            Car *pCar = road->carhead[i];
            while (pCar && pCar->IswaitState) {
                sum++;
                pCar = pCar->backcar;
            }
        }
    }
    return sum;
}

//得到通向该路口的所有道路中处于等待状态的车辆的数目//done
int Handle::ToCrossWaitStatueNum(int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *roadsMinid = pCross->roads_minid;
    int tmp=0;
    for (int i = 0; i <4 ; ++i) {
        if(roadsMinid[i]!=-1){
            tmp+=ToCrossWaitStatueNum(roads[roadsMinid[i]-road_base],pCross);
        }
    }
    return tmp;
}

//得到当前道路在按顺时针排好序的数组的对应索引//done
int Handle::getthisRoadIndexOnroads_id(int roadId,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *roadsId = pCross->roads_id;
    for (int i = 0; i <4 ; ++i) {
        if(roadsId[i]==roadId){
            return i;
        }
    }
    return -1;
}

//得到转向的标记  //1左转  2直行  3右转//done
int Handle::getNextDirection(int beginRoadIndexOnroads_id,int endRoadIndexOnroads_id){
    return (endRoadIndexOnroads_id-beginRoadIndexOnroads_id+4)%4;
}

//取得在按照顺时针排好的某条道路的对面道路的id //done
int Handle::getduimianRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+2)%4;
    return pInt[k];
}

//取得在按照顺时针排好的某条道路的左面道路的id //done
int Handle::getleftRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+1)%4;
    return pInt[k];
}

//取得在按照顺时针排好的某条道路的右面道路的id  //done
int Handle::getrightRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+3)%4;
    return pInt[k];
}

//判断在某个路口内a道路是否有可能通过该路口会到达b路口  //done
bool Handle::AisCanGotoBinOneCross(int aRoadId,int bRoadId,int crossId){
    Road *aRoad = roads[aRoadId - road_base];
    Road *bRoad = roads[bRoadId - road_base];
    if(aRoad->one_way&&bRoad->one_way){
        if(aRoad->to==crossId&&bRoad->from==crossId){
            return true;
        } else{
            return false;
        }
    } else if(aRoad->one_way&&!bRoad->one_way){
        if(aRoad->to==crossId){
            return true;
        } else{
            return false;
        }
    } else if(!aRoad->one_way&&bRoad->one_way){
        if(bRoad->from==crossId){
            return true;
        } else{
            return false;
        }
    } else{
        return true;
    }
}

//得到处于等待状态的车辆如果出发的话会走向哪一条道路  //前提：会通过路口不会到达终点//done
int Handle::NextToRoadIdBaseWaitStateCar(Car * car,int roadId){
    int *route = car->route;
    int routeLength = car->now_routeLength;
    for (int i = routeLength-1; i >=0 ; i--) {
        if(route[i]==roadId){
            return route[i+1];
        }
    }
    return -1;
}

//判断处于等待状态的车辆(优先级最高)下一时刻是否会到达终点  //done
bool Handle::IsGoToEnd(Car *car, int roadId) {//如果该车之前为等待状态，现到达终点，也不做处理，由调用它的代码处理
//    /////////////////////////////////////////
//    bool b=false;
//    if(nowTime==579&&roadId==5149){
//        b=aaaa(2);
//    }
////    ///////////////////////////////

    int to = car->to;
    if(roads[roadId-road_base]->one_way){
        if(roads[roadId-road_base]->to==to){
            //到达终点继续移动//<更改>
        } else{
            return false;
        }
    } else{
        if(roads[roadId-road_base]->from==to||roads[roadId-road_base]->to==to){
            //到达终点继续移动//<更改>
        } else{
            return false;
        }
    }
    int speed=min(car->speed,roads[roadId-road_base]->speed);
    if(speed<roads[roadId-road_base]->length-car->distance){//不能到达路口
        return false;
    }
    //<更改>
    sumCarsOnRoads--;
//    //    ////////////////////debug///////////////////
//    if(nowTime>159){
//        int iii=aaa();
//    }
////    ////////////////////debug/////////////////////
//    cout<<"路上车减一"<<endl;////////////////////////////////////
//    crosss[car->to-cross_base]->TothisCrosswaitCarsum--;///////////////////////////delete//////////////////////////出路口不再标记为等待状态
    int now_lane = car->now_lane;
    Road *pRoad = roads[roadId - road_base];
//    /////////////////////////debug////////////////////////////////
//    bool ab;
//    if(nowTime==725&&pRoad->id==5081){
//        ab=aaaa(2);
//    }
//    /////////////////////////////////////////////

    pRoad->carhead[now_lane]=car->backcar;
    if(car->backcar==NULL){
        pRoad->carlast[now_lane]=NULL;
    } else{
        car->backcar->frontcar=NULL;
    }
    if(pRoad->one_way){
        int from=pRoad->from;
        int to=pRoad->to;
        if(from<to){
            pRoad->carnumx--;  //对后加的属性的改变
        } else{
            pRoad->carnumd--; //对后加的属性的改变
        }
    } else{
        int from=pRoad->from;
        int to=pRoad->to;
        int small;
//        int big;
        if(from<to){
            small=from;
//            big=to;
        } else{
            small=to;
//            big=from;
        }
        if(small==car->to){
            pRoad->carnumd--; ////对后加的属性的改变
        } else{
            pRoad->carnumx--;//对后加的属性的改变
        }
    }
    car->backcar=car->frontcar=NULL;//<更改>
    car->IswaitState=false;//可能由于前车影响，该车之前是等待状态//<更改>
//    car->frontWaitCar=car->nextWaitCar=NULL;//到达终点等待链表还未改变，不能改指针情况//<更改>
    car->IstoEnd=true;
    return true;//<更改>
}

Car *Handle::findNowYoucianCar(Car **pCar,int size) {
    Car * car=NULL;
    for (int i = 0; i <size ; ++i) {
        if(pCar[i]!=NULL){
            car=pCar[i];
        }
    }
    for (int i = 0; i <size ; ++i) {
        if(pCar[i]!=NULL&&pCar[i]->distance>car->distance){
            car=pCar[i];
        }
    }
    return car;
}

//得到某条道路通向该路口的所有 处于等待状态的车辆的调度优先级的链表  //done
Car * Handle:: getWaitStatecarsTothisCross(Road * road,Cross * cross){
    Car * car=NULL;
    Car * tmpCar=NULL;
    int start;
    int end;
    int duimianId;
    int crossId = cross->id;
    int from = road->from;
    int to = road->to;
    if(from==crossId){
        duimianId=to;
    } else{
        duimianId=from;
    }
    int tmp1=road->channel;
    if(road->one_way&&to==crossId){
        start=0;
        end=road->channel-1;
        Car* cars[road->channel];
        for (int k = start; k <=end ; ++k) {
            if(road->carhead[k]!=NULL&&road->carhead[k]->IswaitState){
                cars[k-start]= road->carhead[k];
            }else{
                cars[k-start]=NULL;//<更改>
                tmp1--;
            }
        }
        while (tmp1>0) {
            Car * pCar=findNowYoucianCar(cars,road->channel);
            if(car==NULL){
                car=pCar;
                tmpCar=car;
                car->nextWaitCar=car->frontcar=NULL;
                if(pCar->backcar!=NULL&&pCar->backcar->IswaitState) {
                    cars[pCar->now_lane - start]=pCar->backcar;
                } else {
                    cars[pCar->now_lane - start]=NULL;
                    tmp1--;
                }
            } else{
                car->nextWaitCar=pCar;
                pCar->frontWaitCar=car;
                pCar->nextWaitCar=NULL;
                car=car->nextWaitCar;
                if(pCar->backcar!=NULL&&pCar->backcar->IswaitState) {
                    cars[pCar->now_lane - start]=pCar->backcar;
                } else {
                    cars[pCar->now_lane - start]=NULL;
                    tmp1--;
                }
            }
        }
    } else if(!road->one_way){
        if(cross->id<duimianId){
            start=road->channel;
            end=road->channel+road->channel-1;
        } else{
            start=0;
            end=road->channel-1;
        }
        int tmp2=road->channel;
        Car* cars[road->channel];
        for (int k = start; k <=end ; ++k) {
            if(road->carhead[k]!=NULL&&road->carhead[k]->IswaitState){
                Car *pCar = road->carhead[k];
                cars[k-start]=pCar;
            }else{
                cars[k-start]=NULL;//<更改>
                tmp2--;
            }
        }
        while (tmp2>0) {
            Car * pCar=findNowYoucianCar(cars,road->channel);
            if(car==NULL){
                car=pCar;
                tmpCar=car;
                car->nextWaitCar=car->frontcar=NULL;
                if(pCar->backcar!=NULL&&pCar->backcar->IswaitState) {
                    cars[pCar->now_lane - start]=pCar->backcar;
                } else {
                    cars[pCar->now_lane - start]=NULL;
                    tmp2--;
                }
            } else{
                car->nextWaitCar=pCar;
                pCar->frontWaitCar=car;
                pCar->nextWaitCar=NULL;
                car=car->nextWaitCar;
                if(pCar->backcar!=NULL&&pCar->backcar->IswaitState) {
                    cars[pCar->now_lane - start]=pCar->backcar;
                } else {
                    cars[pCar->now_lane - start]=NULL;
                    tmp2--;
                }
            }
        }

    }
    return tmpCar;
}

//得到某条道路通向该路口的所有 处于等待状态的车辆的调度优先级的链表//链表头  //done
Car * Handle:: getWaitStatecarsTothisCross(int roadId,int crossId){
    Road *pRoad = roads[roadId - road_base];
    if(pRoad->one_way){
        int from=pRoad->from;
        int to=pRoad->to;
        if(from<to){
            return pRoad->waitheadx;
        } else{
            return pRoad->waitheadd;
        }
    } else{
        int from=pRoad->from;
        int to=pRoad->to;
        int small;
        int big;
        if(from<to){
            small=from;
            big=to;
        } else{
            small=to;
            big=from;
        }
        if(small==crossId){
            return pRoad->waitheadd;
        } else{
            return pRoad->waitheadx;
        }

    }
}

//为道路的Waitheadx或者Waitheadh或者二者 赋值  //done
void Handle::weiWaitheadxOrWaitheadhFUZHI(int roadId) {
    Road *pRoad = roads[roadId - road_base];
    if(pRoad->one_way){
        int from = pRoad->from;
        int to = pRoad->to;
        if(from<to){
            pRoad->waitheadx=getWaitStatecarsTothisCross(pRoad,crosss[to-cross_base]);
        } else{
            pRoad->waitheadd=getWaitStatecarsTothisCross(pRoad,crosss[to-cross_base]);
        }
    } else{
        int from=pRoad->from;
        int to=pRoad->to;
        int small;
        int big;
        if(from<to){
            small=from;
            big=to;
        } else{
            small=to;
            big=from;
        }
        pRoad->waitheadx=getWaitStatecarsTothisCross(pRoad,crosss[big-cross_base]);
        pRoad->waitheadd=getWaitStatecarsTothisCross(pRoad,crosss[small-cross_base]);
    }
}

//处于等待状态的车俩移动后是否是等待状态
bool Handle::afterMoveIsWaitState(Car *car,int crossId,int roadId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]){
////    /////////////////////////////////////////
//    bool b=false;
//    if(nowTime>570&&roadId==5149){
//        b=aaaa(2);
//    }
////    ///////////////////////////////////////


    int toRoadId = GetNextGoToRoadId(roads[roadId - road_base], car);
    Road *pRoad = roads[toRoadId - road_base];
    Road *pRoad2 = roads[roadId - road_base];
    int tocarChannel = waitGoCarGoTocarChannel(toRoadId, crossId);
    if(tocarChannel==-1){
        if(pRoad->one_way){
            //int channel=pRoad->channel;
            if(pRoad->carlast[0]->IswaitState){
                for (int i = 0; i <FirOneIsWaitStateAndNoGoLength ; ++i) {
                    if(needSimulationRoad[i]==roadId){
                        FirOneIsWaitStateAndNoGo[i]= true;
                    }
                }
                return true;
            } else{
                car->distance=car->distance+min(min(car->speed,pRoad2->speed),pRoad2->length-car->distance);
                car->IswaitState= false;
                waitCarsum--;
                crosss[crossId-cross_base]->TothisCrosswaitCarsum--;
                //对等待车辆的链表进行处理--start
                if (pRoad2->one_way){
                    if(pRoad2->from<pRoad2->to){
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    } else{
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    }
                } else{
                    int from = pRoad2->from;
                    int to = pRoad2->to;
                    int duimianID;
                    if(from==crossId){
                        duimianID=to;
                    } else{
                        duimianID=from;
                    }
                    if(crossId<duimianID){
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    } else{
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    }
                }
                //对等待车辆的链表进行处理--end
                return false;
            }
        } else{
            int channel=pRoad->channel;
            int duimianID;
            int from = pRoad->from;
            int to = pRoad->to;
            if(from==crossId){
                duimianID=to;
            } else{
                duimianID=from;
            }
            int start;
            int end;
            if(crossId<duimianID){
                start=0;
                end=channel-1;
            } else{
                start=channel;
                end=channel+channel-1;
            }
            if(pRoad->carlast[start]->IswaitState){
                for (int i = 0; i <FirOneIsWaitStateAndNoGoLength ; ++i) {
                    if(needSimulationRoad[i]==roadId){
                        FirOneIsWaitStateAndNoGo[i]= true;
                    }
                }
                return true;
            } else{
                car->distance=car->distance+min(min(car->speed,pRoad2->speed),pRoad2->length-car->distance);
                car->IswaitState= false;
                waitCarsum--;
                crosss[crossId-cross_base]->TothisCrosswaitCarsum--;
//对等待车辆的链表进行处理--start
                if (pRoad2->one_way){
                    if(pRoad2->from<pRoad2->to){
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    } else{
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    }
                } else{
                    int from = pRoad2->from;
                    int to = pRoad2->to;
                    int duimianID;
                    if(from==crossId){
                        duimianID=to;
                    } else{
                        duimianID=from;
                    }
                    if(crossId<duimianID){
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    } else{
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                    }
                }
                //对等待车辆的链表进行处理--end
                return false;
            }
        }
    } else{
        //要去往的道路不满...


        Car *pCar = pRoad->carlast[tocarChannel];
        if(pCar==NULL){
            //离开本条车道
//            /////////////////////////debug////////////////////////////////
//            bool ab;
//            if(nowTime==725&&pRoad2->id==5081){
//                ab=aaaa(2);
//            }
//            /////////////////////////////////////////////


            if(car->backcar!=NULL){
                pRoad2->carhead[car->now_lane]=car->backcar;
                car->backcar->frontcar=NULL;
            } else{
                pRoad2->carhead[car->now_lane]=pRoad2->carlast[car->now_lane]=NULL;
                // car->backcar->frontcar=NULL;
            }

            //去往新的车道
            int dist = min(pRoad->speed ,car->speed)* 1 - (roads[roadId - road_base]->length - car->distance);
//            /////////////////////////debug////////////////////////////////
//            bool ab2;
//            if(nowTime==725&&pRoad->id==5081){
//                ab2=aaaa(2);
//            }
//            /////////////////////////////////////////////

            pRoad->carlast[tocarChannel]=pRoad->carhead[tocarChannel]=car;

            //为后加的属性carnumx或carnumd赋值--start(要去往的道路）
            if(pRoad->one_way){
                int from = pRoad->from;
                int to = pRoad->to;
                if(from<to){
                    pRoad->carnumx++;
                } else{
//                    ///////////////////debug//////////////////////
//                    bool b=false;
//                    if(nowTime>572&&pRoad->id==5149){
//                        b=aaaa(2);
//                    }
//                    //    ////////////////////////////



                    pRoad->carnumd++;
                }
            } else{
                int duimianId;
                int from = pRoad->from;
                int to = pRoad->to;
                if(from==crossId){
                    duimianId=to;
                } else{
                    duimianId=from;
                }
                if(crossId<duimianId){
                    pRoad->carnumx++;
                } else{
//                    ///////////////////debug//////////////////////
//                    bool b=false;
//                    if(nowTime>572&&pRoad->id==5149){
//                        b=aaaa(2);
//                    }
//                    //    ////////////////////////////


                    pRoad->carnumd++;
                }
            }
            //为后加的属性carnumx或carnumd赋值--end(要去往的道路）


            car->frontcar=car->backcar=NULL;
//            ///////////////////debug///////////////////
//            bool a2b=false;
//            if(car->frontcar==car){
//                a2b=aaaa(2);
//            }
//            ///////////////////////////////////



            car->now_lane=tocarChannel;
            car->IswaitState= false;
            car->distance=dist;
            waitCarsum--;
            crosss[crossId-cross_base]->TothisCrosswaitCarsum--;

            //对等待车辆的链表进行处理--start
            if (pRoad2->one_way){
                if(pRoad2->from<pRoad2->to){
                    pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                    if(pRoad2->waitheadx!=NULL)
                        pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumx--;//对后加的属性的改变
                } else{
                    pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                    if(pRoad2->waitheadd!=NULL)//<更改>pRoad2写成了pRoad！！！
                        pRoad2->waitheadd->frontWaitCar=NULL;//<更改>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumd--;//对后加的属性的改变
                }
            } else{
                int from = pRoad2->from;
                int to = pRoad2->to;
                int duimianID;
                if(from==crossId){
                    duimianID=to;
                } else{
                    duimianID=from;
                }
                if(crossId<duimianID){
                    pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                    if(pRoad2->waitheadd!=NULL)//<更改>
                        pRoad2->waitheadd->frontWaitCar=NULL;//<更改>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumd--;//对后加的属性的改变
                } else{
                    pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                    if(pRoad2->waitheadx!=NULL)
                        pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumx--;//对后加的属性的改变
                }
            }
            //对等待车辆的链表进行处理--end
            return false;
        } else{

            //要去往的那条小道上有车
            int dist = min(pRoad->speed,car->speed) * 1 - (roads[roadId - road_base]->length - car->distance);
            if(pCar->distance<=dist){
                if(pCar->IswaitState){
                    //该车行走后为等待状态，不移动
                    for (int i = 0; i <FirOneIsWaitStateAndNoGoLength ; ++i) {
                        if(needSimulationRoad[i]==roadId){
                            FirOneIsWaitStateAndNoGo[i]= true;
                        }
                    }
                    return true;
                } else{
                    //基本属性的改变
                    waitCarsum--;
                    crosss[crossId-cross_base]->TothisCrosswaitCarsum--;

                    //对原车道的链表进行改变
                    if(car->backcar==NULL){
                        pRoad2->carlast[car->now_lane]=pRoad2->carhead[car->now_lane]=NULL;
                    } else{
//                        /////////////////////////debug////////////////////////////////
//                        bool ab;
//                        if(nowTime==725&&pRoad2->id==5081){
//                            ab=aaaa(2);
//                        }
//                        /////////////////////////////////////////////


                        pRoad2->carhead[car->now_lane]=car->backcar;
                        car->backcar->frontcar=NULL;

                    }


                    //对等待车辆的链表进行处理--start
                    if (pRoad2->one_way){
                        if(pRoad2->from<pRoad2->to){
                            if(pRoad2->waitheadx->nextWaitCar!=NULL){
                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                            if(pRoad2->waitheadx!=NULL)
                                pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumx--;//对后加的属性的改变
                        } else{
                            if(pRoad2->waitheadd->nextWaitCar!=NULL){
                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumd--;//对后加的属性的改变
                        }

                    } else{
                        int from = pRoad2->from;
                        int to = pRoad2->to;
                        int duimianID;
                        if(from==crossId){
                            duimianID=to;
                        } else{
                            duimianID=from;
                        }
                        if(crossId<duimianID){
                            if(pRoad2->waitheadd->nextWaitCar!=NULL){
                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumd--;//对后加的属性的改变
                        } else{
                            if(pRoad2->waitheadx->nextWaitCar!=NULL){
                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                            if(pRoad2->waitheadx!=NULL)
                                pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumx--;//对后加的属性的改变
                        }
                    }
                    //对等待车辆的链表进行处理--end

                    //对车移动后链表进行改变
                    car->frontcar=pRoad->carlast[tocarChannel];
                    car->backcar=NULL;
                    pRoad->carlast[tocarChannel]->backcar=car;
                    pRoad->carlast[tocarChannel]=car;
                    car->now_lane=tocarChannel;
                    car->distance=car->frontcar->distance-1;
                    car->IswaitState= false;
                    car->nextWaitCar=NULL;

                    //为后加的属性carnumx或carnumd赋值--start
                    if(pRoad->one_way){
                        int from = pRoad->from;
                        int to = pRoad->to;
                        if(from<to){
                            pRoad->carnumx++;//<更改>
                        } else{
//                            ///////////////////debug//////////////////////
//                            bool b=false;
//                            if(nowTime>572&&pRoad->id==5149){
//                                b=aaaa(2);
//                            }
//                            //    ////////////////////////////


                            pRoad->carnumd++;//<更改>
                        }
                    } else{
                        int duimianId;
                        int from = pRoad->from;
                        int to = pRoad->to;
                        if(from==crossId){
                            duimianId=to;
                        } else{
                            duimianId=from;
                        }
                        if(crossId<duimianId){
                            pRoad->carnumx++;
                        } else{
//                            ///////////////////debug//////////////////////
//                            bool b=false;
//                            if(nowTime>572&&pRoad->id==5149){
//                                b=aaaa(2);
//                            }
//                            //    ////////////////////////////


                            pRoad->carnumd++;
                        }
                    }
                    //为后加的属性carnumx或carnumd赋值--end


                    return false;//缺少返回值//更改
                }
            } else{
                //基本属性的改变
                waitCarsum--;
                crosss[crossId-cross_base]->TothisCrosswaitCarsum--;

                //对原车道的链表进行改变
                if(car->backcar==NULL){
                    pRoad2->carlast[car->now_lane]=pRoad2->carhead[car->now_lane]=NULL;
                } else{
//                    /////////////////////////debug////////////////////////////////
//                    bool ab;
//                    if(nowTime==725&&pRoad2->id==5081){
//                        ab=aaaa(2);
//                    }
//                    /////////////////////////////////////////////


                    pRoad2->carhead[car->now_lane]=car->backcar;
                    car->backcar->frontcar=NULL;

                }


//对等待车辆的链表进行处理--start
                if (pRoad2->one_way){
                    if(pRoad2->from<pRoad2->to){
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumx--;//对后加的属性的改变
                    } else{
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumd--;//对后加的属性的改变
                    }

                } else{
                    int from = pRoad2->from;
                    int to = pRoad2->to;
                    int duimianID;
                    if(from==crossId){
                        duimianID=to;
                    } else{
                        duimianID=from;
                    }
                    if(crossId<duimianID){
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumd--;//对后加的属性的改变
                    } else{
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumx--;//对后加的属性的改变
                    }
                }
                //对等待车辆的链表进行处理--end

                //对车移动后链表进行改变
                car->frontcar=pRoad->carlast[tocarChannel];
//                ///////////////////debug///////////////////
//                bool a2b=false;
//                if(car->frontcar==car){
//                    a2b=aaaa(2);
//                }
//                ///////////////////////////////////


                car->backcar=NULL;
                pRoad->carlast[tocarChannel]->backcar=car;
                pRoad->carlast[tocarChannel]=car;
                car->now_lane=tocarChannel;
                car->distance=dist;
                car->IswaitState= false;
                car->nextWaitCar=car->frontWaitCar=NULL;

                //为后加的属性carnumx或carnumd赋值--start
                if(pRoad->one_way){
                    int from = pRoad->from;
                    int to = pRoad->to;
                    if(from<to){
                        pRoad->carnumx++;//<更改>
                    } else{
//                        ///////////////////debug//////////////////////
//                        bool b=false;
//                        if(nowTime>572&&pRoad->id==5149){
//                            b=aaaa(2);
//                        }
//                        //    ////////////////////////////


                        pRoad->carnumd++;//<更改>
                    }
                } else{
                    int duimianId;
                    int from = pRoad->from;
                    int to = pRoad->to;
                    if(from==crossId){
                        duimianId=to;
                    } else{
                        duimianId=from;
                    }
                    if(crossId<duimianId){
                        pRoad->carnumx++;
                    } else{
//                        ///////////////////debug//////////////////////
//                        bool b=false;
//                        if(nowTime>572&&pRoad->id==5149){
//                            b=aaaa(2);
//                        }
//                        //    ////////////////////////////


                        pRoad->carnumd++;
                    }
                }
//                if(pRoad->one_way){//多执行一了遍!//<更改>
//                    int from = pRoad->from;
//                    int to = pRoad->to;
//                    if(from<to){
//                        pRoad->carnumx++;//<更改>
//                    } else{
//                        pRoad->carnumd++;//<更改>
//                    }
//                } else{
//                    int duimianId;
//                    int from = pRoad->from;
//                    int to = pRoad->to;
//                    if(from==crossId){
//                        duimianId=to;
//                    } else{
//                        duimianId=from;
//                    }
//                    if(crossId<duimianId){
//                        pRoad->carnumx++;
//                    } else{
//                        pRoad->carnumd++;
//                    }
//                }
                //为后加的属性carnumx或carnumd赋值--end
            }
        }

    }
    return false;//缺少返回值//<更改>
}
bool Handle::IsChongTu(Car * car,int roadId,int crossId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]) {
    int nextToRoadId = NextToRoadIdBaseWaitStateCar(car, roadId);
    int direction = getNextDirection(
            getthisRoadIndexOnroads_id(roadId, crossId),
            getthisRoadIndexOnroads_id(nextToRoadId, crossId));
    if (direction == 1) {  //左转
        //取得左转要去往的道路id的对面的道路id，判断它的优先级第一的车是否为直行
        int duimianRoadId = getduimianRoadId(getthisRoadIndexOnroads_id(nextToRoadId,crossId),crossId);
        bool sff=false;//<更改>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==duimianRoadId){
                sff=FirOneIsWaitStateAndNoGo[i];
            }
        }//<更改>
        if(duimianRoadId !=-1&&!sff){//直行的有路且不费//<更改>
            Road *duimianRoad = roads[duimianRoadId - road_base];
            if (AisCanGotoBinOneCross(duimianRoadId, nextToRoadId, crossId)) {
                //取得A道路上所有处于等待状态车辆的链表
                Car *pCar = getWaitStatecarsTothisCross(duimianRoadId, crossId);
                if (pCar != NULL && NextToRoadIdBaseWaitStateCar(pCar, duimianRoadId) == nextToRoadId) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }else{
            return false;
        }
    } else if (direction == 2) {  //直行
        return false;
    } else {  //右转
        //取得右转要去往的道路id的对面的道路id，判断它的优先级第一的车是否为直行
        int duimianRoadId = getduimianRoadId(getthisRoadIndexOnroads_id(nextToRoadId, crossId),crossId);
        bool sff=false;//<更改>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==duimianRoadId){
                sff=FirOneIsWaitStateAndNoGo[i];
            }
        }//<更改>
        if(duimianRoadId!=-1&&!sff){//直行有路且不费//<更改>
            Road *duimianRoad = roads[duimianRoadId - road_base];
            if (AisCanGotoBinOneCross(duimianRoadId, nextToRoadId, crossId)) {
                Car *pCar = getWaitStatecarsTothisCross(duimianRoadId, crossId);
                if (pCar != NULL && NextToRoadIdBaseWaitStateCar(pCar, duimianRoadId) == nextToRoadId) {
                    return true;
                } else {
                    //啥也不干
                }
            } else {
                //啥也不干
            }
        }

        //取得右转要去往的道路id的右边的道路id，判断它的优先级第一的车是否为左转
        //取得右转要去往的道路id的对面的道路id，判断它的优先级第一的车是否为直行
        int rightbianRoadId = getrightRoadId(getthisRoadIndexOnroads_id(nextToRoadId, crossId),
                                             crossId);
        bool sff2=false;//<更改>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==rightbianRoadId ){
                sff2=FirOneIsWaitStateAndNoGo[i];
            }
        }//<更改>
        if(rightbianRoadId!=-1&&!sff2){//左转的有路且不费//<更改>
            Road *rightRoad = roads[rightbianRoadId - road_base];
            if (AisCanGotoBinOneCross(rightbianRoadId, nextToRoadId, crossId)) {
                Car *pCar = getWaitStatecarsTothisCross(rightbianRoadId, crossId);
                if (pCar != NULL && NextToRoadIdBaseWaitStateCar(pCar, rightbianRoadId) == nextToRoadId) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }else{
            return false;
        }

    }

}

int Handle::GetNextGoToRoadId(Road *road, Car *car) {
//    ////////////////////
//    if(nowTime==575&&road->id==5141){
//        int *route = car->route;
//        int i;
//        for (i = car->now_routeLength-1; i>=0 ; i--) {
//            cout<<car->route[i]<<" :"<<road->id<<endl;
//        }
//    }
//
//
//    ///////////////////////

    int *route = car->route;
    int i;
    for (i = car->now_routeLength-1; i>=0 ; i--) {
        if(route[i]==road->id){
            if(i+1<car->now_routeLength)//<更改>
                return route[i+1];
        } else{
//            return -1;//最后一个路可能不是当前路<更改>
        }
    }
    return -1;//<更改>
}// done  该方法的实现重复了
bool Handle::FirOneIsWaitStateAndNoGo_AllTrue(bool FirOneIsWaitStateAndNoGo[],int num){
    int remark=0;
    for (int i = 0; i <num ; ++i) {
        if(FirOneIsWaitStateAndNoGo[i]== true){

        } else{
            remark=1;
        }
    }
    if(remark==0){
        return true;
    } else{
        return false;
    }
}//done

bool Handle::A(Car * car,int crossId,int roadId, bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]){
    if(car==NULL){return true;}//<更改>
    if(roads[roadId-road_base]->waitheadd!=car&&roads[roadId-road_base]->waitheadx!=car){//如果改车不是等待链表头，也不能执行该方法
        return true;
    }
//    bool isGetToEnd=IsGoToEnd(car,roadId);//能到达路口且为等待状态不会是到达终点车
//    if(isGetToEnd){
//        ////////////////////////////判断是否到达终点，如果到达返回false，否则继续判断是否冲突
//
//        return false;
//    } else{
    ////////////////////////////判断是否冲突，如果冲突返回true，否则继续。。。
    if(IsChongTu( car,roadId,crossId, FirOneIsWaitStateAndNoGo,FirOneIsWaitStateAndNoGoLength, needSimulationRoad)){
        return true;
    } else{
        if(afterMoveIsWaitState(car,crossId,roadId, FirOneIsWaitStateAndNoGo,FirOneIsWaitStateAndNoGoLength,needSimulationRoad)){
            return true;
        } else{
            return false;
        }
    }
//    }
}

bool Handle::Simulation() {
    if(sumCarsOnRoads==0) {
        if(headcarLength>0){
//            cout<<"now"<<nowTime<<endl;
            planheadcar=sortById(this->nowTime,planheadcar);
            int nowTime=this->nowTime;//？？？不加this->nowTime，nowTime=nowTime为0！！！
            Car *waitGoCars=planheadcar;
            int headwaitGoCarsTime=waitGoCars->planTime;
//            cout<<"<<<<<<<<<<<<"<<headwaitGoCarsTime<<"   "<<nowTime<<endl;//////////////
            if(headwaitGoCarsTime>nowTime){

            } else{
                //  Car waitGoCarsArray[headcarLength];
                Car *tmpwaitGoCars =waitGoCars;
                while (tmpwaitGoCars!=NULL&&tmpwaitGoCars->planTime<=nowTime){
                    Car *tempjcar=tmpwaitGoCars->backcar;//tmpwaitGoCars的backcar可能会修改，下一辆车对象丢失//<更改>
                    Car *car = tmpwaitGoCars;
                    int startCrossId = car->from;
                    int *routes = car->route;
                    //判断要出发的道路是否满了
                    int startRoadId = car->route[0];
                    /////////////////////////////////////


                    //////////////////////


                    if(startRoadId!=-1&&waitGoCarIsCanGo(startRoadId,car->from)){//<更改>
                        //如果不满，出发
                        //(预准备)出发，从待出发的车辆中移除该车辆---start
                        Car *frontcar = car->frontcar;
                        Car *backcar = car->backcar;
                        if(frontcar==NULL&&backcar==NULL){
                            planheadcar=NULL;
                        } else if(frontcar==NULL&&backcar!=NULL){
                            backcar->frontcar=NULL;
//                           bool abc;
//                            /////////////////////debug////////////////////////
//                            if(nowTime>720){
//                                abc=aaaa(2);
//                            }
//
//                            ///////////////////////////////////////////////

                            planheadcar=backcar;
                        } else if(frontcar!=NULL&&backcar==NULL){
                            frontcar->backcar=NULL;
                        } else{
                            frontcar->backcar=backcar;
                            backcar->frontcar=frontcar;
//                            ///////////////////debug///////////////////
//                            bool a2b=false;
//                            if(backcar->frontcar==backcar){
//                                a2b=aaaa(2);
//                            }
//                            ///////////////////////////////////

                        }
                        //出发，从待出发的车辆中移除该车辆---end
                        headcarLength--;
                        sumCarsOnRoads++;
//                        cout<<nowTime<<"----"<<car->id<<"start"<<endl;/////////////////////////
                        //正式出发(对车辆和道路的属性进行修改)---start
                        Car *pCar = car;
                        int i = waitGoCarGoTocarChannel(startRoadId, car->from);//得到要进入哪条道
                        //  改变该车的实际速度,在道路上的行驶距离，实际开始时间，车链表,车所处的车道
                        //1.该车的实际开始时间
                        pCar->starttime=nowTime;
                        //2..求该车的distance(取得道路限速，该车期望速度，前车行驶距离)
                        int speed=pCar->speed;  //期望速度
                        Road *pRoad = roads[startRoadId - road_base];
                        int roadMaxSpeed = pRoad->speed;
                        //Car *car1 = pRoad->carlast[i]->backcar;
                        Car *car1 = pRoad->carlast[i];
                        if(car1==NULL){
                            pCar->distance=min(speed,roadMaxSpeed)*1;
                        } else{
                            int nowdistance = pRoad->carlast[i]->distance; //该车的前一辆车的行走距离
                            pCar->distance=min(nowdistance-1,min(speed,roadMaxSpeed)*1);
                        }

                        //3..改变车在的道路
                        pCar->now_lane=i;

                        //对道路属性的修改
                        //对carhead或carlast的修改,同时对汽车的属性进行了修改--start
//                        /////////////////////////debug////////////////////////////////
//                        bool ab;
//                        if(nowTime==725&&pRoad->id==5081){
//                            ab=aaaa(2);
//                        }
//                        /////////////////////////////////////////////


                        if(pRoad->carlast[i]==NULL){
                            pRoad->carlast[i]=pRoad->carhead[i]=pCar;
                            pCar->frontcar=pCar->backcar=NULL;
                        } else{
                            pRoad->carlast[i]->backcar=pCar;
                            pCar->frontcar=pRoad->carlast[i];
//                            ///////////////////debug///////////////////
//                            bool a2b=false;
//                            if(pCar->frontcar==pCar){
//                                a2b=aaaa(2);
//                            }
//                            ///////////////////////////////////



                            pCar->backcar=NULL;
                            pRoad->carlast[i]=pCar;
                        }
                        //对carhead或carlast的修改,同时对汽车的属性进行了修改--end
                        //carnumx或carnumd赋值--start
                        Road *pRoad1 = roads[startRoadId - road_base];
                        if(pRoad1->one_way){
                            int from = pRoad1->from;
                            int to = pRoad1->to;
                            if(from<to){
                                pRoad1->carnumx++;
                            } else{
//                                ///////////////////debug//////////////////////
//                                bool b=false;
//                                if(nowTime>572&&pRoad->id==5149){
//                                    b=aaaa(2);
//                                }
//                                //    ////////////////////////////

                                pRoad1->carnumd++;
                            }
                        } else{
                            int duimianId;
                            int from = pRoad1->from;
                            int to = pRoad1->to;
                            if(from==startCrossId){
                                duimianId=to;
                            } else{
                                duimianId=from;
                            }
                            if(startCrossId<duimianId){
                                pRoad1->carnumx++;
                            } else{
//                                ///////////////////debug//////////////////////
//                                bool b=false;
//                                if(nowTime>572&&pRoad->id==5149){
//                                    b=aaaa(2);
//                                }
//                                //    ////////////////////////////


                                pRoad1->carnumd++;
                            }
                        }
                        //carnumx或carnumd赋值--end

                        //特别说明:Car的bool IswaitState; Car * nextWaitCar; Car * frontWaitCar;
                        //道路的Car * waitheadx;  Car * waitheadd;
                        //Handle里的waitCarsum未进行任何改动，，这些属性都需要在调度路上的车辆时进行操作


                    } else{
                        //满了，不出发
                    }
                    tmpwaitGoCars=tempjcar;
                }

            }
        }
    } else{
        //思路：
        // 1.先判断车的状态是等待还是终止
        // 2.对路上的所有处于终止状态的车进行调度一个单位时间的距离改变
        // 3.调度路上处于等待状态的车辆
        //...
        //...
        // 4.所有在路上的车辆都调度完成，进行处于未出发状态车辆的调度

        //实现------
        // 1.先判断车的状态是等待还是终止---start//如果终止已经移动
        for (int i = 0; i <query_roads_length ; ++i) {
            IswaitState(query_roads[i]);
        }
        // 判断车的状态是等待还是终止---end
        for (int i = 0; i <query_roads_length ; ++i) {//形成每条道路等待状态车链表
            weiWaitheadxOrWaitheadhFUZHI(query_roads[i]->id);
        }
        //2.求所有车道的总的等待的车辆数---start
        this->waitCarsum=0;
        Cross *cross = headcross;
        while (cross!=NULL) {
            int *roadsMinid = cross->roads_minid;
            for (int i = 0; i <4 ; ++i) {
                if(roadsMinid[i]!=-1){
                    waitCarsum+=ToCrossWaitStatueNum(roads[roadsMinid[i]-road_base],cross);
                }
            }
            cross=cross->nextcross;
        }
        //求所有车道的总的等待的车辆数---end

//        // 3..对路上的所有处于终止状态的车进行调度一个单位时间的距离改变--start//之前就移动，此处不再移动<更改>
//        for (int j = 0; j <query_roads_length ; ++j) {
//            driveAllCarJustOnRoadToEndState(query_roads[j]);
//        }
        // 对路上的所有处于终止状态的车进行调度一个单位时间的距离改变--end

        // 4..调度路上处于等待状态的车辆--start

        int tmpCount=0;
        while (tmpCount<=query_cross_length&&waitCarsum>0){
            Cross *nowcross=headcross;
            for (; nowcross!=NULL; nowcross=nowcross->nextcross) {
                /////////////////////////debug//////////////////////////////////
                if(nowTime==1143&&nowcross->id==66){
//                    cout<<nowcross->id<<endl;
                        aaaa(2);
                }
                /////////////////////////////////////////////////////////////


                //   int *roadsId = nowcross->roads_id;
                int *roadsMinid = nowcross->roads_minid;
                //拿到当前要调度的路口的道路id链表开始对该路口调度
                int needChangeroadsNum = 0;
                for (int j = 0; j < 4; ++j) {
                    int i = roadsMinid[j];
                    if (i != -1 && (!roads[i - road_base]->one_way || (roads[i - road_base]->one_way && roads[i - road_base]->to == nowcross->id))) {
                        needChangeroadsNum++;
                    }
                }
                //该数组存放的是与下一个数组相应位置的id对应的车道优先级最高的车是否是离开后任然是等待状态而不能行走。
                bool FirOneIsWaitStateAndNoGo[needChangeroadsNum];
                for (int i = 0; i < needChangeroadsNum; ++i) {
                    FirOneIsWaitStateAndNoGo[i] = false;
                }
                //该数组存放的是该路口实际需要调度的车道的id从小到大
                int needSimulationRoad[needChangeroadsNum];
                int tmp = 0;
                for (int j = 0; j < 4; ++j) {
                    int i = roadsMinid[j];
                    if (i != -1 && (!roads[i - road_base]->one_way ||
                                    (roads[i - road_base]->one_way && roads[i - road_base]->to == nowcross->id))) {
                        //  needChangeroadsNum++;
                        needSimulationRoad[tmp] = i;
                        tmp++;
                    }
                }
                nowcross->TothisCrosswaitCarsum = ToCrossWaitStatueNum(nowcross->id);
                //接下来的while循环结束的条件是正在调度的路口的全部道路的第一优先级的车辆调度后为等待状态不能前进或者通向该路口内全部车辆为终止状态的车辆
                //需要一个标志位和通向该路口的道路中处于等待状态的车的数目和
                while (!(FirOneIsWaitStateAndNoGo_AllTrue(FirOneIsWaitStateAndNoGo, needChangeroadsNum) ||
                         nowcross->TothisCrosswaitCarsum == 0)) {
                    //  int toRoadId = GetNextGoToRoadId(roads[*roadsMinid - road_base], waitStatecarsTothisCross);
                    for (int i = 0; i < needChangeroadsNum; i++) {//<更改>
                        if(FirOneIsWaitStateAndNoGo[i]){//改道路标记为费，不用检查
                            continue;
                        }//<更改>
                        Car *firstCar  = getWaitStatecarsTothisCross(needSimulationRoad[i], nowcross->id);
                        if(firstCar==NULL){//改道路没有等待状态车  //<更改>
                            FirOneIsWaitStateAndNoGo[i]=true;//改道路不用再检查
                            continue;
                        }//<更改>
                        if(A(firstCar,nowcross->id,needSimulationRoad[i],&FirOneIsWaitStateAndNoGo[0],needChangeroadsNum,needSimulationRoad)){
                            continue;
                        } else{
                            Car *waitStatecarsTothisCross3 = getWaitStatecarsTothisCross(needSimulationRoad[i], nowcross->id);
                            for (;waitStatecarsTothisCross3!=NULL; ) {
                                Car *waitStatecarsTothisCross2=waitStatecarsTothisCross3;
                                waitStatecarsTothisCross3=waitStatecarsTothisCross3->nextWaitCar;//这辆车属性改变，可能丢失下一辆车的指针//<更改>
                                bool Waitbool= IsWaitStatetoCross(waitStatecarsTothisCross2,roads[needSimulationRoad[i] - road_base]);
                                if(!waitStatecarsTothisCross2->IstoEnd&&Waitbool){//车未到达终点且有希望过路口//<更改>
                                    A(waitStatecarsTothisCross2,nowcross->id,needSimulationRoad[i],&FirOneIsWaitStateAndNoGo[0],needChangeroadsNum,needSimulationRoad);
                                }else if(waitStatecarsTothisCross2->IstoEnd||!waitStatecarsTothisCross2->IswaitState){//如果车终止态移动或到达终点（判断函数不对等待链表处理）,更改等待链表
                                    Road *pRoad2 = roads[needSimulationRoad[i] - road_base];
                                    //对等待车辆的链表进行处理--start
                                    if (pRoad2->one_way){
                                        if(pRoad2->from<pRoad2->to){
                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                                                if(pRoad2->waitheadx!=NULL)
                                                    pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
//                                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;//<更改>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<更改>
                                                } else{
                                                }
                                            }
                                        } else{

                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                                                if(pRoad2->waitheadd!=NULL)
                                                    pRoad2->waitheadd->frontWaitCar=NULL;//<更改>
//                                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<更改>
                                                } else{
                                                }
                                            }
                                        }
                                    } else{
                                        int from = pRoad2->from;
                                        int to = pRoad2->to;
                                        int duimianID;
                                        if(from==nowcross->id){
                                            duimianID=to;
                                        } else{
                                            duimianID=from;
                                        }
                                        if(nowcross->id<duimianID){


                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                                                if(pRoad2->waitheadd!=NULL)
                                                    pRoad2->waitheadd->frontWaitCar=NULL;//<更改>
//                                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;//<更改>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//更改
                                                } else{
                                                }
                                            }
                                        } else{


                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                                                if(pRoad2->waitheadx!=NULL)
                                                    pRoad2->waitheadx->frontWaitCar=NULL;//<更改>
//                                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;//<更改>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<更改>
                                                } else{
                                                }
                                            }
                                        }
                                    }
                                    //对等待车辆的链表进行处理--end
                                    //有等待状态变为其他，对其他等待标识值更改
                                    nowcross->TothisCrosswaitCarsum--;//<更改>
                                    waitCarsum--;//<更改>
                                    waitStatecarsTothisCross2->nextWaitCar=waitStatecarsTothisCross2->frontWaitCar=NULL;
                                }
                            }
                        }
                    }
                }
            }
            tmpCount++;
//            if(tmpCount>this->query_cross_length-3){
////            cout<<"zhcs<<<<<<<<<<<<<<<<<:"<<tmpCount<<endl;/////////////////////////////
////                return false;
//                continue;
//            }else{
////            cout<<"zhcs<<<<<<<<<<<<<<<<<:"<<tmpCount<<endl;/////////////////////////////
//            }
//
//            cout<<"temp<<<<<<<<<<"<<tmpCount<<endl;/////////////////
        }
        if(tmpCount>this->query_cross_length){
//            cout<<"zhcs<<<<<<<<<<<<<<<<<:"<<tmpCount<<endl;/////////////////////////////
            return false;
        }else{
//            cout<<"zhcs<<<<<<<<<<<<<<<<<:"<<tmpCount<<endl;/////////////////////////////
        }
        // 4..调度路上处于等待状态的车辆--end
        //5.调度还未上路的车辆--start
        if(headcarLength>0){
//            ////////////////////debug////////////////////////////////
//            bool ab;
//            if(nowTime==725&&planheadcar!=NULL&&planheadcar->id==5092){
//                ab=aaaa(2);
//            }
//            /////////////////
            if(planheadcar==NULL){//没有计划出发的车，无需判断
                return true;
            }
            planheadcar=sortById(this->nowTime,planheadcar);
            int nowTime=this->nowTime;//<更改>
            Car *waitGoCars=planheadcar;
//            ////////////////////debug////////////////////////////////
//            bool ab22;
//            if(nowTime==725&&planheadcar!=NULL&&planheadcar->id==5092){
//                ab=aaaa(2);
//            }
//            /////////////////

            int headwaitGoCarsTime=waitGoCars->planTime;
            if(headwaitGoCarsTime>nowTime){

            } else{
                //  Car waitGoCarsArray[headcarLength];
                Car *tmpwaitGoCars =waitGoCars;
                while (tmpwaitGoCars!=NULL&&tmpwaitGoCars->planTime<=nowTime){
//                    ////////////////////debug////////////////////////////////
//                    bool ab;
//                    if(nowTime==279){
//                        ab=aaaa(2);
//                    }
//                    /////////////////


                    Car *car = tmpwaitGoCars;
                    tmpwaitGoCars=tmpwaitGoCars->backcar;//<更改>
                    int startCrossId = car->from;
                    int *routes = car->route;
                    //判断要出发的道路是否满了
                    int startRoadId = car->route[0];


                    if(startRoadId!=-1&&waitGoCarIsCanGo(startRoadId,car->from)){//<更改>
                        //如果不满，出发
                        //(预准备)出发，从待出发的车辆中移除该车辆---start
                        Car *frontcar = car->frontcar;
                        Car *backcar = car->backcar;
                        if(frontcar==NULL&&backcar==NULL){
                            planheadcar=NULL;
                        } else if(frontcar==NULL&&backcar!=NULL){
                            backcar->frontcar=NULL;
//                            bool abc;
//                            /////////////////////debug////////////////////////
//                            if(nowTime>720){
//                                abc=aaaa(2);
//                            }
//
//                            ///////////////////////////////////////////////


                            planheadcar=backcar;
                        } else if(frontcar!=NULL&&backcar==NULL){
                            frontcar->backcar=NULL;
                        } else{
                            frontcar->backcar=backcar;
                            backcar->frontcar=frontcar;
                            ///////////////////debug///////////////////
                            bool a2b=false;
//                            if(backcar->frontcar==backcar){
//                                a2b=aaaa(2);
//                            }
//                            ///////////////////////////////////


                        }
                        //出发，从待出发的车辆中移除该车辆---end
                        headcarLength--;
                        sumCarsOnRoads++;
//                        cout<<nowTime<<"----"<<car->id<<"start"<<endl;//////////////////////////
//                        return false;/////////////////
                        //正式出发(对车辆和道路的属性进行修改)---start
                        Car *pCar = car;
                        int i = waitGoCarGoTocarChannel(startRoadId, car->from);//得到要进入哪条道
                        //  改变该车的实际速度,在道路上的行驶距离，实际开始时间，车链表,车所处的车道
                        //1.该车的实际开始时间
                        pCar->starttime=nowTime;
                        //2..求该车的distance(取得道路限速，该车期望速度，前车行驶距离)
                        int speed=pCar->speed;  //期望速度
                        Road *pRoad = roads[startRoadId - road_base];
                        int roadMaxSpeed = pRoad->speed;
                        //Car *car1 = pRoad->carlast[i]->backcar;
                        Car *car1 = pRoad->carlast[i];
                        if(car1==NULL){
                            pCar->distance=min(speed,roadMaxSpeed)*1;
                        } else{
                            int nowdistance = pRoad->carlast[i]->distance; //该车的前一辆车的行走距离
                            pCar->distance=min(nowdistance-1,min(speed,roadMaxSpeed)*1);
                        }

                        //3..改变车在的道路
                        pCar->now_lane=i;

                        //对道路属性的修改
                        //对carhead或carlast的修改,同时对汽车的属性进行了修改--start
                        /////////////////////////debug////////////////////////////////
                        bool ab;
                        if(nowTime==725&&pRoad->id==5081){
                            ab=aaaa(2);
                        }
                        /////////////////////////////////////////////


                        if(pRoad->carlast[i]==NULL){
                            pRoad->carlast[i]=pRoad->carhead[i]=pCar;
                            pCar->frontcar=pCar->backcar=NULL;
                        } else{
                            pRoad->carlast[i]->backcar=pCar;
                            pCar->frontcar=pRoad->carlast[i];
//                            ///////////////////debug///////////////////
//                            bool a2b=false;
//                            if(pCar->frontcar==pCar){
//                                a2b=aaaa(2);
//                            }
//                            ///////////////////////////////////


                            pCar->backcar=NULL;
                            pRoad->carlast[i]=pCar;
                        }
                        //对carhead或carlast的修改,同时对汽车的属性进行了修改--end
                        //carnumx或carnumd赋值--start
                        Road *pRoad1 = roads[startRoadId - road_base];
                        if(pRoad1->one_way){
                            int from = pRoad1->from;
                            int to = pRoad1->to;
                            if(from<to){
                                pRoad1->carnumx++;
                            } else{
//                                ///////////////////debug//////////////////////
//                                bool b=false;
//                                if(nowTime>572&&pRoad->id==5149){
//                                    b=aaaa(2);
//                                }
//                                //    ////////////////////////////



                                pRoad1->carnumd++;
                            }
                        } else{
                            int duimianId;
                            int from = pRoad1->from;
                            int to = pRoad1->to;
                            if(from==startCrossId){
                                duimianId=to;
                            } else{
                                duimianId=from;
                            }
                            if(startCrossId<duimianId){
                                pRoad1->carnumx++;
                            } else{
//                                ///////////////////debug//////////////////////
//                                bool b=false;
//                                if(nowTime>572&&pRoad->id==5149){
//                                    b=aaaa(2);
//                                }
//                                //    ////////////////////////////


                                pRoad1->carnumd++;
                            }
                        }
                        //carnumx或carnumd赋值--end

                        //特别说明:Car的bool IswaitState; Car * nextWaitCar; Car * frontWaitCar;
                        //道路的Car * waitheadx;  Car * waitheadd;
                        //Handle里的waitCarsum未进行任何改动，，这些属性都需要在调度路上的车辆时进行操作


                    } else{
                        //满了，不出发
                    }

                }

            }
        }
        //5.调度还未上路的车辆--end
    }
    /////////////////////debug//////////////////////////////
    int js=0;
    for(int i=0;i<query_roads_length;i++){
        int end;
        if(query_roads[i]->one_way){
            end=query_roads[i]->channel;
        }else{
            end=query_roads[i]->channel*2;
        }
        for(int j=0;j<end;j++){
            if(query_roads[i]->carhead[j]!=NULL){
                js++;
            }
        }
    }
//    cout<<"车头数："<<js<<endl;
    /////////////////////debug/////////////////////////////////
    return true;
}
//白贺

int Handle::roadcarsum()
{
    int rcarsum=0;
    for(int i4=0;i4<query_roads_length;i4++){
        if(query_roads[i4]->one_way)
            rcarsum+=query_roads[i4]->channel*query_roads[i4]->length;
        else
            rcarsum+=2*query_roads[i4]->channel*query_roads[i4]->length;
    }
    return rcarsum;
}

bool aaa(int i){////////////////////////////
    if(i==2)
        return true;
}///////////////////////////////////
int Handle::threeroadselect(Cross *cur,int i,Car *cur1,int nroad)
{
//    bool aab=false;
//    ////////////////////////////////
//    if(nowTime==9313&&cur1->id==13011){
//        aaa(2);
//    }

    /////////////////////////
    Road *btemproad=roads[cur->roads_minid[i]-road_base];//////////////////////////////

    int dis[3];
    int rindex=1;
    for(int i2=0;i2<4;i2++){
        if(nroad==-1){
            dis[0]=-1;
        }
        if(cur->roads_id[i2]==nroad){
            dis[0]=i2;
        }
        else if(cur->roads_id[i2]!=nroad&&cur->roads_id[i2]!=cur->roads_minid[i]&&cur->roads_id[i2]!=-1){
            if(!roads[cur->roads_id[i2]-road_base]->one_way||roads[cur->roads_id[i2]-road_base]->from==cur->id){
                dis[rindex]=i2;
                rindex++;
            }
        }
    }
    if(rindex==1){
        dis[1]=-1;
        dis[2]=-1;
    }
    else if(rindex==2){
        dis[2]=-1;
    }
    else if(rindex==3){
        long long len1,len2;
        Road *temproad=roads[cur->roads_id[dis[1]]-road_base];//////////////////////////////
        if(!roads[cur->roads_id[dis[1]]-road_base]->one_way&&roads[cur->roads_id[dis[1]]-road_base]->to==cur->id){
            len1=shortestl[roads[cur->roads_id[dis[1]]-road_base]->from-cross_base][cur1->to-cross_base];//-cross_base<更改>
        }else{
            len1=shortestl[roads[cur->roads_id[dis[1]]-road_base]->to-cross_base][cur1->to-cross_base];//-cross_base<更改>
        }
        if(!roads[cur->roads_id[dis[2]]-road_base]->one_way&&roads[cur->roads_id[dis[2]]-road_base]->to==cur->id){
            len2=shortestl[roads[cur->roads_id[dis[2]]-road_base]->from-cross_base][cur1->to-cross_base];//-cross_base<更改>
        }else{
            len2=shortestl[roads[cur->roads_id[dis[2]]-road_base]->to-cross_base][cur1->to-cross_base];
        }
        if(len1>len2){
            int temp=dis[1];
            dis[1]=dis[2];
            dis[2]=temp;
        }
    }
    for(int m=0;m<3;m++){
//        cout<<dis[m]<<",";
    }
//    cout<<cur->roads_id[3]<<"   "<<cur->roads_minid[i]<<endl;
    int resindex=-1;
    for(int i3=0;i3<3;i3++){
        int c=0;
        if(dis[i3] >= 0 && dis[i3] <= 3 && cur->roads_id[dis[i3]] != -1){
            if(roads[cur->roads_id[dis[i3]]-road_base]->from==cur->id) {
                c=roads[cur->roads_id[dis[i3]]-road_base]->to;
            }else{
                c=roads[cur->roads_id[dis[i3]]-road_base]->from;
            }
        }
        if(dis[i3]<0||dis[i3]>3||cur->roads_id[dis[i3]]==-1||
           (roads[cur->roads_id[dis[i3]]-road_base]->one_way&&roads[cur->roads_id[dis[i3]]-road_base]->from!=cur->id)
           ||(shortestPath[c-cross_base][cur1->to-cross_base]==-1||shortestPath[c-cross_base][cur1->to-cross_base]+cross_base==cur->id)
           &&c!=cur1->to){//如果该路口是终点,也能走
            continue;
        }else{
            if(roads[cur->roads_id[dis[i3]]-road_base]->from==cur->id){
                if(roads[cur->roads_id[dis[i3]]-road_base]->to>cur->id){
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumx2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//进入下一条路
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumd2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//进入下一条路
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
            else if(roads[cur->roads_id[dis[i3]]-road_base]->to==cur->id&&!roads[cur->roads_id[dis[i3]]-road_base]->one_way){
                if(roads[cur->roads_id[dis[i3]]-road_base]->from>cur->id){
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumx2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//进入下一条路
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumd2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//进入下一条路
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
        }
    }
    if(resindex==-1){
        for(int i4=0;i4<3;i4++){
            if(dis[i4] >= 0 && dis[i4] <= 3 && cur->roads_id[dis[i4]] != -1){
                resindex=dis[i4];
//                cout<<cur->roads_id[dis[i4]];
                if(cur->id == roads[cur->roads_id[dis[i4]] - road_base]->from){
                    if(roads[cur->roads_id[dis[i4]]-road_base]->to>cur->id){
                        roads[cur->roads_id[dis[i4]]-road_base]->carnumx2++;
                    }
                    else{
                        roads[cur->roads_id[dis[i4]]-road_base]->carnumd2++;
                    }
                }
                else if(roads[cur->roads_id[dis[i4]]-road_base]->to==cur->id){
                    if(roads[cur->roads_id[dis[i4]]-road_base]->from>cur->id){
                        roads[cur->roads_id[dis[i4]]-road_base]->carnumx2++;
                    }
                    else{
                        roads[cur->roads_id[dis[i4]]-road_base]->carnumd2++;
                    }
                }
                return resindex;
            }
        }
    }
}

void Handle::cardirect(Cross *cur,int i,int i1)///<待改>
{
    for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
        int minspeed=min(roads[cur->roads_minid[i]-road_base]->speed,cur1->speed);//<更改>
        if(minspeed<=roads[cur->roads_minid[i]-road_base]->length-cur1->distance){
            break;//头车不过路口，后面车一定无法过路口
        }//<更改>
        if(cur->roads_minid[i]==cur1->route[cur1->now_routeLength-1]){//规划好的道路走完了
            if(cur1->to==cur->id){//得到终点不分配路线//<更改>
                continue;//后面车可能走
            }
            int ncross=shortestPath[cur->id-cross_base][cur1->to-cross_base];
            int nroad=cross_road[cur->id-cross_base][ncross];
            if(ncross==-1){
                nroad=-1;
            }
            int resindex=threeroadselect(cur,i,cur1,nroad);
            cur1->route[cur1->now_routeLength]=cur->roads_id[resindex];
            cur1->now_routeLength++;
//            int minv=0;
//            if(cur1->speed<roads[cur->roads_id[resindex]-road_base]->speed){
//                minv=cur1->speed;
//            }else{
//                minv=roads[cur->roads_id[resindex]-road_base]->speed;
//            }
//            if(minv>roads[cur->roads_minid[i]-road_base]->length-cur1->distance){
//                cur1->route[cur1->now_routeLength]=cur->roads_id[resindex];
//                cur1->now_routeLength++;
//            }
        }
    }
}

int Handle::fourroadselect(Car *curcar,int nroad)
{
    Cross *cross=crosss[curcar->from-cross_base];
    int dis[4];
    int rindex=1;
    for(int i5=0;i5<4;i5++){
        if(cross->roads_id[i5]==nroad){
            dis[0]=i5;
        }
        else if(cross->roads_id[i5]!=-1){////////////////////////
            dis[rindex]=i5;
            rindex++;
        }
    }
    if(rindex==1){
        dis[1]=-1;
        dis[2]=-1;
        dis[3]=-1;
    }
    else if(rindex==2){
        dis[2]=-1;
        dis[3]=-1;
    }
    else if(rindex==3){
        dis[3]=-1;
        long long len1,len2;
        if(roads[cross->roads_id[dis[1]]-road_base]->from==cross->id){
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->to-cross_base][curcar->to-cross_base];//<更改>
        }
        else if(roads[cross->roads_id[dis[1]] - road_base]->to == cross->id){
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->from-cross_base][curcar->to-cross_base];//<更改>
        }
        if(roads[cross->roads_id[dis[2]]-road_base]->from==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->to-cross_base][curcar->to-cross_base];//<更改>
        }
        else if(roads[cross->roads_id[dis[2]]-road_base]->to==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->from-cross_base][curcar->to-cross_base];//<更改>
        }
        if(len1>len2){
            int temp=dis[1];
            dis[1]=dis[2];
            dis[2]=temp;
        }
    }
    else if(rindex==4){
        long long len1,len2,len3;
        if(roads[cross->roads_id[dis[1]]-road_base]->from==cross->id){
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->to-cross_base][curcar->to-cross_base];//<更改>↓
        }
        else if(roads[cross->roads_id[dis[1]]-road_base]->to==cross->id){
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->from-cross_base][curcar->to-cross_base];
        }
        if(roads[cross->roads_id[dis[2]]-road_base]->from==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->to-cross_base][curcar->to-cross_base];
        }
        else if(roads[cross->roads_id[dis[2]]-road_base]->to==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->from-cross_base][curcar->to-cross_base];
        }
        if(roads[cross->roads_id[dis[3]]-road_base]->from==cross->id){
            len3=shortestl[roads[cross->roads_id[dis[3]]-road_base]->to-cross_base][curcar->to-cross_base];
        }
        else if(roads[cross->roads_id[dis[3]]-road_base]->to==cross->id){
            len3=shortestl[roads[cross->roads_id[dis[3]]-road_base]->from-cross_base][curcar->to-cross_base];
        }
        if(len1>len2){
            if(len2>len3){//321
                int temp=dis[1];
                dis[1]=dis[3];
                dis[3]=temp;
            }else{
                if(len1>len3){//231
                    int temp=dis[1];
                    dis[1]=dis[2];
                    dis[2]=dis[3];
                    dis[3]=temp;
                }else{//213
                    int temp=dis[1];
                    dis[1]=dis[2];
                    dis[2]=temp;
                }
            }
        }else{
            if(len1>len3){//312
                int temp=dis[1];
                int temp2=dis[2];
                dis[1]=dis[3];
                dis[2]=temp;
                dis[3]=temp2;
            }else{
                if(len2>len3){//132
                    int temp=dis[2];
                    dis[2]=dis[3];
                    dis[3]=temp;
                }
            }
        }
    }
//    for(int m=0;m<4;m++){
//        cout<<dis[m]<<",";
//    }
    int resindex=-1;
    for(int i6=0;i6<4;i6++){
        int c=0;
        if(!(dis[i6]<0||dis[i6]>3||cross->roads_id[dis[i6]]==-1)){
            if(roads[cross->roads_id[dis[i6]]-road_base]->from==curcar->from) {
                c=roads[cross->roads_id[dis[i6]]-road_base]->to;
            }else{
                c=roads[cross->roads_id[dis[i6]]-road_base]->from;
            }
        }
        if(dis[i6]<0||dis[i6]>3||cross->roads_id[dis[i6]]==-1||(roads[cross->roads_id[dis[i6]]-road_base]->one_way==1&&roads[cross->roads_id[dis[i6]]-road_base]->from!=cross->id)||shortestPath[c-cross_base][curcar->to-cross_base]==-1||shortestPath[c-cross_base][curcar->to-cross_base]+cross_base==curcar->from){
            continue;
        }else{
            if(roads[cross->roads_id[dis[i6]]-road_base]->from==cross->id){
                if(roads[cross->roads_id[dis[i6]]-road_base]->to>cross->id){
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumx2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//进入下一条路
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumd2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//进入下一条路
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
            else if(roads[cross->roads_id[dis[i6]]-road_base]->to==cross->id&&!roads[cross->roads_id[dis[i6]]-road_base]->one_way){
                if(roads[cross->roads_id[dis[i6]]-road_base]->from>cross->id){
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumx2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//进入下一条路
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumd2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//进入下一条路
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
        }
    }
}

void Handle::onrdcarjudge()////待改
{
    for(Cross *cur=headcross;cur!=NULL;cur=cur->nextcross){//遍历路口

        for(int i=0;i<4;i++){//遍历该路口的道路
            if(cur->roads_minid[i]!=-1){//路是否存在
                //只判断通往本路口的车
                if(!roads[cur->roads_minid[i]-road_base]->one_way){//双行道
                    if(roads[cur->roads_minid[i]-road_base]->from==cur->id){//寻找道路的另一个路口是to
                        if(roads[cur->roads_minid[i]-road_base]->to<cur->id){//比较两路口，确定车道下标
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//遍历车道
                                cardirect(cur,i,i1);
                            }
                        }
                        else{
                            for(int i1=roads[cur->roads_minid[i]-road_base]->channel;i1<2*roads[cur->roads_minid[i]-road_base]->channel;i1++){
                                cardirect(cur,i,i1);
                            }
                        }
                    }else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//寻找道路的另一个路口是from
                        if(roads[cur->roads_minid[i]-road_base]->from<cur->id){//比较两路口，确定车道下标

                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//遍历车道
                                cardirect(cur,i,i1);
                            }
                        }
                        else{
                            for(int i1=roads[cur->roads_minid[i]-road_base]->channel;i1<2*roads[cur->roads_minid[i]-road_base]->channel;i1++){
                                cardirect(cur,i,i1);
                            }
                        }
                    }
                }
                else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//单行道//且道路通向本车道//<更改>
                    for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//
                        cardirect(cur,i,i1);
                    }
                }
            }
        }
    }
}

void Handle::waitcarjudge()
{
//    int rcarsum=roadcarsum();
    int rxcarsum=sumCarsOnRoads;
    int maxcar=(int)(roadsTotalmil*limitP);
    int p2=fluRange;
    int l=0;
    Car *plancar=planheadcar;
    for(Car *curplancar=planheadcar;curplancar!=NULL;curplancar=curplancar->backcar,l++){
        if(curplancar->backcar==NULL){
            plancar=curplancar;
        }
    }
//    cout<<maxcar-p2<<"hh";
    for(Car *tcurcar=headcar;tcurcar!=NULL;){
        Car *curcar=tcurcar;
        tcurcar=tcurcar->backcar;//之后tcurcar可能被移出，需要先指向下一个
//        cout<<curcar->id<<"hscyggg"<<endl;
        if(curcar->planTime>nowTime){
            return;
        }
        if(curcar->route[0]==-1){//<更改>
            if(rxcarsum<=maxcar-p2&&l+rxcarsum<=maxcar){//<更改>
                int ncross;
                ncross = shortestPath[curcar->from - cross_base][curcar->to - cross_base];
                int nroad;
                nroad = cross_road[curcar->from - cross_base][ncross];
                int resindex=fourroadselect(curcar,nroad);
//                cout<<resindex<<"jbdhcbiudi"<<endl;
//                cout<<roads[crosss[curcar->from-cross_base]->roads_id[resindex]-road_base]->id<<"jbdhcbiudi"<<endl;
                if(resindex>=0&&resindex<=3){
                    curcar->route[curcar->now_routeLength]=roads[crosss[curcar->from-cross_base]->roads_id[resindex]-road_base]->id;
                    curcar->now_routeLength++;
                    l++;//只减l不减rxcarsum
                    if(curcar==headcar){
                        headcar=curcar->backcar;
                        if(headcar!=NULL){
                            headcar->frontcar=NULL;
                        }
                    }else{
                        curcar->frontcar->backcar=curcar->backcar;
                        curcar->backcar->frontcar=curcar->frontcar;
                    }
                    if(planheadcar==NULL){
                        planheadcar=curcar;
                        planheadcar->backcar=NULL;
                        planheadcar->frontcar=NULL;
                        plancar=planheadcar;
                    }else{
                        plancar->backcar=curcar;
                        plancar->backcar->backcar=NULL;
                        plancar->backcar->frontcar=plancar;
                        plancar=plancar->backcar;
                    }
                }else{
//                        curcar->planTime=nowTime+1;
                }
            }else{//车数允许，不用再检测
                return;
//                    curcar->planTime=nowTime+1;
            }
        }
    }
}

void Handle::judgeRoute()
{
    for(int i=0;i<query_roads_length;i++){
        query_roads[i]->carnumd2=query_roads[i]->carnumd;
        query_roads[i]->carnumx2=query_roads[i]->carnumx;
    }
    for(Cross *cur=headcross;cur!=NULL;cur=cur->nextcross){//遍历路口
        for(int i=0;i<4;i++){//遍历该路口的道路
            if(cur->roads_minid[i]!=-1){//路是否存在
                if(!roads[cur->roads_minid[i]-road_base]->one_way){//双行道
                    if(roads[cur->roads_minid[i]-road_base]->from==cur->id){//寻找道路的另一个路口是to
                        if(roads[cur->roads_minid[i]-road_base]->to<cur->id){//比较两路口，确定车道下标
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//遍历车道
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
                                    if(cur->roads_minid[i]!=cur1->route[cur1->now_routeLength-1]){
                                        if(cur->id == roads[cur->roads_minid[i]-road_base]->from){
                                            if(roads[cur->roads_minid[i]-road_base]->to>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                        else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){
                                            if(roads[cur->roads_minid[i]-road_base]->from>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            for(int i1=roads[cur->roads_minid[i]-road_base]->channel;i1<2*roads[cur->roads_minid[i]-road_base]->channel;i1++){
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
                                    if(cur->roads_minid[i]!=cur1->route[cur1->now_routeLength-1]){
                                        if(cur->id == roads[cur->roads_minid[i]-road_base]->from){
                                            if(roads[cur->roads_minid[i]-road_base]->to>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                        else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){
                                            if(roads[cur->roads_minid[i]-road_base]->from>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//寻找道路的另一个路口是from
                        if(roads[cur->roads_minid[i]-road_base]->from<cur->id){//比较两路口，确定车道下标
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//遍历车道
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
                                    if(cur->roads_minid[i]!=cur1->route[cur1->now_routeLength-1]){
                                        if(cur->id == roads[cur->roads_minid[i]-road_base]->from){
                                            if(roads[cur->roads_minid[i]-road_base]->to>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                        else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){
                                            if(roads[cur->roads_minid[i]-road_base]->from>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            for(int i1=roads[cur->roads_minid[i]-road_base]->channel;i1<2*roads[cur->roads_minid[i]-road_base]->channel;i1++){
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
                                    if(cur->roads_minid[i]!=cur1->route[cur1->now_routeLength-1]){
                                        if(cur->id == roads[cur->roads_minid[i]-road_base]->from){
                                            if(roads[cur->roads_minid[i]-road_base]->to>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                        else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){
                                            if(roads[cur->roads_minid[i]-road_base]->from>cur->id){
                                                roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                            }
                                            else{
                                                roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else{//单行道
                    for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//
                        for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//遍历车道上的车
                            if(cur->roads_minid[i]!=cur1->route[cur1->now_routeLength-1]){
                                if(cur->id == roads[cur->roads_minid[i]-road_base]->from){
                                    if(roads[cur->roads_minid[i]-road_base]->to>cur->id){
                                        roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                    }
                                    else{
                                        roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                    }
                                }
                                else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){
                                    if(roads[cur->roads_minid[i]-road_base]->from>cur->id){
                                        roads[cur->roads_minid[i]-road_base]->carnumx2++;
                                    }
                                    else{
                                        roads[cur->roads_minid[i]-road_base]->carnumd2++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    onrdcarjudge();//已出发车辆判断
    waitcarjudge();//未出发车辆判断
}

bool  test(int i){
    if(i==1){
        return NULL;
    }else if(i==0){
        return  true;
    }else{
        return false;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;

    if(argc < 5){
        std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
        exit(1);
    }

    std::string carPath(argv[1]);
    std::string roadPath(argv[2]);
    std::string crossPath(argv[3]);
    std::string answerPath(argv[4]);

    std::cout << "carPath is " << carPath << std::endl;
    std::cout << "roadPath is " << roadPath << std::endl;
    std::cout << "crossPath is " << crossPath << std::endl;
    std::cout << "answerPath is " << answerPath << std::endl;

    Handle h;
    cout<<h.startrun(crossPath,roadPath,carPath)<<endl;
    h.printResult(answerPath);
    return 0;
}