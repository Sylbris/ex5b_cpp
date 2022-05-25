#include "OrgChart.hpp"
#include <queue>
#include <stack>
using namespace ariel;

namespace ariel{

    /**
     * @brief Add the root node to our organization.
     * 
     * @param root 
     */
    OrgChart& OrgChart::add_root(const std::string& root){
        if(_root_node != nullptr){
            _root_node->_value = root;
        }
        else {
            _root_node = new Node(root);
        }
        return *this;
    }
    /**
     * @brief add a sub node to a node.
     * if we have 2 tree nodes with the same name,
     * it will locate the one closer to the root node,
     * since we are searching using bfs.
     * 
     * @param father 
     * @param son 
     */
    OrgChart& OrgChart::add_sub(const std::string& father, const std::string& son){
        Node* searched_node = search(father, _root_node);
        //cout << father << " \n";
        //cout << searched_node->_value << " \n" ;
        //If we found the node.
        if(searched_node != nullptr){
            searched_node->_children.push_back(new Node(son));
        }
        else {
            throw invalid_argument("couldn't find the node");
        }
        return *this;
    }
    /**
     * @brief breathd first search.
     * 
     * @param node_string 
     * @param node 
     * @return Node* 
     */

    Node* OrgChart::search(const std::string& node_string, Node* node){
        if(node == nullptr){
            return nullptr;
        }
        //check root node.
        if(node->_value == node_string){
            return node;
        }
        

        queue<Node*> q;
        q.push(node);

        while(!q.empty()){
            Node* curr = q.front();
            q.pop();
            //cout << "value is: " << curr->_value << " \n";
            for(auto *n: curr->_children){
                //cout << "child is: " << n->_value << " \n";
                if(n->_value == node_string){
                    return n;
                }
                q.push(n);
            }
        }
        return nullptr;
    }
    /**
     * @brief Free the momeory of the tree.
     * 
     * @param root 
     */
    void OrgChart::freeTree(Node* root){
        if(root == nullptr){
            return;
        }
        // Standard level order traversal code
        // using queue
        queue<Node *> q;  // Create a queue
        q.push(root); // Enqueue root
        while (!q.empty())
        {
            int n = q.size();
    
            // If this node has children
            while (n > 0)
            {
                // Dequeue an item from queue and print it
                Node * p = q.front();
                q.pop();
    
                // Enqueue all children of the dequeued item
                for (int i=0; i<p->_children.size() ; i++){
                    q.push(p->_children[(size_t)i]);
                } 
                delete p;
                n--;
            }
        }
    }
/**
 * @brief 
 * 
 * @param out 
 * @param orgchart 
 * @return std::ostream& 
 */
    std::ostream& operator<<(ostream& out, const OrgChart& org_chart){
        queue<Node*> q;
        q.push(org_chart._root_node);
        string ans = q.front()->_value;
        while(!q.empty()){
            Node* curr = q.front();
            q.pop();
            //ans += curr->_value + "\n|\n";
            //cout << "value is: " << curr->_value << " \n";
            for(auto *n: curr->_children){
                ans += "\n|--------" + n->_value;
                q.push(n);
            }
        }
        out << ans;
        return out;
    }
    ////////////////////////////////////////Iterator stuff /////////////////////////////////////////////////////
    void OrgChart::Iterator::fill_level_order(Node* root){
        _ordered.clear();
        if(root == nullptr){
            return;
        }
        // Standard level order traversal code
        // using queue
        queue<Node *> q;  // Create a queue
        q.push(root); // Enqueue root
        while (!q.empty())
        {
            int n = q.size();
    
            // If this node has children
            while (n > 0)
            {
                // Dequeue an item from queue and print it
                Node * p = q.front();
                q.pop();
                _ordered.push_back(p);
                //std::cout << p->_value << " ";
                
    
                // Enqueue all children of the dequeued item
                for (int i=0; i<p->_children.size() ; i++){
                    q.push(p->_children[(size_t)i]);
                }
                n--;
            }
        }
    
           //cout << endl; // Print new line between two levels
    }
    /**
     * @brief reverse order.
     * 
     * @param root 
     */
    void OrgChart::Iterator::fill_reverse_order(Node* root){
        _ordered.clear();
        vector<vector <Node *>> _depth;
        vector <Node *> init = {root};
        _depth.push_back(init);

       if(root == nullptr){
            return;
        }
        // Standard level order traversal code
        // using queue
        queue<Node *> q;  // Create a queue
        q.push(root); // Enqueue root
        int cnt = q.size();
        vector<Node *> children;
        while (!q.empty())
        {
                
                Node * p = q.front();
                q.pop();
                cnt --;
                // Enqueue all children of the dequeued item
                for (int i=0; i < p->_children.size() ; i++){
                    q.push(p->_children[(size_t)i]);
                    children.push_back(p->_children[(size_t)i]);
                }
                // We finish all children at this depth.
                if(cnt == 0){
                    _depth.push_back(children);
                    cnt= q.size();
                    children.clear();
                }
                
        }

        for(int i= (int)_depth.size() -1; i >= 0; i--){
            vector<Node *> child = _depth[(size_t)i];
            for(auto *c: child){
                _ordered.push_back(c);
            }
            
        }
    }
    /**
     * @brief dfs recursive.
     * 
     * @param root 
     */
    void OrgChart::Iterator::fill_preorder(Node* root){
        if(root == nullptr){
            return;
        }
        _ordered.push_back(root);

        for(auto *n: root->_children){
            fill_preorder(n);
        }

    }
    
}

