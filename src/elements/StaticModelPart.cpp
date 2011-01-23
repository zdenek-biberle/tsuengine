#include "StaticModelPart.h"

#include <algorithm>
#include <cmath>
#include "CBaseEngine.h"
#include "elements/Plane.h"

StaticModelPart::StaticModelPart(json::mValue& data){
  double radiusSqr=0;

  json::mObject& obj = data.get_obj();
  m_material = engine->materials->getMaterial(obj.find("material")->second.get_str());

  json::mArray& vertices = obj.find("vertices")->second.get_array();
  m_vertices.reserve(vertices.size());

  for(json::mArray::iterator it=vertices.begin(); it!=vertices.end(); ++it){
    m_vertices.push_back(Vertex(*it));
  }

  json::mArray& indices = obj.find("indices")->second.get_array();
  m_indices.reserve(indices.size());

  if(indices.size()%3){
    engine->warning(sformat("Incorrect number of indices: %d", indices.size()));
  }

  for(json::mArray::iterator it=indices.begin(); it!=indices.end(); ++it){
    int i1=(*it).get_int();
    ++it;
    if(it==indices.end()) break;
    int i2=(*it).get_int();
    ++it;
    if(it==indices.end()) break;
    int i3=(*it).get_int();
    if(i1 == i2 || i1 == i3 || i2 == i3){
      engine->warning(sformat("Indices %d, %d and %d do not form a triangle, skipping...", i1, i2, i3));
      continue;
    }
    Plane plane = Plane(m_vertices[i1], m_vertices[i2], m_vertices[i3]);
    m_vertices[i1].addNormal(plane.getNormal());
    m_vertices[i2].addNormal(plane.getNormal());
    m_vertices[i3].addNormal(plane.getNormal());
    m_indices.push_back(i1);
    m_indices.push_back(i2);
    m_indices.push_back(i3);
    radiusSqr = std::max(radiusSqr, m_vertices[i1].getPosition().lengthSqr());
    radiusSqr = std::max(radiusSqr, m_vertices[i2].getPosition().lengthSqr());
    radiusSqr = std::max(radiusSqr, m_vertices[i3].getPosition().lengthSqr());
  }
  m_radius = sqrt(radiusSqr);

}

void StaticModelPart::uploadData(){
  StaticVertexData* vertices;
  vertices = new StaticVertexData[getVertexCount()];
  GLuint* indices;
  indices = new GLuint[getIndexCount()];
  int i=0;
  for(VertexList::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it, ++i){
    vertices[i].x = it->getPosition().x;
    vertices[i].y = it->getPosition().y;
    vertices[i].z = it->getPosition().z;
    vertices[i].nx = it->getNormal().x;
    vertices[i].ny = it->getNormal().y;
    vertices[i].nz = it->getNormal().z;
    vertices[i].u = it->getTexCoord().x;
    vertices[i].v = it->getTexCoord().y;
  }

  i=0;
  for(IndexList::iterator it = m_indices.begin(); it != m_indices.end(); ++it, ++i){
    indices[i] = (*it);
  }

  glBufferSubData(GL_ARRAY_BUFFER, m_vboOffset, getVertexCount(), vertices);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_indexVboOffset, getIndexCount(), indices);
}

void StaticModelPart::draw(){
  m_material->bind();
  glDrawRangeElements(GL_TRIANGLES, m_vboOffset, m_vboOffset+getVertexCount()-1, getIndexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(m_indexVboOffset));
}