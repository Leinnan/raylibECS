//
// Created by piotr on 06.04.19.
//

#include "JsonParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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

void Components::from_json(const json &j, Components::Missile &t) {
    t.angle = j.at("angle").get<float>();
    t.speed = j.at("speed").get<float>();
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

void Components::to_json(json &j, const Components::Collisions &t) {
    json collisions = json::array();
    for(const auto& collision : t.collisions)
    {
        collisions.push_back({{"sizeX", collision.size.x}, {"sizeY", collision.size.y}, {"sizeZ", collision.size.z},
                              {"offsetX", collision.offset.x}, {"offsetY", collision.offset.y}, {"offsetZ", collision.offset.z}});
    }
    j = json{{"type", "Collisions"},{"collisions",collisions}};

}

void Components::from_json(const json &j, Components::Collisions &t) {
    json collisions = j.at("collisions");

    if(!collisions.is_array())
        return;

    for(json& point : collisions)
        t.collisions.push_back(Components::Collision(
                Vector3{point.at("offsetX").get<float>(), point.at("offsetY").get<float>(), point.at("offsetZ").get<float>()},
                Vector3{point.at("sizeX").get<float>(), point.at("sizeY").get<float>(), point.at("sizeZ").get<float>()}));
}

void Components::parseToFile(entt::registry<> &registry, const char *filename) {
    nlohmann::json jsonReader;

    registry.each([&](auto entity) {
        json entityObject;
        if(registry.has<Components::MeshRenderer>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::MeshRenderer>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::CameraTarget>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::CameraTarget>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Transform>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Transform>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::PlayerInput>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::PlayerInput>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Velocity>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Velocity>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Actor>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Actor>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::RotatingObject>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::RotatingObject>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Missile>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Missile>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::DestroyAfterTime>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::DestroyAfterTime>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Patrol>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Patrol>(entity));
            entityObject.push_back(component);
        }
        if(registry.has<Components::Collisions>(entity))
        {
            json component;
            Components::to_json(component,registry.get<Components::Collisions>(entity));
            entityObject.push_back(component);
        }
        jsonReader.push_back(entityObject);
    });

    std::ofstream o;
    o.open(filename, std::ios::trunc);
    if(o.is_open())
    {
        o << jsonReader << std::endl;
        o.close();
    }
    else
    {
        std::cout << "CANNOT OPEN FILE\n";
    }
}

void Components::readFromFile(entt::registry<> &registry, const char *filename) {

    nlohmann::json jsonReader;
    std::ifstream file(filename);
    file >> jsonReader;

    for (nlohmann::json &object : jsonReader)
    {
        if(!object.is_array())
            continue;

        auto entity = registry.create();

        for(nlohmann::json &component : object)
        {
            const std::string type = component.at("type").get<std::string>();

            if(type.compare("MeshRenderer") == 0)
            {
                registry.assign<Components::MeshRenderer>(entity, component.get<Components::MeshRenderer>());
            }
            else if(type.compare("Transform") == 0)
            {
                registry.assign<Components::Transform>(entity, component.get<Components::Transform>());
            }
            else if(type.compare("CameraTarget") == 0)
            {
                registry.assign<Components::CameraTarget>(entity, component.get<Components::CameraTarget>());
            }
            else if(type.compare("PlayerInput") == 0)
            {
                registry.assign<Components::PlayerInput>(entity, component.get<Components::PlayerInput>());
            }
            else if(type.compare("Velocity") == 0)
            {
                registry.assign<Components::Velocity>(entity, component.get<Components::Velocity>());
            }
            else if(type.compare("Actor") == 0)
            {
                registry.assign<Components::Actor>(entity, component.get<Components::Actor>());
            }
            else if(type.compare("RotatingObject") == 0)
            {
                registry.assign<Components::RotatingObject>(entity, component.get<Components::RotatingObject>());
            }
            else if(type.compare("Missile") == 0)
            {
                registry.assign<Components::Missile>(entity, component.get<Components::Missile>());
            }
            else if(type.compare("DestroyAfterTime") == 0)
            {
                registry.assign<Components::DestroyAfterTime>(entity, component.get<Components::DestroyAfterTime>());
            }
            else if(type.compare("Patrol") == 0)
            {
                registry.assign<Components::Patrol>(entity, component.get<Components::Patrol>());
            }
            else if(type.compare("Collisions") == 0)
            {
                registry.assign<Components::Collisions>(entity, component.get<Components::Collisions>());
            }
        }
    }
}
