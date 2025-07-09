#pragma ones

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <string>
#include <memory>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include "node.hpp"
#include "variable_nodes.hpp"
#include "math_nodes.hpp"
#include "ui_elements.hpp"


class MainUI
{
private:
    GLFWwindow* window;
    ImVec2 window_pos;
    ImVec2 window_size;
    ImGuiWindowFlags window_flags;
    UI::Button* addNodeButton;
    UI::Button* intNodeButton;

public:
    std::unique_ptr<NodeManager> nodeManager;
    
    std::function<void()> on_click_add_node_button();
    std::function<void()> on_click_int_node_button();
    MainUI(GLFWwindow* window);
    ~MainUI();
    void draw();
};