#include "math_nodes.hpp"
#include <iostream>

using namespace mnode;

AddNode::AddNode(int uid, const char* name, int v1_id, int v2_id, int out_id) : 
            UINode(uid, name)
            {
                input_point input1{v1_id};
                input_point input2{v2_id};
                output_point output1{out_id, 0.0f};

                input.push_back(input1);
                input.push_back(input2);
                output.push_back(output1);
            };

AddNode::~AddNode(){}

bool AddNode::evaluate() {
    float value_1{}, value_2{};

    // Check pointers to avoid null dereference
    // if (!input[0].node || !input[1].node) return false;
    if(!input[0].node){
        value_1 = 0.0f;
    }
    else{
        for (output_point* point : input[0].node->get_outputs()) {
        value_1 = (float)std::any_cast<int>(point->value);
        }
    }

    if(!input[0].node){
        value_1 = 0.0f;
    }
    else{
        for (output_point* point : input[1].node->get_outputs()) {
        value_2 = (float)std::any_cast<int>(point->value);
        }
    }

    output[0].value = value_1 + value_2;

    // Optional: log to ImGui window
    ImGui::LogToTTY();
    float value = std::any_cast<float>(output[0].value);
    ImGui::LogText("added : value = %f\n", value);
    ImGui::LogFinish();

    return true;
}



std::vector<output_point*> AddNode::get_outputs() {
    std::vector<output_point*> r_output;
    for (auto& out : output) {
        r_output.push_back(&out);
    }
    return r_output;
}

std::vector<input_point*> AddNode::get_inputs() {
    std::vector<input_point*> r_input;
    for (auto& in : input) {
        r_input.push_back(&in);
    }
    return r_input;
}

void AddNode::draw(){
    // Add Node
    ImNodes::BeginNode(get_uid());
    if (!position_set) {
        ImNodes::SetNodeGridSpacePos(get_uid(), get_pos());
        position_set = true;
    }
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
