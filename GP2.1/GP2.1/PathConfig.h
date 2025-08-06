#pragma once
#include <string>
#include <filesystem>

inline std::string GetTexturePath(const std::string& filename) {
    return (std::filesystem::current_path() / "Textures" / filename).string();
}

inline std::string GetShaderPath(const std::string& filename) {
    return (std::filesystem::current_path() / filename).string();
}
