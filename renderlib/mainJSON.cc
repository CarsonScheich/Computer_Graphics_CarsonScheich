#include <iostream>
#include <memory>

#include "JSON/SceneLoader.h"
#include "JSON/SceneParser_JSON.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: jsonTest <scene.json>\n";
        return 1;
    }

    Scene sceneJSON;
    std::shared_ptr<ISceneLoader> loader = std::make_shared<SceneLoader>(sceneJSON);
    SceneParser_JSON parser(loader);
    parser.parseFileData("../sceneData/scenes_A/oneSphere.json");
    return 0;
}