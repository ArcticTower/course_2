#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>





int main(int argc, char *argv[]){
    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
            boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;

    typedef boost::graph_traits <Graph>::edge_descriptor Edge;
    typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
    typedef std::pair<int, int> P;
    int num_nodes;
    int v;
    Graph g;
    menu:
    std::cout<<"Введите неориентированный граф:\n"<<std::endl;
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




    boost::property_map<Graph, boost::edge_weight_t >::type weight = get(boost::edge_weight, g);
    std::vector < Edge > spanning_tree;

    ch:
    std::cout<<"Выберите алгоритм нахождения остовного дерева:\n1 - алгоритм Крускала\n2 - алгоритм Прима\n"<<std::endl;
    int ch;
    std::cin>>ch;
    if(ch==1){
        boost::kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

        std::cout << "Рёбра остовного дерева:" << std::endl;
        long w_s =0;
        for (std::vector <Edge>::iterator ei = spanning_tree.begin();
             ei != spanning_tree.end(); ++ei){
            std::cout << source(*ei, g)+1
                      << " - "
                      << target(*ei, g)+1
                      << " с тяжестью "
                      << weight[*ei]
                      << std::endl;
            w_s += weight[*ei];
        }
        std::cout<<"Общая тяжесть:"<<w_s<<std::endl;
    }else if(ch == 2){
        int w_s =0;
        std::vector<Vertex> p(boost::num_vertices(g));
        boost::prim_minimum_spanning_tree(g,&p[0]);

        for(int i=0;i < boost::num_vertices(g);++i){
            if (p[i] != i)
                std::cout<<i+1
                <<" - "
                <<p[i]+1
                <<std::endl;
           // w_s += get(weight, boost::edge(p[i],i,g).first);
        }
        //std::cout<<"Общая тяжесть:"<<w_s<<std::endl;

        }else{goto ch;}
    int ch2;
    ch2:
    std::cout<<"\n1 - выйти\n2 - выбрать алгоритм\n3 - ввести граф"<<std::endl;
    std::cin>>ch2;
    switch (ch2) {
        case 1:
            exit(0);
        case 2:
            goto ch;
        case 3:
            g.clear();
            goto menu;
        default:
            goto ch2;

    }


    return 0;
    }
