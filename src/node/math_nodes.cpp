#include "math_nodes.hpp"

using namespace mnode;

AddNode::AddNode(int uid, const char* name, int v1_id, int v2_id, int out_id) : 
            UINode(uid, name)
            {
                input_point input1{v1_id};
                input_point input2{v2_id};
                add_output output1{out_id, 0.0f};

                input.push_back(input1);
                input.push_back(input2);
                output.push_back(output1);
            };

AddNode::~AddNode(){}


bool AddNode::evaluate(){
    return false;
}

std::vector<output_point> AddNode::get_outputs(){
    std::vector<output_point> r_output;
    
    for(add_output out : output){
        output_point new_out_point{out.attr_id};
        r_output.push_back(new_out_point);
    }
    return r_output;
}

std::vector<input_point> AddNode::get_inputs(){
    return input;
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
    ImNodes::BeginInputAttribute(input[0].attr_id);
    ImGui::Text("value 1");
    ImNodes::EndInputAttribute();
    ImNodes::BeginInputAttribute(input[1].attr_id);
    ImGui::Text("value 2");
    ImNodes::EndInputAttribute();
    ImNodes::BeginOutputAttribute(output[0].attr_id);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
}
