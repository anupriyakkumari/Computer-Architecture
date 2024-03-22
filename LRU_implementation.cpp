#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

signed main(signed argc, char **argv){
    string PageTableString=argv[1];  

    string out="22116015_"+PageTableString+'_'+argv[2]+"_"+argv[3]+"_"+argv[4]; 
    ofstream MyFile(out);

    ifstream inputs(PageTableString);
    string vpns;
    getline(inputs,vpns);
    getline(inputs,vpns);
    getline(inputs,vpns);
    map<int,int> PageTable;
    while(getline(inputs,vpns)){
        string pfns;
        int string_size=vpns.size();
        int index; 
        for(int i=0;i<string_size;i++){
            if(vpns.at(i)==' '){
                index=i;
                break;
            }
        }
        for(int i=index+1;i<string_size;i++){
            if(vpns.at(i)!=' '){
                pfns=vpns.substr(i,string_size-i);
                vpns=vpns.substr(0,index);
                break;
            }
        }
        PageTable.insert({stoll(vpns),stoll(pfns)});
    }

    string tlbaccessstring=argv[2];
    ifstream input2(tlbaccessstring);
    string VAstring;
    getline(input2,VAstring);
    int offset_bits=stoll(VAstring); 

    vector<pair<int,int>> outvec;

    vector<pair<int,int>> TLBvec; 
    int TLBmax=stoll(argv[4]); 
    int miss=0,hits=0;
    bool flag;
    int accesses=0;
    int pfn;
    while(getline(input2,VAstring)){
        int virtadd=stoll(VAstring);
        int vpn=virtadd>>offset_bits;
        flag=false;
        for(int i=0;i<TLBvec.size();i++){ 
            if(TLBvec[i].first==vpn){
                pfn=TLBvec[i].second;
                int phyadd=((pfn)<<offset_bits);
                phyadd+=virtadd-(vpn<<offset_bits);
                TLBvec.erase(TLBvec.begin()+i);
                TLBvec.push_back({vpn,pfn});

                flag=true;
                outvec.push_back({1,phyadd});
            }
        }
        if(flag==false){ 
            miss++;
            int vpn=virtadd>>offset_bits; 
            if(TLBvec.size()==TLBmax){
                TLBvec.erase(TLBvec.begin()); 
            }
            int pfn=PageTable[vpn];
            int phyadd=((pfn)<<offset_bits);
            phyadd+=virtadd-(vpn<<offset_bits); 
            TLBvec.push_back({vpn,pfn}); 

            outvec.push_back({0,phyadd}); 
        }else hits++;
        accesses++;
    }
    MyFile<<"TOTAL_ACCESSES = "<<accesses<<"\n";
    MyFile<<"TOTAL_MISSES = "<<miss<<"\n";
    MyFile<<"TOTAL_HITS = "<<hits<<"\n";
    for(auto it:outvec){
        if(it.first==1){
            MyFile<<it.second<<" HIT\n";
        }else{
            MyFile<<it.second<<" MISS\n";
        }
    }
    return 0;
}