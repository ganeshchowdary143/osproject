#include<iostream>
using namespace std;

class os10v {
int *rem_bt,*index,*a_tm,*b_tm,*w_tm,*c_tm,*ta_tm;
int cur_tm=0,noOfProcesses,total_tm=0,quant_tm,idle_tm=0;
int *sortindex;
public:
 bool total_rm_tm0(){
bool rm_tm = true;
for (int i = 0; i < noOfProcesses; i++) {
    if(rem_bt[i]!=0){
        return false;
    }
}
return rm_tm;
}
 void add_rem_bt(){
    for (int i = 0; i < noOfProcesses; i++) {
        if(rem_bt[i]==-1){
            if(a_tm[i]<=cur_tm){
                rem_bt[i]=b_tm[i];
            }
        }
    }
}
 void set_sortest_rem(){
    sortindex[0]=0;sortindex[1]=(noOfProcesses-(noOfProcesses/2));
    for (int i = 0; i < noOfProcesses/2; i++) {
        int temp=-1;
        if(rem_bt[sortindex[0]]==0){
           rem_bt[sortindex[0]]=total_tm;
           temp=sortindex[0];
        }
        if(rem_bt[i]>0){
            if(rem_bt[sortindex[0]]>rem_bt[i]){
                // std::cout << "check" <<rem_bt[0]<<'\n';
                sortindex[0]=i;
            }
        }
        if(temp!=-1){
            rem_bt[temp]=0;
        }
    }
    // if(sortindex[0]==total_tm){
    //     sortindex[0]=0;
    // }
    for (int i = (noOfProcesses-(noOfProcesses/2)); i < noOfProcesses; i++) {
               int temp=-1;
        if(rem_bt[sortindex[1]]==0){
           rem_bt[sortindex[1]]=total_tm;
           temp=sortindex[1];
        }
        if(rem_bt[i]>0){
            if(rem_bt[sortindex[1]]>rem_bt[i]){
                sortindex[1]=i;
            }
        }
        if(temp!=-1){
            rem_bt[temp]=0;
        }
    }
    // std::cout << "check" <<rem_bt[0]<<"-"<<c_tm[0]<<"-"<<sortindex[0]<<'\n';
    // if(sortindex[1]==total_tm){
    //     sortindex[1]=0;
    // }
}
 bool all_empty(int check){
    switch(check){
        case 1:    for (int i = 0; i < noOfProcesses; i++) {
            if(rem_bt[i]>=0){
                return false;
            }
        }
        break;
        case 2:    for (int i = 0; i < noOfProcesses/2; i++) {
            if(rem_bt[i]!=0){
                return false;
            }
        }
        break;
        case 3:    for (int i = (noOfProcesses-(noOfProcesses/2)); i < noOfProcesses; i++) {
            if(rem_bt[i]!=0){
                return false;
            }
        }
        break;
    }
    return true;
}
 int get_next_a_t(){
    int n_a_t=total_tm;
    for (int i = 0; i < noOfProcesses; i++) {
        if(rem_bt[i]==-1){
            if(n_a_t>a_tm[i]){
                n_a_t=a_tm[i];
            }
    }
}
    return n_a_t;
}
void pro_add_sub(int c,int cr){
    cur_tm+=c;
    rem_bt[cr]-=c;
    c_tm[cr]=cur_tm;
}
 void pro_add(int a,int b,int cr){
    if(a>=b){
        pro_add_sub(b, cr);
    }
    else{
        pro_add_sub(a, cr);
    }
}
 void pro_sel(bool q1){
    int cur;
    if(q1){
        cur=sortindex[0];
        // std::cout << "check" <<rem_bt[0]<<'\n';
    }
    else{
        cur=sortindex[1];
    }
    int next_a_tm=get_next_a_t();
    if(next_a_tm>=quant_tm){
        if(rem_bt[cur]>0)
        pro_add(rem_bt[cur],quant_tm,cur);
    }
    else{
        if(rem_bt[cur]>0)
        pro_add(rem_bt[cur],next_a_tm,cur);
    }
}
 os10v() {
    quant_tm=2;int avg_wtm=0,avg_tatm=0;
    // noOfProcesses=4;
    cout<<"enter number of processes: ";
    cin>>noOfProcesses;
    sortindex = new int[2];
    rem_bt = new int[noOfProcesses];
    a_tm = new int[noOfProcesses];
    b_tm = new int[noOfProcesses];
    w_tm = new int[noOfProcesses];
    c_tm = new int[noOfProcesses];
    ta_tm = new int[noOfProcesses];
    //     a_tm[0] = 0;a_tm[1] = 1;a_tm[2] = 2;a_tm[3] = 3;
    // b_tm[0] = 2;b_tm[1] = 5;b_tm[2] = 4;b_tm[3] = 5;
    for (int i = 0; i < noOfProcesses; i++) {
        cout<<"enter arrival time, burst time of p"<<(i+1)<<":";
        cin>>a_tm[i]>>b_tm[i];
    }
    for (int i = 0; i < noOfProcesses; i++) {
        rem_bt[i]=-1;
        c_tm[i]=0;
        total_tm+=b_tm[i];
    }
    while(total_rm_tm0()!=true){
        // std::cout << "check" << '\n';
        add_rem_bt();
        set_sortest_rem();
        if(all_empty(1)){
            // std::cout << "check" << '\n';
            cur_tm++;
            idle_tm++;
            continue;
        }
        if(all_empty(2)){
            // std::cout << "check" << '\n';
            pro_sel(false);
        }
        else{
            // std::cout << "check" << '\n';
            pro_sel(true);
        }
    }
    for (int i = 0; i < noOfProcesses; i++) {
        w_tm[i]=((c_tm[i]-a_tm[i])-b_tm[i]);
        ta_tm[i]=(c_tm[i]-a_tm[i]);
        avg_tatm+=ta_tm[i];
        avg_wtm+=w_tm[i];
        cout<<w_tm[i]<<" "<<ta_tm[i]<<"\n";
    }
    cout<<"avg waiting time:"<<avg_wtm/noOfProcesses<<"\navg turn around time: "<<avg_tatm/noOfProcesses;
}    
};
int main(int argc, char const *argv[])
{
    os10v obj;
    return 0;
}
