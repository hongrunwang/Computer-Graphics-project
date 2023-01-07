#pragma once

#include "common.h"

class Object final {
 public:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Shader> shader;
  std::unique_ptr<Transform> transform;
  Vec3 color;

  Object(std::shared_ptr<Mesh> mesh,
         std::shared_ptr<Shader> shader);
  Object(std::shared_ptr<Mesh> mesh,
         std::shared_ptr<Shader> shader,
         const Transform& transform); // should not be used if all world coordinate

  Object(const Object&) = delete;
  Object(Object&&) = default;
  Object& operator=(const Object&) = delete;
  Object& operator=(Object&&) = default;
  ~Object() = default;

	// these should not be used for simplicity
	void FixedUpdate() const;
	void ApplyTransform(Transform transform) const;
	void BufferMeshVertices() const;
	void Simulate() const;
};
