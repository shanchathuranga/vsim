#include "RenderSystem.h"
#include "InputEventHandler.h"
#include "RenderWindow.h"
#include "OpenGLRenderer.h"
#include "RenderObject.h"
#include "KeyBoard.h"
#include "FPSCamera.h"
#include "OpenGLVBO.h"
#include <iostream>

namespace smoke
{
	RenderSystem::RenderSystem() : mCamera(NULL)
	{
		mInputEventHandler = new InputEventHandler;
		mRenderWindow = new RenderWindow(mInputEventHandler);
		mRenderWindow->setMouseVisibility(false);
		mRenderer = new OpenGLRenderer;
		mKeyBoard = new KeyBoard;
		mInputEventHandler->addKeyListener(mKeyBoard);
		//mCamera = new FPSCamera(*mKeyBoard, *mRenderWindow);
		//mCamera->init(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
	}

	RenderSystem::~RenderSystem()
	{
		delete mKeyBoard;
		delete mRenderer;
		delete mRenderWindow;
		delete mInputEventHandler;
	}

	ICamera* RenderSystem::createCamera(CameraType type, const std::string& name)
{
		switch(type)
		{
		case CAMERA_FPS:
			return new FPSCamera(name, *mKeyBoard, *mRenderWindow);
		case CAMERA_3RD_PERSON:
			return NULL;
		case CAMERA_FREE:
			return NULL;
		}
		return NULL;
	}

	void RenderSystem::setActiveCamera(ICamera* camera)
	{
		mCamera = camera;
	}

	void RenderSystem::initialize()
	{
		mRenderWindow->create("Game", 900, 600, false);
		mRenderer->initialize(mRenderWindow);
	}

	InputEventHandler& RenderSystem::getInputEventHandler()
	{
		return *mInputEventHandler;
	}

	bool RenderSystem::isContextAvailable()
	{
		return mRenderWindow->handleEvents();
	}

	void RenderSystem::startFrame()
	{
		return mRenderer->beginRender();
	}

	void RenderSystem::endFrame()
	{
		return mRenderer->endRender();
	}

	IRenderObject* RenderSystem::createRenderObject( OBJModel* model )
	{
		if ( !model )
		{		
			return new RenderObject(NULL);
		}
		const std::map<std::string,std::string>& textures = model->getTextures();
		const std::vector<Vertex>& vertices = model->getVertexData();

		OpenGLVBO* vbo = new OpenGLVBO;
		VertexBuffer* vb = new VertexBuffer(vertices);
		vbo->setVertexBuffer(vb);

		for (std::map<std::string,std::string>::const_iterator it = textures.begin(), eit = textures.end(); it != eit; ++it)
		{
			mRenderer->addTexture(it->first, it->second);

			const std::vector<unsigned short>& indices = model->getIndexData(it->first);
			IndexBuffer* ib = new IndexBuffer(indices);
			vbo->addIndexBuffer(it->first, ib);
		}

		return new RenderObject(vbo);
	}

	IRenderObject* RenderSystem::createRenderObject(std::string& textureName, std::string& texturePath, 
		const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices)
	{
		OpenGLVBO* vbo = new OpenGLVBO;
		VertexBuffer* vb = new VertexBuffer(vertices);
		vbo->setVertexBuffer(vb);
		mRenderer->addTexture(textureName, texturePath);
		IndexBuffer* ib = new IndexBuffer(indices);
		vbo->addIndexBuffer(textureName, ib);
		return new RenderObject(vbo);
	}

	void RenderSystem::drawCurrentFrame()
	{
		if ( !mCamera )
		{
			std::cout << "Active camera not found" << std::endl;
			return;
		}
		Matrix4f cam;
		if (mCamera->getType() == CAMERA_FPS)
		{
			FPSCamera* fpsCamera = static_cast<FPSCamera*>(mCamera);
			if ( !fpsCamera->m_isInit )
			{
				std::cout << "Unsupported camera type" << std::endl;
				return;
			}
			fpsCamera->update(cam);
		}
		else
		{
			std::cout << "Uninitialized camera cannot be active" << std::endl;
			return;
		}
		
		mRenderer->pushMatrix(framework::Matrix_ModelView);
		mRenderer->multiplyMatrix(framework::Matrix_ModelView, cam);
		
		std::map<IRenderObject*,Matrix4f>::iterator it = m_renderObjectsInCurrentFrame.begin();
		std::map<IRenderObject*,Matrix4f>::iterator eit = m_renderObjectsInCurrentFrame.end();

		while ( it != eit)
		{
// 			RenderObject* renderObject = static_cast<RenderObject*>(it->first);
// 			glm::mat4& mat = it->second;
			drawObjectRecursive(it->first, it->second);
			++it;
		}

		mRenderer->popMatrix(framework::Matrix_ModelView);
		m_renderObjectsInCurrentFrame.clear();
	}

	void RenderSystem::drawObjectRecursive(IRenderObject* object, Matrix4f& mat)
	{
		RenderObject* robj = static_cast<RenderObject*>(object);
		if (robj->getVBO())
		{
			OpenGLVBO* vbo = static_cast<OpenGLVBO*>(robj->getVBO());
			mRenderer->pushMatrix(framework::Matrix_ModelView);
			mRenderer->multiplyMatrix(framework::Matrix_ModelView, mat);
			vbo->render(*mRenderer);
			mRenderer->popMatrix(framework::Matrix_ModelView);
		}
		
		RenderObject::RenderChildren& children = robj->getChildren();
		for (RenderObject::RenderChildren::iterator sit = children.begin(), eit = children.end(); sit != eit; ++sit)
		{
			const std::string& name = sit->first;
			std::pair<IRenderObject*,Matrix4f>& data = sit->second;
			drawObjectRecursive(data.first, /*mat **/ data.second);
		}
	}

	void RenderSystem::addToCurrentFrame( IRenderObject* renderObject, Matrix4f& mat )
	{
		m_renderObjectsInCurrentFrame[renderObject] = mat;
	}

	void RenderSystem::addTexture( std::string name, std::string path )
	{
		mRenderer->addTexture(name, path);
	}

	ICamera* RenderSystem::getActiveCamera()
	{
		return mCamera;
	}

	void RenderSystem::update( float elapsedTime )
	{
		startFrame();
		drawCurrentFrame();
		endFrame();
	}

	framework::IKeyBoard* RenderSystem::getKeyBoard()
	{
		return mKeyBoard;
	}

}