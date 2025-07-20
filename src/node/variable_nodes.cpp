#include "variable_nodes.hpp"
#include <iostream>

using namespace vnode;


IntNode::IntNode(int uid, const char* name, int out_id) : UINode(uid, name){
    output_point output1{out_id, 0};
    output.push_back(output1);
};
IntNode::~IntNode(){}

bool IntNode::evaluate(){
    // std::cout << "int value" << std::any_cast<int>(output[0].value) << std::endl;
    return false;
}

std::vector<input_point* > IntNode::get_inputs(){
    std::vector<input_point*> empty;
    return empty;
}

std::vector<output_point*> IntNode::get_outputs(){
    std::vector<output_point*> r_output;
    for(auto& out : output){
        r_output.push_back(&out);
    }
    return r_output;
}

void IntNode::draw(){
    ImGui::SetCursorPos(get_pos());
    ImNodes::BeginNode(get_uid());
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(get_node_name());
    ImNodes::EndNodeTitleBar();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("value", std::any_cast<int>(&output[0].value));
    ImNodes::BeginOutputAttribute(output[0].attr_id);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
}


