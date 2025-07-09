#include "ui.hpp"
#include "imgui_vec2_utils.hpp"

MainUI::MainUI(GLFWwindow* window) : window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    nodeManager = std::make_unique<NodeManager>();

    //Buttons section
    addNodeButton = new UI::Button(std::string("Add"),on_click_add_node_button());
    intNodeButton = new UI::Button(std::string("Int"),on_click_int_node_button());

}

std::function<void()> MainUI::on_click_add_node_button(){
    return [this](){
    ImVec2 screen_center = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
                                    ImGui::GetIO().DisplaySize.y * 0.5f);

    ImVec2 pan = ImNodes::EditorContextGetPanning();
    ImVec2 node_pos = screen_center - pan;

    ImGui::LogToTTY();
    ImGui::LogText("Adding node at grid-space: %.1f, %.1f\n", node_pos.x, node_pos.y);
    ImGui::LogFinish();

    UINode* node = new mnode::AddNode(nodeManager->generate_nuid(),
                        "add node", 
                        nodeManager->generate_auid(), 
                        nodeManager->generate_auid(),
                        nodeManager->generate_auid());
    node->set_pos(node_pos);
    nodeManager->add_node(node);
    };
}

std::function<void()> MainUI::on_click_int_node_button(){
    return [this](){
        ImVec2 screen_center = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
                                    ImGui::GetIO().DisplaySize.y * 0.5f);

        ImVec2 pan = ImNodes::EditorContextGetPanning();
        ImVec2 node_pos = screen_center - pan;

        UINode* node = new vnode::IntNode(nodeManager->generate_nuid(), 
                        "main value", 
                        nodeManager->generate_nuid());
        node->set_pos(node_pos);
        nodeManager->add_node(node);
    };
}

MainUI::~MainUI()
{
    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MainUI::draw(){
    // inside the draw funtion
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    window_size = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(window_size);
    window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
                   ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("NodeGraphFullscreen", nullptr, window_flags);
        ImGui::PopStyleVar();
        ImNodes::BeginNodeEditor();
            nodeManager->draw_nodes();
            nodeManager->draw_links();
        ImNodes::EndNodeEditor();
// 
        nodeManager->create_link();
    ImGui::End();
    ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::CollapsingHeader("Add Nodes")) {
            if (addNodeButton) addNodeButton->draw(ImVec2(0, 0));
            if (intNodeButton) intNodeButton->draw(ImVec2(0, 0));
        }
    ImGui::End();
    ImGui::Render();
}
