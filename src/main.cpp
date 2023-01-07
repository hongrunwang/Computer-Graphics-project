#include "scene.h"

int main() {

  /// settings

  // window
  constexpr int window_width = 1920;
  constexpr int window_height = 1080;

  /// setup window
  GLFWwindow* window;
  {
    if (!glfwInit()) // initialize glfw library
      return -1;

    // setting glfw window hints and global configurations
    {
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use core mode
      // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // use debug context
    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif
    }

    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(window_width, window_height, "CS171 HW5: Cloth Simulation", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return -1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // load Opengl
    if (!gladLoadGL()) {
      glfwTerminate();
      return -1;
    }

    // setup call back functions
    glfwSetFramebufferSizeCallback(window, Input::CallBackResizeFlareBuffer);
  }

  /// main Loop
  {
    // shader
    Shader::Initialize();

    // scene
    Scene scene(45);
    scene.camera.transform.position = { 0, -1.5, -6 };
    scene.camera.transform.rotation = { 0, 0, 1, 0 };
    scene.light_position = { 0, 3, -10 };
    scene.light_color = Vec3(1, 1, 1) * Float(1.125);

    // mesh primitives
    auto mesh_cube = std::make_shared<Mesh>(MeshPrimitiveType::cube);
    auto mesh_sphere = std::make_shared<Mesh>(MeshPrimitiveType::sphere);

	mesh_cube->ApplyTransform(Transform(Vec3(-3.5, -1.8, 0.3),
                              Quat(1, 0, 0, 0),
                              Vec3(1, 1, 1)));
	mesh_cube->BufferMeshVertices();
	mesh_sphere->ApplyTransform(Transform(Vec3(3.5, -1.8, 0.3),
                                Quat(1, 0, 0, 0),
                                Vec3(1, 1, 1)));
	mesh_sphere->BufferMeshVertices();


    // objects
    auto object_cube = scene.AddObject(mesh_cube,
                                       Shader::shader_phong);
    auto object_sphere = scene.AddObject(mesh_sphere,
                                         Shader::shader_phong);
    object_cube->color = { Float(0.75), one, zero };
    object_sphere->color = { one, Float(0.75), zero };

    // loop until the user closes the window
    Input::Start(window);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
      Input::Update();
      Time::Update();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      /// terminate
      if (Input::GetKey(KeyCode::Escape))
        glfwSetWindowShouldClose(window, true);

      /// fixed update
      for (unsigned i = 0; i < Time::fixed_update_times_this_frame; ++i) {
        if(Input::GetKey(KeyCode::Space)) { //! only when space is pressed
          scene.FixedUpdate();
        }
      }

      /// update
      {
        scene.Update();
//        printf("Pos = (%f, %f, %f)\n", scene.camera.transform.position.x, scene.camera.transform.position.y, scene.camera.transform.position.z);
//        printf("Rot = (%f, %f, %f, %f)\n", scene.camera.transform.rotation.w, scene.camera.transform.rotation.x, scene.camera.transform.rotation.y, scene.camera.transform.rotation.z);
//        printf("\n");
      }

      /// render
      {
        scene.RenderUpdate();
      }

      // swap front and back buffers
      glfwSwapBuffers(window);

      // poll for and process events
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}
