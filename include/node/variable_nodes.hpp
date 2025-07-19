#pragma once

#include "imnodes.h"
#include "node.hpp"




namespace vnode
{
    class IntNode : public UINode
    {
    private:
        const char* node_type = "addtion";
        std::vector<output_point> output;
        
    public:
        IntNode(int uid, const char* name, int out_id);
        ~IntNode();
        bool evaluate() override;
        void draw() override;
        std::vector<input_point*> get_inputs() override;
        std::vector<output_point*> get_outputs() override;
    };
    
} // namespace vnode
