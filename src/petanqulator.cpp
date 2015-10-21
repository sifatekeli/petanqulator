
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <cmath>
#include <iostream>

bool gMouseMotion = false;
float gTx = 0;
float gTy = 0;
double gCursorOldX;
double gCursorOldY;

static void handleError(int, const char * description)
{
    std::cerr << description << std::endl;
}

static void handleKey(GLFWwindow * ptrWindow, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)
        glfwSetWindowShouldClose(ptrWindow, GL_TRUE);
}

static void handleCursorPos(GLFWwindow *, double xpos, double ypos)
{
    if (gMouseMotion)
    {
        gTx += (xpos - gCursorOldX)*0.001;
        gTy -= (ypos - gCursorOldY)*0.001;
    }
    gCursorOldX = xpos;
    gCursorOldY = ypos;
}

void handleMouseButton(GLFWwindow *, int button, int action, int)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            gMouseMotion = true;
        else if (action == GLFW_RELEASE)
            gMouseMotion = false;
    }
}

int main()
{

    glfwSetErrorCallback(handleError);

    if (0 == glfwInit())
    {
        std::cerr << "error: glfwInit" << std::endl;
        exit(-1);
    }

    GLFWwindow * ptrWindow = glfwCreateWindow(640, 480, 
            "PETANQue simULATOR", nullptr, nullptr);
    if (nullptr == ptrWindow)
    {
        glfwTerminate();
        exit(-1);
    }

    glfwGetCursorPos(ptrWindow, &gCursorOldX, &gCursorOldY);

    glfwSetKeyCallback(ptrWindow, handleKey);
    glfwSetCursorPosCallback(ptrWindow, handleCursorPos);
    glfwSetMouseButtonCallback(ptrWindow, handleMouseButton);

    glfwMakeContextCurrent(ptrWindow);

    glfwSwapInterval(1);

    // cegui
    CEGUI::OpenGLRenderer& uiRenderer = CEGUI::OpenGLRenderer::bootstrapSystem();
    //CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
    CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");
    CEGUI::Window * ptrUiRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("petanqulator.layout");
    CEGUI::System::getSingleton().setGUISheet(ptrUiRoot);

    while (GL_TRUE != glfwWindowShouldClose(ptrWindow))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(ptrWindow, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(gTx, gTy, 1.f);
        float t = glfwGetTime();
        glBegin(GL_TRIANGLES);
        glColor3f(cos(t), 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, sin(t), 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

        CEGUI::System::getSingleton().renderGUI();

        glfwSwapBuffers(ptrWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(ptrWindow);
    glfwTerminate();
    return 0;
}

