#include<iostream>
using namespace std;
#include<vector>
#include<algorithm> // for sort

// This code demonstrates the use of the STL vector and its functionalities
// like insertion, deletion, accessing elements, and sorting.
int main(){
    vector<int> ds = {11,2,4};
    sort(ds.begin(), ds.end());
    for(auto i: ds){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}