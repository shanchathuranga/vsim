#ifndef _OpenGLRenderer_
#define _OpenGLRenderer_

#include "RenderWindow.h"
#include "Definitions.h"
#include "Vertex.h"
#include <vector>
#include <map>
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "vmath.h"

namespace smoke
{
	class OpenGLRenderer
	{
		typedef std::map<std::string, std::string> TextureNameMap;
		typedef std::map<std::string, GLuint> TextureIDMap;
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		void initialize(RenderWindow* renderWindow);
		void enableFog();
		void disableFog();
		void enableDepthTest();
		void disableDepthTest();

		void pushMatrix(framework::MatrixType type);
		void popMatrix(framework::MatrixType type);
		void loadMatrix(framework::MatrixType type, const Matrix4f& matrix);
		void multiplyMatrix(framework::MatrixType type, const Matrix4f& matrix);

		void beginRender();
		void endRender();

		void drawBuffers(const VertexBuffer* vb, const IndexBuffer* ib);
		void drawQuad(Vector3f& point00, Vector3f& point11, bool hasTexture, int repeat);
		void drawTiledPlane(int tileCount, int tileSize, int textureRepeat);
		void drawCube(float size);

		void setTextureLoadType(framework::TextureLoadType loadType);
		void addTexture(std::string name, std::string fileName);
		void setActiveTexture(const std::string& name);

	private:
		GLuint loadTexture(std::string& fileName);

		RenderWindow* m_renderWindow;
		TextureNameMap m_textureNames;
		TextureIDMap m_textureIDs;
		framework::TextureLoadType m_textureLoadType;
	};
}

#endif