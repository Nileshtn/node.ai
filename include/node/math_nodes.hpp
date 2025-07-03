#pragma once

#include "node.hpp"

namespace mnode
{
    class AddNode : public UINode
    {
    private:
        const char* node_type = "addition";
        float value_1 {0.0f};
        float value_2 {0.0f};
        int value_1_id {};
        int value_2_id {};
        float output {};
        int output_id {};
        

    public:
        AddNode(int uid, const char* name, int v1_id, int v2_id, int out_id);
        ~AddNode();
        bool evaluate() override;
        void draw() override;
    };
} // namespace mnode
