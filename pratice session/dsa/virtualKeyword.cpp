
#include <iostream>
using namespace std;
#include<memory>
// class a{
//     public:
//     void show(){
//         cout<<"a"<<endl;
//     }
// };
// class b:virtual public a{};
// class c:virtual public a{};
// class d:public b,public c{};
// int main()
// {
//     d obj;
//     obj.show();

//     return 0;
// }

// class animal{
//     public:
//     virtual void sound()=0;
// };

// class dog:public animal{
//     public:
//     void sound() override{
//         cout<<"dog bark"<<endl;
//     }  
// };

// class lion:public animal{
//     public:
//     void sound(){
//         cout<<"lion roar"<<endl;
//     }
// };

// int main(){
//     // animal a1;// so we can not create the object of pure virtual function
//     // a1.sound();
//     dog d1;
//     d1.sound();
//     lion l1;
//     l1.sound();
//     return 0;
// }




// class animal{
//     public:
//     // virtual void sound(){
//     //     cout<<"animal sound"<<endl;
//     // }
//     virtual void sound();
// };

// class dog:public animal{
//     public:
//     void sound() override{
//         cout<<"dog bark"<<endl;
//     }  
// };

// class lion:public animal{
//     public:
//     void sound(){
//         cout<<"lion roar"<<endl;
//     }
// };

// int main(){
//     animal a1;
//     a1.sound();
//     dog d1;
//     d1.sound();
//     lion l1;
//     l1.sound();
//     return 0;
// }



// class animal {
// public:
//     virtual void sound() = 0;   // pure virtual
// };

// void animal::sound() {          // definition provided
//     cout << "animal default sound" << endl;
// }

// class lion : public animal {
// public:
//     void sound() override {
//         animal::sound();   // call base’s version
//         cout << "lion roar" << endl;
//     }
// };

// class cat : public animal {
// public:
//     // I don't override sound()
// };

// class tiger : public animal {
// public:
//     void sound() override {
//         cout << "tiger growl" << endl;
//     }
// };

// int main(){
//     animal a1;
//     a1.sound();
//     dog d1;
//     d1.sound();
//     lion l1;
//     l1.sound();
//     return 0;
// }






class animal {
public:
    void sound() { cout << "animal sound\n"; }
};

class tiger : public animal {
public:
    void sound() { cout << "tiger growl\n"; }
};

int main() {
    animal* a = new tiger();
    a->sound();
}





































































