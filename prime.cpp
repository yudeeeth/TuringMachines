#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<string>
const int LIM = 100;
using namespace std;

class table{
    public:
    bool empty;
    int state;
    char output;
    bool dir;
    table(){
    }
    table(int s,char c,bool b,bool emp=false){
        state = s;
        output = c;
        dir = b;
        empty = emp;
    }
};

class turing{
    public:
    vector<vector<table>> t;
    unordered_map<char,int> m;
    vector<char> tape; 
    int numofstates;
    int symbols;
    int finalstate;
    int count;
    turing(){
        count = 0;
    }
    void inputlanguage();
    void print(){
        for(auto & x: m){
            cout<<x.first<<" ";
        }
        cout<<endl;
        for(auto &x : t){
            for( auto &i : x){
                cout<<i.state<<i.output<<i.dir<<" ";
            }
            cout<<endl;
        }
    }
    void gettape(){
        int num;
        cin>>num;
        tape.push_back('B');
        for(int i=0;i<num;i++){
            char k;
            cin>>k;
            tape.push_back(k);
        }
        tape.push_back('B');
    }
    void printtape(){
        for(auto &x:tape){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    void compute(int N=0){
        int i = 1;
        int s = 0;
        char red;
        table match;
        while(s!=finalstate){
            if(i==-1){
                tape.insert(tape.begin(),'B');
                i++;
            }
            if(i==tape.size()){
                tape.push_back('B');
            }
            red = tape[i];
            match = t[s][m[red]];
            if(match.empty) {
                //cout<<N<<" is NOT Prime."<<endl;
                cout<<"is not valid"<<endl;
                return;
            }
            s = match.state;
            tape[i] = match.output;
            i += (match.dir)?1:-1;
            printtape();
            for(int it=0;it<tape.size();it++){
                if(it==i) cout<<"^ ";
                else cout<<"  ";
            }
            cout<<endl;
        }
        //cout<<N<<" is Prime."<<endl;
        //cout<<N<<endl;
        cout<<"is valid."<<endl;
        count++;
    }
    void check_primes(){
        for(int i=0;i<LIM;i++){
            tape.clear();
            tape.push_back('B');
            for(int it = 0;it<i;it++){
                tape.push_back('0');
            }
            tape.push_back('1');
            for(int it = 0;it<i;it++){
                tape.push_back('0');
            }
            tape.push_back('B');
            compute(i);
        }
    }
};

void turing::inputlanguage(){
    cin>>numofstates>>symbols;
    for(int i=0;i<symbols;i++){
        char ch;
        cin>>ch;
        m[ch] = i;
    }
    for(int i=0;i<numofstates;i++){
        int xe;
        int tmp;
        cin>>xe;
        t.push_back(vector<table>());
        for(int en=0;en<symbols;en++){
            // char check;
            string check;
            char ch;
            cin>>check;
            if(check == "-"){
                table temp(0,'-',0,1);
                t[i].push_back(temp);
                cin>>check;
                cin>>check;
                continue;
            }
            int state = stoi(check);
            cin>>ch;
            table temp(state,ch,0);
            cin>>ch;
            if(ch=='R'){
                temp.dir = true;
            }
            else temp.dir = false;
            t[i].push_back(temp);
        }
    }
    cin>>finalstate;
}

int main(){
    turing t;
    t.inputlanguage();
    t.gettape();
    t.compute();
    // t.check_primes();
    // cout<<"Number of primes are: "<<t.count<<endl;
}