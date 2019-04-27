#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "base_obj.hpp"

class Composite : public BaseObj {
public:
    Composite() {}
    ~Composite() {
        hide_all();
    }

    //=================Overriding Base class methods======================//
    bool is_composite() override { return true; }

    int add_instance(const color col, const components comp = {}) override {
        comp_infos.push_back(components(comp));
        return BaseObj::add_instance(col);
    }

    int duplicate_instance(const int i) override {
        components ith_comp;
        for (auto& id : comp_infos[i]) {
            ith_comp.push_back(id.duplicate());
        }
        comp_infos.push_back(ith_comp);
        return BaseObj::duplicate_instance(i);
    }

    void hide_all() override {
        BaseObj::hide_all();
        for (auto& info : comp_infos) {
            for (auto& id : info) {
                id.hide();
            }
        }
    }

    void hide_instance(const int i) override {
        BaseObj::hide_instance(i);
        for (auto& id : comp_infos[i]) {
            id.hide();
        }
    }

    void show_all() override {
        BaseObj::show_all();
        for (auto& info : comp_infos) {
            for (auto& id : info) {
                id.show();
            }
        }
    }

    void show_instance(const int i) override {
        BaseObj::show_instance(i);
        for (auto& id : comp_infos[i]) {
            id.show();
        }
    }

    void set_color(const int i, const color c) override {
        BaseObj::set_color(i, c);
        for (auto& id : comp_infos[i]) {
            id.set_color(c);
        }
    }

    void set_model(const int i, const glm::mat4 m) override {
        BaseObj::set_model(i, m);
        for (auto& id : comp_infos[i]) {
            id.set_model(m);
        }
    }

    void reset_model(const int i) override {
        BaseObj::reset_model(i);
        for (auto& id : comp_infos[i]) {
            id.reset_model();
        }
    }

    void rotate(const int i, const float angle, const glm::vec3 axis) override {
        BaseObj::rotate(i, angle, axis);
        for (auto& id : comp_infos[i]) {
            id.rotate(angle, axis);
        }
    }

    void set_rotation(
        const int i, const float angle, const glm::vec3 axis) override {
        BaseObj::set_rotation(i, angle, axis);
        for (auto& id : comp_infos[i]) {
            id.set_rotation(angle, axis);
        }
    }

    void translate(const int i, const glm::vec3 translation) override {
        BaseObj::translate(i, translation);
        for (auto& id : comp_infos[i]) {
            id.translate(translation);
        }
    }

    void set_translation(const int i, const glm::vec3 translation) override {
        BaseObj::set_translation(i, translation);
        for (auto& id : comp_infos[i]) {
            id.set_translation(translation);
        }
    }

    void scale(const int i, const glm::vec3 scale) override {
        BaseObj::scale(i, scale);
        for (auto& id : comp_infos[i]) {
            id.scale(scale);
        }
    }

    void set_scale(const int i, const glm::vec3 scale) override {
        BaseObj::scale(i, scale);
        for (auto& id : comp_infos[i]) {
            id.set_scale(scale);
        }
    }

private:
    std::vector<components> comp_infos;
};

#endif