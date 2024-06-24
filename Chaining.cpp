#include "Chaining.h"
#include <cmath>
#include <vector>
using namespace std;

Chaining::Chaining(){
        size=0;
        for(int i=0;i<100000;i++){
            vector<Account> v;
            bankStorage2d.push_back(v);
        }
    }




void merge(vector<int>& vec, int left, int mid, int right) {
   
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> Left(n1);
    vector<int> Right(n2);

    for (int i = 0; i < n1; i++){
        
        Left[i] = vec[left + i];
    }

    for (int j = 0; j < n2; j++){
    
        Right[j] = vec[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        
        if(Left[i] <= Right[j]){
            vec[k] = Left[i];
            i++;
        } 
        else{
            vec[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        
        vec[k] = Left[i];
        i++;
        k++;
    }


    while(j < n2){
        
        vec[k] = Right[j];
        j++;
        k++;
    }
}


void mergesort(vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(vec, left, mid);
        mergesort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}


void Chaining::createAccount(std::string id, int count) {
    
    Account a;
    a.id=id;
    a.balance=count;
    bankStorage2d[hash(id)].push_back(a);
    size++;

}

std::vector<int> Chaining::getTopK(int k) {
    
    vector<int> Balance;
    vector<int> sortbalance;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            Balance.push_back(bankStorage2d[i][j].balance);
        }
    }
    mergesort(Balance,0,Balance.size()-1);
    int y=0;
    for(int z=Balance.size()-1;z>=0;z--){
        if(y<k){
            sortbalance.push_back(Balance[z]);
            y++;
        }
    }
    return sortbalance;
}

int Chaining::getBalance(std::string id) {
    
    if(doesExist(id)){
        for(int k=0;k<bankStorage2d[hash(id)].size();k++){
           if(bankStorage2d[hash(id)][k].id==id) {
            return bankStorage2d[hash(id)][k].balance;
           }
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    
    if(doesExist(id)){
       for(int k=0;k<bankStorage2d[hash(id)].size();k++){
           if(bankStorage2d[hash(id)][k].id==id) {
               bankStorage2d[hash(id)][k].balance = bankStorage2d[hash(id)][k].balance + count;
               break; 
           }
        } 
    }
    else{
        createAccount(id,count);    
    }
}

bool Chaining::doesExist(std::string id) {
    
    for(int i=0;i<bankStorage2d[hash(id)].size();i++){
        if(bankStorage2d[hash(id)][i].id==id){
            return true;
        }
    }
    return false;

}

bool Chaining::deleteAccount(std::string id) {
    
     if(doesExist(id)){
       for(int j=0;j<bankStorage2d[hash(id)].size();j++){
        if(bankStorage2d[hash(id)][j].id==id){
            bankStorage2d[hash(id)].erase(bankStorage2d[hash(id)].begin()+j);
            size--;
            return true;
        }
        } 
     }
     return false;
}
int Chaining::databaseSize() {
    
    return size;
}

int Chaining::hash(std::string id) {
    
    int val=0;

    for(int i=0;i<id.size();i++){
        val=(val + int(pow(29,i))*(int(id[i])-'0'+1))%100000;
    }

    return val;
}



