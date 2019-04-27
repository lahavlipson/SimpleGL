#ifndef BASE_OBJ_HPP
#define BASE_OBJ_HPP

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
    bool hidden = false;    // default to show

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

// components: contains ObjIds that form the Composite object.
class ObjId;
typedef std::vector<ObjId> components;

class BaseObj {
public:
    virtual ~BaseObj() {}

    virtual bool is_composite() { return false; }

    virtual void bindVAO() const {}

    virtual int get_v_size() const { return 0; }

    virtual int add_instance(const color col, const components comp = {}) {
        render_infos.push_back(render_info(col, transformation()));
        return render_infos.size() - 1;
    }

    virtual int duplicate_instance(const int i) {
        render_infos.push_back(render_infos[i]);
        return render_infos.size() - 1;
    }

    virtual void hide_all() {
        for (auto& info : render_infos) {
            info.second.hidden = true;
        }
    }

    virtual void hide_instance(const int i) {
        render_infos[i].second.hidden = true;
    }

    virtual void show_all() {
        for (auto& info : render_infos) {
            info.second.hidden = false;
        }
    }

    virtual void show_instance(const int i) {
        render_infos[i].second.hidden = false;
    }

    virtual void set_color(const int i, const color c) {
        render_infos[i].first = c;
    }

    virtual void set_model(const int i, const glm::mat4 m) {
        render_infos[i].second.model = m;
    }
    
    virtual void reset_model(const int i) {
        render_infos[i].second = transformation();
    }
    
    virtual void rotate(const int i, const float angle, const glm::vec3 axis) {
        render_infos[i].second.rotation = glm::rotate(
            render_infos[i].second.rotation, glm::radians(angle), axis);
    }

    virtual void set_rotation(
        const int i, const float angle, const glm::vec3 axis) {
        render_infos[i].second.rotation = glm::rotate(glm::radians(angle), axis);
    }

    virtual void translate(const int i, const glm::vec3 translation) {
        render_infos[i].second.translation = glm::translate(
            render_infos[i].second.translation, translation);
    }

    virtual void set_translation(const int i, const glm::vec3 translation) {
        render_infos[i].second.translation = glm::translate(translation);
    }
    
    virtual void scale(const int i, const glm::vec3 scale) {
        render_infos[i].second.scaling = glm::scale(
            render_infos[i].second.scaling, scale);
    }

    virtual void set_scale(const int i, const glm::vec3 scale) {
        render_infos[i].second.scaling = glm::scale(scale);
    }
    
    inline glm::vec3 get_loc(const int i) const {
        // This gets the location from the model matrix, as explained here:
        // https://stackoverflow.com/a/19448411
        return glm::vec3(render_infos[i].second.get_model()[3]);
    }

    inline std::vector<render_info> obj_infos() const {
        return render_infos;
    }

    inline int count() const {
        return render_infos.size();
    }

protected:
    std::vector<render_info> render_infos;
};

// ObjId: represents the id to a specific instance of BaseObj
// to modify its model matrices and color.
class ObjId {
public:
    ObjId(int idx, BaseObj *obj_p): idx(idx), obj_ptr(obj_p) {}
    ~ObjId() {}

    // Duplicates the current instance and returns the id to the copy.
    ObjId duplicate() {
        return ObjId(obj_ptr->duplicate_instance(idx), obj_ptr);
    }

    // Methods for manipulating mesh instances.
    void remove() {
        hide();
    }

    void hide() {
        obj_ptr->hide_instance(idx);
    }

    void show() {
        obj_ptr->show_instance(idx);
    }

    void set_color(glm::vec3 c) {
        obj_ptr->set_color(idx, c);
    }

    void set_model(glm::mat4 m) {
        obj_ptr->set_model(idx, m);
    }

    void reset_model() {
        obj_ptr->reset_model(idx);
    }

    void translate(glm::vec3 translation) {
        obj_ptr->translate(idx, translation);
    }

    void set_translation(const glm::vec3 translation) {
        obj_ptr->set_translation(idx, translation);
    }

    void scale(glm::vec3 factor) {
        obj_ptr->scale(idx, factor);
    }

    void scale(double factor) {
        obj_ptr->scale(idx, {factor, factor, factor});
    }

    void set_scale(const glm::vec3 factor) {
        obj_ptr->set_scale(idx, factor);
    }

    void set_scale(const double factor) {
        obj_ptr->set_scale(idx, {factor, factor, factor});
    }

    void rotate(float angle, glm::vec3 axis) {
        obj_ptr->rotate(idx, angle, axis);
    }

    void set_rotation(const float angle, glm::vec3 axis) {
        obj_ptr->set_rotation(idx, angle, axis);
    }

    glm::vec3 get_loc() {
        return obj_ptr->get_loc(idx);
    }

    bool operator==(const ObjId& b) const {
        return idx == b.idx && obj_ptr == b.obj_ptr;
    }

    int idx;
    BaseObj *obj_ptr;
};

namespace std {
    template <>
    struct hash<ObjId> {
        std::size_t operator()(const ObjId& k) const {
            using std::size_t;
            using std::hash;
            using std::string;

            return ((hash<int>()(k.idx)
                     ^ (hash<BaseObj *>()(k.obj_ptr) << 1)) >> 1);
        }
    };
}

#endif
