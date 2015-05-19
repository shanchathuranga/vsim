#include "OBJModel.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>

#pragma warning(disable:4996)

namespace smoke
{
	OBJModel::OBJModel()
	{

	}

	OBJModel::~OBJModel()
	{

	}

	void OBJModel::loadFromFile( const std::string& filePath )
	{
		std::string dirPath;
		if (filePath.find_last_of('\\') != std::string::npos)
		{
			dirPath = filePath.substr(0, filePath.find_last_of('\\')+1);
		}

		std::ifstream f(filePath.c_str());
		if (!f.is_open())
		{
			std::cout << "File open failed : " << filePath << "\n";
			return;
		}

		std::vector<std::string> lines;
		char buffer[256];
		while (!f.eof()) 
		{
			f.getline(buffer, 256);
			lines.push_back(std::string(buffer));
		}

		f.close();

		std::string mtlFilePath;
		for (std::vector<std::string>::const_iterator it = lines.begin(),eit = lines.end(); it != eit; ++it)
		{
			if ((*it).empty()) 
				continue;
			if (startsWith("mtllib", *it) == true)
			{
				char mtlFileName[256];
				sscanf((*it).c_str(), "mtllib %s", mtlFileName);
				mtlFilePath = dirPath + std::string(mtlFileName);
				break;
			}
		}

		processMaterials(dirPath, mtlFilePath);
		std::vector<std::string> positions;
		std::vector<std::string> normals;
		std::vector<std::string> texcoords;
		std::vector<std::string> triangleGroup;
		std::map<std::string, std::vector<std::string> > triangles;
		std::string currentMaterialName;

		for (std::vector<std::string>::iterator it = lines.begin(),eit = lines.end(); it != eit; ++it)
		{
			std::string s = *it;

			if (s.empty()) continue;
			if (startsWith("# ", s) == true) continue;

			if (startsWith("v ", s) == true)
			{
				positions.push_back(s);
			}
			else if (startsWith("vt ", s) == true)
			{
				texcoords.push_back(s);
			}
			else if (startsWith("vn ", s) == true)
			{
				normals.push_back(s);
			}
			else if (startsWith("f ", s) == true)
			{
				triangleGroup.push_back(s);
			}
			else if (startsWith("usemtl ", s) == true)
			{
				char mtlName[256];
				sscanf(s.c_str(), "usemtl %s", mtlName);
				if (!currentMaterialName.empty())
				{
					triangles[currentMaterialName] = triangleGroup;
					triangleGroup.clear();
				}
				currentMaterialName = mtlName;
			}

		}
		triangles[currentMaterialName] = triangleGroup;

		unsigned short index = 0;
		for (std::map<std::string, std::vector<std::string> >::iterator it = triangles.begin(),eit = triangles.end(); it != eit; ++it)
		{
			std::string materialName = it->first;
			std::vector<std::string>& tris = it->second;
			std::vector<unsigned short> indices;

			for (std::vector<std::string>::iterator itS = tris.begin(), itE = tris.end(); itS != itE; ++itS)
			{
				std::string& s = *itS;
				int p1,p2,p3, t1,t2,t3, n1,n2,n3;
				sscanf(s.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", 
					&p1, &t1, &n1, &p2, &t2, &n2, &p3, &t3, &n3 );

				{
					Vertex v;
					std::string& pos = positions[--p1];
					sscanf(pos.c_str(), "v %f %f %f", &v.position[0], &v.position[1], &v.position[2]);
					std::string& nom = normals[--n1];
					sscanf(nom.c_str(), "vn %f %f %f", &v.normal[0], &v.normal[1], &v.normal[2]);
					std::string& tex = texcoords[--t1];
					sscanf(tex.c_str(), "vt %f %f", &v.texcoord[0], &v.texcoord[1]);
					m_vertices.push_back(v);
					indices.push_back(index++);
				}
				{
					Vertex v;
					std::string& pos = positions[--p2];
					sscanf(pos.c_str(), "v %f %f %f", &v.position[0], &v.position[1], &v.position[2]);
					std::string& nom = normals[--n2];
					sscanf(nom.c_str(), "vn %f %f %f", &v.normal[0], &v.normal[1], &v.normal[2]);
					std::string& tex = texcoords[--t2];
					sscanf(tex.c_str(), "vt %f %f", &v.texcoord[0], &v.texcoord[1]);
					m_vertices.push_back(v);
					indices.push_back(index++);
				}
				{
					Vertex v;
					std::string& pos = positions[--p3];
					sscanf(pos.c_str(), "v %f %f %f", &v.position[0], &v.position[1], &v.position[2]);
					std::string& nom = normals[--n3];
					sscanf(nom.c_str(), "vn %f %f %f", &v.normal[0], &v.normal[1], &v.normal[2]);
					std::string& tex = texcoords[--t3];
					sscanf(tex.c_str(), "vt %f %f", &v.texcoord[0], &v.texcoord[1]);
					m_vertices.push_back(v);
					indices.push_back(index++);
				}
			}
			m_indices[materialName] = indices;
		}
	}

	const std::map<std::string,std::string>& OBJModel::getTextures() const
	{
		return m_textures;
	}

	void OBJModel::processMaterials(std::string& dirPath, std::string& mtlFile)
	{
		std::ifstream f(mtlFile.c_str());
		if (!f.is_open())
		{
			std::cout << "File open failed : " << mtlFile << "\n";
			return;
		}

		std::vector<std::string> lines;
		char buffer[256];
		while (!f.eof()) 
		{
			f.getline(buffer, 256);
			lines.push_back(std::string(buffer));
		}

		f.close();

		char newmtlBuffer[256];
		char mapKdBuffer[256];
		for (unsigned int i=0; i<lines.size(); ++i)
		{
			std::string line = lines.at(i);
			if (startsWith("newmtl", line) == true)
			{
				sscanf(line.c_str(), "newmtl %s", newmtlBuffer);
			}
			if (startsWith("map_Kd", line) == true)
			{
				sscanf(line.c_str(), "map_Kd %s", mapKdBuffer);
				m_textures[newmtlBuffer] = dirPath + std::string(mapKdBuffer);
			}
		}
	}

	bool OBJModel::startsWith( std::string starter, std::string text )
	{
		if (starter.length() > text.length())
			return false;

		std::string::iterator starterIt = starter.begin();
		std::string::iterator textIt = text.begin();

		for (; starterIt != starter.end(); ++starterIt, ++textIt)
		{
			if (*starterIt != *textIt)
				return false;
		}
		return true;
	}

	const std::vector<Vertex>& OBJModel::getVertexData() const
	{
		return m_vertices;
	}

	const std::vector<unsigned short>& OBJModel::getIndexData( const std::string& matName )
	{
		std::map<std::string, std::vector<unsigned short> >::iterator findIt = m_indices.find(matName);
		if (findIt == m_indices.end())
		{
			throw std::exception("No texture found for material");	
		}
		return findIt->second;
	}

	void OBJModel::getVertices(std::vector<float>& vertices) const
	{
		for (std::vector<Vertex>::const_iterator it = m_vertices.begin(), itE = m_vertices.end(); it != itE; ++it)
		{
			const Vertex& v = *it;
			vertices.push_back(v.position[0]);
			vertices.push_back(v.position[1]);
			vertices.push_back(v.position[2]);
		}
	}

	void OBJModel::getIndices(std::vector<unsigned int>& indices) const
	{
		for (std::map<std::string, std::vector<unsigned short> >::const_iterator it = m_indices.begin(),
			itE = m_indices.end(); it != itE; ++it)
		{
			const std::vector<unsigned short>& ind = it->second;
			indices.insert(indices.end(), ind.begin(), ind.end());
		}
	}
}