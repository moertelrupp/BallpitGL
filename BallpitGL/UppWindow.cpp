#include "UppWindow.hpp"

// Prevent circular Dependencies
#include "GameLoop.hpp"
#include "Timer.hpp"
#include "Input.hpp"

namespace upp
{
    UppWindow::UppWindow()
    {
        window = nullptr;
        gameLoop = nullptr;
        input = nullptr;
        timer = nullptr;
        initialized = false;
    }

    void UppWindow::initialize(bool fullscreen, bool vsync, int width, int height)
    {
        if (!initialized)
        {
            // Create Objects
            gameLoop = new GameLoop();
            input = new Input();
            timer = new Timer();

            // Initialize Window
            initializeGLFW();
            createGlfwWindow(fullscreen, width, height);
            glfwMakeContextCurrent(window);
            initializeGlad();

            setVsync(vsync);
            setShowCursor(true);

            initialized = true;

            // Initialize Objects
            gameLoop->initialize(this);
        }
    }

    void UppWindow::shutdown()
    {
        SHUTDOWN_AND_DELETE_OBJ(gameLoop);
        DELETE_OBJ(timer);
        DELETE_OBJ(input);

        if (initialized)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            initialized = false;
        }

        DELETE_OBJ(instance);
    }

    void UppWindow::startGame()
    {
        gameLoop->start();
    }

    void UppWindow::stopGame()
    {
        if (gameLoop)
        {
            gameLoop->stop();
        }
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        handleMessages();
    }

    bool UppWindow::shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void UppWindow::swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void UppWindow::handleMessages(bool blocking)
    {
        input->updateInput();
        if (blocking)
        {
            glfwWaitEvents();
        }
        else
        {
            glfwPollEvents();
        }
    }

    float UppWindow::getAspectRatio()
    {
        return (float)framebufferWidth / (float)framebufferHeight;
    }

    int UppWindow::getWindowWidth()
    {
        return windowWidth;
    }

    int UppWindow::getWindowHeight()
    {
        return windowHeight;
    }

    int UppWindow::getFramebufferWidth()
    {
        return framebufferWidth;
    }

    int UppWindow::getFramebufferHeight()
    {
        return framebufferHeight;
    }

    GLFWwindow* UppWindow::getGLFWwindow()
    {
        return window;
    }

    Input* UppWindow::getInput()
    {
        return input;
    }

    Timer* UppWindow::getTimer()
    {
        return timer;
    }

    void UppWindow::setVsync(bool vsync)
    {
        this->vsync = vsync;
        if (vsync)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    bool UppWindow::getVsync()
    {
        return vsync;
    }

    void UppWindow::toggleVsync()
    {
        setVsync(!vsync);
    }

    void UppWindow::setFullscreen(bool fullscreen)
    {
        this->fullscreen = fullscreen;

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (fullscreen) {
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            // GLFW bug:
            setVsync(vsync);
        }
        else {
            glfwSetWindowMonitor(window, nullptr,
                prev_WindowPosX, prev_WindowPosY,
                prev_windowWidth, prev_windowHeight, mode->refreshRate);
            // GLFW bug:
            setVsync(vsync);
        }
    }

    bool UppWindow::getFullscreen()
    {
        return fullscreen;
    }

    void UppWindow::toggleFullscreen()
    {
        setFullscreen(!fullscreen);
    }

    void UppWindow::setShowCursor(bool showCursor)
    {
        this->showCursor = showCursor;
        if (showCursor)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    bool UppWindow::getShowCursor()
    {
        return showCursor;
    }

    void UppWindow::toggleShowCursor()
    {
        setShowCursor(!showCursor);
    }

    void UppWindow::initializeGLFW()
    {
        if (glfwInit() == GLFW_FALSE)
        {
            THROW_EXCEPTION("Couldn't initialize GLFW");
        }
    }

    void UppWindow::createGlfwWindow(bool fullscreen, int width, int height)
    {
        // Set OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Save windowed size
        prev_windowWidth = width;
        prev_windowHeight = height;

        // Create Window
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (fullscreen)
        {
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            window = glfwCreateWindow(mode->width, mode->height, "UppGL", monitor, nullptr);

            windowWidth = mode->width;
            windowHeight = mode->height;
            windowPosX = 0;
            windowPosY = 0;
            prev_WindowPosX = 0;
            prev_WindowPosY = 0;
        }
        else
        {
            // Create windowed Window with specified Size
            windowWidth = width;
            windowHeight = height;
            window = glfwCreateWindow(windowWidth, windowHeight, "UppGL", nullptr, nullptr);

            // Put window in the middle of the screen
            windowPosX = static_cast<int>(mode->width / 2.0f - windowWidth / 2.0f);
            windowPosY = static_cast<int>(mode->height / 2.0f - windowHeight / 2.0f);
            glfwSetWindowPos(window, windowPosX, windowPosY);

            prev_WindowPosX = windowPosX;
            prev_WindowPosY = windowPosY;
        }

        if (window == nullptr)
        {
            THROW_EXCEPTION("Couldn't create GLFW window!");
        }

        // Set window callbacks
        glfwSetCursorPosCallback(window, &mouse_callback);
        glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
        glfwSetWindowSizeCallback(window, &window_size_callback);
        glfwSetKeyCallback(window, &key_callback);
        glfwSetWindowPosCallback(window, &window_pos_callback);
        glfwSetWindowIconifyCallback(window, &iconify_callback);
        glfwSetErrorCallback(&error_callback);

        // Get Framebuffer size
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    }

    void UppWindow::initializeGlad()
    {
        if (!gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress))
        {
            THROW_EXCEPTION("Couldn't initialize GLAD!");
        }
    }

    void UppWindow::shutdownGLFW()
    {
        glfwTerminate();
    }

    void UppWindow::framebuffer_size_changed(int width, int height)
    {
        framebufferWidth = width;
        framebufferHeight = height;
        gameLoop->framebuffer_resized(width, height);
    }

    void UppWindow::window_size_changed(int width, int height)
    {
        if (width != 0 && height != 0)
        {
            windowWidth = width;
            windowHeight = height;
            if (!fullscreen)
            {
                prev_windowWidth = windowWidth;
                prev_windowHeight = windowHeight;
            }
        }
    }

    void UppWindow::mouse_changed(double xPos, double yPos)
    {
        input->processMouseInput(xPos, yPos);
    }

    void UppWindow::key_changed(int key, int scancode, int action, int mods)
    {
        input->processKeyInput(key, scancode, action, mods);
    }

    void UppWindow::window_pos_changed(int xPos, int yPos)
    {
        if (!fullscreen)
        {
            windowPosX = xPos;
            windowPosY = yPos;
            prev_WindowPosX = xPos;
            prev_WindowPosY = yPos;
        }
    }

    void UppWindow::iconify_changed(int iconified)
    {
        if (iconified) {
            minimized = true;
            gameLoop->gameMinimizedChanged(minimized);
        }
        else
        {
            minimized = false;
            gameLoop->gameMinimizedChanged(minimized);
        }
    }

    // -------
    // Statics
    // -------

    UppWindow* UppWindow::instance = nullptr;

    UppWindow* UppWindow::getInstance()
    {
        if (!instance)
        {
            instance = new UppWindow();
        }

        return instance;
    }

    void UppWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        instance->framebuffer_size_changed(width, height);
    }

    void UppWindow::window_size_callback(GLFWwindow* window, int width, int height)
    {
        instance->window_size_changed(width, height);
    }

    void UppWindow::mouse_callback(GLFWwindow* window, double xPos, double yPos)
    {
        instance->mouse_changed(xPos, yPos);
    }

    void UppWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        instance->key_changed(key, scancode, action, mods);
    }

    void UppWindow::window_pos_callback(GLFWwindow* window, int xPos, int yPos)
    {
        instance->window_pos_changed(xPos, yPos);
    }

    void UppWindow::iconify_callback(GLFWwindow* window, int iconified)
    {
        instance->iconify_changed(iconified);
    }

    void UppWindow::error_callback(int errorCode, const char* error)
    {
        THROW_EXCEPTION("Glfw Error: " + std::to_string(errorCode) + " Msg: " + error);
    }
}
