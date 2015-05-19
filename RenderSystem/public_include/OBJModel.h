#ifndef _OBJModel_
#define _OBJModel_

#include "Vertex.h"
#include <string>
#include <vector>
#include <map>

namespace smoke
{
	class OBJModel
	{
	public:
		OBJModel();
		~OBJModel();
		void loadFromFile(const std::string& filePath);
		const std::map<std::string,std::string>& getTextures() const;
		const std::vector<Vertex>& getVertexData() const;
		const std::vector<unsigned short>& getIndexData(const std::string& matName);
		void getVertices(std::vector<float>& vertices) const;
		void getIndices(std::vector<unsigned int>& indices) const;

	private:
		void processMaterials(std::string& dirPath, std::string& mtlFile);
		bool startsWith(std::string starter, std::string text);

		std::map<std::string,std::string> m_textures;
		std::vector<Vertex> m_vertices;
		std::map<std::string, std::vector<unsigned short> > m_indices;

	};

}

#endif