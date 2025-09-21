#include "../include/FileManager.hpp"
#include <iostream>
using namespace std;

FileManager::FileManager(){};

// Create a new file, if it doesn't exist already
void FileManager::create(string filename){
    File* file = new File();
    if(Files.get(filename, file)){
        cout << "Error: File already exists.\n";
        return ;
    }
    Files.put(filename, file);
    file->modified_timestamp = time(nullptr);
    cout << "File successfully created.\n";
    return ;
};

// Read the content of the file
void FileManager::read(string filename){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    cout << file->active_version->content << "\n";
    return ;
};

// Append content to the file 
// Create a new version if the active version is snapshotted
void FileManager::insert(string filename, string content){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    TreeNode* active = file->active_version;
    if(active->message == ""){
        active->content += content;
        cout << "Content of active version (version ID " << file->active_version->version_id << ") appended in place.\n";
        return ;
    }
    TreeNode* new_version = new TreeNode();
    new_version->parent = active;
    new_version->version_id = file->total_versions;
    new_version->content = active->content + content;
    active->children.push_back(new_version);
    cout << "Created a new version (version ID " << new_version->version_id << ") with appended content.\n";
    file->active_version = new_version;
    file->total_versions++;
    file->version_map.push_back(new_version);
    file->modified_timestamp = time(nullptr);
    return ;
};

// Update the content of the file
// Same versioning logic as insert
void FileManager::update(string filename, string content){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    TreeNode* active = file->active_version;
    if(active->message == ""){
        active->content = content;
        cout << "Content of active version (version ID " << file->active_version->version_id << ") updated in place.\n";
        return ;
    }
    TreeNode* new_version = new TreeNode();
    new_version->parent = active;
    new_version->version_id = file->total_versions;
    new_version->content = content;
    active->children.push_back(new_version);
    cout << "Created a new version (version ID " << new_version->version_id << ") with updated content.\n";
    file->active_version = new_version;
    file->total_versions++;
    file->version_map.push_back(new_version);
    file->modified_timestamp = time(nullptr);
    return ;
};

// Snapshot the active version, making it immutable
void FileManager::snapshot(string filename, string message){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    if(file->active_version->message!=""){
        cout << "Active version (version ID " << file->active_version->version_id << ") is already a snapshot.\n";
        return ;
    }
    file->active_version->message = message;
    file->active_version->snapshot_timestamp = time(nullptr);
    cout << "Current version (version ID " << file->active_version->version_id << ") snapshotted with given message.\n";
    return ;
};

// Rollback to a previous version
// Rollback to parent if version ID is not specified
void FileManager::rollback(string filename, string version_id){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    if(version_id == ""){
        if(file->active_version->parent==nullptr){
            cout << "Error: Active version (version ID " << file->active_version->version_id << ") has no parent.\n";
            return ;
        }
        file->active_version = file->active_version->parent;
        cout << "Reverting to parent (version ID " << file->active_version->version_id << ").\n";
        return ;
    }
    int version_id_int = stoi(version_id);
    if(version_id_int <0 || version_id_int >= file->total_versions){
        cout << "Error: Given version ID does not exist.\n";
        return ;
    }
    file->active_version = file->version_map[version_id_int];
    cout << "Active version has been set to version " << version_id_int << ".\n"; 
    return ;
};

// Lists all snapshotted versions of the file chronologically, which lie on the path
// from active node to the root in the file tree, showing their ID, timestamp, and message.
void FileManager::history(string filename){
    File* file = nullptr;
    if(!Files.get(filename, file)){
        cout << "Error: File with given filename does not exist.\n";
        return ;
    }
    TreeNode* temp = file->active_version;
    while(temp!=nullptr){
        if(temp->message!=""){
            cout << "ID: " << temp->version_id << "\n";
            cout << "Timestamp: " << ctime(&temp->created_timestamp);
            cout << "Message: " << temp->message << "\n";
        }
        temp = temp->parent;
    }
    return ;
};

// Lists files in descending order of their last modification time restricted to the
// first num entries
void FileManager::recent_files(int num){
    vector<string> keys = Files.keys();
    vector<pair<string, File*>> file_list;
    for(int i=0; i<keys.size(); i++){
        File* file = nullptr;
        Files.get(keys[i], file);
        file_list.push_back({keys[i], file});
    }
    Heap max_files = Heap(file_list, false);
    int max_limit = file_list.size();
    
    if(num<max_limit && num>0){
        max_limit = num;
    }
    for(int j=0; j<max_limit; j++){
        pair<string, File*> file = max_files.pop();
        cout << "File Name: " << file.first << " | Last modified time: " << ctime(&file.second->modified_timestamp) << "\n";
    }
    return ;
};

// Lists files in descending order of their total version count restricted to the first
// num entries
void FileManager::biggest_trees(int num){
    vector<string> keys = Files.keys();
    vector<pair<string, File*>> file_list;
    for(int i=0; i<keys.size(); i++){
        File* file = nullptr;
        Files.get(keys[i], file);
        file_list.push_back({keys[i], file});
    }
    Heap max_files = Heap(file_list, true);
    int max_limit = file_list.size();
    if(num<max_limit && num>0){
        max_limit = num;
    }
    for(int j=0; j<max_limit; j++){
        pair<string, File*> file = max_files.pop();
        cout << "File Name: " << file.first << " | Total versions: " << file.second->total_versions << "\n";
    }
    return ;
};