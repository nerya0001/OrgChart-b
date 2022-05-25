#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <vector>
#include <iostream>


namespace ariel {
    class Node
    {
        
    public:
        std::string _title;
        std::vector<Node *> _subordinates;
        int payLevel;

    
        
        Node(const std::string &title, int level) : _title(title), payLevel(level){}
        Node(Node &other) = default;
        Node(Node &&other) = default;
        Node& operator=(Node &&other) = default;
        Node& operator=(const Node &other) = default;
        ~Node(){}
        // std::string getTitle();
        // int getPayLevel();

        
        // std::vector<Node *> getSubor();
       
        // void setTitle(std::string &title);
       
        // friend std::ostream& operator<<(std::ostream& output, Node* const &node);
    };
}

#endif 