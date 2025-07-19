#include "variable_nodes.hpp"

using namespace vnode;


IntNode::IntNode(int uid, const char* name, int out_id) : UINode(uid, name){
    int_output output1{out_id, 0};
    output.push_back(output1);
};
IntNode::~IntNode(){}

bool IntNode::evaluate(){
    return false;
}

std::vector<input_point> IntNode::get_inputs(){
    std::vector<input_point> empty;
    return empty;
}

std::vector<output_point> IntNode::get_outputs(){
    std::vector<output_point> r_output;
    
    for(int_output out : output){
        output_point new_out_point{out.attr_id};
        r_output.push_back(new_out_point);
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
    ImGui::InputInt("value", &output[0].value);
    ImNodes::BeginOutputAttribute(output[0].attr_id);
    ImGui::Text("out");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
}


