#include <iostream>
using namespace std;

int add(int a, int b){
    return a + b;
}
double add(double a, double b){
    return a + b;
}

int main(){
    cout << "Int addition: " << add(5, 3) << endl;
    cout << "Double addition: " << add(5.5, 3.3) << endl;
}