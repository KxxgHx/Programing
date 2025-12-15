#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Graph {
private:
    int size; // 전체 노드의 개수
    vector<T> data; // 각 노드의 데이터
    vector<vector<bool>> adj_matrix; // 인접 행렬

public:
    Graph(){
        size = 0;
        data = vector<T>();
        adj_matrix = vector<vector<bool>>();
    }

    // value 값을 가지는 노드 추가
    void add_node(const T& value) {
        size++;
        data.push_back(value);
        adj_matrix.push_back(vector<bool>(size - 1, false));
        for (int i = 0; i < adj_matrix.size(); i++)
            adj_matrix[i].push_back(false);
    }

    // value 값을 가지는 노드 제거
    void remove_node(const T& value) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                index = i;
                break;
            }
        }
        if (index == -1) return;

        data.erase(data.begin() + index);
        for (int i = 0; i < size; i++)
            adj_matrix[i].erase(adj_matrix[i].begin() + index);
        adj_matrix.erase(adj_matrix.begin() + index);
        size--;
    }

    // source에서 target으로 향하는 엣지 추가
    void add_edge(size_t source, size_t target) {
        if (source < size && target < size)
            adj_matrix[source][target] = true;
    }

    // source에서 target으로 향하는 엣지 제거
    void remove_edge(size_t source, size_t target) {
        if (source < size && target < size)
            adj_matrix[source][target] = false;
    }

    // source에서 target으로 향하는 엣지 존재 여부
    bool is_edge(size_t source, size_t target) {
        return adj_matrix[source][target];
    }

    int get_size() {
        return size;
    }

    T get_value(size_t index) {
        return data[index];
    }

    // 진입 차수
    int in_degree(size_t index) {
        int id = 0;
        for (int i = 0; i < size; i++)
            id += adj_matrix[i][index];
        return id;
    }

    // 진출 차수
    int out_degree(size_t index) {
        int od = 0;
        for (int i = 0; i < size; i++)
            od += adj_matrix[index][i];
        return od;
    }

    // 전체 차수
    int degree(size_t index) {
        return in_degree(index) + out_degree(index);
    }

    // 인접 행렬 출력
    void print_adj() {
        cout << "\n\t";
        for (int i = 0; i < size; i++)
            cout << data[i] << "\t";
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << data[i] << "\t";
            for (int j = 0; j < size; j++) {
                cout << adj_matrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
};