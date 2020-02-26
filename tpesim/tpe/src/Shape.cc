/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include "ignition/physics/tpe/Shape.hh"

using namespace ignition;
using namespace physics;
using namespace tpe;

//////////////////////////////////////////////////
math::AxisAlignedBox Shape::GetBoundingBox()
{
  if (this->dirty)
  {
    this->UpdateBoundingBox();
    this->dirty = false;
  }
  return this->bbox;
}

//////////////////////////////////////////////////
void Shape::UpdateBoundingBox()
{
  // No op. To be overriden by derived classes
}

//////////////////////////////////////////////////
ShapeType Shape::GetType() const
{
  return this->type;
}

//////////////////////////////////////////////////
BoxShape::BoxShape() : Shape()
{
  this->type = ShapeType::BOX;
}

//////////////////////////////////////////////////
void BoxShape::SetSize(const math::Vector3d &_size)
{
  this->size = _size;
  this->dirty = true;
}

//////////////////////////////////////////////////
void BoxShape::UpdateBoundingBox()
{
  math::Vector3d halfSize = this->size * 0.5;
  this->bbox = math::AxisAlignedBox(-halfSize, halfSize);
}

//////////////////////////////////////////////////
CylinderShape::CylinderShape() : Shape()
{
  this->type = ShapeType::CYLINDER;
}

//////////////////////////////////////////////////
void CylinderShape::SetRadius(double _radius)
{
  this->radius = _radius;
  this->dirty = true;
}

//////////////////////////////////////////////////
void CylinderShape::SetLength(double _length)
{
  this->length = _length;
  this->dirty = true;
}

//////////////////////////////////////////////////
void CylinderShape::UpdateBoundingBox()
{
  math::Vector3d halfSize(this->radius, this->radius, this->length*0.5);
  this->bbox = math::AxisAlignedBox(-halfSize, halfSize);
}

//////////////////////////////////////////////////
SphereShape::SphereShape() : Shape()
{
  this->type = ShapeType::SPHERE;
}

//////////////////////////////////////////////////
void SphereShape::SetRadius(double _radius)
{
  this->radius = _radius;
  this->dirty = true;
}

//////////////////////////////////////////////////
void SphereShape::UpdateBoundingBox()
{
  math::Vector3d halfSize(this->radius, this->radius, this->radius);
  this->bbox = math::AxisAlignedBox(-halfSize, halfSize);
}

//////////////////////////////////////////////////
MeshShape::MeshShape() : Shape()
{
  this->type = ShapeType::MESH;
}

//////////////////////////////////////////////////
void MeshShape::SetScale(double _scale)
{
  this->scale = _scale;
  this->dirty = true;
}

//////////////////////////////////////////////////
void MeshShape::SetMesh(const common::Mesh &_mesh)
{
  math::Vector3d center;
  math::Vector3d min;
  math::Vector3d max;
  _mesh.AABB(center, min, max);
  this->meshAABB = math::AxisAlignedBox(min, max);
  this->dirty = true;
}

//////////////////////////////////////////////////
void MeshShape::UpdateBoundingBox()
{
  this->bbox = math::AxisAlignedBox(
      this->scale * this->meshAABB.Min(), this->scale * this->meshAABB.Max());
}

