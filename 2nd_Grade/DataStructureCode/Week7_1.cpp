#include <iostream>
#include <vector>
using namespace std;
// [1] 압축 함수
vector<int> compress1D(const vector<int>& data) {
    vector<int> result;
    int index = 1;
    int cnt = 1;

    for (index; index < data.size(); index++)
    {
        if(data[index] == data[index-1])
        {
            cnt++;
        }
        else{
            result.push_back(cnt);
            result.push_back(data[index - 1]);
            cnt = 1;
        }
        
    }

    result.push_back(cnt);
    result.push_back(data[index - 1]);

    return result;
}

// [2] 복원 함수
vector<int> decompress1D(const vector<int>& compressed) {
    vector<int> result;
    for (int i = 0; i < compressed.size(); i += 2){
        int count = compressed[i];
        int num = compressed[i + 1];
        for (int j = 0; j < count; j++){
            result.push_back(num);
        }
    }

    return result;
}

// [3] 출력 함수
void printVector(const vector<int>& v, const string& title) {
    cout << "[" << title << "]" << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "배열 크기 입력: ";
    cin >> n;

    vector<int> data(n);
    cout << "배열 원소 입력 (0과 1로 구성): ";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    // [원본 출력]
    printVector(data, "원본 배열");

    // [압축]
    vector<int> compressed = compress1D(data);
    printVector(compressed, "압축 결과 ([횟수, 값] 순)");

    // [복원]
    vector<int> decompressed = decompress1D(compressed);
    printVector(decompressed, "복원 결과");

    return 0;
}
