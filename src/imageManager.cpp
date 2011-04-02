#include <sys/stat.h>
#include "imageManager.h"
#include "log.h"

ImageManager::ImageManager() {
  std::string dirs[] = { "res", "../res" };
  for (size_t i = 0; i < sizeof(dirs); i++) {
    struct stat st;
    if (stat(dirs[i].c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
      resDir = dirs[i];
      break;
    }
  }
}

ImageManager::~ImageManager() {
  std::map<std::string, sf::Image*>::iterator i;
  for (i = pool.begin(); i != pool.end(); i++)
    delete i->second;
}

sf::Image *ImageManager::get(std::string name) {
  sf::Image *value = pool[name];
  if (value == NULL) {
    sf::Image *image = new sf::Image();
    if (!image->LoadFromFile(nameToFile(name))) {
      log("Error: Loading of `" + name + "' failed");
      return NULL;
    }

    image->SetSmooth(false);
    pool[name] = image;
    return image;
  }

  return pool[name];
}

std::string ImageManager::nameToFile(std::string name) {
  return resDir + "/" + name + ".png";
}
