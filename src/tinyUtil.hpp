#ifndef __TINY_UTIL_HPP__
#define __TINY_UTIL_HPP__

#include <glm/glm.hpp>

namespace tinygltf
{
    void ExtractVec3(const std::string &attributeName, std::vector<glm::vec3> &out, const tinygltf::Model &model, const tinygltf::Primitive &primitive)
    {
        if (!primitive.attributes.contains(attributeName))
        {
            return;
        }

        const auto &accessor = model.accessors[primitive.attributes.at(attributeName)];
        const auto &view = model.bufferViews[accessor.bufferView];
        const auto &buffer = model.buffers[view.buffer];

        const float *data = reinterpret_cast<const float *>(&buffer.data[view.byteOffset + accessor.byteOffset]);

        for (size_t index = 0; index < accessor.count; index++)
        {
            glm::vec3 vertex;
            vertex.x = data[index * 3 + 0];
            vertex.y = data[index * 3 + 1];
            vertex.z = data[index * 3 + 2];
            out.push_back(vertex);
        }
    }

    void ExtractVec2(const std::string &attributeName, std::vector<glm::vec2> &out, const tinygltf::Model &model, const tinygltf::Primitive &primitives)
    {
        if (!primitives.attributes.contains(attributeName))
        {
            return;
        }

        const auto &accessor = model.accessors[primitives.attributes.at(attributeName)];
        const auto &view = model.bufferViews[accessor.bufferView];
        const auto &buffer = model.buffers[view.buffer];

        const float *data = reinterpret_cast<const float *>(&buffer.data[view.byteOffset + accessor.byteOffset]);

        for (size_t index = 0; index < accessor.count; index++)
        {
            glm::vec2 vertex;
            vertex.x = data[index * 2 + 0];
            vertex.y = data[index * 2 + 1];
            out.push_back(vertex);
        }
    }

    void ExtractIndices(std::vector<unsigned int> &out, const tinygltf::Model &model, const tinygltf::Primitive &primitives)
    {
        const auto &accessor = model.accessors[primitives.indices];
        const auto &view = model.bufferViews[accessor.bufferView];
        const auto &buffer = model.buffers[view.buffer];
        const void *data = &buffer.data[view.byteOffset + accessor.byteOffset];

        for (size_t i = 0; i < accessor.count; ++i)
        {
            switch (accessor.componentType)
            {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                out.push_back(((const uint16_t *)data)[i]);
                break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                out.push_back(((const uint32_t *)data)[i]);
                break;
            default:
                break;
            }
        }
    }
}

#endif // __TINY_UTIL_HPP__