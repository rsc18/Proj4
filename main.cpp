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
            cout<<i<<endl;
            a++;
        }
    }
    ack.push_back(600000);
    cout<<"**************"<<endl;
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
                    cout << "ack length: " << tt << " \t ack in : " << *show << endl;
                    actual_ack.push_back(*show);
                    act_ack++;
                }

                show = it + 1;
                tt=0;

            //}
           // else{
             //   tt=0;
               // continue;
            //}
            //tt=0;
        }
    }
    cout<<endl<<"actual ack "<<act_ack<<endl;
    cout<<endl<<a;
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
    cout<<"**************"<<endl;
    int act_Apkt=0;
    int tt=0;
    auto show=Apkt.begin();
    for(auto it=Apkt.begin();it!=Apkt.end();it++){
        if(*(it+1)-*(it)==1){
            tt++;
        } else{
            if(tt>170) {
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
            }
        }
    }
    cout<<endl<<"actual A packets "<<act_Apkt<<endl;
    cout<<endl<<a;
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
    cout<<"**************"<<endl;
    int act_Bpkt=0;
    int tt=0;
    auto show=Bpkt.begin();
    for(auto it=Bpkt.begin();it!=Bpkt.end();it++){
        if(*(it+1)-*(it)<5){
            tt++;
        } else{
            if(tt>20) {
                //advance(show, tt / 2);
                cout<<"Bpacket length: "<<tt<<" \t B in : "<<*show<<endl;
                tt = 0;
                show = it + 1;
                act_Bpkt++;
            }
            else{
                continue;
            }
        }
    }
    cout<<endl<<"actual B packets "<<act_Bpkt<<endl;
    cout<<endl<<a<<endl;
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
    cout<<"**************"<<endl;
    int act_Cpkt=0;
    int tt=0;
    auto show=Cpkt.begin();
    for(auto it=Cpkt.begin();it!=Cpkt.end();it++){
        if(*(it+1)-*(it)<3){
            tt++;
        } else{
            if(tt>40) {
                //advance(show, tt / 2);
                cout<<"Cpacket length: "<<tt<<" \t C in : "<<*show<<endl;
                tt = 0;
                show = it + 1;
                act_Cpkt++;
            }
            else{
                continue;
            }
        }
    }
    cout<<endl<<"actual C packets "<<act_Cpkt<<endl;
    cout<<endl<<a<<endl;
}

void find_A_detail(){
    int count=0;
    int transmission[10];
    for(int i=0;i<10;i++)
        transmission[i]=0;
    int received=0;
    for(int i: A_trans){
        int x=i;
        count++;
        for(int j: actual_ack){
            if(x+170<j and x+190> j){
                received++;
                cout<<"The successful transmission of node A at "<< j<<" took "<<count <<" tries"<<endl;
                if(count>=0 && count<=10)
                    transmission[count]++;
                count=0;
                break;
            }

        }
    }
    cout<<"Total packet AP received are: "<<received<<endl;

    cout<<"*********************************";
    for(int i=0;i<10;i++)
        cout<<i<<" transmission :"<< transmission[i]<<endl;
    cout<<"*********************************";

}

int main() {
    readfile("/home/tangent/Desktop/spring2019/untitled/proj4_MAC_testdata1");
    find_ack();
    find_nodeA();
    find_A_detail();
    //find_nodeB();
    //find_nodeC();

    return 0;
}
