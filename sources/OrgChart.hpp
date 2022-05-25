// got help from a couple of studets, in particular - Eitan shenkolevski, dvir biton, ori howard
// in addition got help from www.stackoveflow.com and www.geeksforgeeks.com
#ifndef _ORGCHART_HPP_
#define _ORGCHART_HPP_

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include <stack>
#include <map>
#include <queue>
#include <list>
#include "Node.hpp"

namespace ariel
{
    enum class Iter_type {
        levelOrder,
        preOrder,
        reverseOrder
    };

    class OrgChart
    {

    private:
        ariel::Node *_root; 
        int _numOfEmp = 0;
      

    public:
        OrgChart() : _root(nullptr), _numOfEmp(0) {}
        OrgChart(OrgChart &other) = default;
        OrgChart(OrgChart &&other) = default;
        OrgChart& operator=(OrgChart &&other) = default;
        OrgChart& operator=(const OrgChart &other) = default;
        ~OrgChart();
        

        OrgChart add_root(const std::string &name);
        OrgChart add_sub(const std::string &boss, const std::string &sub);
        void addSubordinate(ariel::Node *root, const std::string &boss, const std::string &sub); 

        friend std::ostream &operator<<(std::ostream &output, const OrgChart &chart);

        /**
         * @brief the iterator class
         * 
         */
        class Iterator
        {

        private:
            ariel::Node* cur;
            std::list<ariel::Node *> nodes;

        public:
            // constructor
            Iterator(Iter_type type, Node *node=nullptr);

            // type of traversals
            void levelOrder(Node *node=nullptr);
            void reverseLevelOrder(Node *node=nullptr);
            void preOrder(Node *node=nullptr);

            // operators overide
            std::string &operator*() const {return this->cur->_title;}
            std::string *operator->() const {return &this->cur->_title;}
            ariel::OrgChart::Iterator &operator++();
            ariel::OrgChart::Iterator operator++(int) {OrgChart::Iterator iter = *this; return iter;}
            bool operator==(const OrgChart::Iterator &other) const {return this->cur == other.cur;}
            bool operator!=(const OrgChart::Iterator &other) const {return this->cur != other.cur;}
        };


        Iterator begin_level_order() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::levelOrder, this->_root};
        }
        Iterator end_level_order() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::levelOrder, nullptr};
        }
        Iterator begin_reverse_order() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::reverseOrder, this->_root};
        }
        Iterator reverse_order() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::reverseOrder, nullptr};
        }
        Iterator begin_preorder() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::preOrder, this->_root};
        }
        Iterator end_preorder() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::preOrder, nullptr};
        }
        // iterator end_reverse_order() {return OrgChart::Iterator{reverseLevelOrder, nullptr, &this->levelMap};} //maybe will change
        
        // for the for each loops 
        Iterator begin() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::levelOrder, this->_root};
        }
        Iterator end() {
            if (this->_root == nullptr)
            {
                throw std::invalid_argument("There is no root");
            }
            return OrgChart::Iterator{Iter_type::levelOrder, nullptr};
        }


        // getters
        ariel::Node* getRoot() {return this->_root;}
        int getNumOfEmp() const {return this->_numOfEmp;}

        void printChart(std::ostream &output) const;
    };
}
#endif