#ifndef _RenderSystem_
#define _RenderSystem_

#include <map>
#include "vmath.h"
#include "InputEventHandler.h"
#include "OBJModel.h"
#include "ICamera.h"
#include "IKeyBoard.h"

namespace smoke
{
	class RenderWindow;
	class OpenGLRenderer;
	class KeyBoard;
	class IRenderObject;

	class RenderSystem
	{
	public:
		RenderSystem();
		~RenderSystem();

		void update(float elapsedTime);
		void initialize();
		InputEventHandler& getInputEventHandler();
		ICamera* createCamera(CameraType type, const std::string& name);
		void setActiveCamera(ICamera* camera);
		ICamera* getActiveCamera();
		framework::IKeyBoard* getKeyBoard(); // need to move to the InputSystem
		void addTexture(std::string name, std::string path);
		IRenderObject* createRenderObject(OBJModel* model);
		IRenderObject* createRenderObject(std::string& textureName, std::string& texturePath, 
			const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices);
		void addToCurrentFrame(IRenderObject* renderObject, Matrix4f& mat);
		bool isContextAvailable();
		void startFrame();
		void drawCurrentFrame();
		void endFrame();

	private:
		void drawObjectRecursive(IRenderObject* object, Matrix4f& mat);

		RenderWindow* mRenderWindow;
		OpenGLRenderer* mRenderer;
		InputEventHandler* mInputEventHandler;
		KeyBoard* mKeyBoard;
		ICamera* mCamera;
		std::map<IRenderObject*,Matrix4f> m_renderObjectsInCurrentFrame;
	};
}

#endif