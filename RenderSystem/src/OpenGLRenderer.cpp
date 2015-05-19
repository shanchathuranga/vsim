#include "OpenGLRenderer.h"
#include <cstdlib>
#include <ctime>
#include <stddef.h>

namespace
{
	unsigned long glMatrixType[] = {
		GL_MODELVIEW,
		GL_PROJECTION,
		GL_TEXTURE
	};	
}

namespace smoke
{

	OpenGLRenderer::OpenGLRenderer() : m_renderWindow(NULL), m_textureLoadType(framework::Load_Lazy)
	{
		srand ((unsigned int)time(NULL));
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		for (TextureIDMap::iterator it = m_textureIDs.begin(), eit = m_textureIDs.end(); it != eit; ++it)
		{
			GLuint texId = it->second;
			glDeleteTextures(1, &texId);
		}
	}

	void OpenGLRenderer::initialize( RenderWindow* renderWindow )
	{
		m_renderWindow = renderWindow;
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.f, (float)m_renderWindow->getWidth()/(float)m_renderWindow->getHeight(), 0.1f, 1000.f);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::pushMatrix( framework::MatrixType type )
	{
		glMatrixMode(glMatrixType[type]);
		glPushMatrix();
	}

	void OpenGLRenderer::popMatrix( framework::MatrixType type )
	{
		glMatrixMode(glMatrixType[type]);
		glPopMatrix();
	}

	void OpenGLRenderer::loadMatrix( framework::MatrixType type, const Matrix4f& matrix )
	{
		glMatrixMode(glMatrixType[type]);
		glLoadMatrixf(matrix);
	}

	void OpenGLRenderer::multiplyMatrix( framework::MatrixType type, const Matrix4f& matrix )
	{
		glMatrixMode(glMatrixType[type]);
		glMultMatrixf(matrix);
	}

	void OpenGLRenderer::beginRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}

	void OpenGLRenderer::endRender()
	{
		m_renderWindow->draw();
	}

	void OpenGLRenderer::drawBuffers(const VertexBuffer* vb, const IndexBuffer* ib)
	{
		vb->bind();
		ib->bind();

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(struct Vertex, position)));

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(struct Vertex, texcoord)));

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(offsetof(struct Vertex, normal)));

		glDrawElements(GL_TRIANGLES, ib->getIndexCount(), GL_UNSIGNED_SHORT, 0);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		ib->unbind();
		vb->unbind();
	}

	void OpenGLRenderer::drawCube(float size)
	{
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		//glColor3f(182.f/255.f, 252.f/255.f, 213.f/255.f);

		glColor3f(112/255.f, 219/255.f, 147/255.f);
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glEnd();

		glColor3f(174/255.f, 238/255.f, 238/255.f);
		glBegin(GL_QUADS);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glEnd();

		glColor3f(131/255.f, 111/255.f, 255/255.f);
		glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glEnd();

		glColor3f(255/255.f, 64/255.f, 64/255.f);
		glBegin(GL_QUADS);
		// Bottom face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glEnd();

		glColor3f(255/255.f, 127/255.f, 36/255.f);
		glBegin(GL_QUADS);		
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glEnd();

		glColor3f(255/255.f, 218/255.f, 185/255.f);
		glBegin(GL_QUADS);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f, -1.0f * size/2.f);  // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f * size/2.f, -1.0f * size/2.f,  1.0f * size/2.f);  // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f,  1.0f * size/2.f);  // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f * size/2.f,  1.0f * size/2.f, -1.0f * size/2.f);  // Top Left Of The Texture and Quad
		glEnd();

		glColor3f(1.f, 1.f, 1.f);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}

	void OpenGLRenderer::addTexture( std::string name, std::string fileName )
	{
		TextureIDMap::iterator idIter = m_textureIDs.find(name);
		if (idIter != m_textureIDs.end())
		{
			return;
		}
		TextureNameMap::iterator nameIter = m_textureNames.find(name);
		if (nameIter != m_textureNames.end())
		{
			return;
		}
		if (m_textureLoadType == framework::Load_Eager)
		{
			GLuint texId = loadTexture(fileName);
			m_textureIDs[name] = texId;
		}
		else
		{
			m_textureNames[name] = fileName;
		}
	}

	void OpenGLRenderer::setActiveTexture( const std::string& name )
	{
		TextureIDMap::iterator idIter = m_textureIDs.find(name);
		if (idIter == m_textureIDs.end())
		{
			TextureNameMap::iterator nameIter = m_textureNames.find(name);
			if (m_textureLoadType == framework::Load_Lazy && nameIter != m_textureNames.end())
			{
				GLuint texId = loadTexture(nameIter->second);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texId);
				m_textureIDs[name] = texId;
				m_textureNames.erase(nameIter);
			}
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, idIter->second);
		}
	}

	GLuint OpenGLRenderer::loadTexture( std::string& fileName )
	{
		Texture texture(fileName);
		GLuint textureHandle;
		glGenTextures(1,&textureHandle);

		glBindTexture(GL_TEXTURE_2D, textureHandle);

		glTexParameteri(GL_TEXTURE_2D, 0x8191, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, /*GL_CLAMP*/GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, /*GL_CLAMP*/GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			texture.getBPP(),
			texture.getWidth(),
			texture.getHeight(),
			0,
			texture.getImageFormat(),
			GL_UNSIGNED_BYTE,
			texture.getImageData()
			);
		return textureHandle;
	}

	void OpenGLRenderer::setTextureLoadType( framework::TextureLoadType loadType )
	{
		m_textureLoadType = loadType;
	}

	void OpenGLRenderer::drawQuad( Vector3f& point00, Vector3f& point11, bool hasTexture, int repeat )
	{
		if (hasTexture) glEnable(GL_TEXTURE_2D);
		//else glEnable(GL_COLOR_MATERIAL);
		glBegin(GL_QUADS);
		if (hasTexture) glTexCoord2f(0.f,0.f);
		glVertex3f(point00.x, point00.y, point00.z);
		if (hasTexture) glTexCoord2f(repeat*1.f,0.f);
		glVertex3f(point11.x, point11.y, point00.z);
		if (hasTexture) glTexCoord2f(repeat*1.f,repeat*1.f);
		glVertex3f(point11.x, point11.y, point11.z);
		if (hasTexture) glTexCoord2f(0.f,repeat*1.f);
		glVertex3f(point00.x, point00.y, point11.z);
		glEnd();
		if (hasTexture) glDisable(GL_TEXTURE_2D);
		//else glDisable(GL_COLOR_MATERIAL);
	}

	void OpenGLRenderer::enableFog()
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogi(GL_FOG_START, 120);
		glFogi(GL_FOG_END, 200);
		glFogf(GL_FOG_DENSITY,0.03f);
		glHint(GL_FOG_HINT,GL_FASTEST);
		float color[] = {0.9f, 0.9f, 0.9f, 1.0f};
		glFogfv(GL_FOG_COLOR, color);
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderer::disableFog()
	{
		glDisable(GL_FOG);
		glClearColor(0.f, 0.f, 0.f, 1.f);
	}

	void enableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void disableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::drawTiledPlane( int tileCount, int tileSize, int textureRepeat )
	{
		bool hasTexture = textureRepeat > 0;
		if (hasTexture) glEnable(GL_TEXTURE_2D);
		for (int z=-tileCount/2; z < tileCount/2-1; z++)
		{
			bool b=true;
			glBegin(GL_QUAD_STRIP);
			for (int x=-tileCount/2; x < tileCount/2; x++)
			{
				if (b)
				{
					if (hasTexture) glTexCoord2f(0.f,0.f);
					glVertex3f((float)x*tileSize, 0, (float)z*tileSize);
					if (hasTexture) glTexCoord2f(0.f,textureRepeat*1.f);
					glVertex3f((float)x*tileSize, 0, (float)(z+1)*tileSize);
					b=false;
				}
				else
				{
					if (hasTexture) glTexCoord2f(textureRepeat*1.f,0.f);
					glVertex3f((float)x*tileSize, 0, (float)z*tileSize);
					if (hasTexture) glTexCoord2f(textureRepeat*1.f,textureRepeat*1.f);
					glVertex3f((float)x*tileSize, 0, (float)(z+1)*tileSize);				
					b=true;
				}

			}
			glEnd();
		}

		if (hasTexture) glDisable(GL_TEXTURE_2D);
	}
}