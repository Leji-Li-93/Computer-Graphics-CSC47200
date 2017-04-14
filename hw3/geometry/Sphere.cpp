// ======================================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2017 by George Wolberg
//
// Sphere.cpp -  Sphere class implementation
//
// Written by: George Wolberg, Siavash Zokai 2017
// ======================================================================


#include "Sphere.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::Sphere:
//
// Sphere default constructor function.
//
Sphere::Sphere(): m_color   (vec3(1.0f, 1.0f, 1.0f)),
		  m_center  (vec3(0.0f, 0.0f, 0.0f)),
		  m_radius  (1.0f),
		  m_nSeg    (8)

{
	initializeGLFunctions();
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_indicesBuffer);
	castShadow(true);
	setDrawable(true);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::set:
//
// Set sphere: center, radius, #rings (slices), #segments, and color
//
Sphere::Sphere(vec3 center, float radius, uint nSeg): m_color(vec3(1.0f, 1.0f, 1.0f))
{
	m_center = center;
	m_radius = radius;
	m_nSeg   = nSeg;
	initializeGLFunctions();
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_indicesBuffer);
	castShadow(true);
	setDrawable(true);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::initVertices
//
//init vertices, colors, and normals:
//
void
Sphere::initVertices()
{
	// init increments for drawing sphere rings (slices) and segments
	float r = 1.0f / (m_nSeg - 1);
	float s = 1.0f / (m_nSeg - 1);

	// visit all segments on each sphere ring (slice)
	for(uint y = 0; y < m_nSeg; ++y) {
		for(uint x = 0; x < m_nSeg; ++x) {
			// init spherical coordinate
			float const yy = sin(-M_PI_2 + M_PI * y * r);
			float const xx = cos(2 * M_PI * x * s) * sin(M_PI * y * r);
			float const zz = sin(2 * M_PI * x * s) * sin(M_PI * y * r);

			// push point, color, and normal to array
			m_vertices.push_back(vec3(xx*m_radius, yy*m_radius, zz*m_radius));
			m_colors.push_back(m_color);
			m_normals.push_back(vec3(xx, yy, zz));
		}
	}
	m_verticesSize =(GLuint) m_vertices.size();

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:initIndices:
//
// Indices for drawing sphere triangle strips.
// Triangle strips can be connected by duplicating indices
// between the strips. If connecting strips have opposite
// vertex order then last index of the first strip and first
// index of the second strip needs to be duplicated. If
// connecting strips have same vertex order then only last
// index of the first strip needs to be duplicated.
//
void
Sphere::initIndices()
{
	// push indices to array
	for(uint y = 0; y < m_nSeg-1; ++y) {
		for(uint x = 0; x < m_nSeg-1; ++x) {
			m_indices.push_back((y) * m_nSeg     + x);
			m_indices.push_back((y + 1) * m_nSeg + x);
		}
	}

	// store the number of indices for later use
	m_indicesSize = (GLuint) m_indices.size();

	// bind index buffer to the GPU and copy indices from CPU to GPU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesSize * sizeof(GLushort), &m_indices[0], GL_STATIC_DRAW);


	// clear CPU indices buffers
	m_indices.clear();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:uploadVertices:
//
// bind vertex buffer to the GPU and copy the vertices from CPU to GPU
// 
void
Sphere::uploadVertices()
{
	// bind vertex buffer to the GPU and copy the vertices from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize * sizeof(vec3), &m_t_vertices[0], GL_STATIC_DRAW);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:uploadColors:
//
// bind color buffer to the GPU and copy the color for each vertex from CPU to GPU
// 
//
void
Sphere::uploadColors()
{
	// bind color buffer to the GPU and copy colors from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize * sizeof(vec3), &m_colors[0], GL_STATIC_DRAW);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:uploadNormals:
//
// bind normals buffer to the GPU and copy the normal for each vertex from CPU to GPU
// 
//
void
Sphere::uploadNormals()
{
	// bind normal buffer to the GPU and copy normals from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_verticesSize * sizeof(vec3), &m_t_normals[0], GL_STATIC_DRAW);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::createGeometry:
//
// create sphere geometry.
//
void
Sphere::createGeometry()
{
	initVertices();
	initIndices();
	applyTransformation();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::updateGeometry:
//
// update Sphere geometry whenever apply transformation.
//
void
Sphere::updateGeometry()
{
	uploadVertices();
	uploadColors();
	uploadNormals();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:translate:
//
// Apply translation transformations.
//
void
Sphere::translate(vec3 &t)
{
	m_t_vertices.clear();
	m_t_vertices.resize(m_verticesSize);
	m_center = t;
	for(uint i = 0; i < m_verticesSize; ++i) {
		// translate
		m_t_vertices[i] = m_vertices[i] + t;
	}
	uploadVertices();
	m_t_vertices.clear();

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere:applyTransformation:
//
// Apply translation transformations to sphere.
//
void
Sphere::applyTransformation()
{
	m_t_vertices.clear();
	m_t_normals.clear();

	m_t_vertices.resize(m_verticesSize);
	m_t_normals.resize(m_verticesSize);
	for(uint i = 0; i < m_verticesSize; ++i) {
		m_t_vertices[i] = m_vertices[i] + m_center;
		m_t_normals[i]  = m_normals[i];
	}
	updateGeometry();
	m_t_vertices.clear();
	m_t_normals.clear();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sphere::display:
//
// Display sphere.
//
void
Sphere::display()
{
	// bind vertex buffer to the GPU; enable buffer to be copied to the
	// attribute vertex variable and specify data format
	glBindBuffer		 (GL_ARRAY_BUFFER, m_vertexBuffer);
	glEnableVertexAttribArray(ATTRIB_VERTEX);
	glVertexAttribPointer	 (ATTRIB_VERTEX, 3, GL_FLOAT, false, 0, NULL);

	// bind color buffer to the GPU; enable buffer to be copied to the
	// attribute color variable and specify data format
	glBindBuffer		 (GL_ARRAY_BUFFER, m_colorBuffer);
	glEnableVertexAttribArray(ATTRIB_COLOR);
	glVertexAttribPointer	 (ATTRIB_COLOR, 3, GL_FLOAT, false, 0, NULL);

	// bind normal buffer to the GPU; enable buffer to be copied to the
	// attribute normal variable and specify data format
	glBindBuffer		 (GL_ARRAY_BUFFER, m_normalBuffer);
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glVertexAttribPointer	 (ATTRIB_NORMAL, 3, GL_FLOAT, false, 0, NULL);

	// bind index buffer to the GPU and use it to draw triangle strip
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) m_indicesSize, GL_UNSIGNED_SHORT, 0);
}
