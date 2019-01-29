#ifndef CACHE_CONTROLLER_HPP
#define CACHE_CONTROLLER_HPP
#include "Controller.hpp"
#include "raylib.h"
#include <entt/entt.hpp>


namespace Controllers
{
    class CacheController : public Controller<CacheController>
    {
    public:
        entt::resource_cache<Image>& getImageCache(){ return imageCache; }
        ~CacheController()
        {
            imageCache.clear();
            fontCache.clear();
        }
    private:
        entt::resource_cache<sf::Image> imageCache;
    };
}

#endif