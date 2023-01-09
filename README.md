## CS171.01 Final Project - Massive Rigid-Body Simulation

Name: 丁弘毅 王鸿润 刘放勋
Student ID: 2020533039 __ 2020533047

**Please write your Chinese name and your student ID in this README.**

## Deadline

**Jan 10, 2023, 18:00 UTC+8** **(Jan 10, 2023, 2:00 UTC-8)**

## Statement

Refer to [course page](https://faculty.sist.shanghaitech.edu.cn/faculty/liuxp/course/cs171.01/).

## Description

+ Adjust time step in `commom.h`: `fixed_delta_time` and `simulation_steps_per_fixed_update_time` (Currently rendering step is 0.02s and silulation step is 0.01s)
+ Now every coordinate in `Mesh::vertices[].position` is world coordinate. So Class `Object` is rather redundant and `Object::transform` should always be identity transform
+ I disabled `FIRST_PERSON_CAMERA` in `camera.h`, so use right mouse button to change view angle. And use space to resume simulation

+ Implement part of an accurate `Mesh::CollisionResponse()`
+ Add mass, mu_n, mu_t as constants to the constructor of mesh

## References

Lectures 3,4,9 of 

[GAMES103：基于物理的计算机动画入门 – 计算机图形学与混合现实在线平台 (games-cn.org)](http://games-cn.org/games103/)

Lecture notes 
[GAMES103笔记 Lecture4 刚体碰撞（Rigid Body Contacts） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/440596941)
[GAMES103笔记 Lecture 9 碰撞处理（Collision Handling） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/451243910)

## TODO

- [ ] Optimize `Scene::FixedUpdate()` with Spatial Hashing
- [ ] Implement an accurate `Mesh::CollisionResponse()` (Currently just part of it)
- [x] Derive subclasses `Sphere`,`Plane`,`Cube` etc. from `Mesh` for better performance by making `sdf()` virtual
- [ ] Build a scene that many rigid bodies falling to an inclined plane
- [ ] Need rotation matrix R and inertia I