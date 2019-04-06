//
// Created by piotr on 06.04.19.
//

#include "JsonParser.hpp"

void Components::to_json(json &j, const Components::MeshRenderer &m) {
    j = json{{"type", "MeshRenderer"}, {"modelPath", m.modelPath}, {"diffusePath", m.diffusePath}, {"scale", m.scale}};
}

void Components::from_json(const json &j, Components::MeshRenderer &m) {
    j.at("modelPath").get_to(m.modelPath);
    j.at("diffusePath").get_to(m.diffusePath);
    j.at("scale").get_to(m.scale);
}

void Components::to_json(json &j, const Components::Transform &t) {
    j = json{{"type", "Transform"}, {"posX", t.pos.x}, {"posY", t.pos.y}, {"posZ", t.pos.z}, {"angle", t.angle}};
}

void Components::from_json(const json &j, Components::Transform &t) {
    t.pos = {j.at("posX").get<float>(),
             j.at("posY").get<float>(),
             j.at("posZ").get<float>()};
    j.at("angle").get_to(t.angle);
}

void Components::to_json(json &j, const Components::CameraTarget &t) {
    j = json{{"type", "CameraTarget"}, {"offsetX", t.offset.x}, {"offsetY", t.offset.y}, {"offsetZ", t.offset.z}};
}

void Components::from_json(const json &j, Components::CameraTarget &t) {
    t.offset = {j.at("offsetX").get<float>(),
                j.at("offsetY").get<float>(),
                j.at("offsetZ").get<float>()};
}

void Components::to_json(json &j, const Components::PlayerInput &t) {
    j = json{{"type", "PlayerInput"}};
}

void Components::from_json(const json &j, Components::PlayerInput &t) {}

void Components::to_json(json &j, const Components::Velocity &t) {
    j = json{{"type", "Velocity"}};
}

void Components::from_json(const json &j, Components::Velocity &t) {
}

void Components::to_json(json &j, const Components::Actor &t) {
    j = json{{"type", "Actor"}};
}

void Components::from_json(const json &j, Components::Actor &t) {
}

void Components::to_json(json &j, const Components::RotatingObject &t) {
    j = json{{"type", "RotatingObject"},{"rotationSpeed",t.rotationSpeed}};
}

void Components::from_json(const json &j, Components::RotatingObject &t) {
    t.rotationSpeed = j.at("rotationSpeed").get<float>();
}

void Components::to_json(json &j, const Components::Missile &t) {
    j = json{{"type", "Missile"},{"angle",t.angle},{"speed",t.speed}};

}

void Components::to_json(json &j, const Components::DestroyAfterTime &t) {
    j = json{{"type", "DestroyAfterTime"},{"timeLeft",t.timeLeft}};
}

void Components::from_json(const json &j, Components::DestroyAfterTime &t) {
    t.timeLeft = j.at("timeLeft").get<float>();
}

void Components::to_json(json &j, const Components::Patrol &t) {
    json points = json::array();
    for(const auto& point : t.points)
    {
        points.push_back({{"x", point.x}, {"y", point.y}, {"z", point.z}});
    }
    j = json{{"type", "Patrol"},{"waitTime",t.waitTime},{"points",points}};
}

void Components::from_json(const json &j, Components::Patrol &t) {
    t.waitTime = j.at("waitTime");
    json pointsArray = j.at("points");

    if(!pointsArray.is_array())
        return;

    for(json& point : pointsArray)
        t.points.push_back({point.at("x").get<float>(),
                            point.at("y").get<float>(),
                            point.at("z").get<float>()});

}
