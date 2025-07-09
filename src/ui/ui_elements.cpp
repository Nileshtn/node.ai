#include "ui_elements.hpp"
using namespace UI;

//BUTTON
Button::Button(std::string& label, std::function<void()> onClick) :
    label(label), onClick(onClick) {
        ImVec2 size = ImGui::CalcTextSize(label.c_str());
        size.x += 20;
        size.y += 4;
    };

Button::~Button(){}

void Button::draw(ImVec2 pos){
    ImGui::SetCursorPos(pos);
    if (ImGui::Button(label.c_str(), size)) {
            if (onClick) onClick();
        }
}
