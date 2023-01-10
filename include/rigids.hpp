#pragma once

#include "mesh.h"

class Rect : public Mesh{
public:
	// Vec3 center,normal;
	Rect():Mesh(MeshPrimitiveType::rectangle){
		center=Vec3(0,0,0);
		normal=Vec3(0,1,0);
		type=MeshPrimitiveType::rectangle;
	}
	virtual void ApplyTransform(Transform transform){
		this->Mesh::ApplyTransform(transform);
		center=transform.TransformPoint(center);
		normal=transform.RotationMat()*normal;
	}
	virtual Float sdf(Interaction &interaction){
		interaction.dis=glm::dot(interaction.position-center,normal);
		interaction.normal=normal;
		return interaction.dis;
	}
};

class Sphere : public Mesh{
public:
	// Vec3 center;
	// Float radius;
	Sphere():Mesh(MeshPrimitiveType::sphere){
		center=Vec3(0,0,0);
		radius=0.5f;
		type=MeshPrimitiveType::sphere;
	}
	virtual void ApplyTransform(Transform transform){
		this->Mesh::ApplyTransform(transform);
		center=transform.TransformPoint(center);
		radius=radius*transform.scale.x; // does not support ellipse
	}
	virtual Float sdf(Interaction &interaction){
		Vec3 t1=interaction.position-center;
		interaction.normal=glm::normalize(t1);
		interaction.dis=glm::dot(t1,interaction.normal);
		return interaction.dis;
	}
	virtual bool CollisionDetect(std::shared_ptr<Mesh> other, Interaction &interaction){
		if(isFixed)return false;
		if(other->type==MeshPrimitiveType::sphere){
			Vec3 t1=center-other->center;
			interaction.normal=glm::normalize(t1);
			interaction.dis=glm::dot(t1,interaction.normal)-radius-other->radius;
			interaction.position=center-radius*interaction.normal;
			return interaction.dis<0;
		}
		if(other->type==MeshPrimitiveType::rectangle){
			Vec3 t1=center-other->center;
			interaction.normal=other->normal;
			interaction.dis=glm::dot(t1,interaction.normal)-radius;
			interaction.position=center-radius*interaction.normal;
			return interaction.dis<0;
		}
		return this->Mesh::CollisionDetect(other,interaction);
	}
};

class Cube : public Mesh{
public:
	// Vec3 center;
	// Float radius;
	Cube():Mesh(MeshPrimitiveType::cube){
		center=Vec3(0,0,0);
		radius=0.5f;
		type=MeshPrimitiveType::cube;
	}
	virtual void ApplyTransform(Transform transform){
		this->Mesh::ApplyTransform(transform);
		center=transform.TransformPoint(center);
		radius=radius*transform.scale.x; // does not support different scaling on different axes
	}
	virtual Float sdf(Interaction &interaction){ // not that easy
		Vec3 t1=interaction.position-center;
		// interaction.dis=max(max(abs(t1.x),abs(t1.y)),abs(t1.z))-radius;
		if(abs(t1.x)>abs(t1.y)&&abs(t1.x)>abs(t1.z)){
			interaction.dis=abs(t1.x)-radius;
			t1=(1.0f/abs(t1.x))*t1;
			interaction.position=center+t1;
			if(t1.x>0) interaction.normal=Vec3(1,0,0);
			else interaction.normal=Vec3(-1,0,0);
		}else if(abs(t1.y)>abs(t1.x)&&abs(t1.y)>abs(t1.z)){
			interaction.dis=abs(t1.y)-radius;
			t1=(1.0f/abs(t1.y))*t1;
			interaction.position=center+t1;
			if(t1.y>0) interaction.normal=Vec3(0,1,0);
			else interaction.normal=Vec3(0,-1,0);
		}else{
			interaction.dis=abs(t1.z)-radius;
			t1=(1.0f/abs(t1.z))*t1;
			interaction.position=center+t1;
			if(t1.z>0) interaction.normal=Vec3(0,0,1);
			else interaction.normal=Vec3(0,0,-1);
		}
		return interaction.dis;
	}
};