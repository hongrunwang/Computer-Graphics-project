#include "mesh.h"
#include "object.h"
#include "transform.h"

Object::Object(std::shared_ptr<Mesh> mesh,
               std::shared_ptr<Shader> shader) :
  mesh(std::move(mesh)),
  shader(std::move(shader)),
  transform(std::make_unique<Transform>()),
  color(0, 0, 0) {
}

Object::Object(std::shared_ptr<Mesh> mesh,
               std::shared_ptr<Shader> shader,
               const Transform& transform) :
  mesh(std::move(mesh)),
  shader(std::move(shader)),
  transform(std::make_unique<Transform>(transform)),
  color(0, 0, 0) {
} // should not be used if all world coordinate

void Object::FixedUpdate() const {
  if (mesh)
    mesh->FixedUpdate();
}

void Object::ApplyTransform(Transform transform) const {
  if (mesh)
    mesh->ApplyTransform(transform);
}

void Object::BufferMeshVertices() const {
  if (mesh)
    mesh->BufferMeshVertices();
}

void Object::Simulate() const {
  if (mesh)
    mesh->Simulate();
}
