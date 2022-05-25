#include "OrgChart.hpp"

using namespace ariel;
namespace ariel
{


    OrgChart::~OrgChart() {
        this->_root = nullptr;
    }

    /**
     * @brief adding root to the chart, replacing if already exist
     *
     * @param name
     * @return ariel::OrgChart&
     */
    OrgChart OrgChart::add_root(const std::string &name)
    {
        if (this->_root == nullptr)
        {
            this->_root = new Node(name, 0);
        }
        else
        {
            this->_root->_title = name;
        }
        this->_numOfEmp++;
        return *this;
        
    }


    /**
     * @brief adding employees
     *
     * @param boss
     * @param sub
     * @return ariel::OrgChart
     */
    OrgChart OrgChart::add_sub(const std::string &boss, const std::string &sub)
    {
        if (this->_root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        if (boss.empty() || sub.empty())
        {
            throw std::invalid_argument("There is no names");
        }

        int x = this->_numOfEmp;
        addSubordinate(this->_root, boss, sub);
        if (x == this->_numOfEmp)
        {
            throw std::invalid_argument("no boss was found");
        }
        return *this;
    }

    void OrgChart::addSubordinate(Node * root, const std::string &boss, const std::string &sub)
    {

        if (root->_title == boss)
        {
            ariel::Node *new_node = nullptr;
            new_node = new ariel::Node(sub, root->payLevel + 1);
            root->_subordinates.push_back(new_node);
            this->_numOfEmp++;
        }
        else
        {
            for (uint i = 0; i < root->_subordinates.size(); i++)
            {
                addSubordinate(root->_subordinates[i], boss, sub);
            }
        }
    }

    std::ostream &operator<<(std::ostream &output, const OrgChart &chart)
    {
        // std::vector<Node*> temp_childs = chart._org_chart->get_children();
        // chart.printChart(output);
        return output;
    }

    /*--------------------------------------Iterator class implementation--------------------------------------*/

    /**
     * @brief Construct a new Iterator object that is type dependent
     *
     * @param type
     * @param node
     * @param levelmap
     */
    ariel::OrgChart::Iterator::Iterator(ariel::Iter_type type, Node *node)
    {
        if (node != nullptr)
        {
            switch (type)
            {
            case Iter_type::levelOrder:
                levelOrder(node);
                break;
            case Iter_type::reverseOrder:
                reverseLevelOrder(node);
                break;
            case Iter_type::preOrder:
                preOrder(node);
                break;
            }
            this->cur = this->nodes.front();
            this->nodes.pop_front();
        }
        else
        {
            this->cur = nullptr;
        }
    }

    /**
     * @brief level order iterator
     *
     * @param node
     * @param levelmap
     */
    void OrgChart::Iterator::levelOrder(Node *node)
    {
        std::queue<ariel::Node*> queue;

        queue.push(node);
        while(!queue.empty()) {
            this->cur = queue.front();
            queue.pop();
            nodes.push_back(this->cur);
            for (ariel::Node *n : this->cur->_subordinates) {
                queue.push(n);
            }
        }
    }

    /**
     * @brief reverse level order iterator
     *
     * @param node
     * @param levelmap
     */
    void OrgChart::Iterator::reverseLevelOrder(Node *node)
    {
        std::map<int, std::vector<ariel::Node *>> levels;
        std::queue<Node *> queue;
        queue.push(node);
        while (!queue.empty())
        {
            this->cur = queue.front();
            queue.pop();
            levels[this->cur->payLevel].push_back(this->cur);
            for (ariel::Node *n : this->cur->_subordinates)
            {
                queue.push(n);
            }
        }

        for (size_t key = levels.size(); key > 0; key--)
        {
            for (ariel::Node *n : levels[key-1])
            {
                this->nodes.push_back(n);
            }
        }
    }

    /**
     * @brief preorder iterator
     *
     * @param node
     * @param levelmap
     */
    void OrgChart::Iterator::preOrder(Node *node)
    {
        std::stack<Node *> stack;
        stack.push(node);
        while (!stack.empty())
        {
            this->cur = stack.top();
            stack.pop();
            this->nodes.push_back(this->cur);

            for (uint i = this->cur->_subordinates.size(); i > 0; i--)
            {
                stack.push(this->cur->_subordinates[i - 1]);
            }
        }
    }

    ariel::OrgChart::Iterator &ariel::OrgChart::Iterator::operator++()
    {
        if (!this->nodes.empty())
        {
            this->cur = this->nodes.front();
            this->nodes.pop_front();
        }
        else
        {
            this->cur = nullptr;
        }
        return *this;
    }

    

    void printChart(std::ostream &output) {
        std::cout << "hey" << std::endl;
    }
}