#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui.cpp"
#include "imgui/imgui_draw.cpp"
#include "imgui/imgui_tables.cpp"
#include "imgui/imgui_widgets.cpp"
#include "imgui/backends/imgui_impl_win32.cpp"
#include "imgui/backends/imgui_impl_opengl3.cpp"
#if 1
#include "imgui/imgui_demo.cpp"
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define Assert(x) if((x) == 0) { *(int*)(0) = 0; }

LRESULT __stdcall WindowProc(HWND Window, UINT Msg, WPARAM Wparam, LPARAM Lparam)
{
    if(ImGui_ImplWin32_WndProcHandler(Window, Msg, Wparam, Lparam))
    {
        return 1;
    }

    LRESULT Result = 0;
    switch(Msg)
    {
        case WM_KEYDOWN:
        {
            switch(Wparam)
            {
                case VK_ESCAPE:
                {
                    DestroyWindow(Window);
                } break;
            }
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Msg, Wparam, Lparam);
        } break;
    }
    return Result;
}

int __stdcall WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int ShowCmd)
{
    WNDCLASSEXA WindowClassEx = {0};
    WindowClassEx.cbSize = sizeof(WindowClassEx);
    WindowClassEx.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW|CS_DROPSHADOW;
    WindowClassEx.lpfnWndProc = WindowProc;
    WindowClassEx.cbClsExtra = 0;
    WindowClassEx.cbWndExtra = 0;
    WindowClassEx.hInstance = Instance;
    WindowClassEx.hIcon = 0;
    WindowClassEx.hCursor = 0;
    WindowClassEx.hbrBackground = 0;
    WindowClassEx.lpszMenuName = 0;
    WindowClassEx.lpszClassName = "ImGuiTestWindowClass";
    WindowClassEx.hIconSm = 0;
    Assert(RegisterClassExA(&WindowClassEx));

    HWND Window;
    Assert(Window = CreateWindowExA(WS_EX_OVERLAPPEDWINDOW,
                                    "ImGuiTestWindowClass",
                                    "ImGuiTest",
                                    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                    CW_USEDEFAULT, CW_USEDEFAULT,
                                    CW_USEDEFAULT, CW_USEDEFAULT,
                                    0, 0, Instance, 0));

    HDC DC;
    Assert(DC = GetDC(Window));

    PIXELFORMATDESCRIPTOR PixelFormatDescriptor = {0};
    PixelFormatDescriptor.nSize = sizeof(PixelFormatDescriptor);
    PixelFormatDescriptor.nVersion = 1;
    PixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    PixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    PixelFormatDescriptor.cColorBits = 32;

    int PixelFormat;
    Assert(PixelFormat = ChoosePixelFormat(DC, &PixelFormatDescriptor));
    Assert(SetPixelFormat(DC, PixelFormat, &PixelFormatDescriptor));

    HGLRC GLRC;
    Assert(GLRC = wglCreateContext(DC));
    wglMakeCurrent(DC, GLRC);

    ImGui::CreateContext();
    ImGuiIO& ImIO = ImGui::GetIO();
    ImIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsLight();
    ImGui_ImplWin32_InitForOpenGL(Window);
    ImGui_ImplOpenGL3_Init();

    bool Finished = false;
    while(!Finished)
    {
        MSG Msg;
        if(GetMessage(&Msg, 0, 0, 0) < 0)
        {
            break;
        }

        do
        {
            if(Msg.message == WM_QUIT)
            {
                Finished = true;
            }

            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        while(PeekMessage(&Msg, 0, 0, 0, PM_REMOVE));

        if(Finished)
        {
            break;
        }

        RECT ClientRect = {0};
        Assert(GetClientRect(Window, &ClientRect));
        int Width = ClientRect.right - ClientRect.left;
        int Height = ClientRect.bottom - ClientRect.top;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

#if 1
        ImGui::ShowDemoWindow(0);
#else
        ImGui::Text("This is dear ImGui!");
#endif

        ImGui::Render();
        glViewport(0, 0, Width, Height);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SwapBuffers(DC);
    }

    return 0;
}
