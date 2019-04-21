#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

struct transformation {
    glm::mat4 model;        // the overall model matrix
    glm::mat4 rotation;     // rotation matrix
    glm::mat4 translation;  // translation matrix
    glm::mat4 scaling;      // scaling matrix

    glm::mat4 get_model() const {
        return model * translation * rotation * scaling;
    }
    // assumption here is that the user will not use other helper methods
    // if they are setting the model matrix themselves. 
};

// color: use vec3 as rgb color.
typedef glm::vec3 color;
// render_info: contains color and transformation for each instance
// and is used in the render loop in Scene class.
typedef std::pair<color, transformation> render_info;

class Mesh {
public:

    // When first initializing, generate buffers and store the vertices data.
    Mesh(std::vector<double>& vertices, const color col)
        : v_size(vertices.size()) {

        add_instance(col);

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
    
    inline int add_instance(const color col) {
        // what if user adds a bunch of instances but doesn't transform them?
        render_infos.push_back(render_info(col, transformation()));
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
        render_infos[i].second.model = m;
    }
    
    inline void reset_model(const int i) {
        render_infos[i].second = transformation();
    }
    
    inline void rotate(const int i, const float angle, const glm::vec3 axis) {
        render_infos[i].second.rotation = glm::rotate(
            render_infos[i].second.rotation, glm::radians(angle), axis);
    }

    inline void set_rotation(const int i, const float angle, const glm::vec3 axis) {
        render_infos[i].second.rotation = glm::rotate(glm::radians(angle), axis);
    }

    inline void translate(const int i, const glm::vec3 translation) {
        render_infos[i].second.translation = glm::translate(
            render_infos[i].second.translation, translation);
    }

    inline void set_translation(const int i, const glm::vec3 translation) {
        render_infos[i].second.translation = glm::translate(translation);
    }
    
    inline void scale(const int i, const glm::vec3 scale) {
        render_infos[i].second.scaling = glm::scale(
            render_infos[i].second.scaling, scale);
    }

    inline void set_scale(const int i, const glm::vec3 scale) {
        render_infos[i].second.scaling = glm::scale(scale);
    }
    
    inline glm::vec3 get_loc(const int i) const {
        // This gets the location from the model matrix, as explained here:
        // https://stackoverflow.com/a/19448411
        glm::mat4 model = render_infos[i].second.get_model();
        return glm::vec3(model[3]);
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
