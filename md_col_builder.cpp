#include <iostream>
#include <fstream>
using namespace std;
class stringlist{
    stringlist * head = nullptr;


public:
    void add_next(string s);
    string pop();
    stringlist(string s):ele(s){head =this;}
    stringlist(){head= this;}

    string ele="";
    stringlist * next= nullptr;
};


void stringlist::add_next(string s) {
    stringlist *insert_pos = this;
    if (insert_pos->ele == "") {
        ele = s;
    } else{
        while(insert_pos->next!= nullptr){
            insert_pos = insert_pos->next;
        }
        insert_pos->next = new stringlist(s);
    }
}

string stringlist::pop() {
    if(head== nullptr){
        return "";
    }else{
        string pop = head->ele;
        head = head->next;
        return pop;
    }
}

int main(int argc,char *args[]) {
    ofstream out;
    bool out_to_file = false;
    if(argc > 0){
        for(int i = 0 ;i <argc;i++){
            string s=args[i];
            if(s=="-o"){
                out.open(args[i+1]);
                out_to_file = true;
                break;
            }
        }
    }
    cout<<"Please enter the number of columns"<<endl;
    int num=0;
    cin>>num;
    stringlist table[num]={};
    string format[3]={"-------------",":-------------:","-----:"};
    for(int i = 0 ; i < num ;i++) {
        std::cout << "Enter col " << i+1 <<"'s title"<< std::endl;
        string s = "";
        int forma = 0;
        cin>>s;
        table[i].add_next(s);
        std::cout << "Enter col " << i+1 <<"'s format (left-align 0 ,center 1 ,right-align 2)"<< std::endl;
        cin>>forma;
        table[i].add_next(format[forma%3]);
        std::cout << "Enter col " << i+1 <<"'s data \n1 data/line  \n ended by a / "<< std::endl;
        while (true) {
            cin >> s;
            if (s == "/") {
                break;
            } else {
                table[i].add_next(s);
            }
        }
    }
    string data[num]={};
    bool nodata = true;
    string output = "";
    for(int i = 0 ; i < num ;i=(i+1)%num) {
        data[i]= table[i].pop();
        nodata = nodata&&(data[i]=="");
        output+=("|"+data[i]);
        if(i+1 == num) {
            if(!nodata){
                if(out_to_file){
                    out<<output<<"|"<<endl;
                }else{
                    cout<<output<<"|"<<endl;
                }
                output="";
                nodata =true;
            }else{
                break;
            }
        }
    }
    out.close();
    exit(0);
}
