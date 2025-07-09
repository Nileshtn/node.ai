#include "variable_nodes.hpp"

using namespace vnode;


IntNode::IntNode(int uid, const char* name, int out_id) : UINode(uid, name), output_id(out_id){
    out_attr.push_back(out_id);
};
IntNode::~IntNode(){}
bool IntNode::evaluate(){
    return false;
}

void IntNode::draw(){
    ImGui::SetCursorPos(get_pos());
    ImNodes::BeginNode(get_uid());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(get_node_name());
    ImNodes::EndNodeTitleBar();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("value", &output);
    ImNodes::BeginOutputAttribute(output_id);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
}


