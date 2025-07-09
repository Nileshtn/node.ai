#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "imnodes.h"


struct Link {
    int id;
    int start_attr;
    int end_attr;
};

class UINode
{
private:
    int uid{};
    const char* name {};
    ImVec2 pos;

protected:
    std::vector<int> in_link_id;
    std::vector<int> out_link_id;
    std::vector<int> in_attr;
    std::vector<int> out_attr;

public:
    bool position_set = false;
    UINode(int uid, const char* name);
    virtual ~UINode();
    virtual bool evaluate() = 0;
    virtual void draw() = 0;
    int get_uid();
    void set_pos(ImVec2 pos);
    ImVec2 get_pos();
    const char* get_node_name();
};

class NodeManager
{
private:
    std::vector<UINode*> nodes;
    std::vector<Link> links;
    int link_id {50000};
    int node_id {0};
    int attr_id {300000};

public:
    NodeManager(/* args */);
    ~NodeManager();
    int generate_nuid();
    int generate_luid();
    int generate_auid();
    void add_node(UINode* node);
    void create_link();
    void draw_links();
    void draw_nodes();
    void delete_nodes(int node_id);
    void delete_links(int link_id);
};

#endif //NODE_HPP
