#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int readFile(string filename, vector<string> &result){
    string line;
    ifstream file(filename);

    while(getline(file, line)){
        result.push_back(line);
    }
    //Need to add the part 
    /*
        try{

        }catch{

        }
        block
    */


    return 1;
}

bool findLine(vector<string>& file, string &line){
    for(int i = 0; i < file.size(); i++){
        if(file[i] == line){
            return true;
        }
    }
    return false;
}

void compareChanges(vector<string> &result1, vector<string> &result2, vector<vector<string> > &masterLog){
    bool changed = false;
    if(result1.size() != result2.size()){
        changed = true;
    }
    cout << "Lines Deleted: \n"; 
    for(int i = 0; i < result1.size(); i++){
        if(!findLine(result2, result1[i])){
            changed = true;
            cout << "\tLine " << i + 1 << " /* " << result1[i] << " *\n";
        }
    }

    cout << "Lines Added: \n"; 
    for(int i = 0; i < result2.size(); i++){
        if(!findLine(result1, result2[i])){
            changed = true;
            cout << "\tLine " << i + 1 << " /* " << result2[i] << " *\n";
        }
    }
    if(changed){
        masterLog.push_back(result2);
    }
}

int main(){
    string filename;
    cin >> filename;
    vector<vector<string> > masterLog;
    vector<string> oldResult;
    if(!readFile(filename, oldResult)){
        perror("Read File Error");
        return 1;
    }
    masterLog.push_back(oldResult);
    char track;
    do{
        cout << "Do you want to track the file: " << filename << " (y/n)? ";
        cin >> track;
        vector<string> newResult;
        readFile(filename, newResult);
        compareChanges(oldResult, newResult, masterLog);
        oldResult = newResult;
    }while(track == 'y' || track == 'Y');

    return 0;
}
