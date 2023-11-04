#ifndef CAT_HPP_
#define CAT_HPP_

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include <unordered_map>
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 position;
};

class Cat {
public:
  void create(GLuint program);
  void loadModelFromFile(std::string_view path);
  void paint();
  void destroy();

private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  GLint m_modelMatrixLocation{};
  GLint m_colorLocation{};
};

#endif