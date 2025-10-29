#include <iostream>
#include <cstring>
using namespace std;

class BufferManager{
private:
    char *buffer;
    size_t size;

public:
    //constructor
    BufferManager(size_t bufferSize):size(bufferSize){
        buffer = new char[size];
        cout << "Buffer allocated with size: " << size << endl;
    }

    //소멸자
    ~BufferManager(){
        delete[] buffer;
        cout << "Buffer deallocated" << endl;
    }

    void writeData(const char *data){
        if(strlen(data)<size){
            strcpy(buffer, data);
        }
        else{
            cerr << "Data exceeds buffer size" << endl;
        }
        
    }
    void readData() const{
        cout << "Buffer content: " << buffer << endl;
    }
};

int main(){
    BufferManager bufManager(50);
    bufManager.writeData("Hello, Dynamic Buffer");
    bufManager.readData();
    return 0;
}