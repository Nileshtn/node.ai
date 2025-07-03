#pragma once

#include "imnodes.h"
#include "node.hpp"

namespace vnode
{
    class IntNode : public UINode
    {
    private:
        const char* node_type = "addtion";
        int output {};
        int output_id {};
        
    public:
        IntNode(int uid, const char* name, int out_id);
        ~IntNode();
        bool evaluate() override;
        void draw() override;
    };
    
} // namespace vnode
