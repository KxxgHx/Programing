#include <string>
#include "Graph.hpp" 

using namespace std;

int main() {
    Graph<string> g = Graph<string>();

    cout << "그래프 초기 세팅: " << endl;
    g.add_node("민수");
    g.add_node("지향");
    g.add_node("문정");

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);

    g.print_adj();
    cout << "현재 그래프 크기: " << g.get_size() << endl;

    cout << "\n새로운 노드 추가: '지현'" << endl;
    g.add_node("지현");
    g.print_adj();
    cout << "현재 그래프 크기: " << g.get_size() << endl;

    cout << "\n새로운 엣지 추가: (2, 0), (3, 2)" << endl;
    g.add_edge(2, 0);
    g.add_edge(3, 2);
    g.print_adj();

    cout << "\n노드 '문정'의 진출 차수: " << g.out_degree(2) << endl;
    cout << "노드 '문정'의 진입 차수: " << g.in_degree(2) << endl;
    cout << "노드 '문정'의 전체 차수: " << g.degree(2) << endl;

    cout << "\n노드 '지향' 제거: " << endl;
    g.remove_node("지향");
    g.print_adj();
    cout << "현재 그래프 크기: " << g.get_size() << endl;

    return 0;
}