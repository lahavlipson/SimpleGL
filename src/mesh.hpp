#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// render_info: contains color and model matrix for each instance
// and is used in the render loop in Scene class.
typedef std::pair<glm::vec3, glm::mat4> render_info;

typedef glm::vec3 color;

class Mesh {
public:

    // When first initializing, generate buffers and store the vertices data.
    Mesh(std::vector<double>& vertices, const color col, const glm::mat4 model)
        : v_size(vertices.size()) {

        add_instance(col, model);

        glGenVertexArrays(1, &vao_id);
        glBindVertexArray(vao_id);
        
        glGenBuffers(1, &vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        glBufferData(GL_ARRAY_BUFFER, v_size*sizeof(double), 
                     vertices.data(), GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(
            0, 3, GL_DOUBLE, GL_FALSE, 6*sizeof(double), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 
                              6*sizeof(double), (void*)(3*sizeof(double)));
        glEnableVertexAttribArray(1);  
    }
    
    inline int add_instance(const color col, const glm::mat4 model) {
        render_infos.push_back(render_info(col, model));
        return render_infos.size() - 1;
    }

    inline void bindVAO() const {
        glBindVertexArray(vao_id);
    }

    inline std::vector<render_info>& mesh_infos() {
        return render_infos;
    }

    inline int get_v_size() const {
        return v_size;
    }

    // Methods for manipulating a specific instance of this Mesh.
    inline void set_color(const int i, const color c) {
        render_infos[i].first = c;
    }

    inline void set_model(const int i, const glm::mat4 m) {
        render_infos[i].second = m;
    }
    
    inline void reset_model(const int i) {
        render_infos[i].second = glm::mat4(1.0f);
    }
    
    inline void rotate(const int i, const float angle, const glm::vec3 axis) {
        render_infos[i].second = glm::rotate(
            render_infos[i].second, glm::radians(angle), axis);
    }

    inline void translate(const int i, const glm::vec3 translation) {
        render_infos[i].second = glm::translate(
            render_infos[i].second, translation);
    }
    
    inline void scale(const int i, const glm::vec3 scale) {
        render_infos[i].second = glm::scale(render_infos[i].second, scale);
    }
    
    // Delete the buffers on destrunction.
    ~Mesh(){
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(1, &vbo_id);
    }

private:
    unsigned int vao_id, vbo_id;
    int v_size;
    std::vector<render_info> render_infos;
};

#endif
