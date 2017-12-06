#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
#include <algorithm>

#include <plog/Log.h>

#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/mainui.hpp"
#include "core/globals.hpp"
#include "debug/ui.hpp"

#define NANOVG_GL3_IMPLEMENTATION
#define OTTO_NVG_CREATE nvgCreateGL3
#define OTTO_NVG_DELETE nvgDeleteGL3

#include <NanoCanvas.h>

// C APIs. Include last
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

namespace otto::ui {

  namespace {

    Key keyboardKey(int xKey, int mods) {
      switch (xKey) {

        // Rotaries
      case GLFW_KEY_Q:
        if (mods & GLFW_MOD_CONTROL) return K_BLUE_CLICK;
        return K_BLUE_UP;
      case GLFW_KEY_A:
        if (mods & GLFW_MOD_CONTROL) return K_BLUE_CLICK;
        return K_BLUE_DOWN;
      case GLFW_KEY_W:
        if (mods & GLFW_MOD_CONTROL) return K_GREEN_CLICK;
        return K_GREEN_UP;
      case GLFW_KEY_S:
        if (mods & GLFW_MOD_CONTROL) return K_GREEN_CLICK;
        return K_GREEN_DOWN;
      case GLFW_KEY_E:
        if (mods & GLFW_MOD_CONTROL) return K_WHITE_CLICK;
        return K_WHITE_UP;
      case GLFW_KEY_D:
        if (mods & GLFW_MOD_CONTROL) return K_WHITE_CLICK;
        return K_WHITE_DOWN;
      case GLFW_KEY_R:
        if (mods & GLFW_MOD_CONTROL) return K_RED_CLICK;
        return K_RED_UP;
      case GLFW_KEY_F:
        if (mods & GLFW_MOD_CONTROL) return K_RED_CLICK;
        return K_RED_DOWN;

      case GLFW_KEY_LEFT:  return K_LEFT;
      case GLFW_KEY_RIGHT: return K_RIGHT;

        // Tapedeck
      case GLFW_KEY_SPACE: return K_PLAY;
      case GLFW_KEY_Z:     return K_REC;
      case GLFW_KEY_F1:    return K_TRACK_1;
      case GLFW_KEY_F2:    return K_TRACK_2;
      case GLFW_KEY_F3:    return K_TRACK_3;
      case GLFW_KEY_F4:    return K_TRACK_4;

        // Numbers
      case GLFW_KEY_1:     return K_1;
      case GLFW_KEY_2:     return K_2;
      case GLFW_KEY_3:     return K_3;
      case GLFW_KEY_4:     return K_4;
      case GLFW_KEY_5:     return K_5;
      case GLFW_KEY_6:     return K_6;
      case GLFW_KEY_7:     return K_7;
      case GLFW_KEY_8:     return K_8;
      case GLFW_KEY_9:     return K_9;
      case GLFW_KEY_0:     return K_0;

      case GLFW_KEY_T:     if (mods & GLFW_MOD_CONTROL) return K_TAPE; else break;
      case GLFW_KEY_Y:     if (mods & GLFW_MOD_CONTROL) return K_MIXER; else break;
      case GLFW_KEY_U:     if (mods & GLFW_MOD_CONTROL) return K_SYNTH; else break;
      case GLFW_KEY_G:     if (mods & GLFW_MOD_CONTROL) return K_METRONOME; else break;
      case GLFW_KEY_H:     if (mods & GLFW_MOD_CONTROL) return K_SAMPLER; else break;
      case GLFW_KEY_J:     if (mods & GLFW_MOD_CONTROL) return K_DRUMS; else break;

      case GLFW_KEY_L:     return K_LOOP;
      case GLFW_KEY_I:     return K_LOOP_IN;
      case GLFW_KEY_O:     return K_LOOP_OUT;

      case GLFW_KEY_X:     return K_CUT;
      case GLFW_KEY_C:     if (mods & GLFW_MOD_CONTROL) return K_LIFT; else break;
      case GLFW_KEY_V:     if (mods & GLFW_MOD_CONTROL) return K_DROP;

      case GLFW_KEY_LEFT_SHIFT:
      case GLFW_KEY_RIGHT_SHIFT:
        return K_SHIFT;

      default:             return K_NONE;
      }
      return K_NONE;
    }


    void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
      using namespace ui;
      MainUI& self = global::ui;
      Key k = keyboardKey(key, mods);
      if (action == GLFW_PRESS) {
        self.keypress(k);
      } else if (action == GLFW_REPEAT) {
        switch (k) {
        case K_RED_UP:
        case K_RED_DOWN:
        case K_BLUE_UP:
        case K_BLUE_DOWN:
        case K_WHITE_UP:
        case K_WHITE_DOWN:
        case K_GREEN_UP:
        case K_GREEN_DOWN:
        case K_LEFT:
        case K_RIGHT:
          self.keypress(k);
        default: break;
        }
      } else if (action == GLFW_RELEASE) {
        self.keyrelease(k);
      }
    }
  }

  struct DbgData {
    static inline bool         mouse_pressed[3] = { false, false, false };
    static inline float        mouse_wheel = 0.0f;
    static inline double       time = 0.0f;
    static inline GLuint       font_texture = 0;
    static inline int          shader_handle = 0, vert_handle = 0, frag_handle = 0;
    static inline int          attrib_location_tex = 0, attrib_location_proj = 0;
    static inline int          attrib_location_position = 0, attrib_location_UV = 0, attrib_location_color = 0;
    static inline unsigned int vbo_handle = 0, vao_handle, elements_handle = 0;
    static inline GLFWwindow*  window;

    static void init()
    {
#if OTTO_DEBUG_UI
      window = glfwCreateWindow(1280, 720, "OTTO Debugging", NULL, NULL);
      auto prev_ctx = glfwGetCurrentContext();
      glfwMakeContextCurrent(window);
      glfwSwapInterval(1);
      gl3wInit();

      ImGuiIO& io = ImGui::GetIO();
      io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
      io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
      io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
      io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
      io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
      io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
      io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
      io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
      io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
      io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
      io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
      io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
      io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
      io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
      io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
      io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
      io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
      io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
      io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

      io.RenderDrawListsFn = nullptr;

      io.SetClipboardTextFn = set_clipboard;
      io.GetClipboardTextFn = get_clipboard;
      io.ClipboardUserData = window;
#ifdef _WIN32
      io.ImeWindowHandle = glfwGetWin32Window(window);
#endif

      glfwSetMouseButtonCallback(window, mouse_callback);
      glfwSetScrollCallback(window, scroll_callback);
      glfwSetKeyCallback(window, key_callback);
      glfwSetCharCallback(window, char_callback);
      glfwSwapInterval(1);

      glfwMakeContextCurrent(prev_ctx);

#endif // OTTO_DEBUG_UI
    }

    static void draw_frame()
    {
#if OTTO_DEBUG_UI
      auto prev_win = glfwGetCurrentContext();
      glfwMakeContextCurrent(window);
      glfwPollEvents();

      if (!font_texture)
        create_device_objects();

      ImGuiIO& io = ImGui::GetIO();

      // Setup display size (every frame to accommodate for window resizing)
      int w, h;
      int display_w, display_h;
      glfwGetWindowSize(window, &w, &h);
      glfwGetFramebufferSize(window, &display_w, &display_h);
      io.DisplaySize = ImVec2((float)w, (float)h);
      io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

      // Setup time step
      double current_time =  glfwGetTime();
      io.DeltaTime = (float)(current_time - time);
      time = current_time;

      // Setup inputs
      // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
      if (io.WantMoveMouse)
      {
        glfwSetCursorPos(window, (double)io.MousePos.x, (double)io.MousePos.y);   // Set mouse position if requested by io.WantMoveMouse flag (used when io.NavMovesTrue is enabled by user and using directional navigation)
      }
      else
      {
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Get mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
      }

      for (int i = 0; i < 3; i++)
      {
        io.MouseDown[i] = mouse_pressed[i] || glfwGetMouseButton(window, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
        mouse_pressed[i] = false;
      }

      io.MouseWheel = mouse_wheel;
      mouse_wheel = 0.0f;

      // Hide OS mouse cursor if ImGui is drawing it
      glfwSetInputMode(window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

      // Start the frame
      ImGui::NewFrame();

      static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

      debug::ui::draw();

      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui::Render();
      imgui_renderdrawlists(ImGui::GetDrawData());
      glfwSwapBuffers(window);

      glfwMakeContextCurrent(prev_win);
#endif // OTTO_DEBUG_UI
    }

  private: 
#if OTTO_DEBUG_UI

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      ImGuiIO& io = ImGui::GetIO();
      if (action == GLFW_PRESS)
        io.KeysDown[key] = true;
      if (action == GLFW_RELEASE)
        io.KeysDown[key] = false;

      (void)mods; // Modifiers are not reliable across systems
      io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
      io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
      io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
      io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    }

    static const char* get_clipboard(void* user_data)
    {
      return glfwGetClipboardString((GLFWwindow*)user_data);
    }

    static void set_clipboard(void* user_data, const char* text)
    {
      glfwSetClipboardString((GLFWwindow*)user_data, text);
    }

    static void mouse_callback(GLFWwindow*, int button, int action, int /*mods*/)
    {
      if (action == GLFW_PRESS && button >= 0 && button < 3)
        mouse_pressed[button] = true;
    }

    static void scroll_callback(GLFWwindow*, double /*xoffset*/, double yoffset)
    {
      mouse_wheel += (float)yoffset; // Use fractional mouse wheel, 1.0 unit 5 lines.
    }

    static void char_callback(GLFWwindow*, unsigned int c)
    {
      ImGuiIO& io = ImGui::GetIO();
      if (c > 0 && c < 0x10000)
        io.AddInputCharacter((unsigned short)c);
    }

    static void imgui_renderdrawlists(ImDrawData* draw_data)
    {
      // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
      ImGuiIO& io = ImGui::GetIO();
      int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
      int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
      if (fb_width == 0 || fb_height == 0)
        return;
      draw_data->ScaleClipRects(io.DisplayFramebufferScale);

      // Backup GL state
      GLenum last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
      glActiveTexture(GL_TEXTURE0);
      GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
      GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
      GLint last_sampler; glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler);
      GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
      GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
      GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
      GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
      GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
      GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
      GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
      GLenum last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
      GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
      GLenum last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
      GLenum last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
      GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
      GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
      GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
      GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

      // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
      glEnable(GL_BLEND);
      glBlendEquation(GL_FUNC_ADD);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_SCISSOR_TEST);

      // Setup viewport, orthographic projection matrix
      glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
      const float ortho_projection[4][4] =
        {
          { 2.0f/io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
          { 0.0f,                  2.0f/-io.DisplaySize.y, 0.0f, 0.0f },
          { 0.0f,                  0.0f,                  -1.0f, 0.0f },
          {-1.0f,                  1.0f,                   0.0f, 1.0f },
        };

      glUseProgram(shader_handle);
      glUniform1i(attrib_location_tex, 0);
      glUniformMatrix4fv(attrib_location_proj, 1, GL_FALSE, &ortho_projection[0][0]);
      glBindVertexArray(vao_handle);
      glBindSampler(0, 0); // Rely on combined texture/sampler state.

      for (int n = 0; n < draw_data->CmdListsCount; n++)
      {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = 0;

        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
          const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
          if (pcmd->UserCallback)
          {
            pcmd->UserCallback(cmd_list, pcmd);
          }
          else
          {
            glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
            glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
            glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
          }
          idx_buffer_offset += pcmd->ElemCount;
        }
      }

      // Restore modified GL state
      glUseProgram(last_program);
      glBindTexture(GL_TEXTURE_2D, last_texture);
      glBindSampler(0, last_sampler);
      glActiveTexture(last_active_texture);
      glBindVertexArray(last_vertex_array);
      glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
      glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
      glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
      if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
      if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
      if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
      if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
      glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
      glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
    }

    static void create_device_objects()
    {
      // Backup GL state
      GLint last_texture, last_array_buffer, last_vertex_array;
      glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
      glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
      glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

      const GLchar *vertex_shader =
        "#version 330\n"
        "uniform mat4 ProjMtx;\n"
        "in vec2 Position;\n"
        "in vec2 UV;\n"
        "in vec4 Color;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "	Frag_UV = UV;\n"
        "	Frag_Color = Color;\n"
        "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

      const GLchar* fragment_shader =
        "#version 330\n"
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
        "}\n";

      shader_handle = glCreateProgram();
      vert_handle = glCreateShader(GL_VERTEX_SHADER);
      frag_handle = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(vert_handle, 1, &vertex_shader, 0);
      glShaderSource(frag_handle, 1, &fragment_shader, 0);
      glCompileShader(vert_handle);
      glCompileShader(frag_handle);
      glAttachShader(shader_handle, vert_handle);
      glAttachShader(shader_handle, frag_handle);
      glLinkProgram(shader_handle);

      attrib_location_tex = glGetUniformLocation(shader_handle, "Texture");
      attrib_location_proj = glGetUniformLocation(shader_handle, "ProjMtx");
      attrib_location_position = glGetAttribLocation(shader_handle, "Position");
      attrib_location_UV = glGetAttribLocation(shader_handle, "UV");
      attrib_location_color = glGetAttribLocation(shader_handle, "Color");

      glGenBuffers(1, &vbo_handle);
      glGenBuffers(1, &elements_handle);

      glGenVertexArrays(1, &vao_handle);
      glBindVertexArray(vao_handle);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
      glEnableVertexAttribArray(attrib_location_position);
      glEnableVertexAttribArray(attrib_location_UV);
      glEnableVertexAttribArray(attrib_location_color);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
      glVertexAttribPointer(attrib_location_position, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
      glVertexAttribPointer(attrib_location_UV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
      glVertexAttribPointer(attrib_location_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

      create_fonts_texture();

      // Restore modified GL state
      glBindTexture(GL_TEXTURE_2D, last_texture);
      glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
      glBindVertexArray(last_vertex_array);
    }

    static void create_fonts_texture()
    {
      // Build texture atlas
      ImGuiIO& io = ImGui::GetIO();
      unsigned char* pixels;
      int width, height;
      // Load as RGBA 32-bits (75% of the memory is wasted, but default font is
      // so small) because it is more likely to be compatible with user's
      // existing shaders. If your ImTextureId represent a higher-level concept
      // than just a GL texture id, consider calling GetTexDataAsAlpha8()
      // instead to save on GPU memory.
      io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

      // Upload texture to graphics system
      GLint last_texture;
      glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
      glGenTextures(1, &font_texture);
      glBindTexture(GL_TEXTURE_2D, font_texture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

      // Store our identifier
      io.Fonts->TexID = (void *)(intptr_t)font_texture;

      // Cleanup (don't clear the input data if you want to append new fonts later)
      io.Fonts->ClearInputData();
      io.Fonts->ClearTexData();

      // Restore state
      glBindTexture(GL_TEXTURE_2D, last_texture);
    }

#endif // OTTO_DEBUG_UI

  };


  void error_callback(int error, const char* description) {
    LOGF << description;
  }

  void MainUI::mainRoutine() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
      LOGE << ("Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    DbgData::init();

    GLFWwindow* window = glfwCreateWindow(vg::WIDTH, vg::HEIGHT, "OTTO", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
#if !OTTO_DEBUG_UI
    gl3wInit();
#endif

    glfwSetWindowAspectRatio(window, 4, 3);
    glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetKeyCallback(window, key);

    NVGcontext* vg = OTTO_NVG_CREATE(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
      printf("Could not init nanovg.\n");
      return;
    }

    vg::Canvas canvas(vg, vg::WIDTH, vg::HEIGHT);
    vg::initUtils(canvas);

    LOGD << "Opening GLFW Window";

    struct DbgInfo : debug::Info {

      float FPS_limit = 60.f;
      util::ringbuffer<std::pair<float, float>, 512> fps_history;

      void draw() override {
        ImGui::Begin("Graphics");
        ImGui::Text("FPS limit");
        ImGui::SliderFloat("", &FPS_limit, 0.f, 300.f);
        auto fps = fps_history.front();
        ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / fps.first, fps.first);
        ImGui::Text("FPS History");
        ImGui::PlotLines("", [] (void* self, int n) {
            return ((DbgInfo*)self)->fps_history[n].first;
          }, this, fps_history.size(), 0, nullptr, 0, 120, ImVec2(0, 80));
        ImGui::Text("Percentage of time used rendering");
        ImGui::PlotLines("", [] (void* self, int n) {
            auto&& el = ((DbgInfo*)self)->fps_history[n];
            return el.first / el.second * 100.f;
          }, this, fps_history.size(), 0, nullptr, 0, 0, ImVec2(0, 80));
        ImGui::End();
      }
    } info;

    glfwSetTime(0);
    double prevt = glfwGetTime();

    double mx, my, t, dt, spent;
    while (!glfwWindowShouldClose(window) && global::running())
    {
      int winWidth, winHeight;
      int fbWidth, fbHeight;
      float pxRatio;
      float scale;

      t = glfwGetTime();
      dt = t - prevt;
      prevt = t;

      glfwGetCursorPos(window, &mx, &my);
      glfwGetWindowSize(window, &winWidth, &winHeight);
      glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
      // Calculate pixel ration for hi-dpi devices.
      pxRatio = (float)fbWidth / (float)winWidth;
      scale = std::min((float)winWidth/(float)vg::WIDTH, (float)winHeight/(float)vg::HEIGHT);
      canvas.setSize(winWidth, winHeight);

      // Update and render
      glViewport(0, 0, fbWidth, fbHeight);

      glClearColor(0,0,0,0);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);

      canvas.clearColor(vg::Colours::Black);
      canvas.begineFrame(winWidth, winHeight);

      canvas.scale(scale, scale);
      draw(canvas);

      canvas.endFrame();

      glEnable(GL_DEPTH_TEST);

      glfwSwapBuffers(window);

      glfwPollEvents();

      DbgData::draw_frame();

      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(
        std::chrono::milliseconds(int(1000 / info.FPS_limit - spent*1000)));

      info.fps_history.push({ImGui::GetIO().Framerate, 1.f / spent});
    }

    OTTO_NVG_DELETE(vg);

    glfwTerminate();

    global::exit(global::ErrorCode::ui_closed);
  }

} // otto::ui
