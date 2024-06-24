#include "LinearProbing.h"
#include <cmath>
using namespace std;

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

LinearProbing::LinearProbing(){
        int size=0;
        Account ac = {"{}[]()shivang", -1};
        std::vector<Account> x(100000, ac);
        bankStorage1d = x;
    }

void LinearProbing::createAccount(std::string id, int count) {
    Account a;
    a.id=id;
    a.balance=count;
    int i=hash(id);
    while(bankStorage1d[i].balance!=-1){
        i=(i+1)%100000;
    }
    bankStorage1d[i].id=id;
    bankStorage1d[i].balance=count;
    size++;
}

std::vector<int> LinearProbing::getTopK(int k) {
    vector<int>Balance;
    vector<int>sortbalance;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].balance==-1){
            continue;
        }
        else{
            Balance.push_back(bankStorage1d[i].balance);
        }
    }
    mergesort(Balance,0,Balance.size()-1);
    for(int z=Balance.size()-1;z>=0;z--){
        if(sortbalance.size()<k){
            sortbalance.push_back(Balance[z]);
        }
        else{
            break;
        }
    }
    return sortbalance;
}

int LinearProbing::getBalance(std::string id) {
    if(doesExist(id)){
        int ind=hash(id);
        for(int j=0;j<bankStorage1d.size();j++){
            if(bankStorage1d[(j+ind)%100000].id==id && bankStorage1d[(j+ind)%100000].balance!=-1){
                return bankStorage1d[(j+ind)%100000].balance;
            }
        }
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    if(doesExist(id)){
        int ind=hash(id);
        for(int j=0;j<bankStorage1d.size();j++){
            if(bankStorage1d[(j+ind)%100000].id==id && bankStorage1d[(j+ind)%100000].balance!=-1){
                bankStorage1d[(j+ind)%100000].balance=bankStorage1d[(j+ind)%100000].balance+count;
            }
        }
    }
    else{
        createAccount(id,count);
    }
}

bool LinearProbing::doesExist(std::string id) {
    int ind=hash(id);
    for(int j=0;j<bankStorage1d.size();j++){
        if(bankStorage1d[(j+ind)%100000].id==id && bankStorage1d[(j+ind)%100000].balance!=-1){
            return true;
        }
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int ind=hash(id);
    for(int j=0;j<bankStorage1d.size();j++){
        if(bankStorage1d[(j+ind)%100000].id==id){
            bankStorage1d[(j+ind)%100000].balance=-1;
            size--;
            return true;
        }
    }
    return false;
}
int LinearProbing::databaseSize() {
    return size;
}

int LinearProbing::hash(std::string id) {
    int val=0;

    for(int i=0;i<id.size();i++){
        val=(val + int(pow(29,i))*(int(id[i])-'0'+1))%100000;
    }

    return val;
}

