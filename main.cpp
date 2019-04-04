#include <iostream>
#include<fstream>
#include<vector>
#include <map>
#include<algorithm>
#include <bits/stdc++.h>
#include<math.h>

using namespace std;
vector<float> data;
vector<float> amp_data;
vector<int > ack;
vector<float> Apkt;
vector<float> Bpkt;
vector<float> Cpkt;
vector<int > actual_ack;
vector<int > A_trans;
vector<int > B_trans;
vector<int > C_trans;
map<int,string> AP_pkt;
int A_transmission[20];

int A_total,B_total,C_total;
int useful_work=0;
double medium_busy=0;

vector<float> parsestring(string line){
    vector<float> tokens;
    stringstream check1(line);
    string intermediate;
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(stof(intermediate));
    }
    return tokens;
}

void readfile(string file_name){
    string line;
    vector<float> each_line;
    int i=0;
    ifstream projfile( file_name );
    if (projfile) {
        while (getline(projfile, line)) {
            if(line.empty()) continue;
            each_line=parsestring(line);
            amp_data.push_back(each_line[0]);
            data.push_back(sqrt((each_line[0]*each_line[0])+(each_line[1]*each_line[1])));
            i++;
        }
        projfile.close();
    } else cout << "Unable to open file";

}

void find_ack(){
    int a=0;
    for(int i=0;i<data.size();i++){
        if(0.15<data[i] && data[i]<0.35){
            ack.push_back(i);
            //cout<<i<<endl;
            a++;
        }
    }
    ack.push_back(600000);
    //cout<<"**************"<<endl;
    int act_ack=0;
    int tt=0;
    auto show=ack.begin();
    for(auto it=ack.begin();it!=ack.end()-1;++it){

        if(*(it+1)-*(it)<3){
            tt++;
        } else{
            if(tt>3 && tt<15) {
                advance(show, tt / 2);
                //if(tt<15) {
                    //cout << "ack length: " << tt << " \t ack in : " << *show << endl;
                    actual_ack.push_back(*show);
                    act_ack++;
                }

                show = it + 1;
                tt=0;
        }
    }
    //cout<<endl<<"actual ack "<<act_ack<<endl;
    //cout<<endl<<a;
}

void find_nodeA(){
    int a=0;
    for(int i=0;i<data.size();i++){
        if(0.35<data[i] && data[i]<0.6){
            Apkt.push_back(i);
            //cout<<i<<endl;
            a++;
        }
    }
    Apkt.push_back(600000);
    //cout<<"**************"<<endl;
    int act_Apkt=0;
    int tt=0;
    auto show=Apkt.begin();
    for(auto it=Apkt.begin();it!=Apkt.end();it++){
        if(*(it+1)-*(it)<7){
            tt++;
        } else{

            if(tt>160 && tt<180) {
                //advance(show, tt / 2);
                //if(tt<15) {
                //cout << "A length: " << tt << " \t Pkacket A in : " << *show << endl;
                //cout<<"node A transmitted a Packet at "<<*show<<endl;
                A_trans.push_back(*show);
                act_Apkt++;
            }
            show = it + 1;
            tt=0;

            /*if(tt>170) {
                //advance(show, tt / 2);
                if(tt<180) {
                    cout << "Apacket length: " << tt << " \t A in : " << *show << endl;
                    A_trans.push_back(*show);
                }
                tt = 0;
                show = it + 1;
                act_Apkt++;
            }
            else{
                continue;
            }*/
        }
    }
    //cout<<endl<<"actual A packets "<<act_Apkt<<endl;
    //cout<<endl<<a;
}



void find_A_detail(){
    int count=0;
    int transmission[20];
    for(int i=0;i<20;i++)
        transmission[i]=0;
    int received=0;
    for(int i: A_trans){
        int x=i;
        count++;
        for(int j: actual_ack){
            if(x+170<j and x+190> j){
                received++;
                //cout<<"The successful transmission of node A at "<< j<<" took "<<count <<" tries"<<endl;
                AP_pkt[j]="A";
                if(count>=0 && count<20)
                    transmission[count]++;
                count=0;
                break;
            }

        }
    }
/*    cout<<"Total packet AP received are: "<<received<<endl;

    cout<<"*********************************";
    for(int i=0;i<20;i++)
        cout<<i<<" transmission :"<< transmission[i]<<endl;
    cout<<"*********************************";*/

    for(int i=0;i<20;i++)
        A_transmission[i]=transmission[i];

    A_total=received;
    //AP_pkt[received]="A";

}

void find_nodeB(){
    int a=0;
    for(int i=0;i<data.size();i++){
        if(0.02<data[i] && data[i]<0.06){
            Bpkt.push_back(i);
            //cout<<i<<endl;
            a++;
        }
    }
    Bpkt.push_back(600000);
    //cout<<"**************"<<endl;
    int act_Bpkt=0;
    int tt=0;
    auto show=Bpkt.begin();
    for(auto it=Bpkt.begin();it!=Bpkt.end();it++){
        if(*(it+1)-*(it)<7 ||(*(it+1)-*(it)<15) && data[*(it+1)]<0.02){
            tt++;
        } else{
            if(tt>160 && tt<260) {
                //advance(show, tt / 2);
                //if(tt<15) {
                //cout << "B length: " << tt << " \t Pkacket B in : " << *show << endl;
                B_trans.push_back(*show);
                act_Bpkt++;
                //show = it + 1;
            }
            show = it + 1;
            tt=0;

            /*if(tt>170) {
                //advance(show, tt / 2);
                if(tt<180) {
                    cout << "Apacket length: " << tt << " \t A in : " << *show << endl;
                    A_trans.push_back(*show);
                }
                tt = 0;
                show = it + 1;
                act_Bpkt++;
            }
            else{
                continue;
            }*/
        }
    }
    //cout<<endl<<"actual B packets "<<act_Bpkt<<endl;
    //cout<<endl<<a;

}


void find_B_detail(){
    int count=0;
    int transmission[10];
    for(int i=0;i<10;i++)
        transmission[i]=0;
    int received=0;
    for(int i: B_trans){
        int x=i;
        count++;
        for(int j: actual_ack){
            if(x+150<j && x+300> j){
                received++;
               // cout<<"The successful transmission of node B at "<< j<<" took "<<count <<" tries"<<endl;
                AP_pkt[j]="B";
                if(count>=0 && count<10)
                    transmission[count]++;
                count=0;
                break;
            }

        }
    }
/*    cout<<"Total packet AP received are: "<<received<<endl;

    cout<<"*********************************";
    for(int i=0;i<10;i++)
        cout<<i<<" transmission :"<< transmission[i]<<endl;
    cout<<"*********************************";*/
    B_total=received;
    //AP_pkt[received]="B";
}



void find_nodeC(){
    int a=0;
    for(int i=0;i<data.size();i++){
        if(0.005<data[i] && data[i]<0.02){
            Cpkt.push_back(i);
            //cout<<i<<endl;
            a++;
        }
    }
    Cpkt.push_back(600000);
    //cout<<"**************"<<endl;
    int act_Cpkt=0;
    int tt=0;
    auto show=Cpkt.begin();
    for(auto it=Cpkt.begin();it!=Cpkt.end();it++){
        if(*(it+1)-*(it)<7) {
            tt++;
        } else{
            if(tt>421 && tt<520) {
                //advance(show, tt / 2);
                //if(tt<15) {
                //cout << "C length: " << tt << " \t Pkacket C in : " << *show << endl;
                C_trans.push_back(*show);
                act_Cpkt++;
                //show=it+1;
            }
            show = it + 1;
            tt=0;

            /*if(tt>170) {
                //advance(show, tt / 2);
                if(tt<180) {
                    cout << "Apacket length: " << tt << " \t A in : " << *show << endl;
                    C_trans.push_back(*show);
                }
                tt = 0;
                show = it + 1;
                act_Cpkt++;
            }
            else{
                continue;
            }*/
        }
    }
    C_total=act_Cpkt;
    //cout<<endl<<"actual C packets "<<act_Cpkt<<endl;
    //cout<<endl<<a;
}


void find_C_detail(){
    int count=0;
    int transmission[10];
    for(int i=0;i<10;i++)
        transmission[i]=0;
    int received=0;
    for(int i: C_trans){
        int x=i;
        count++;
        for(int j: actual_ack){
            if(x+420<j && x+540> j){
                received++;
                //cout<<"The successful transmission of node C at "<< j<<" took "<<count <<" tries"<<endl;
                AP_pkt[j]="C";
                if(count>=0 && count<10)
                    transmission[count]++;
                count=0;
                break;
            }

        }
    }
/*    cout<<"Total packet AP received are: "<<received<<endl;

    cout<<"*********************************";
    for(int i=0;i<10;i++)
        cout<<i<<" transmission :"<< transmission[i]<<endl;
    cout<<"*********************************";*/
    C_total=received;

}

void medium_busy_func(){
    medium_busy=0;
    for(int i=0;i<data.size();i++){
        if(0.001<data[i]){
           medium_busy++;
            //cout<<i<<endl;

        }
    }
}


int main(int argc, char* argv[]) {
    if(argc<2){
        cout<<"Useage: ./output file_name"<<endl;
        exit(0);
    }
    readfile(argv[1]);
    find_ack();
    find_nodeA();
    find_A_detail();
    find_nodeB();
    find_B_detail();
    find_nodeC();
    find_C_detail();
    medium_busy_func();
    double usefulwork=((A_total*174+B_total*250+C_total*500));
    double total=data.size();
    //double medium_busy_result=medium_busy/total;
    //cout<<per_usefulwork;
    cout<<endl;
    cout<<"-------------------- REPORT BGN ---------------------------"<<endl;
    cout<<"1. The number of packets from A "<<A_total<<" , B "<<B_total<<", C "<<C_total<<endl;
    cout<<"2. The percentage medium busy "<<(medium_busy/total)*100<<endl;
    cout<<"3. The percentage medium doing useful work "<<(usefulwork/total)*100<<endl;
    cout<<"-------------------- REPORT END ---------------------------"<<endl;

    cout<<endl;

    cout<<"-------------------- BONUS  BGN ---------------------------"<<endl;
    cout<<"For node A to get a packet received:"<<endl;
    for(int i=1;i<20;i++)
        cout<<i<<" transmission: "<<A_transmission[i]<<endl;
    cout<<"-------------------- BONUS  END ---------------------------"<<endl;

    for(auto i: AP_pkt){
        cout<<"AP received a packet from node " <<i.second <<" at "<<i.first<<endl;
        //AP received a packet from node B at 197
    }
    for(auto i: A_trans) {
        cout << "node A transmitted a Packet at " << i << endl;
    }

    return 0;
}
