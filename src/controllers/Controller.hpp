#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

namespace Controllers {
template <typename T> class Controller {
  public:
    static T &getInstance() {
        static T newInstance;

        return newInstance;
    }
    T *operator->() { return getInstance(); }
    const T *operator->() const { return getInstance(); }
    T &operator*() { return *getInstance(); }
    const T &operator*() const { return *getInstance(); }

  protected:
    Controller() {}
};
} // namespace Controllers
  // Controllers
#endif