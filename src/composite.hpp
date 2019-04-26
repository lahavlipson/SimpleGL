#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "mesh.hpp"

class Composite {
public:
    Composite(std::initializer_list<Mesh_id> l) : ids(l) {}
    ~Composite() {
        hide();
    }

    void hide() {
        for (auto& x : ids) {
            x.mesh_ptr->hide_instance(x.id);
        }
    }

    void show() {
        for (auto& x : ids) {
            x.mesh_ptr->show_instance(x.id);
        }
    }

    void set_color(glm::vec3 c) {
        for (auto& x : ids) {
            x.mesh_ptr->set_color(x.id, c);
        }
    }

    void set_model(glm::mat4 m) {
        T.model = m;
        for (auto& x : ids) {
            x.mesh_ptr->set_model(x.id, m);
        }
    }

    void reset_model() {
        T = transformation();
        for (auto& x : ids) {
            x.mesh_ptr->reset_model(x.id);
        }
    }

    void translate(glm::vec3 translation) {
        T.translation = glm::translate(T.translation, translation);
        for (auto& x : ids) {
            x.mesh_ptr->translate(x.id, translation);
        }
    }

    void set_translation(const glm::vec3 translation) {
        T.translation = glm::translate(translation);
        for (auto& x : ids) {
            x.mesh_ptr->set_translation(x.id, translation);
        }
    }

    void scale(glm::vec3 factor) {
        T.scaling = glm::scale(T.scaling, factor);
        for (auto& x : ids) {
            x.mesh_ptr->scale(x.id, factor);
        }
    }

    void set_scale(const glm::vec3 factor) {
        T.scaling = glm::scale(factor);
        for (auto& x : ids) {
            x.mesh_ptr->set_scale(x.id, factor);
        }
    }

    void rotate(float angle, glm::vec3 axis) {
        T.rotation = glm::rotate(T.rotation, angle, axis);
        for (auto& x : ids) {
            x.mesh_ptr->rotate(x.id, angle, axis);
        }
    }

    void set_rotation(const float angle, glm::vec3 axis) {
        T.rotation = glm::rotate(angle, axis);
        for (auto& x : ids) {
            x.mesh_ptr->set_rotation(x.id, angle, axis);
        }
    }

    glm::vec3 get_loc() {
        glm::mat4 model = T.get_model();
        return glm::vec3(model[3]);
    }

private:
    transformation T;
    std::vector<Mesh_id> ids;
};

// comp_id: represents the id to a Composite object for future manipulation.
class Comp_id {
public:
    Comp_id(Composite *comp_p): comp_ptr(comp_p) {}
    ~Comp_id() {}

    // Methods for manipulating the Composite object.
    void remove() {
        hide();
    }

    void hide() {
        comp_ptr->hide();
    }

    void show() {
        comp_ptr->show();
    }

    void set_color(glm::vec3 c) {
        comp_ptr->set_color(c);
    }

    void set_model(glm::mat4 m) {
        comp_ptr->set_model(m);
    }

    void reset_model() {
        comp_ptr->reset_model();
    }

    void translate(glm::vec3 translation) {
        comp_ptr->translate(translation);
    }

    void set_translation(const glm::vec3 translation) {
        comp_ptr->set_translation(translation);
    }

    void scale(glm::vec3 factor) {
        comp_ptr->scale(factor);
    }

    void scale(double factor) {
        comp_ptr->scale({factor, factor, factor});
    }

    void set_scale(const glm::vec3 factor) {
        comp_ptr->set_scale(factor);
    }

    void set_scale(const double factor) {
        comp_ptr->set_scale({factor, factor, factor});
    }

    void rotate(float angle, glm::vec3 axis) {
        comp_ptr->rotate(angle, axis);
    }

    void set_rotation(const float angle, glm::vec3 axis) {
        comp_ptr->set_rotation(angle, axis);
    }

    glm::vec3 get_loc() {
        return comp_ptr->get_loc();
    }

    Composite *comp_ptr;
};

#endif