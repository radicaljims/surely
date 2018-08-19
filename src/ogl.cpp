#include "ogl.h"
#include <OpenGL/gl3.h>

#include <string>
#include <utility>

namespace {

  GLuint program_id = 0;
  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint ibo = 0;
  GLint unif = 0;

  using Status = std::pair<int, std::string>;

  std::string read_program(std::string path) {
    return "";
  }

  Status compile_program(GLuint program_id, std::string text, GLenum shader_type) {

    GLuint shader = glCreateShader(shader_type);

    const char* source = text.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    auto compiled_ok = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled_ok);

    if (compiled_ok != GL_TRUE) {
      return std::make_pair(-1, "Failed to compile shader");
    }

    glAttachShader(program_id, shader);

    return std::make_pair(shader, "");
  }

  // Caller's responsibility to call glCreateProgram and glLinkProgram
  Status load_program(GLuint program_id, std::string path, GLenum shader_type) {

    std::string text = read_program(path);

    return compile_program(program_id, text, shader_type);
  }

}

namespace ogl {

  void initialize() {

    // temp hack until switch to vao's for real
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //VBO data
    GLfloat vertexData[] =
      {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f,  0.5f
      };

    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };

    //Create VBO
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

    //Create IBO
    glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );

    program_id = glCreateProgram();

    std::string vertex_shader = "#version 400\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }";
    std::string fragment_shader = "#version 400\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }";

    compile_program(program_id, vertex_shader, GL_VERTEX_SHADER);
    compile_program(program_id, fragment_shader, GL_FRAGMENT_SHADER);

    glLinkProgram(program_id);

    unif = glGetAttribLocation(program_id, "LVertexPos2D");

  }

  void render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 0.0, 1.0);

    //Bind program
    glUseProgram( program_id );

    //Enable vertex position
    glEnableVertexAttribArray(unif);

    //Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(unif, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo );
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    //Disable vertex position
    glDisableVertexAttribArray(unif);

    //Unbind program
    glUseProgram(0);

  }

}
