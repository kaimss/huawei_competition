//
// Created by Think on 2019/3/24.
//
#include <iostream>
#include <fstream>

using namespace std;
class Car{//��
public:
    int id;
    int speed;
    int planTime,from,to;
    int now_speed;//ʵ���ٶ�
    int now_lane;//����������//3���������е�012��˫�е�idС->��:012id��->С:345
    int distance;//�ڵ�·�ϵ���ʻ����
    int starttime;//ʵ�ʿ�ʼʱ��
    bool IswaitState;//�Ƿ�ȴ�״̬
    bool IstoEnd;//�Ƿ��ѵ����յ�
    Car *backcar,*frontcar;//Road������ָ��
    Car *nextWaitCar,*frontWaitCar;//�ȴ�������ָ��
    Car(int id,int from,int to,int speed,int planTime,int route_length);
    void Output_route();//���·��
    int *route;//·��
    int route_length;
    int now_routeLength;
private:

};
class Road{//��·
public :
    int id,length,speed;
    bool one_way;//�Ƿ��е�
    int channel;//������
    int from,to;//ʼĩ·��
    int carnumx;//�����ϳ���Ŀ//idС��id��
    int carnumd;//id��idС
    int carnumd2;
    int carnumx2;
    Car *waitheadx;//�ȴ�����ͷ //id��С����
    Car *waitheadd;//id�Ӵ�С
    Car **carhead;//����ͷ����
    Car **carlast;//����β����
    Road(int id,int length,int speed,int chanel,int from,int to,int isDuplex);
private:

};
class Cross{//·��
public:
    int id;
    int *roads_id;//0-4���飬˳ʱ���·id
    int *roads_minid;//��·id��С��������
    int TothisCrosswaitCarsum;
//		Road **in_roads;//��·��������0-4
//		Road **out_roads;//
    Cross *nextcross;//����ָ��
    Cross(int id,int l1,int l2,int l3,int l4);
private:

};
class Handle{
public:

    int nowTime;
    int startrun(string crossPath,string roadPath,string carPath);
    void printResult(string path);
    //��ʼ��
    void Initialize(string crossPath,string roadPath,string carPath);
    //ģ��ƪ
    bool Simulation();//��ʱ����ȣ������������
    //����ƪ
    void judgeRoute();//
private:
    //Ԫ�ش���ƪ//����ֵ����NULL��-1(int)��ʼ�������ж��Ƿ���ֵ
    int cross_base;//����id�����id-cross_baseΪ���������±� //=��Сid
    int road_base;
    Cross **crosss;//·�ڶ�������
    Road **roads;//id-road_baseΪ�±�
    Road **query_roads;//��·����//����ʹ��
    int query_roads_length;
    int query_cross_length;
    int crosss_length;//�����С//�������id-��Сid+1+10//+10��ֹ���
    int roads_length;
    Car *headcar;//�ȴ����������г������ͷ
    Car *planheadcar;//�ƻ������ĳ�������ͷ
    Cross *headcross;//·�������ͷ//��·�������������������ֹ·��id������ɢ���ٱ���·��ʱ������������ʱ//����ʹ��
    void SetEleStorage();//��װ��������-�ļ�����
    //���·��ƪ
    int **shortestPath;//��ά�������·����[i][j]��Ŵ�i��j��һ��Ҫ������·�ڵ�id-cross_base//i,j��·��id-cross_base
    int **cross_road;//����·�ڼ�ֱ�ӵ�·��id
    long long **shortestl;//���·����
    long long maxlong;//���·����//�ﵽ��ʾû��·
    void GetShortestPath();//���·������-���������㷨
    //ģ��ƪ
    int sumCarsOnRoads;//·�����г�
    int headcarLength;//δ����������
    int waitCarsum;//·�ϵȴ�״̬
    bool waitGoCarIsCanGo(int roadId,int startCrossId);  //�жϵȴ������ĳ����Ƿ��ܹ�����
    int  waitGoCarGoTocarChannel(int roadId,int startCrossId); //ȷ���ȴ������ĳ�����������Ӧ��·����һ������
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
//		void sortById();//�ȴ���������������
    Car **outputcar;//������泵ָ������
    int carsum;//������
    int minplanTime,maxplanTime;//�ļ��г��������СplanTime
    Car* MergesortBytimeid(Car *head);//����Ĺ鲢����//���س�ͷ
    Car* MergesortByid(Car *head);
    void  OtherInitialize();
    Car* findNowYoucianCar(Car **pCar,int size);
    //����ƪ
    int roadsTotalmil;
    int roadcarsum();//���ɳ�����
    int threeroadselect(Cross *cur,int i,Car *cur1,int nroad);//3��·ѡ��
    void cardirect(Cross *cur,int i,int i1);//�������ķ���
    int fourroadselect(Car *curcar,int nroad);//4��·ѡ��
    void onrdcarjudge();//�ѳ��������ж�
    void waitcarjudge();//δ���������ж�
    //��̬�仯
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
    for(int i=0;i<route_length;i++){//<����>
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
        carhead=new Car*[channel];//����ͷ����
        carlast=new Car*[channel];//����β����
        for(int i=0;i<channel;i++){
            carhead[i]=NULL;
            carlast[i]=NULL;
        }
    }else{
        carhead=new Car*[channel*2];//����ͷ����
        carlast=new Car*[channel*2];//����β����
        for(int i=0;i<channel*2;i++){
            carhead[i]=NULL;
            carlast[i]=NULL;
        }
    }

}
Cross::Cross(int id,int l1,int l2,int l3,int l4){
    this->id=id;
    roads_id=new int[4];//0-4���飬˳ʱ���·id
    roads_id[0]=l1;
    roads_id[1]=l2;
    roads_id[2]=l3;
    roads_id[3]=l4;
    roads_minid=new int[4];//id��С����������
    TothisCrosswaitCarsum=0;
    for(int i=0;i<4;i++){
        int j=i;
        for(;j>0;j--){
            if(roads_minid[j-1]>roads_id[i]){////<����>
                roads_minid[j]=roads_minid[j-1];
            }else{
                break;
            }
        }
        roads_minid[j]=roads_id[i];
    }
    nextcross=NULL;//����ָ��
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
//            cout<<"ѭ����������·����"<<endl;
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
    crosss_length=crosssum+10;//�����С//�������id-��Сid+1+10//+10��ֹ���
    crosss=new Cross*[crosss_length];//����ָ������
    for(int i=0;i<crosss_length;i++){
        crosss[i]=NULL;
    }
    cross_road=new int*[crosss_length];
    for(int i=0;i<crosss_length;i++) {
        cross_road[i] = new int[crosss_length];
        for (int j = 0; j < crosss_length; j++) {
            cross_road[i][j] = -1;//��·
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
    roads=new Road*[roads_length];//����ָ������

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

            if(sz[6]==1){//˫�е�
                int jid=cross_road[sz[5]-cross_base][sz[4]-cross_base];
                if(jid==-1||roads[jid-road_base]->length>sz[1]){//��·�ڼ��ж�����·��ž���̵�
                    cross_road[sz[5]-cross_base][sz[4]-cross_base]=sz[0];
                }
            }
            int jid=cross_road[sz[4]-cross_base][sz[5]-cross_base];
            if(jid==-1||roads[jid-road_base]->length>sz[1]){//��·�ڼ��ж�����·��ž���̵�
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
    Car *frontcar=NULL;//��һ����
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
                thecar=new Car(sz[0],sz[1],sz[2],sz[3],sz[4],roadsum);///////////////////////���ܸ�
                frontcar->backcar=thecar;
            }else{
                thecar=headcar=new Car(sz[0],sz[1],sz[2],sz[3],sz[4],roadsum);///////////////////////���ܸ�
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
Car* Handle::sortById(int time,Car *theadcar){//�ȴ���������������
    Car *i=theadcar;
    for(;i!=NULL&&i->planTime<=time;i=i->backcar){//�ҵ��������ʱ��ĳ���������
    }
    if(i!=NULL){//ֻ��iǰ��Ҫ����
        Car *c=i->backcar;//����i����Ϊi��planTime�󣬲�Ӱ����
        i->backcar=NULL;
        theadcar= MergesortByid(theadcar);
        for(Car *i2=theadcar;i2!=NULL;i2=i2->backcar){//������������
            if(i2->backcar==NULL){
                i2->backcar=c;
                break;
            }
        }
    }else {//��������Ҫ����
        theadcar = MergesortByid(theadcar);
    }
    theadcar->frontcar=NULL;
    return theadcar;
}
Car* Handle::MergesortBytimeid(Car *head){//�鲢����//���س�ͷ
    if(head==NULL||head->backcar==NULL){
        return head;
    }else{
        //����ָ���ҵ��м�ڵ�
        Car *fast=head;
        Car *slow=head;
        while(fast->backcar!=NULL&&fast->backcar->backcar!=NULL){
            fast=fast->backcar->backcar;//���յ�ĩβ
            slow=slow->backcar;//���յ��м�
        }
        fast=slow;
        slow=slow->backcar;
        fast->backcar=NULL;//�����м�ָ�
        fast= MergesortBytimeid(head);//ǰ���
        slow= MergesortBytimeid(slow);//����
        Car *chead,*tc;
        if(slow==NULL){
            return fast;
        }else if(fast==NULL){
            return slow;
        }
        if(fast->planTime<slow->planTime||fast->planTime==slow->planTime&&fast->id<slow->id){//ȷ������ͷ
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
                fast->frontcar=tc;////<����>
                tc=fast;
                fast=fast->backcar;
            }else{
                tc->backcar=slow;
                slow->frontcar=tc;////<����>
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
Car* Handle::MergesortByid(Car *head){//�鲢����//���س�ͷ
    if(head==NULL||head->backcar==NULL){
        return head;
    }else{
        //����ָ���ҵ��м�ڵ�
        Car *fast=head;
        Car *slow=head;
        while(fast->backcar!=NULL&&fast->backcar->backcar!=NULL){
            fast=fast->backcar->backcar;//���յ�ĩβ
            slow=slow->backcar;//���յ��м�
        }
        fast=slow;
        slow=slow->backcar;
        fast->backcar=NULL;//�����м�ָ�
        fast= MergesortByid(head);//ǰ���
        slow= MergesortByid(slow);//����
        Car *chead,*tc;
        if(slow==NULL){
            return fast;
        }else if(fast==NULL){
            return slow;
        }
        if(fast->id<slow->id){//ȷ������ͷ
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
                fast->frontcar=tc;////<����>
                tc=fast;
                fast=fast->backcar;
            }else{
                tc->backcar=slow;
                slow->frontcar=tc;////<����>
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
            if(lastcross){//��ΪNULL
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
//	int **shortestPath;//��ά�������·����[i][j]��Ŵ�i��j��һ��Ҫ������·�ڵ�id-cross_base//i,j��·��id-cross_base
//	int **cross_road;//����·�ڼ�ֱ�ӵ�·
//	int **shortestl;//���·����
    //��ʼ��
    maxlong=1000000000;
    shortestPath=new int*[crosss_length];
    shortestl=new long long*[crosss_length];
    int shortroadsum[crosss_length][crosss_length];//�����·���е�·����Ŀ
    for(int i=0;i<crosss_length;i++){
        shortestPath[i]=new int[crosss_length];
        shortestl[i]=new long long[crosss_length];
        for(int j=0;j<crosss_length;j++){

            if(cross_road[i][j]<0){//��·
                shortestPath[i][j]=-1;
                shortestl[i][j]=maxlong;
                shortroadsum[i][j]=2*crosss_length;
            }else{
//				cout<<i<<" "<<j<<":"<<cross_road[i][j]-road_base<<endl;////////
                shortestl[i][j]=roads[cross_road[i][j]-road_base]->length;
                shortestPath[i][j]=j;//i->j��·��i������Ҫȥj
                shortroadsum[i][j]=1;
            }
        }
    }
    //
//	cout<<shortestl[0][1]<<" "<<shortestl[1][0]<<endl;
    for(int k=0;k<crosss_length;k++){
        for(int i=0;i<crosss_length;i++){
            if(i==k){//i->i�Ľ������Щ����
                continue;
            }
            for(int j=0;j<crosss_length;j++){
                if(i==j){//i->i�Ľ������Щ����
                    continue;
                }
                if(shortestl[i][k]+shortestl[k][j]<shortestl[i][j]){
                    shortestl[i][j]=shortestl[i][k]+shortestl[k][j];
                    shortestPath[i][j]=shortestPath[i][k];
                    shortroadsum[i][j]=shortroadsum[i][k]+shortroadsum[k][j];
                }else if(shortestl[i][k]+shortestl[k][j]==shortestl[i][j]&&shortroadsum[i][k]+shortroadsum[k][j]<shortroadsum[i][j]){
                    //������·һ���������·�ٵ�·��ƽ����·��������·Խ��Խ�����׳�Ϊ���·����·���ҳ�����Ҳ�󣬲����׶���
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
//	///////////////////////////////////////////����
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
//                    cout<<car->id<<":"<<road->id<<"·����"<<endl;
//                }else{
//                    crossid=road->from;
//                }
//            }else{
//                cout<<car->id<<"·������ͨ"<<endl;
//            }
//            if(roads[car->route[j]-road_base]->to==car->to||roads[car->route[j]-road_base]->from==car->to){
//                if(j+1!=car->now_routeLength){
//                    cout<<car->id<<"·������"<<endl;
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


//���ƪ
bool aaaa(int i){
    if(i==1){
        return true;
    }
}//////////////19880
//�жϵ���������ʱ��ĳ����Ƿ��ܹ�������������Ǹ�·���Ƿ�����//done
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

//���ܳ�����ǰ�����ж�������������//done
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

//Ϊĳ����·�����еĳ��Ƿ�Ϊ��ֹ̬��ȴ���״̬��ȷ�����÷�������ȥ���������˴���//done
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
        while(tpCar!=NULL){//<����>
            Car *pCar=tpCar;
            tpCar=tpCar->backcar;//�ȴ�����һ��������Ȼ���ܶ�ʧ
            IsWaitStatetoCross(pCar, road);//�����������Ƿ��ǵȴ�״̬����һ���������//���ͬʱ�͸��˵ȴ�����
        }//<����>
//        if(pCar!=NULL){
//            int speed=min(road->speed,pCar->speed);
//            int distance1 = pCar->distance;
//            int sumdistance=road->length-distance1;
//            if(sumdistance>=speed*1){//�����·��
//                pCar->IswaitState= false;
//                Car *car= pCar->backcar;
//                while (car!=NULL){
//                    car->IswaitState= false;
//                    car=car->backcar;
//                }
//            } else{//�ܵ���·�ڣ��Ƿ�������·�ڣ��д���
//                //�ж��Ƿ񵽴��յ㣬����������յ㻹��route����������������
//                if(IsGoToEnd(pCar,road->id)){//���ͷ�������յ㣬������Ȼ�жϵȴ���ֹ״̬
//
//                }
//                if(road->one_way&&pCar->to==road->to){
//                    pCar->IswaitState= true;
//                } else if(!road->one_way&&(pCar->to==road->from||pCar->to==road->to)){
//                    pCar->IswaitState= true;
//                } else{
//                    //���ᵽ���յ�
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

//�ж�ĳ�����Ƿ�Ϊ�ȴ�״̬�ĳ���----(����ó�����ֹ״̬��������distance�����˸ı�)//done
bool Handle::IsWaitStatetoCross(Car *car, Road *road) {//�ȴ�true��ֹfalse�յ�NULL(NULL==false)
    /////////////////////////////////////////////
//    bool bbb=false;
//    if(nowTime>7653&&car->id==12153&&road->id==5002){
//        bbb=aaaa(1);
//    }


    ////////////////////////////////////////

    int speed=min(road->speed,car->speed);
    int distance1 = car->distance;
    int sumdistance=road->length-distance1;
    if(car->frontcar!=NULL){//���ڳ�����ǰ���г��赲//<����>
        sumdistance=car->frontcar->distance-distance1;
        if(sumdistance<=speed*1){//��ǰ��Ӱ��
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
        return false;//��ʱ����·��
    }//<����>
    //�޳��赲���л����·��//


    if(sumdistance>=speed*1){
        car->distance=car->distance+speed*1;
        car->IswaitState=false;
        return false;
    }else{
        //�Ƿ񵽴��յ�
        if(IsGoToEnd(car,road->id)){//��������յ㣬����false//<����>
//        return NULL;//����NULl��falseһ��
            return false;
        }
        int nextRoadId;
        int *routes = car->route;
        for (int j = car->now_routeLength-1; j >=0 ; j--) {
            if(routes[j]==road->id){
                nextRoadId=routes[j+1];
                Road *pRoad = roads[nextRoadId - road_base];
                int speed1 = min(pRoad->speed,car->speed);//<����>
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


//��ĳ����·�ϴ�����ֹ״̬�ĳ������е���//done
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

//�õ�ͨ���·�ڵ�ĳ����·�д��ڵȴ�״̬�ĳ�������Ŀ//done
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

//�õ�ͨ���·�ڵ����е�·�д��ڵȴ�״̬�ĳ�������Ŀ//done
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

//�õ���ǰ��·�ڰ�˳ʱ���ź��������Ķ�Ӧ����//done
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

//�õ�ת��ı��  //1��ת  2ֱ��  3��ת//done
int Handle::getNextDirection(int beginRoadIndexOnroads_id,int endRoadIndexOnroads_id){
    return (endRoadIndexOnroads_id-beginRoadIndexOnroads_id+4)%4;
}

//ȡ���ڰ���˳ʱ���źõ�ĳ����·�Ķ����·��id //done
int Handle::getduimianRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+2)%4;
    return pInt[k];
}

//ȡ���ڰ���˳ʱ���źõ�ĳ����·�������·��id //done
int Handle::getleftRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+1)%4;
    return pInt[k];
}

//ȡ���ڰ���˳ʱ���źõ�ĳ����·�������·��id  //done
int Handle::getrightRoadId(int index,int crossId){
    Cross *pCross = crosss[crossId - cross_base];
    int *pInt = pCross->roads_id;
    int k=(index+3)%4;
    return pInt[k];
}

//�ж���ĳ��·����a��·�Ƿ��п���ͨ����·�ڻᵽ��b·��  //done
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

//�õ����ڵȴ�״̬�ĳ�����������Ļ���������һ����·  //ǰ�᣺��ͨ��·�ڲ��ᵽ���յ�//done
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

//�жϴ��ڵȴ�״̬�ĳ���(���ȼ����)��һʱ���Ƿ�ᵽ���յ�  //done
bool Handle::IsGoToEnd(Car *car, int roadId) {//����ó�֮ǰΪ�ȴ�״̬���ֵ����յ㣬Ҳ���������ɵ������Ĵ��봦��
//    /////////////////////////////////////////
//    bool b=false;
//    if(nowTime==579&&roadId==5149){
//        b=aaaa(2);
//    }
////    ///////////////////////////////

    int to = car->to;
    if(roads[roadId-road_base]->one_way){
        if(roads[roadId-road_base]->to==to){
            //�����յ�����ƶ�//<����>
        } else{
            return false;
        }
    } else{
        if(roads[roadId-road_base]->from==to||roads[roadId-road_base]->to==to){
            //�����յ�����ƶ�//<����>
        } else{
            return false;
        }
    }
    int speed=min(car->speed,roads[roadId-road_base]->speed);
    if(speed<roads[roadId-road_base]->length-car->distance){//���ܵ���·��
        return false;
    }
    //<����>
    sumCarsOnRoads--;
//    //    ////////////////////debug///////////////////
//    if(nowTime>159){
//        int iii=aaa();
//    }
////    ////////////////////debug/////////////////////
//    cout<<"·�ϳ���һ"<<endl;////////////////////////////////////
//    crosss[car->to-cross_base]->TothisCrosswaitCarsum--;///////////////////////////delete//////////////////////////��·�ڲ��ٱ��Ϊ�ȴ�״̬
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
            pRoad->carnumx--;  //�Ժ�ӵ����Եĸı�
        } else{
            pRoad->carnumd--; //�Ժ�ӵ����Եĸı�
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
            pRoad->carnumd--; ////�Ժ�ӵ����Եĸı�
        } else{
            pRoad->carnumx--;//�Ժ�ӵ����Եĸı�
        }
    }
    car->backcar=car->frontcar=NULL;//<����>
    car->IswaitState=false;//��������ǰ��Ӱ�죬�ó�֮ǰ�ǵȴ�״̬//<����>
//    car->frontWaitCar=car->nextWaitCar=NULL;//�����յ�ȴ�����δ�ı䣬���ܸ�ָ�����//<����>
    car->IstoEnd=true;
    return true;//<����>
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

//�õ�ĳ����·ͨ���·�ڵ����� ���ڵȴ�״̬�ĳ����ĵ������ȼ�������  //done
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
                cars[k-start]=NULL;//<����>
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
                cars[k-start]=NULL;//<����>
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

//�õ�ĳ����·ͨ���·�ڵ����� ���ڵȴ�״̬�ĳ����ĵ������ȼ�������//����ͷ  //done
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

//Ϊ��·��Waitheadx����Waitheadh���߶��� ��ֵ  //done
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

//���ڵȴ�״̬�ĳ����ƶ����Ƿ��ǵȴ�״̬
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
                //�Եȴ�������������д���--start
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
                //�Եȴ�������������д���--end
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
//�Եȴ�������������д���--start
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
                //�Եȴ�������������д���--end
                return false;
            }
        }
    } else{
        //Ҫȥ���ĵ�·����...


        Car *pCar = pRoad->carlast[tocarChannel];
        if(pCar==NULL){
            //�뿪��������
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

            //ȥ���µĳ���
            int dist = min(pRoad->speed ,car->speed)* 1 - (roads[roadId - road_base]->length - car->distance);
//            /////////////////////////debug////////////////////////////////
//            bool ab2;
//            if(nowTime==725&&pRoad->id==5081){
//                ab2=aaaa(2);
//            }
//            /////////////////////////////////////////////

            pRoad->carlast[tocarChannel]=pRoad->carhead[tocarChannel]=car;

            //Ϊ��ӵ�����carnumx��carnumd��ֵ--start(Ҫȥ���ĵ�·��
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
            //Ϊ��ӵ�����carnumx��carnumd��ֵ--end(Ҫȥ���ĵ�·��


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

            //�Եȴ�������������д���--start
            if (pRoad2->one_way){
                if(pRoad2->from<pRoad2->to){
                    pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                    if(pRoad2->waitheadx!=NULL)
                        pRoad2->waitheadx->frontWaitCar=NULL;//<����>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                } else{
                    pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                    if(pRoad2->waitheadd!=NULL)//<����>pRoad2д����pRoad������
                        pRoad2->waitheadd->frontWaitCar=NULL;//<����>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
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
                    if(pRoad2->waitheadd!=NULL)//<����>
                        pRoad2->waitheadd->frontWaitCar=NULL;//<����>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
                } else{
                    pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                    if(pRoad2->waitheadx!=NULL)
                        pRoad2->waitheadx->frontWaitCar=NULL;//<����>
                    car->nextWaitCar=car->frontWaitCar=NULL;
                    pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                }
            }
            //�Եȴ�������������д���--end
            return false;
        } else{

            //Ҫȥ��������С�����г�
            int dist = min(pRoad->speed,car->speed) * 1 - (roads[roadId - road_base]->length - car->distance);
            if(pCar->distance<=dist){
                if(pCar->IswaitState){
                    //�ó����ߺ�Ϊ�ȴ�״̬�����ƶ�
                    for (int i = 0; i <FirOneIsWaitStateAndNoGoLength ; ++i) {
                        if(needSimulationRoad[i]==roadId){
                            FirOneIsWaitStateAndNoGo[i]= true;
                        }
                    }
                    return true;
                } else{
                    //�������Եĸı�
                    waitCarsum--;
                    crosss[crossId-cross_base]->TothisCrosswaitCarsum--;

                    //��ԭ������������иı�
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


                    //�Եȴ�������������д���--start
                    if (pRoad2->one_way){
                        if(pRoad2->from<pRoad2->to){
                            if(pRoad2->waitheadx->nextWaitCar!=NULL){
                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                            if(pRoad2->waitheadx!=NULL)
                                pRoad2->waitheadx->frontWaitCar=NULL;//<����>
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                        } else{
                            if(pRoad2->waitheadd->nextWaitCar!=NULL){
                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
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
                            pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
                        } else{
                            if(pRoad2->waitheadx->nextWaitCar!=NULL){
                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                            }
                            pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                            if(pRoad2->waitheadx!=NULL)
                                pRoad2->waitheadx->frontWaitCar=NULL;//<����>
                            car->nextWaitCar=car->frontWaitCar=NULL;
                            pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                        }
                    }
                    //�Եȴ�������������д���--end

                    //�Գ��ƶ���������иı�
                    car->frontcar=pRoad->carlast[tocarChannel];
                    car->backcar=NULL;
                    pRoad->carlast[tocarChannel]->backcar=car;
                    pRoad->carlast[tocarChannel]=car;
                    car->now_lane=tocarChannel;
                    car->distance=car->frontcar->distance-1;
                    car->IswaitState= false;
                    car->nextWaitCar=NULL;

                    //Ϊ��ӵ�����carnumx��carnumd��ֵ--start
                    if(pRoad->one_way){
                        int from = pRoad->from;
                        int to = pRoad->to;
                        if(from<to){
                            pRoad->carnumx++;//<����>
                        } else{
//                            ///////////////////debug//////////////////////
//                            bool b=false;
//                            if(nowTime>572&&pRoad->id==5149){
//                                b=aaaa(2);
//                            }
//                            //    ////////////////////////////


                            pRoad->carnumd++;//<����>
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
                    //Ϊ��ӵ�����carnumx��carnumd��ֵ--end


                    return false;//ȱ�ٷ���ֵ//����
                }
            } else{
                //�������Եĸı�
                waitCarsum--;
                crosss[crossId-cross_base]->TothisCrosswaitCarsum--;

                //��ԭ������������иı�
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


//�Եȴ�������������д���--start
                if (pRoad2->one_way){
                    if(pRoad2->from<pRoad2->to){
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                    } else{
                        if(pRoad2->waitheadd->nextWaitCar!=NULL){
                            pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
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
                        pRoad2->carnumd--;//�Ժ�ӵ����Եĸı�
                    } else{
                        if(pRoad2->waitheadx->nextWaitCar!=NULL){
                            pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;
                        }
                        pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                        car->nextWaitCar=car->frontWaitCar=NULL;
                        pRoad2->carnumx--;//�Ժ�ӵ����Եĸı�
                    }
                }
                //�Եȴ�������������д���--end

                //�Գ��ƶ���������иı�
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

                //Ϊ��ӵ�����carnumx��carnumd��ֵ--start
                if(pRoad->one_way){
                    int from = pRoad->from;
                    int to = pRoad->to;
                    if(from<to){
                        pRoad->carnumx++;//<����>
                    } else{
//                        ///////////////////debug//////////////////////
//                        bool b=false;
//                        if(nowTime>572&&pRoad->id==5149){
//                            b=aaaa(2);
//                        }
//                        //    ////////////////////////////


                        pRoad->carnumd++;//<����>
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
//                if(pRoad->one_way){//��ִ��һ�˱�!//<����>
//                    int from = pRoad->from;
//                    int to = pRoad->to;
//                    if(from<to){
//                        pRoad->carnumx++;//<����>
//                    } else{
//                        pRoad->carnumd++;//<����>
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
                //Ϊ��ӵ�����carnumx��carnumd��ֵ--end
            }
        }

    }
    return false;//ȱ�ٷ���ֵ//<����>
}
bool Handle::IsChongTu(Car * car,int roadId,int crossId,bool * FirOneIsWaitStateAndNoGo,int FirOneIsWaitStateAndNoGoLength,int needSimulationRoad[]) {
    int nextToRoadId = NextToRoadIdBaseWaitStateCar(car, roadId);
    int direction = getNextDirection(
            getthisRoadIndexOnroads_id(roadId, crossId),
            getthisRoadIndexOnroads_id(nextToRoadId, crossId));
    if (direction == 1) {  //��ת
        //ȡ����תҪȥ���ĵ�·id�Ķ���ĵ�·id���ж��������ȼ���һ�ĳ��Ƿ�Ϊֱ��
        int duimianRoadId = getduimianRoadId(getthisRoadIndexOnroads_id(nextToRoadId,crossId),crossId);
        bool sff=false;//<����>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==duimianRoadId){
                sff=FirOneIsWaitStateAndNoGo[i];
            }
        }//<����>
        if(duimianRoadId !=-1&&!sff){//ֱ�е���·�Ҳ���//<����>
            Road *duimianRoad = roads[duimianRoadId - road_base];
            if (AisCanGotoBinOneCross(duimianRoadId, nextToRoadId, crossId)) {
                //ȡ��A��·�����д��ڵȴ�״̬����������
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
    } else if (direction == 2) {  //ֱ��
        return false;
    } else {  //��ת
        //ȡ����תҪȥ���ĵ�·id�Ķ���ĵ�·id���ж��������ȼ���һ�ĳ��Ƿ�Ϊֱ��
        int duimianRoadId = getduimianRoadId(getthisRoadIndexOnroads_id(nextToRoadId, crossId),crossId);
        bool sff=false;//<����>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==duimianRoadId){
                sff=FirOneIsWaitStateAndNoGo[i];
            }
        }//<����>
        if(duimianRoadId!=-1&&!sff){//ֱ����·�Ҳ���//<����>
            Road *duimianRoad = roads[duimianRoadId - road_base];
            if (AisCanGotoBinOneCross(duimianRoadId, nextToRoadId, crossId)) {
                Car *pCar = getWaitStatecarsTothisCross(duimianRoadId, crossId);
                if (pCar != NULL && NextToRoadIdBaseWaitStateCar(pCar, duimianRoadId) == nextToRoadId) {
                    return true;
                } else {
                    //ɶҲ����
                }
            } else {
                //ɶҲ����
            }
        }

        //ȡ����תҪȥ���ĵ�·id���ұߵĵ�·id���ж��������ȼ���һ�ĳ��Ƿ�Ϊ��ת
        //ȡ����תҪȥ���ĵ�·id�Ķ���ĵ�·id���ж��������ȼ���һ�ĳ��Ƿ�Ϊֱ��
        int rightbianRoadId = getrightRoadId(getthisRoadIndexOnroads_id(nextToRoadId, crossId),
                                             crossId);
        bool sff2=false;//<����>
        for(int i=0;i<FirOneIsWaitStateAndNoGoLength;i++){
            if(needSimulationRoad[i]==rightbianRoadId ){
                sff2=FirOneIsWaitStateAndNoGo[i];
            }
        }//<����>
        if(rightbianRoadId!=-1&&!sff2){//��ת����·�Ҳ���//<����>
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
            if(i+1<car->now_routeLength)//<����>
                return route[i+1];
        } else{
//            return -1;//���һ��·���ܲ��ǵ�ǰ·<����>
        }
    }
    return -1;//<����>
}// done  �÷�����ʵ���ظ���
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
    if(car==NULL){return true;}//<����>
    if(roads[roadId-road_base]->waitheadd!=car&&roads[roadId-road_base]->waitheadx!=car){//����ĳ����ǵȴ�����ͷ��Ҳ����ִ�и÷���
        return true;
    }
//    bool isGetToEnd=IsGoToEnd(car,roadId);//�ܵ���·����Ϊ�ȴ�״̬�����ǵ����յ㳵
//    if(isGetToEnd){
//        ////////////////////////////�ж��Ƿ񵽴��յ㣬������ﷵ��false����������ж��Ƿ��ͻ
//
//        return false;
//    } else{
    ////////////////////////////�ж��Ƿ��ͻ�������ͻ����true���������������
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
            int nowTime=this->nowTime;//����������this->nowTime��nowTime=nowTimeΪ0������
            Car *waitGoCars=planheadcar;
            int headwaitGoCarsTime=waitGoCars->planTime;
//            cout<<"<<<<<<<<<<<<"<<headwaitGoCarsTime<<"   "<<nowTime<<endl;//////////////
            if(headwaitGoCarsTime>nowTime){

            } else{
                //  Car waitGoCarsArray[headcarLength];
                Car *tmpwaitGoCars =waitGoCars;
                while (tmpwaitGoCars!=NULL&&tmpwaitGoCars->planTime<=nowTime){
                    Car *tempjcar=tmpwaitGoCars->backcar;//tmpwaitGoCars��backcar���ܻ��޸ģ���һ��������ʧ//<����>
                    Car *car = tmpwaitGoCars;
                    int startCrossId = car->from;
                    int *routes = car->route;
                    //�ж�Ҫ�����ĵ�·�Ƿ�����
                    int startRoadId = car->route[0];
                    /////////////////////////////////////


                    //////////////////////


                    if(startRoadId!=-1&&waitGoCarIsCanGo(startRoadId,car->from)){//<����>
                        //�������������
                        //(Ԥ׼��)�������Ӵ������ĳ������Ƴ��ó���---start
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
                        //�������Ӵ������ĳ������Ƴ��ó���---end
                        headcarLength--;
                        sumCarsOnRoads++;
//                        cout<<nowTime<<"----"<<car->id<<"start"<<endl;/////////////////////////
                        //��ʽ����(�Գ����͵�·�����Խ����޸�)---start
                        Car *pCar = car;
                        int i = waitGoCarGoTocarChannel(startRoadId, car->from);//�õ�Ҫ����������
                        //  �ı�ó���ʵ���ٶ�,�ڵ�·�ϵ���ʻ���룬ʵ�ʿ�ʼʱ�䣬������,�������ĳ���
                        //1.�ó���ʵ�ʿ�ʼʱ��
                        pCar->starttime=nowTime;
                        //2..��ó���distance(ȡ�õ�·���٣��ó������ٶȣ�ǰ����ʻ����)
                        int speed=pCar->speed;  //�����ٶ�
                        Road *pRoad = roads[startRoadId - road_base];
                        int roadMaxSpeed = pRoad->speed;
                        //Car *car1 = pRoad->carlast[i]->backcar;
                        Car *car1 = pRoad->carlast[i];
                        if(car1==NULL){
                            pCar->distance=min(speed,roadMaxSpeed)*1;
                        } else{
                            int nowdistance = pRoad->carlast[i]->distance; //�ó���ǰһ���������߾���
                            pCar->distance=min(nowdistance-1,min(speed,roadMaxSpeed)*1);
                        }

                        //3..�ı䳵�ڵĵ�·
                        pCar->now_lane=i;

                        //�Ե�·���Ե��޸�
                        //��carhead��carlast���޸�,ͬʱ�����������Խ������޸�--start
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
                        //��carhead��carlast���޸�,ͬʱ�����������Խ������޸�--end
                        //carnumx��carnumd��ֵ--start
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
                        //carnumx��carnumd��ֵ--end

                        //�ر�˵��:Car��bool IswaitState; Car * nextWaitCar; Car * frontWaitCar;
                        //��·��Car * waitheadx;  Car * waitheadd;
                        //Handle���waitCarsumδ�����κθĶ�������Щ���Զ���Ҫ�ڵ���·�ϵĳ���ʱ���в���


                    } else{
                        //���ˣ�������
                    }
                    tmpwaitGoCars=tempjcar;
                }

            }
        }
    } else{
        //˼·��
        // 1.���жϳ���״̬�ǵȴ�������ֹ
        // 2.��·�ϵ����д�����ֹ״̬�ĳ����е���һ����λʱ��ľ���ı�
        // 3.����·�ϴ��ڵȴ�״̬�ĳ���
        //...
        //...
        // 4.������·�ϵĳ�����������ɣ����д���δ����״̬�����ĵ���

        //ʵ��------
        // 1.���жϳ���״̬�ǵȴ�������ֹ---start//�����ֹ�Ѿ��ƶ�
        for (int i = 0; i <query_roads_length ; ++i) {
            IswaitState(query_roads[i]);
        }
        // �жϳ���״̬�ǵȴ�������ֹ---end
        for (int i = 0; i <query_roads_length ; ++i) {//�γ�ÿ����·�ȴ�״̬������
            weiWaitheadxOrWaitheadhFUZHI(query_roads[i]->id);
        }
        //2.�����г������ܵĵȴ��ĳ�����---start
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
        //�����г������ܵĵȴ��ĳ�����---end

//        // 3..��·�ϵ����д�����ֹ״̬�ĳ����е���һ����λʱ��ľ���ı�--start//֮ǰ���ƶ����˴������ƶ�<����>
//        for (int j = 0; j <query_roads_length ; ++j) {
//            driveAllCarJustOnRoadToEndState(query_roads[j]);
//        }
        // ��·�ϵ����д�����ֹ״̬�ĳ����е���һ����λʱ��ľ���ı�--end

        // 4..����·�ϴ��ڵȴ�״̬�ĳ���--start

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
                //�õ���ǰҪ���ȵ�·�ڵĵ�·id����ʼ�Ը�·�ڵ���
                int needChangeroadsNum = 0;
                for (int j = 0; j < 4; ++j) {
                    int i = roadsMinid[j];
                    if (i != -1 && (!roads[i - road_base]->one_way || (roads[i - road_base]->one_way && roads[i - road_base]->to == nowcross->id))) {
                        needChangeroadsNum++;
                    }
                }
                //�������ŵ�������һ��������Ӧλ�õ�id��Ӧ�ĳ������ȼ���ߵĳ��Ƿ����뿪����Ȼ�ǵȴ�״̬���������ߡ�
                bool FirOneIsWaitStateAndNoGo[needChangeroadsNum];
                for (int i = 0; i < needChangeroadsNum; ++i) {
                    FirOneIsWaitStateAndNoGo[i] = false;
                }
                //�������ŵ��Ǹ�·��ʵ����Ҫ���ȵĳ�����id��С����
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
                //��������whileѭ�����������������ڵ��ȵ�·�ڵ�ȫ����·�ĵ�һ���ȼ��ĳ������Ⱥ�Ϊ�ȴ�״̬����ǰ������ͨ���·����ȫ������Ϊ��ֹ״̬�ĳ���
                //��Ҫһ����־λ��ͨ���·�ڵĵ�·�д��ڵȴ�״̬�ĳ�����Ŀ��
                while (!(FirOneIsWaitStateAndNoGo_AllTrue(FirOneIsWaitStateAndNoGo, needChangeroadsNum) ||
                         nowcross->TothisCrosswaitCarsum == 0)) {
                    //  int toRoadId = GetNextGoToRoadId(roads[*roadsMinid - road_base], waitStatecarsTothisCross);
                    for (int i = 0; i < needChangeroadsNum; i++) {//<����>
                        if(FirOneIsWaitStateAndNoGo[i]){//�ĵ�·���Ϊ�ѣ����ü��
                            continue;
                        }//<����>
                        Car *firstCar  = getWaitStatecarsTothisCross(needSimulationRoad[i], nowcross->id);
                        if(firstCar==NULL){//�ĵ�·û�еȴ�״̬��  //<����>
                            FirOneIsWaitStateAndNoGo[i]=true;//�ĵ�·�����ټ��
                            continue;
                        }//<����>
                        if(A(firstCar,nowcross->id,needSimulationRoad[i],&FirOneIsWaitStateAndNoGo[0],needChangeroadsNum,needSimulationRoad)){
                            continue;
                        } else{
                            Car *waitStatecarsTothisCross3 = getWaitStatecarsTothisCross(needSimulationRoad[i], nowcross->id);
                            for (;waitStatecarsTothisCross3!=NULL; ) {
                                Car *waitStatecarsTothisCross2=waitStatecarsTothisCross3;
                                waitStatecarsTothisCross3=waitStatecarsTothisCross3->nextWaitCar;//���������Ըı䣬���ܶ�ʧ��һ������ָ��//<����>
                                bool Waitbool= IsWaitStatetoCross(waitStatecarsTothisCross2,roads[needSimulationRoad[i] - road_base]);
                                if(!waitStatecarsTothisCross2->IstoEnd&&Waitbool){//��δ�����յ�����ϣ����·��//<����>
                                    A(waitStatecarsTothisCross2,nowcross->id,needSimulationRoad[i],&FirOneIsWaitStateAndNoGo[0],needChangeroadsNum,needSimulationRoad);
                                }else if(waitStatecarsTothisCross2->IstoEnd||!waitStatecarsTothisCross2->IswaitState){//�������ֹ̬�ƶ��򵽴��յ㣨�жϺ������Եȴ�������,���ĵȴ�����
                                    Road *pRoad2 = roads[needSimulationRoad[i] - road_base];
                                    //�Եȴ�������������д���--start
                                    if (pRoad2->one_way){
                                        if(pRoad2->from<pRoad2->to){
                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                                                if(pRoad2->waitheadx!=NULL)
                                                    pRoad2->waitheadx->frontWaitCar=NULL;//<����>
//                                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;//<����>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<����>
                                                } else{
                                                }
                                            }
                                        } else{

                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadd=pRoad2->waitheadd->nextWaitCar;
                                                if(pRoad2->waitheadd!=NULL)
                                                    pRoad2->waitheadd->frontWaitCar=NULL;//<����>
//                                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<����>
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
                                                    pRoad2->waitheadd->frontWaitCar=NULL;//<����>
//                                                pRoad2->waitheadd->nextWaitCar->frontWaitCar=NULL;//<����>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//����
                                                } else{
                                                }
                                            }
                                        } else{


                                            if(waitStatecarsTothisCross2->frontWaitCar==NULL){
                                                pRoad2->waitheadx=pRoad2->waitheadx->nextWaitCar;
                                                if(pRoad2->waitheadx!=NULL)
                                                    pRoad2->waitheadx->frontWaitCar=NULL;//<����>
//                                                pRoad2->waitheadx->nextWaitCar->frontWaitCar=NULL;//<����>
                                            } else{
                                                Car *frontWaitCar = waitStatecarsTothisCross2->frontWaitCar;
                                                frontWaitCar->nextWaitCar= waitStatecarsTothisCross2->nextWaitCar;
                                                if(waitStatecarsTothisCross2->nextWaitCar!=NULL){
                                                    waitStatecarsTothisCross2->nextWaitCar->frontWaitCar=frontWaitCar;//<����>
                                                } else{
                                                }
                                            }
                                        }
                                    }
                                    //�Եȴ�������������д���--end
                                    //�еȴ�״̬��Ϊ�������������ȴ���ʶֵ����
                                    nowcross->TothisCrosswaitCarsum--;//<����>
                                    waitCarsum--;//<����>
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
        // 4..����·�ϴ��ڵȴ�״̬�ĳ���--end
        //5.���Ȼ�δ��·�ĳ���--start
        if(headcarLength>0){
//            ////////////////////debug////////////////////////////////
//            bool ab;
//            if(nowTime==725&&planheadcar!=NULL&&planheadcar->id==5092){
//                ab=aaaa(2);
//            }
//            /////////////////
            if(planheadcar==NULL){//û�мƻ������ĳ��������ж�
                return true;
            }
            planheadcar=sortById(this->nowTime,planheadcar);
            int nowTime=this->nowTime;//<����>
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
                    tmpwaitGoCars=tmpwaitGoCars->backcar;//<����>
                    int startCrossId = car->from;
                    int *routes = car->route;
                    //�ж�Ҫ�����ĵ�·�Ƿ�����
                    int startRoadId = car->route[0];


                    if(startRoadId!=-1&&waitGoCarIsCanGo(startRoadId,car->from)){//<����>
                        //�������������
                        //(Ԥ׼��)�������Ӵ������ĳ������Ƴ��ó���---start
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
                        //�������Ӵ������ĳ������Ƴ��ó���---end
                        headcarLength--;
                        sumCarsOnRoads++;
//                        cout<<nowTime<<"----"<<car->id<<"start"<<endl;//////////////////////////
//                        return false;/////////////////
                        //��ʽ����(�Գ����͵�·�����Խ����޸�)---start
                        Car *pCar = car;
                        int i = waitGoCarGoTocarChannel(startRoadId, car->from);//�õ�Ҫ����������
                        //  �ı�ó���ʵ���ٶ�,�ڵ�·�ϵ���ʻ���룬ʵ�ʿ�ʼʱ�䣬������,�������ĳ���
                        //1.�ó���ʵ�ʿ�ʼʱ��
                        pCar->starttime=nowTime;
                        //2..��ó���distance(ȡ�õ�·���٣��ó������ٶȣ�ǰ����ʻ����)
                        int speed=pCar->speed;  //�����ٶ�
                        Road *pRoad = roads[startRoadId - road_base];
                        int roadMaxSpeed = pRoad->speed;
                        //Car *car1 = pRoad->carlast[i]->backcar;
                        Car *car1 = pRoad->carlast[i];
                        if(car1==NULL){
                            pCar->distance=min(speed,roadMaxSpeed)*1;
                        } else{
                            int nowdistance = pRoad->carlast[i]->distance; //�ó���ǰһ���������߾���
                            pCar->distance=min(nowdistance-1,min(speed,roadMaxSpeed)*1);
                        }

                        //3..�ı䳵�ڵĵ�·
                        pCar->now_lane=i;

                        //�Ե�·���Ե��޸�
                        //��carhead��carlast���޸�,ͬʱ�����������Խ������޸�--start
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
                        //��carhead��carlast���޸�,ͬʱ�����������Խ������޸�--end
                        //carnumx��carnumd��ֵ--start
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
                        //carnumx��carnumd��ֵ--end

                        //�ر�˵��:Car��bool IswaitState; Car * nextWaitCar; Car * frontWaitCar;
                        //��·��Car * waitheadx;  Car * waitheadd;
                        //Handle���waitCarsumδ�����κθĶ�������Щ���Զ���Ҫ�ڵ���·�ϵĳ���ʱ���в���


                    } else{
                        //���ˣ�������
                    }

                }

            }
        }
        //5.���Ȼ�δ��·�ĳ���--end
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
//    cout<<"��ͷ����"<<js<<endl;
    /////////////////////debug/////////////////////////////////
    return true;
}
//�׺�

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
            len1=shortestl[roads[cur->roads_id[dis[1]]-road_base]->from-cross_base][cur1->to-cross_base];//-cross_base<����>
        }else{
            len1=shortestl[roads[cur->roads_id[dis[1]]-road_base]->to-cross_base][cur1->to-cross_base];//-cross_base<����>
        }
        if(!roads[cur->roads_id[dis[2]]-road_base]->one_way&&roads[cur->roads_id[dis[2]]-road_base]->to==cur->id){
            len2=shortestl[roads[cur->roads_id[dis[2]]-road_base]->from-cross_base][cur1->to-cross_base];//-cross_base<����>
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
           &&c!=cur1->to){//�����·�����յ�,Ҳ����
            continue;
        }else{
            if(roads[cur->roads_id[dis[i3]]-road_base]->from==cur->id){
                if(roads[cur->roads_id[dis[i3]]-road_base]->to>cur->id){
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumx2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//������һ��·
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumd2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//������һ��·
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
            else if(roads[cur->roads_id[dis[i3]]-road_base]->to==cur->id&&!roads[cur->roads_id[dis[i3]]-road_base]->one_way){
                if(roads[cur->roads_id[dis[i3]]-road_base]->from>cur->id){
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumx2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//������һ��·
                        resindex=dis[i3];
                        roads[cur->roads_id[dis[i3]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cur->roads_id[dis[i3]]-road_base]->carnumd2<roads[cur->roads_id[dis[i3]]-road_base]->length*onroadbs){//������һ��·
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

void Handle::cardirect(Cross *cur,int i,int i1)///<����>
{
    for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
        int minspeed=min(roads[cur->roads_minid[i]-road_base]->speed,cur1->speed);//<����>
        if(minspeed<=roads[cur->roads_minid[i]-road_base]->length-cur1->distance){
            break;//ͷ������·�ڣ����泵һ���޷���·��
        }//<����>
        if(cur->roads_minid[i]==cur1->route[cur1->now_routeLength-1]){//�滮�õĵ�·������
            if(cur1->to==cur->id){//�õ��յ㲻����·��//<����>
                continue;//���泵������
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
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->to-cross_base][curcar->to-cross_base];//<����>
        }
        else if(roads[cross->roads_id[dis[1]] - road_base]->to == cross->id){
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->from-cross_base][curcar->to-cross_base];//<����>
        }
        if(roads[cross->roads_id[dis[2]]-road_base]->from==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->to-cross_base][curcar->to-cross_base];//<����>
        }
        else if(roads[cross->roads_id[dis[2]]-road_base]->to==cross->id){
            len2=shortestl[roads[cross->roads_id[dis[2]]-road_base]->from-cross_base][curcar->to-cross_base];//<����>
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
            len1=shortestl[roads[cross->roads_id[dis[1]]-road_base]->to-cross_base][curcar->to-cross_base];//<����>��
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
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumx2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//������һ��·
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumd2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//������һ��·
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
            else if(roads[cross->roads_id[dis[i6]]-road_base]->to==cross->id&&!roads[cross->roads_id[dis[i6]]-road_base]->one_way){
                if(roads[cross->roads_id[dis[i6]]-road_base]->from>cross->id){
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumx2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//������һ��·
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumx2++;
                        return resindex;
                    }
                }
                else{
                    if(roads[cross->roads_id[dis[i6]]-road_base]->carnumd2<roads[cross->roads_id[dis[i6]]-road_base]->length*notonroadbs){//������һ��·
                        resindex=dis[i6];
                        roads[cross->roads_id[dis[i6]]-road_base]->carnumd2++;
                        return resindex;
                    }
                }
            }
        }
    }
}

void Handle::onrdcarjudge()////����
{
    for(Cross *cur=headcross;cur!=NULL;cur=cur->nextcross){//����·��

        for(int i=0;i<4;i++){//������·�ڵĵ�·
            if(cur->roads_minid[i]!=-1){//·�Ƿ����
                //ֻ�ж�ͨ����·�ڵĳ�
                if(!roads[cur->roads_minid[i]-road_base]->one_way){//˫�е�
                    if(roads[cur->roads_minid[i]-road_base]->from==cur->id){//Ѱ�ҵ�·����һ��·����to
                        if(roads[cur->roads_minid[i]-road_base]->to<cur->id){//�Ƚ���·�ڣ�ȷ�������±�
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//��������
                                cardirect(cur,i,i1);
                            }
                        }
                        else{
                            for(int i1=roads[cur->roads_minid[i]-road_base]->channel;i1<2*roads[cur->roads_minid[i]-road_base]->channel;i1++){
                                cardirect(cur,i,i1);
                            }
                        }
                    }else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//Ѱ�ҵ�·����һ��·����from
                        if(roads[cur->roads_minid[i]-road_base]->from<cur->id){//�Ƚ���·�ڣ�ȷ�������±�

                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//��������
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
                else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//���е�//�ҵ�·ͨ�򱾳���//<����>
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
        tcurcar=tcurcar->backcar;//֮��tcurcar���ܱ��Ƴ�����Ҫ��ָ����һ��
//        cout<<curcar->id<<"hscyggg"<<endl;
        if(curcar->planTime>nowTime){
            return;
        }
        if(curcar->route[0]==-1){//<����>
            if(rxcarsum<=maxcar-p2&&l+rxcarsum<=maxcar){//<����>
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
                    l++;//ֻ��l����rxcarsum
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
            }else{//�������������ټ��
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
    for(Cross *cur=headcross;cur!=NULL;cur=cur->nextcross){//����·��
        for(int i=0;i<4;i++){//������·�ڵĵ�·
            if(cur->roads_minid[i]!=-1){//·�Ƿ����
                if(!roads[cur->roads_minid[i]-road_base]->one_way){//˫�е�
                    if(roads[cur->roads_minid[i]-road_base]->from==cur->id){//Ѱ�ҵ�·����һ��·����to
                        if(roads[cur->roads_minid[i]-road_base]->to<cur->id){//�Ƚ���·�ڣ�ȷ�������±�
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//��������
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
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
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
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
                    else if(roads[cur->roads_minid[i]-road_base]->to==cur->id){//Ѱ�ҵ�·����һ��·����from
                        if(roads[cur->roads_minid[i]-road_base]->from<cur->id){//�Ƚ���·�ڣ�ȷ�������±�
                            for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//��������
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
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
                                for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
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
                else{//���е�
                    for(int i1=0;i1<roads[cur->roads_minid[i]-road_base]->channel;i1++){//
                        for(Car *cur1=roads[cur->roads_minid[i]-road_base]->carhead[i1];cur1!=NULL;cur1=cur1->backcar){//���������ϵĳ�
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
    onrdcarjudge();//�ѳ��������ж�
    waitcarjudge();//δ���������ж�
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