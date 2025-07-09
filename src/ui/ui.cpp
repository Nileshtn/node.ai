#include "ui.hpp"

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

    window_pos = ImVec2(0, 0);
    window_size = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(window_pos);
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
            //node funtionllity and ui.
            nodeManager->draw_nodes();
            nodeManager->draw_links();
        ImNodes::EndNodeEditor();
        nodeManager->create_link();
    ImGui::End();
    ImGui::Render();
}

