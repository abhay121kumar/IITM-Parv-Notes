#include<iostream>
using namespace std;
#include<mutex>
#include<thread>
#include<memory>

// class PrinterManager{
//     private:
//     static PrinterManager* instance;
//     static mutex mtx;
//     PrinterManager(){}
//     public:
//     static PrinterManager* getInstance(){
//         lock_guard<mutex> lock(mtx);
//         if(!instance){
//             instance =  new PrinterManager();
//         }
//         return instance;
//     }
//     void printDocument(const string& file){
//         cout<<file<<endl;
//     }
// };

// PrinterManager* PrinterManager::instance=nullptr;
// mutex PrinterManager::mtx;

// void employeeTask(const string file){
//     PrinterManager* manager = PrinterManager::getInstance();
//     manager->printDocument(file);
// }

// int main(){
//     thread t1(employeeTask,"file1");
//     thread t2(employeeTask,"file2");
//     t1.join();
//     t2.join();
//     return 0;
// }

// class PrinterManager{
//     private:
//     static PrinterManager* instance;
//     public:
//     static PrinterManager* getInstance(){
//         if(!instance){
//             instance = new PrinterManager();
//         }
//         return instance;
//     }
//     void show(const string file){
//         cout<<file<<endl;
//     }
// };
// PrinterManager* PrinterManager::instance=nullptr;

// int main(){
//     PrinterManager* user1 = PrinterManager::getInstance();
//     PrinterManager* user2 = PrinterManager::getInstance();
//     user1->show("file");
//     user2->show("file2");
//     return 0;
// }



// class Vehicle{
//     public:
//     virtual void startEngine()=0;
//     ~Vehicle();
// };

// class bike: public Vehicle{
//     public:
//     void startEngine() override{
//         cout<<"start engine of bike class"<<endl;
//     }
// };

// class car: public Vehicle{
//     public:
//     void startEngine() override{
//         cout<<"start engine of car class"<<endl;
//     }
// };

// class VehicalFectory{
//     public:
//     static Vehicle* createVehicle(const string type){
//         if(type=="car"){
//             return new car();
//         }else if(type == "bike"){
//             return new bike();
//         }else{
//             return nullptr;
//         }
//     }
// };

// int main(){
//     Vehicle* v1 = VehicalFectory::createVehicle("bike");
//     Vehicle* v2 = VehicalFectory::createVehicle("car");
//     v1->startEngine();
//     v2->startEngine();
// }


// class deep{
//     private:
//     int size;
//     unique_ptr<int[]> arr;
//     public:
//     deep(int size):size(size),arr(make_unique<int[]>(size)){
//         for(int i=0;i<size;i++){
//             arr[i] = i;
//         }
//     }
//     deep(deep& other):size(other.size),arr(make_unique<int[]>(other.size)){
//         for(int i=0;i<size;i++){
//             arr[i] = other.arr[i];
//         }
//     }
//     void show(){
//         for(int i=0;i<size;i++){
//             cout<<arr[i]<<" ";
//         }
//         cout<<endl;
//     }
// };

// int main(){
//     deep d1(5);
//     deep d2 = d1;
//     d1.show();
//     d2.show();
//     return 0;
// }


// class wallet{
//     private:
//     int rupee;
//     public:
//     wallet(int rupee):rupee(rupee){};
//     wallet operator+(const wallet& other){
//         return other.rupee+rupee;
//     }
//     void show(){
//         cout<<rupee<<endl;
//     }
// };

// int main(){
//     wallet w1(10);
//     wallet w2(20);
//     wallet w3 = w1 + w2;
//     w1.show();
//     w3.show();
//     return 0;
// }


// class account{
//     private:
//     int amount;
//     public:
//     account(int amount):amount(amount){}
//     friend class transaction;
//     void show(){
//         cout<<amount<<endl;
//     }
// };
// class transaction{
//     public:
//     void withdraw(account& other,int rupee){
//         if(other.amount>rupee){
//             other.amount-=rupee;
//         }else{
//             cout<<"insuff"<<endl;
//         }
//     }
// };

// int main(){
//     account a1(100);
//     a1.show();
//     transaction t1;
//     t1.withdraw(a1,50);
//     a1.show();
// }


class a{
    public:
    void show(){
        cout<<"a"<<endl;
    }
};

class b:virtual public a{
    public:
};
class c:virtual public a{
    
};
class d:public b,public c{
    
};

int main(){
    d obj;
    obj.show();
}




