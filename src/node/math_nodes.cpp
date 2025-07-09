#include "math_nodes.hpp"

using namespace mnode;

AddNode::AddNode(int uid, const char* name, int v1_id, int v2_id, int out_id) : 
            UINode(uid, name),
            value_1_id(v1_id),
            value_2_id(v2_id),
            output_id(out_id) {
                in_attr.push_back(value_1_id);
                in_attr.push_back(value_2_id);
                out_attr.push_back(output_id);
            };

AddNode::~AddNode(){}


bool AddNode::evaluate(){
    return false;
}

void AddNode::draw(){
    // Add Node
    if (!position_set) {
        ImNodes::SetNodeGridSpacePos(get_uid(), get_pos());
        position_set = true;
    }
    ImNodes::BeginNode(get_uid());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(get_node_name());
    ImNodes::EndNodeTitleBar();
    ImNodes::BeginInputAttribute(value_1_id);
    ImGui::Text("value 1");
    ImNodes::EndInputAttribute();
    ImNodes::BeginInputAttribute(value_2_id);
    ImGui::Text("value 2");
    ImNodes::EndInputAttribute();
    ImNodes::BeginOutputAttribute(output_id);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
}
