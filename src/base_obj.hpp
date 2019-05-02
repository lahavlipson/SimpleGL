#ifndef BASE_OBJ_HPP
#define BASE_OBJ_HPP

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

struct transformation {
    glm::mat4 model;        // the overall model matrix
    glm::mat4 rotation;     // rotation matrix
    glm::mat4 translation;  // translation matrix
    glm::mat4 scaling;      // scaling matrix
    bool hidden = false;    // default to show

    // assumption here is that the user will not use other helper methods
    // if they are setting the model matrix themselves. 
    glm::mat4 get_model() const {
        return model * translation * rotation * scaling;
    }
};

inline std::ostream& operator<<(std::ostream& os, transformation& t) {
    return os << "\n\tmodel: \n\t" << glm::to_string(t.model) 
              << "\n\trotation: \n\t" << glm::to_string(t.rotation)
              << "\n\ttranslation: \n\t" << glm::to_string(t.translation) 
              << "\n\tscaling: \n\t" << glm::to_string(t.scaling) 
              << "\n\thidden: " << t.hidden; 
}

class color : public glm::vec3 {
public:
    using glm::vec3::vec3;

    color(const int r, const int g, const int b):glm::vec3(r/255.0,g/255.0,b/255.0){}
    color(const int hexValue):glm::vec3(((hexValue >> 16) & 0xFF) / 255.0,
                                    ((hexValue >> 8) & 0xFF) / 255.0,
                                    ((hexValue) & 0xFF) / 255.0){}
};

inline std::ostream& operator<<(std::ostream& os, color& c) {
    return os << glm::to_string(glm::vec3(c));
}

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

    inline render_info get_instance_info(const int i) const {
        return render_infos[i];
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
    void hide() {
        obj_ptr->hide_instance(idx);
    }

    void show() {
        obj_ptr->show_instance(idx);
    }

    void set_color(color c) {
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
