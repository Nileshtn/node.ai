#pragma ones

#include "imgui.h"
#include <stdio.h>
#include <vector>
#include <functional>
#include <string>

namespace UI{
    class UIElement
    {
    public:
        virtual void draw(ImVec2 pos) = 0;
        virtual ~UIElement() = default;
    };

    class Button : public UIElement
    {
    private:
        std::string label;
        ImVec2 size;
        std::function<void()> onClick;
    public:
        Button(std::string label, std::function<void()> onClick);
        void draw(ImVec2 pos) override;
        ~Button();
    };

}//ui
