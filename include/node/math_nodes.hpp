#pragma once

#include "node.hpp"
#include <variant>
#include <unordered_map>
#include <vector>


struct add_output : output_point
{
    std::variant<int, float, std::string> value;
};


namespace mnode
{
    class AddNode : public UINode
    {
    private:
        const char* node_type = "addition";
        std::vector<input_point> input;
        std::vector<add_output> output;
        std::vector<input_point> get_inputs() override;
        std::vector<output_point> get_outputs() override;


    public:
        AddNode(int uid, const char* name, int v1_id, int v2_id, int out_id);
        ~AddNode();
        bool evaluate() override;
        void draw() override;
    };
} // namespace mnode
