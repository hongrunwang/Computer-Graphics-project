#include "mesh.h"

Mesh::Mesh(const MeshPrimitiveType& mesh_primitive) :
    draw_mode(DrawMode::elements),
    buffer_data_usage_vbo(GL_STATIC_DRAW),
    buffer_data_usage_ebo(GL_STATIC_DRAW),
    is_bidirectional(false),
    vao(0),
    vbo(0),
    ebo(0),
	velocity(0,0,0),
	acceleration(0,0,0),
  q(1,0,0,0),
  rotate_acceleration(0,0,0),
  rotate_velocity(0,0,0),
	isFixed(false) {
  // setup vertices and indices
  if (mesh_primitive == MeshPrimitiveType::cube) {
    vertices = {
        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(0.0, 0.0)), // forward
        MeshVertex(Vec3( 0.5, -0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3( 0.5,  0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3( 0.5,  0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3(-0.5,  0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3( 0.0,  0.0, -1.0), Vec2(0.0, 0.0)),

        MeshVertex(Vec3(-0.5, -0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(0.0, 0.0)), // back
        MeshVertex(Vec3( 0.5, -0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3(-0.5,  0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3(-0.5, -0.5,  0.5), Vec3( 0.0,  0.0,  1.0), Vec2(0.0, 0.0)),

        MeshVertex(Vec3(-0.5,  0.5,  0.5), Vec3(-1.0,  0.0,  0.0), Vec2(1.0, 0.0)), // left
        MeshVertex(Vec3(-0.5,  0.5, -0.5), Vec3(-1.0,  0.0,  0.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3(-1.0,  0.0,  0.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3(-1.0,  0.0,  0.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3(-0.5, -0.5,  0.5), Vec3(-1.0,  0.0,  0.0), Vec2(0.0, 0.0)),
        MeshVertex(Vec3(-0.5,  0.5,  0.5), Vec3(-1.0,  0.0,  0.0), Vec2(1.0, 0.0)),

        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 1.0,  0.0,  0.0), Vec2(1.0, 0.0)), // right
        MeshVertex(Vec3( 0.5,  0.5, -0.5), Vec3( 1.0,  0.0,  0.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3( 0.5, -0.5, -0.5), Vec3( 1.0,  0.0,  0.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3( 0.5, -0.5, -0.5), Vec3( 1.0,  0.0,  0.0), Vec2(0.0, 1.0)),
        MeshVertex(Vec3( 0.5, -0.5,  0.5), Vec3( 1.0,  0.0,  0.0), Vec2(0.0, 0.0)),
        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 1.0,  0.0,  0.0), Vec2(1.0, 0.0)),

        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3( 0.0, -1.0,  0.0), Vec2(0.0, 1.0)), // down
        MeshVertex(Vec3( 0.5, -0.5, -0.5), Vec3( 0.0, -1.0,  0.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3( 0.5, -0.5,  0.5), Vec3( 0.0, -1.0,  0.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3( 0.5, -0.5,  0.5), Vec3( 0.0, -1.0,  0.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3(-0.5, -0.5,  0.5), Vec3( 0.0, -1.0,  0.0), Vec2(0.0, 0.0)),
        MeshVertex(Vec3(-0.5, -0.5, -0.5), Vec3( 0.0, -1.0,  0.0), Vec2(0.0, 1.0)),

        MeshVertex(Vec3(-0.5,  0.5, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 1.0)), // up
        MeshVertex(Vec3( 0.5,  0.5, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 1.0)),
        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3( 0.5,  0.5,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 0.0)),
        MeshVertex(Vec3(-0.5,  0.5,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 0.0)),
        MeshVertex(Vec3(-0.5,  0.5, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 1.0)),
      };
    indices = {
        UVec3( 0,  1,  2), UVec3( 3,  4,  5),
        UVec3( 6,  7,  8), UVec3( 9, 10, 11),
        UVec3(12, 13, 14), UVec3(15, 16, 17),
        UVec3(18, 19, 20), UVec3(21, 22, 23),
        UVec3(24, 25, 26), UVec3(27, 28, 29),
        UVec3(30, 31, 32), UVec3(33, 34, 35),
      };
  }
  else if (mesh_primitive == MeshPrimitiveType::sphere) {
    // compute vertices and indices for +x part
    const Float deg_to_rad = pi / Float(180);
    for (int i = 0; i < primitive_sphere_resolution; ++i) {
      Float phi = deg_to_rad * (Float(45) - Float(90) * Float(i) / (primitive_sphere_resolution - 1)); // [45°, -45°]
      Vec3 d_phi(-Float(std::sin(phi)), Float(std::cos(phi)), 0);
      auto k1 = unsigned(i * primitive_sphere_resolution);
      auto k2 = k1 + unsigned(primitive_sphere_resolution);
      Float t = Float(i) / (primitive_sphere_resolution - 1);
      for (int j = 0; j < primitive_sphere_resolution; ++j, ++k1, ++k2) {
        // vertex
        Float theta = deg_to_rad * (Float(-45) + Float(90) * Float(j) / (primitive_sphere_resolution - 1)); // [-45°, 45°]
        Vec3 d_theta(-Float(std::sin(theta)), 0, -Float(std::cos(theta)));
        Vec3 n = glm::normalize(glm::cross(d_theta, d_phi));
        Float s = (Float)j / (primitive_sphere_resolution - 1);
        vertices.emplace_back(MeshVertex(n * Float(0.5), n, Vec2(s, t)));

        // index
        if (i < (primitive_sphere_resolution - 1) && j < (primitive_sphere_resolution - 1)) {
          indices.emplace_back(UVec3(k1, k2, k1 + 1));
          indices.emplace_back(UVec3(k1 + 1, k2, k2 + 1));
        }
      }
    }
    size_t num_vertices_per_part = vertices.size();
    size_t num_indices_per_part = indices.size();
    // -x
    auto index_start = unsigned(vertices.size());
    for (size_t i = 0; i < num_vertices_per_part; ++i) {
      Vec3 v = vertices[i].position;
      Vec3 n = vertices[i].normal;
      vertices.emplace_back(MeshVertex(Vec3(-v.x, v.y, -v.z), Vec3(-n.x, n.y, -n.z), vertices[i].uv));
    }
    for (size_t i = 0; i < num_indices_per_part; ++i) {
      UVec3 index = indices[i];
      indices.emplace_back(UVec3(index.x + index_start, index.y + index_start, index.z + index_start));
    }
    // +y
    index_start = unsigned(vertices.size());
    for (size_t i = 0; i < num_vertices_per_part; ++i) {
      Vec3 v = vertices[i].position;
      Vec3 n = vertices[i].normal;
      vertices.emplace_back(MeshVertex(Vec3(-v.z, v.x, -v.y), Vec3(-n.z, n.x, -n.y), vertices[i].uv));
    }
    for (size_t i = 0; i < num_indices_per_part; ++i) {
      UVec3 index = indices[i];
      indices.emplace_back(UVec3(index.x + index_start, index.y + index_start, index.z + index_start));
    }
    // -y
    index_start = unsigned(vertices.size());
    for (size_t i = 0; i < num_vertices_per_part; ++i) {
      Vec3 v = vertices[i].position;
      Vec3 n = vertices[i].normal;
      vertices.emplace_back(MeshVertex(Vec3(-v.z, -v.x, v.y), Vec3(-n.z, -n.x, n.y), vertices[i].uv));
    }
    for (size_t i = 0; i < num_indices_per_part; ++i) {
      UVec3 index = indices[i];
      indices.emplace_back(UVec3(index.x + index_start, index.y + index_start, index.z + index_start));
    }
    // +z
    index_start = unsigned(vertices.size());
    for (size_t i = 0; i < num_vertices_per_part; ++i) {
      Vec3 v = vertices[i].position;
      Vec3 n = vertices[i].normal;
      vertices.emplace_back(MeshVertex(Vec3(-v.z, v.y, v.x), Vec3(-n.z, n.y, n.x), vertices[i].uv));
    }
    for (size_t i = 0; i < num_indices_per_part; ++i) {
      UVec3 index = indices[i];
      indices.emplace_back(UVec3(index.x + index_start, index.y + index_start, index.z + index_start));
    }
    // -z
    index_start = unsigned(vertices.size());
    for (size_t i = 0; i < num_vertices_per_part; ++i) {
      Vec3 v = vertices[i].position;
      Vec3 n = vertices[i].normal;
      vertices.emplace_back(MeshVertex(Vec3(v.z, v.y, -v.x), Vec3(n.z, n.y, -n.x), vertices[i].uv));
    }
    for (size_t i = 0; i < num_indices_per_part; ++i) {
      UVec3 index = indices[i];
      indices.emplace_back(UVec3(index.x + index_start, index.y + index_start, index.z + index_start));
    }
  }
  else if (mesh_primitive == MeshPrimitiveType::rectangle) {
	vertices = {
		MeshVertex(Vec3(-0.5, 0, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 1.0)),
		MeshVertex(Vec3( 0.5, 0, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 1.0)),
		MeshVertex(Vec3( 0.5, 0,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 0.0)),
		MeshVertex(Vec3( 0.5, 0,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(1.0, 0.0)),
		MeshVertex(Vec3(-0.5, 0,  0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 0.0)),
		MeshVertex(Vec3(-0.5, 0, -0.5), Vec3( 0.0,  1.0,  0.0), Vec2(0.0, 1.0)),
	};
	indices = {
		UVec3( 0,  1,  2), UVec3( 3,  4,  5),
	};
  }
  else {
    std::cerr << "Mesh::Mesh(): Invalid mesh primitive" << std::endl;
    abort();
  }

  // construct vao for triangles
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * this->vertices.size(), this->vertices.data(), this->buffer_data_usage_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, uv));
  glEnableVertexAttribArray(2);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UVec3) * this->indices.size(), this->indices.data(), this->buffer_data_usage_ebo);
  glBindVertexArray(0);
}

Mesh::Mesh(std::vector<MeshVertex>&& vertices,
           GLenum buffer_data_usage_vbo/* = GL_STATIC_DRAW*/,
           bool is_bidirectional/* = false*/) :
    draw_mode(DrawMode::arrays),
    vertices(std::move(vertices)),
    buffer_data_usage_vbo(buffer_data_usage_vbo),
    buffer_data_usage_ebo(GL_STATIC_DRAW),
    is_bidirectional(is_bidirectional),
    vao(0),
    vbo(0),
    ebo(0) {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * this->vertices.size(), this->vertices.data(), this->buffer_data_usage_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, uv));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
}

Mesh::Mesh(std::vector<MeshVertex>&& vertices, std::vector<UVec3>&& indices,
           GLenum buffer_data_usage_vbo/* = GL_STATIC_DRAW*/, GLenum buffer_data_usage_ebo/* = GL_STATIC_DRAW*/,
           bool is_bidirectional/* = false*/) :
    draw_mode(DrawMode::elements),
    vertices(std::move(vertices)),
    indices(std::move(indices)),
    buffer_data_usage_vbo(buffer_data_usage_vbo),
    buffer_data_usage_ebo(buffer_data_usage_ebo),
    is_bidirectional(is_bidirectional),
    vao(0),
    vbo(0),
    ebo(0) {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * this->vertices.size(), this->vertices.data(), this->buffer_data_usage_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, uv));
  glEnableVertexAttribArray(2);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UVec3) * this->indices.size(), this->indices.data(), this->buffer_data_usage_ebo);
  glBindVertexArray(0);
}

void Mesh::SetObject(const std::shared_ptr<Object>& new_object) {
  object = new_object;
}

bool Mesh::IsBidirectional() const {
  return is_bidirectional;
}

void Mesh::DrawTriangles() const {
  glBindVertexArray(vao);
  if (draw_mode == DrawMode::arrays)
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  else if (draw_mode == DrawMode::elements)
    glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

/*virtual*/ void Mesh::FixedUpdate() {
	for(unsigned i=0;i<simulation_steps_per_fixed_update_time;i++){
		Simulate();
	}
}

void Mesh::BufferMeshVertices(){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * vertices.size(), vertices.data(), buffer_data_usage_vbo);
	glBindVertexArray(0);
}

void Mesh::ApplyTransform(Transform transform){
	for(int i=0;i<vertices.size();i++){
		vertices[i].position=transform.TransformPoint(vertices[i].position);
		vertices[i].normal=Transform::TransformPoint(vertices[i].normal, transform.RotationMat());
	}
}

void Mesh::Simulate(){
	if(isFixed)return;
	acceleration=-gravity;
	velocity+=acceleration*simulation_delta_time;
  rotate_velocity += rotate_acceleration * simulation_delta_time;
  Quat rotation  = {0, simulation_delta_time *rotate_velocity};
  q = q + rotation * q;
  q = glm::normalize(q);
  WorldToLocal();
	ApplyTransform(Transform(velocity*simulation_delta_time,
                             q,
                             Vec3(1, 1, 1)));
  LocalToWorld();
}

Float Mesh::sdf(Interaction &interaction){
	Vec3 v1,v2,normal;
	interaction.dis=-inf;
	Float t;
	for(int i=0;i<vertices.size()/3;i++){
		v1=vertices[i*3+1].position-vertices[i*3].position;
		v2=vertices[i*3+2].position-vertices[i*3].position;
		normal=glm::normalize(glm::cross(v1,v2));
		v1=vertices[i*3].normal+vertices[i*3+1].normal+vertices[i*3+2].normal;
		if(glm::dot(normal,v1)<0) normal=-normal; // tell apart outside and inside
		v1=interaction.position-vertices[i*3].position;
		t=glm::dot(v1,normal);
		if(t>interaction.dis){
			interaction.dis=t;
			interaction.normal=normal;
		}
	}
	return interaction.dis;
}

bool Mesh::CollisionDetect(std::shared_ptr<Mesh> other, Interaction &interaction){
	if(isFixed) return false; // skip fixed meshes
	// if(other->vertices.size()>6) return false; // temporarily only detect plane
	for(int i=0;i<vertices.size();i++){
		interaction.position=vertices[i].position;
		if(other->sdf(interaction)<0){
			printf("collision at (%f,%f,%f) with dis %f\n",interaction.position.x,interaction.position.y,interaction.position.z,interaction.dis);
			return true;
		}
	}
	return false;
}

void Mesh::CollisionResponse(Interaction &interaction){
	Float t=glm::dot(velocity,interaction.normal);
	if(t<0){
		velocity=-velocity;
		t=-t;
	}
	velocity=2*t*interaction.normal-velocity; // simply bounce
	return;

  // If velocity is not inward, return
  if (glm::dot(velocity, interaction.normal) >= 0)
  {
    return;
  }

  // Caluculate new velocity
  Vec3 velocity_n, velocity_t;
  velocity_n = glm::dot(velocity, interaction.normal) * interaction.normal;
  velocity_t = velocity - velocity_n;

  float a = fmax(1 - mu_t * (1 + mu_n) * glm::length(velocity_n) / glm::length(velocity_t), 0.0f);
  Vec3 new_velocity_n = -mu_n * velocity_n;
  Vec3 new_velocity_t = a * velocity_t;
  Vec3 new_velocity = new_velocity_n + new_velocity_t;

  // Caluculate impulse j
  Mat4 R_Mat, I_ref;
  Mat4 I = R_Mat * I_ref * glm::transpose(R_Mat);

  Vec3 ri = object->transform->TransformPoint(interaction.position, glm::inverse(object->transform->ModelMat())); // get local coordinate
  Vec4 Rri4 = R_Mat * Vec4(ri, 0);
  Vec3 Rri = Vec3(Rri4.x, Rri4.y, Rri4.z);

  Mat4 K = Mat4(1.0f) / mass - CrossMat(Rri) * glm::inverse(I) * CrossMat(Rri);

  Vec4 j4 = glm::inverse(K) * Vec4(new_velocity - velocity, 0);
  Vec3 j = Vec3(j4.x, j4.y, j4.z);

  // Update v and w
  velocity += j / mass;
  Vec4 w4 = glm::inverse(I) * Vec4(glm::cross(Rri, j), 0);
  rotate_velocity += Vec3(w4.x, w4.y, w4.z);
}

Mat4 Mesh::CrossMat(Vec3 v)
{
  return {
    0, -v[2], v[1], 0,
    v[2], 0, -v[0], 0,
    -v[1], v[0], 0, 0,
    0, 0, 0, 1 };
}

void Mesh::WorldToLocal(){
  const Mat4 model_matrix = object->transform->ModelMat();
  const Mat4 model_inverse = glm::inverse(model_matrix);
  for(int i=0;i<vertices.size();i++){
		vertices[i].position=object->transform->TransformPoint(vertices[i].position, model_inverse);
	}
}

void Mesh::LocalToWorld(){
  const Mat4 model_matrix = object->transform->ModelMat();
  const Mat4 model_inverse = glm::inverse(model_matrix);
  for(int i=0;i<vertices.size();i++){
		vertices[i].position=object->transform->TransformPoint(vertices[i].position, model_matrix);
	}
}