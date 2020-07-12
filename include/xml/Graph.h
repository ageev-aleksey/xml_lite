#ifndef XML_DEMON_GRAPH_H
#define XML_DEMON_GRAPH_H

#include <list>
#include <iterator>
#include <type_traits>


/**
 * @brief класс описывающий граф
 * @tparam T - тип данных хранящийся в узлах графа
 */
template<typename T>
class Graph {
public:
    class Iterator;

private:
    struct Node {
        Node(const T &data, int index) : data(data), index(index) {}
        Node(const Node &other) : data(other.data), link(), index(other.index) {}
        T data;
        std::list<Iterator> link;
        int index;
    };
public:
    /**
     * @brief итератор по узлам графа
     */
    class Iterator {
    public:
        using difference_type = size_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;
        Iterator() = default;
        Iterator(const Iterator &itr) : mNodeIterator(itr.mNodeIterator) {}
        Iterator& operator=(const Iterator &other) {
            mNodeIterator = other.mNodeIterator;
            return *this;
        }
        Iterator& operator++() {
            ++mNodeIterator;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp(*this);
            ++mNodeIterator;
            return tmp;
        }
        Iterator& operator--() {
            --mNodeIterator;
            return *this;
        }
        Iterator& operator--(int) {
            Iterator tmp(*this);
            --mNodeIterator;
            return tmp;
        }
        reference operator*() const {
            return mNodeIterator->data;
        }
        pointer operator->() const {
            return &(mNodeIterator->data);
        }
        bool operator==(const Iterator &other) const {
            return mNodeIterator == other.mNodeIterator;
        }
        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }
        std::list<Iterator> getChildren() {
            return mNodeIterator->link;
        }

        friend class Graph;
    private:
        explicit Iterator(typename std::list<Node>::iterator node) : mNodeIterator(node)
        {}
        typename std::list<Graph::Node>::iterator mNodeIterator;
    };

    Graph() = default;
    Graph(const Graph &g) {
        mNodes = g.mNodes;
        for(auto gIter = g.mNodes.begin(), iter = mNodes.begin();
            gIter != g.mNodes.end(); ++gIter, ++iter) {
            for(const auto &gLink : gIter->link) {
                auto el = get(gLink.mNodeIterator->index);
                iter->link.push_back(Iterator(el));
            }
        }
    }
    /**
     * @brief создание нового узла.
     * @param data - данные, нового узла
     * @return итератор на созданный узел.
     */
    Iterator addNode(const T &data) {
        int index = 0;
        if(!mNodes.empty()) {
            index = mNodes.back().index + 1;
        }
        mNodes.push_back({data, index});
        return Iterator(--mNodes.end());
    }
    /**
     * @brief добавление связи между двумя узлами
     * @param begin - итератор узела, в котором начинается связь.
     * @param end  - итератор узла, в котором заканчивается связь.
     */
    void addLink(const Iterator &begin, const Iterator &end) {
        begin.mNodeIterator->link.push_back(end);
    }
    /**
     * @brief Получить итератор на узле, который был первым добавлен в граф.
     * @return итератор первого узла.
     */
    Iterator begin() {
        return Iterator(mNodes.begin());
    }
    /**
     * Итератор указывающий за последний узел графа.
     */
    Iterator end() {
        return Iterator(mNodes.end());
    }
    /**
     * @brief Получить итератор на узел графа по его индексу. Елси такого узла нет, то тогда возращает \see end.
     * @param index - индекс узла.
     * @return итератор узла.
     */
    Iterator get(size_t index) {
        auto itr = mNodes.begin();
        int i = 0;
        while(itr != mNodes.end() && i != index) {
            ++i;
            ++itr;
        }
        if(i == index) {
            return Iterator(itr);
        }
        return Iterator(mNodes.end());
    }
private:
    std::list<Node> mNodes;
};



#endif //XML_DEMON_GRAPH_H
