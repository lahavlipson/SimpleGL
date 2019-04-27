#ifndef MESH_HPP
#define MESH_HPP

#include "base_obj.hpp"

class Mesh : public BaseObj {
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

    // Delete the buffers on destrunction.
    ~Mesh() {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(1, &vbo_id);
    }

    inline void bindVAO() const override {
        glBindVertexArray(vao_id);
    }

    inline int get_v_size() const override {
        return v_size;
    }

private:
    unsigned int vao_id, vbo_id;
    int v_size;
};

#endif
