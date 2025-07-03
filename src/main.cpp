#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "node.hpp"
#include "variable_nodes.hpp"
#include "math_nodes.hpp"

void input_processor(GLFWwindow* window, NodeManager* node_manager) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && 
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)  {
        ImNodes::ClearLinkSelection();
        ImNodes::ClearNodeSelection();
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS){
        int size {ImNodes::NumSelectedNodes()};
        if(size > 0){
            int node_ids[size];
            ImNodes::GetSelectedNodes(node_ids);
            for(int id : node_ids){
                node_manager->delete_nodes(id);
            }
            
        }
        size = ImNodes::NumSelectedLinks();
        if(size > 0){
            int link_ids[size];
            ImNodes::GetSelectedLinks(link_ids);
            for(int id : link_ids){
                node_manager->delete_links(id);
            }
        }
    }
}

void render_nodes() {
    // Print Node
    ImNodes::BeginNode(38917493);
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("rpint");
    ImNodes::EndNodeTitleBar();
    ImNodes::BeginInputAttribute(3482973);
    ImGui::Text("In");
    ImNodes::EndInputAttribute();
    ImGui::Text("Value: %d", 5);
    ImNodes::EndNode();
}

int main(int, char**) {
    if (!glfwInit()) return 1; //glfw initialization
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Node.ai", NULL, NULL);// main window creation
    glfwMakeContextCurrent(window);//make current window active
    glfwSwapInterval(1); //for vsync

    //imgui initial setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    //initial setup end

    //creating the node maneger
    NodeManager* node_manager = new NodeManager();

    //test funtionality
    UINode* node1 = new vnode::IntNode(node_manager->generate_nuid(), 
                        "main value", 
                        node_manager->generate_nuid());
    UINode* node2 = new mnode::AddNode(node_manager->generate_nuid(),
                        "add node", 
                        node_manager->generate_auid(), 
                        node_manager->generate_auid(),
                        node_manager->generate_auid());

    node_manager->add_node(node1);
    node_manager->add_node(node2);

    while (!glfwWindowShouldClose(window)) {
        input_processor(window, node_manager);
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Fullscreen window
        ImVec2 window_pos = ImVec2(0, 0);
        ImVec2 window_size = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowPos(window_pos);
        ImGui::SetNextWindowSize(window_size);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                        ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("NodeGraphFullscreen", nullptr, window_flags);
        ImGui::PopStyleVar();

        ImNodes::BeginNodeEditor();

        node_manager->draw_nodes();
        node_manager->draw_links();

        ImNodes::EndNodeEditor();

        node_manager->create_link();
        
        ImGui::End(); // End NodeGraphFullscreen

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
