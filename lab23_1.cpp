#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream user_file(filename);
    string line;
    while(getline(user_file,line)){
        const char*text=line.c_str();
        char format[]="%[^:]: %d %d %d";
        char username[100];
        string realusername;
        int userscore[3],usergrade,userallscore;
        sscanf(text,format,username,&userscore[0],&userscore[1],&userscore[2]);
        realusername=username;
        userallscore=(userscore[0]+userscore[1]+userscore[2]);
        usergrade=score2grade(userallscore);
        names.push_back(realusername);
        scores.push_back(userallscore);
        grades.push_back(usergrade);
    }
    user_file.close();
    return;
}

void getCommand(string &command,string &key){
    cout<<"Please input your command:\n";
    string line;
    getline(cin,line);
    const char*input=line.c_str();
    char format[]="%s %s";
    char comm[100],keyy[100];
    sscanf(input,format,comm,keyy);
    command=comm;
    line.erase(0,command.size()+1);
    key=line;
    return;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool check=false;
    for(unsigned int i=0;i<names.size();i++){
        if(toUpperStr(names[i])==key){
            cout << "---------------------------------\n";
            cout<<names[i]<<"'s score = "<<scores[i]<<"\n";
            cout<<names[i]<<"'s grade = "<<grades[i]<<"\n";
            cout << "---------------------------------\n";
            check=true;
            break;
        }
    }
    if(!check){
        cout<<"---------------------------------\n";
        cout<<"Cannot found.\n";
        cout<<"---------------------------------\n";
    }
    return;
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool check=false;
    cout<<"---------------------------------\n";
    for(unsigned int i=0;i<grades.size();i++){
        if(toupper(grades[i])==key[0]){
            cout<<names[i]<<" ("<<scores[i]<<")\n";
            check=true;
        }
    }
    if(!check) cout<<"Cannot found.\n";
    cout<<"---------------------------------\n";
    return;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
