#ifndef EDITOR_SYSTEM_HPP
#define EDITOR_SYSTEM_HPP
#include <entt/entt.hpp>

namespace Systems {
class EditorSystem {
  public:
    EditorSystem(){};
    void Update(entt::registry<> &registry);
    void Shutdown(){};
  private:
    int selectedId = -1;
};
} // namespace Systems
  // Systems

#endif
