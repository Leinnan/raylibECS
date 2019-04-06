#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include "components/Actor.hpp"
#include "components/BillboardRenderer.hpp"
#include "components/CameraTarget.hpp"
#include "components/Collisions.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/DestroyAfterTime.hpp"
#include "components/MeshRenderer.hpp"
#include "components/Missile.hpp"
#include "components/Patrol.hpp"
#include "components/PlayerInput.hpp"
#include "components/RotatingObject.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"

#include <string>
#include <entt/entt.hpp>
#include <json.hpp>

using nlohmann::json;

namespace Components {

    void to_json(json& j, const Components::MeshRenderer& m);
    void from_json(const json& j, Components::MeshRenderer& m);

    void to_json(json& j, const Components::Transform& t);
    void from_json(const json& j, Components::Transform& t);

    void to_json(json& j, const Components::CameraTarget& t);
    void from_json(const json& j, Components::CameraTarget& t);

    void to_json(json& j, const Components::PlayerInput& t);
    void from_json(const json& j, Components::PlayerInput& t);

    void to_json(json& j, const Components::Velocity& t);
    void from_json(const json& j, Components::Velocity& t);

    void to_json(json& j, const Components::Actor& t);
    void from_json(const json& j, Components::Actor& t);

    void to_json(json& j, const Components::RotatingObject& t);
    void from_json(const json& j, Components::RotatingObject& t);

    void to_json(json& j, const Components::Missile& t);
    void from_json(const json& j, Components::Missile& t);

    void to_json(json& j, const Components::DestroyAfterTime& t);
    void from_json(const json& j, Components::DestroyAfterTime& t);

    void to_json(json& j, const Components::Patrol& t);
    void from_json(const json& j, Components::Patrol& t);
};


#endif
