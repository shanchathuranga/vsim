#include "RenderWindow.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

namespace smoke
{
	framework::KeyCode getLocalKey( SDLKey sdlKey );

	RenderWindow::RenderWindow(InputEventHandler* inputEventHandler): m_window(NULL), m_width(0), m_height(0),
		m_inputEventHandler(inputEventHandler)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	}

	RenderWindow::~RenderWindow()
	{
		SDL_Quit();
	}

	void RenderWindow::create( std::string title, int width, int height, bool fullscreen )
	{
		m_window = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL);
		SDL_WM_SetCaption(title.c_str(), NULL);
		SDL_WM_GrabInput(SDL_GRAB_ON);
		glewInit();
		m_width = width;
		m_height = height;
	}

	bool RenderWindow::handleEvents()
	{
		while (SDL_PollEvent(&m_evt))
		{
			switch (m_evt.type)
			{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				{
					m_inputEventHandler->injectKeyDown(getLocalKey(m_evt.key.keysym.sym));
				}
				break;
			case SDL_KEYUP:
				{
					m_inputEventHandler->injectKeyUp(getLocalKey(m_evt.key.keysym.sym));
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					framework::MouseButton btn = framework::MouseButton_None;
					if (m_evt.button.button == SDL_BUTTON_LEFT) btn = framework::MouseButton_Left;
					if (m_evt.button.button == SDL_BUTTON_RIGHT) btn = framework::MouseButton_Right;
					if (m_evt.button.button == SDL_BUTTON_MIDDLE) btn = framework::MouseButton_Middle;
					m_inputEventHandler->injectMouseButtonDown(btn, m_evt.button.x, m_evt.button.y);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					framework::MouseButton btn = framework::MouseButton_None;
					if (m_evt.button.button == SDL_BUTTON_LEFT) btn = framework::MouseButton_Left;
					if (m_evt.button.button == SDL_BUTTON_RIGHT) btn = framework::MouseButton_Right;
					if (m_evt.button.button == SDL_BUTTON_MIDDLE) btn = framework::MouseButton_Middle;
					m_inputEventHandler->injectMouseButtonUp(btn, m_evt.button.x, m_evt.button.y);
				}
				break;
			case SDL_MOUSEMOTION:
				{
					framework::MouseButton btn = framework::MouseButton_None;
					if (m_evt.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) btn = framework::MouseButton_Left;
					if (m_evt.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) btn = framework::MouseButton_Right;
					if (m_evt.motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) btn = framework::MouseButton_Middle;
					m_inputEventHandler->injectMouseMotion(btn, m_evt.motion.x, m_evt.motion.y, m_evt.motion.xrel, m_evt.motion.yrel);
				}
				break;
			default:
				break;
			}
		}
		return true;
	}

	void RenderWindow::draw()
	{
		SDL_GL_SwapBuffers();
		SDL_Delay(1);
	}

	int RenderWindow::getWidth() const
	{
		return m_width;
	}

	int RenderWindow::getHeight() const
	{
		return m_height;
	}

	void RenderWindow::setMouseVisibility( bool visible )
	{
		if (visible)
			SDL_ShowCursor(SDL_ENABLE);
		else
			SDL_ShowCursor(SDL_DISABLE);
	}

	void RenderWindow::setMousePosition( int px, int py )
	{
		SDL_WarpMouse(px, py);
	}

	void RenderWindow::getMousePosition( int& px, int& py )
	{
		SDL_GetMouseState(&px, &py);
	}

	framework::KeyCode getLocalKey( SDLKey sdlKey )
	{
		switch(sdlKey)
		{
		case SDLK_0:
			return framework::SK_0;
		case SDLK_1:
			return framework::SK_1;
		case SDLK_2:
			return framework::SK_2;
		case SDLK_3:
			return framework::SK_3;
		case SDLK_4:
			return framework::SK_4;
		case SDLK_5:
			return framework::SK_5;
		case SDLK_6:
			return framework::SK_6;
		case SDLK_7:
			return framework::SK_7;
		case SDLK_8:
			return framework::SK_8;
		case SDLK_9:
			return framework::SK_9;
		case SDLK_UP:
			return framework::SK_UP;
		case SDLK_DOWN:
			return framework::SK_DOWN;
		case SDLK_LEFT:
			return framework::SK_LEFT;
		case SDLK_RIGHT:
			return framework::SK_RIGHT;
		case SDLK_w:
			return framework::SK_W;
		case SDLK_a:
			return framework::SK_A;
		case SDLK_s:
			return framework::SK_S;
		case SDLK_d:
			return framework::SK_D;
		case SDLK_SPACE:
			return framework::SK_SPACE;
		case SDLK_q:
			return framework::SK_Q;
		case SDLK_e:
			return framework::SK_E;
		case SDLK_z:
			return framework::SK_Z;
		case SDLK_c:
			return framework::SK_C;
		case SDLK_i:
			return framework::SK_I;
		case SDLK_j:
			return framework::SK_J;
		case SDLK_k:
			return framework::SK_K;
		case SDLK_l:
			return framework::SK_L;
		case SDLK_ESCAPE:
			return framework::SK_ESCAPE;
		default:
			return framework::SK_UNKNOWN;
		}
		return framework::SK_UNKNOWN;
	}
}