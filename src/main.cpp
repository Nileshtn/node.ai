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
#include "ui.hpp"

void input_processor(GLFWwindow* window, std::unique_ptr<NodeManager>& nodeManager) {
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
                nodeManager->delete_nodes(id);
            }
        }
        size = ImNodes::NumSelectedLinks();
        if(size > 0){
            int link_ids[size];
            ImNodes::GetSelectedLinks(link_ids);
            for(int id : link_ids){
                nodeManager->delete_links(id);
            }
        }
    }
}

// void render_nodes() {
//     // Print Node
//     ImNodes::BeginNode(38917493);
//     ImNodes::BeginNodeTitleBar();
//     ImGui::TextUnformatted("rpint");
//     ImNodes::EndNodeTitleBar();
//     ImNodes::BeginInputAttribute(3482973);
//     ImGui::Text("In");
//     ImNodes::EndInputAttribute();
//     ImGui::Text("Value: %d", 5);
//     ImNodes::EndNode();
// }

int main(int, char**) {
    if (!glfwInit()) return 1; //glfw initialization
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Node.ai", NULL, NULL);// main window creation
    glfwMakeContextCurrent(window);//make current window active
    glfwSwapInterval(1); //for vsync
    MainUI uiManager(window);

    //test funtionality
    // UINode* node1 = new vnode::IntNode(uiManager.nodeManager->generate_nuid(), 
    //                     "main value", 
    //                     uiManager.nodeManager->generate_nuid());
    // UINode* node2 = new mnode::AddNode(uiManager.nodeManager->generate_nuid(),
    //                     "add node", 
    //                     uiManager.nodeManager->generate_auid(), 
    //                     uiManager.nodeManager->generate_auid(),
    //                     uiManager.nodeManager->generate_auid());

    // uiManager.nodeManager->add_node(node1);
    // uiManager.nodeManager->add_node(node2);

    while (!glfwWindowShouldClose(window)) {
        input_processor(window, uiManager.nodeManager);
        glfwPollEvents();

        uiManager.draw();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
