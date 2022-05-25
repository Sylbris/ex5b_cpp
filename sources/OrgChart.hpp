#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

namespace ariel{
    /**
     * @brief 
     * 
     */
    enum Iteration_type {
        LEVEL_ORDER,
        REVERSE_LEVEL_ORDER,
        PREORDER
    };
    /**
     * @brief Our node struct.
     * contains a pointer to all its children.
     * 
     */
    struct Node {

        std::string _value;
        vector<Node*> _children;

        /**
         * @brief Construct a new Node 
         * 
         * @param _val 
         */
        Node(std::string val) :_value(val) {
        }

    };

    class OrgChart {
    /**
     * @brief Our iterator class.
     * We will fill a vector 
     * 
     */
    class Iterator {

        std::vector<Node*> _ordered;
        unsigned long _current;
        void fill_level_order(Node* root);
        void fill_reverse_order(Node* root);
        void fill_preorder(Node* root);

        public:
        
            Iterator(Iteration_type it, Node* start): _current(0) {
                switch(it){
                    case LEVEL_ORDER:
                        _ordered.clear();
                        fill_level_order(start);
                    break;

                    case REVERSE_LEVEL_ORDER:
                        _ordered.clear();
                        fill_reverse_order(start);
                    break;

                    case PREORDER:
                        _ordered.clear();
                        fill_preorder(start);
                    break;
                }
                _ordered.push_back(nullptr);
            }
            /////////////////////////OVERLOADS OPERATORS ///////////////////////////////////////////////////
            //pre increment ++x
            Iterator& operator ++(){
                _current++;
                return *this;
            }
            //post increment x++
            Iterator operator ++(int){
                Iterator it = *this;
                _current++;
                return it;
            }
            //Overload *
            std::string& operator*() const { 
                return _ordered.at(_current)->_value; 
            }
            //return place in memory.
            std::string* operator->() const { 
                return &_ordered.at(_current)->_value;
            }
            //Overload == & !=
            bool operator ==(const Iterator& it) const{
                return _ordered.at(_current) == it._ordered.at(it._current);
            }
            bool operator !=(const Iterator& it) const{
                return _ordered.at(_current) != it._ordered.at(it._current);
            }
        };

        Node* _root_node;
        int _depth = 0;
        vector<int> _children_at_level;

        public:
            //init.
            OrgChart(){
                _root_node = nullptr;
            }
            ~OrgChart(){
                freeTree(_root_node);
            }
            OrgChart& add_root(const std::string& root);
            OrgChart& add_sub(const std::string& father, const std::string& son);
            static Node* search(const std::string& node_string, Node* node);
            static void freeTree(Node* root);

            //Iterators.
            auto begin_level_order(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(LEVEL_ORDER, _root_node);
            }
            auto end_level_order(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(LEVEL_ORDER, nullptr);
            }
            auto begin_reverse_order(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(REVERSE_LEVEL_ORDER, _root_node);
            }
            auto reverse_order(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(REVERSE_LEVEL_ORDER, nullptr);
            }
            auto begin_preorder(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(PREORDER, _root_node);
            }
            auto end_preorder(){
                if(_root_node == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return Iterator(PREORDER, nullptr);
            }
            //Default iterator.
            auto begin(){return begin_level_order();};
            auto end(){return end_level_order();}

            friend std::ostream& operator<<(ostream& out, const OrgChart& org_chart);
    };

}