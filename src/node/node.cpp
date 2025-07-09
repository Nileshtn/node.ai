#include "node.hpp"
#include <algorithm>
#include <string>

int UINode::get_uid(){
    return uid;
}

const char* UINode::get_node_name(){
    return name;
}

void UINode::set_pos(ImVec2 pos){
    this->pos = pos;
}

ImVec2 UINode::get_pos(){
    return pos;
}

UINode::UINode(int uid, const char* name) : uid(uid), name(name) {}
UINode::~UINode(){}



NodeManager::NodeManager(){};
NodeManager::~NodeManager(){};


int NodeManager::generate_luid(){
    link_id++;
    return link_id;
}

int NodeManager::generate_nuid(){
    node_id++;
    return node_id;
}

int NodeManager::generate_auid(){
    attr_id++;
    return attr_id;
}

void NodeManager::add_node(UINode* node){
    nodes.push_back(node);
}

void NodeManager::create_link(){
    int start_attr, end_attr;
    int uid = generate_luid();
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
            links.push_back({uid, start_attr, end_attr });
        }
}

void NodeManager::draw_links(){
    for(const auto& link : links){
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }
}

void NodeManager::draw_nodes(){
    for(UINode* node : nodes){
        node->draw();
    }
}

void NodeManager::delete_nodes(int node_id){
    nodes.erase(
        std::remove_if(nodes.begin(), nodes.end(),
        [node_id](UINode* node) {
            return node->get_uid() == node_id;
        }),
        nodes.end()
    );
}

void NodeManager::delete_links(int link_id) {
    links.erase(
        std::remove_if(links.begin(), links.end(),
            [link_id](const Link& alink) {
                return alink.id == link_id;
            }),
        links.end()
    );
}