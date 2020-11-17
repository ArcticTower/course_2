#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <sys/time.h>
#include <unistd.h>
#include <boost/graph/dijkstra_shortest_paths.hpp>






int main(int argc, char *argv[]){

    struct timeval start_time, end_time;
    struct timeval t_reandomseed;
    long milli_time, seconds, useconds;
    int time;

    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
            boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;

    typedef boost::graph_traits <Graph>::edge_descriptor Edge;
    typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
    typedef std::pair<int, int> P;
    int num_nodes;
    int v;
    Graph g;
    menu:
    std::cout<<"Введите неориентированный граф:"<<std::endl;
    std::cout<<"Введите количество вершин: "<<std::endl;
    std::cin>>num_nodes;

    std::cout<<"\nВведите количество рёбер: "<<std::endl;
    std::cin>>v;

    std::cout<<"\nВведите рёбра в формате \"вершина_1 вершина_2 тяжесть_ребра\" (минимальный номер вершины - 1):\n"<<std::endl;
    int a, b, w;
    for (int i =0; i<v;i++){
        std::cin>>a>>b>>w;
        boost::add_edge(a-1,b-1,w,g);
    }
    int A =0, F =0;
    std::cout<<"\nУкажите номер первой вершины:\n"<<std::endl;
    std::cin>>A;
    A-=1;
    std::cout<<"\nУкажите номер последней вершины:\n"<<std::endl;
    std::cin>>F;
    F-=1;
    int ch3 =0;
    std::cout << "\nВыберите алгоритм:\n1 - алгоритм Дейкстры " << std::endl;
    std::cin>>ch3;
    switch (ch3) {
        case 1: goto dij;

        default: goto menu;
    }

    dij:
    //Deikstr
    std::vector<Vertex> p(boost::num_vertices(g));
    std::vector<int> d(boost::num_vertices(g));

    Vertex start = vertex(A, g);
    Vertex goal = vertex(F, g);
    gettimeofday(&start_time,NULL);
    boost::dijkstra_shortest_paths(g, start, boost::predecessor_map(&p[0]).distance_map(&d[0]));
    gettimeofday(&end_time,NULL);

    seconds = end_time.tv_sec - start_time.tv_sec;
    useconds = end_time.tv_usec - start_time.tv_usec;
    milli_time = (long)((long double) (((long double)seconds) * 1000) + (long double)((long double)useconds/1000.0));

    std::vector<boost::graph_traits<Graph>::vertex_descriptor > path;
    boost::graph_traits<Graph>::vertex_descriptor current = goal;

    while(current!=start)
    {
        path.push_back(current);
        current = p[current];
    }
    path.push_back(start);


    std::cout << "Путь от " << start << " до " << goal << ":"<<std::endl;
    std::vector<boost::graph_traits<Graph>::vertex_descriptor >::reverse_iterator it;

    for (it = path.rbegin(); it != path.rend(); it++) {
        std::cout << *it+1 << " ";
    }
    std::cout <<"\nВремя потрачено: " << milli_time << std::endl;

    return 0;
}
