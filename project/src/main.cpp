#include "../include/FileManager.hpp"
#include <iostream>
#include <sstream>

using namespace std;

vector<string> split(const string &line){
    istringstream iss(line);
    vector<string> tokens;
    string token;
    while(iss >> token){
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    FileManager fm;
    string line;
    while(getline(cin, line)){
        auto tokens = split(line);

        if(tokens.empty()){
            continue;
        }

        if(line == "EXIT" || line == "QUIT"){
            cout << "Exiting.\n";
            break;
        }

        string func;
        func = tokens[0];

        if(func=="CREATE"){
            if(tokens.size() != 2){
                cout << "Input should be of the form CREATE <filename>.\n";
                continue;
            }
            string filename = tokens[1];
            fm.create(filename);
        }
        else if(func=="READ"){
            if(tokens.size() != 2){
                cout << "Input should be of the form READ <filename>.\n";
                continue;
            }
            string filename = tokens[1];
            fm.read(filename);
        }
        else if(func=="INSERT"){
            if(tokens.size()<3){
                cout << "Input should be of the form INSERT <filename> <content>.\n";
                continue;
            }
            string filename = tokens[1];
            string content = "";
            for(int i=2; i<tokens.size(); i++){
                content += tokens[i];
                content += " ";
            }
            fm.insert(filename, content);
        }
        else if(func=="UPDATE"){
            if(tokens.size()<3){
                cout << "Input should be of the form UPDATE <filename> <content>.\n";
                continue;
            }
            string filename = tokens[1];
            string content = "";
            for(int i=2; i<tokens.size(); i++){
                content += tokens[i];
                content += " ";
            }
            fm.update(filename, content);
        }
        else if(func=="SNAPSHOT"){
            if(tokens.size()<3){
                cout << "Input should be of the form SNAPSHOT <filename> <message>.\n";
                continue;
            }
            string filename = tokens[1];
            string message = "";
            for(int i=2; i<tokens.size(); i++){
                message += " ";
                message += tokens[i];
            }
            fm.snapshot(filename, message);
        }
        else if(func=="ROLLBACK"){
            if(tokens.size()<2 || tokens.size()>3){
                cout << "Input should be of the form ROLLBACK <filename> [versionID].\n";
                continue;
            }
            string filename = tokens[1];
            string version_id;
            if(tokens.size()==2){
                version_id = "";
            }
            else if(tokens.size()==3){
                version_id = tokens[2];
                int v = 0;
                try{
                    v = stoi(version_id);
                }
                catch(const invalid_argument& e){
                    cout << "Version ID entered is not an integer.\n";
                    continue;
                }
            }
            fm.rollback(filename, version_id);
        }
        else if(func=="HISTORY"){
            if(tokens.size()<2){
                cout << "Input should be of the form HISTORY <filename>.\n";
                continue;
            }
            string filename = tokens[1];
            fm.history(filename);
        }
        else if(func=="RECENT_FILES"){
            if(tokens.size()<1 || tokens.size()>3){
                cout << "Input should be of the form RECENT_FILES [num].\n";
            }
            int num;
            if(tokens.size()==1){
                num = -1;
            }
            else{
                try{
                    num = stoi(tokens[1]);
                }
                catch(const invalid_argument& e){
                    cout << "Num entered is not an integer.\n";
                    continue;
                }
                if(num<=0){
                    cout << "Num entered should be a positive integer.\n";
                    continue;
                }
            }
            fm.recent_files(num);
        }
        else if(func=="BIGGEST_TREES"){
            if(tokens.size()<1 || tokens.size()>3){
                cout << "Input should be of the form BIGGEST_TREES [num].\n";
            }
            int num;
            if(tokens.size()==1){
                num = -1;
            }
            else{
                try{
                    num = stoi(tokens[1]);
                }
                catch(const invalid_argument& e){
                    cout << "Num entered is not an integer.\n";
                    continue;
                }
                if(num<=0){
                    cout << "Num entered should be a positive integer.\n";
                    continue;
                }
            }
            fm.biggest_trees(num);
        }
        else{
            cout << "Invalid Input.\n";
        }
    }
}