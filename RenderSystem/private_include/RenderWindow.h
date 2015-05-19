#ifndef _RenderWindow_
#define _RenderWindow_

#include <Windows.h>
#include <string>
#include <Windows.h>
#include "GL/glew.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include "SDL.h"
#include "InputEventHandler.h"
#undef main

namespace smoke
{
	class RenderWindow
	{
	public:
		RenderWindow(InputEventHandler* inputEventHandler);
		~RenderWindow();
		void create(std::string title, int width, int height, bool fullscreen);
		bool handleEvents();
		void draw();
		int getWidth() const;
		int getHeight() const;
		void setMouseVisibility(bool visible);
		void setMousePosition(int px, int py);
		void getMousePosition(int& px, int& py);

		static const std::string& getTypeNameStatic();
		const std::string& getTypeName() const;

	private:
		SDL_Surface* m_window;
		SDL_Event m_evt;
		int m_width;
		int m_height;
		InputEventHandler* m_inputEventHandler;
	};
}

#endif