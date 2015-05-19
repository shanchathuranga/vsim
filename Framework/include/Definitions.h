#ifndef _Definitions_
#define _Definitions_

namespace framework
{
	const float PI = 3.14159f;
	const float TWO_PI = 6.28318f;
	const float DEG2RAD = 0.01745f;
	const float RAD2DEG = 57.29577f;

	enum MatrixType
	{
		Matrix_ModelView,
		Matrix_Projection,
		Matrix_Texture
	};

	enum TransformSpace
	{
		Transform_Local_Space,
		Transform_World_Space
	};

	enum VertexDataType
	{
		Vertex_Position,
		Vertex_Normal,
		Vertex_Color,
		Vertex_Texcoord
	};

	enum VertexDataSize
	{
		VertexData_Float3,
		VertexData_Float2,
		VertexData_Float,
		VertexData_Short,
		VertexData_Uint
	};

	enum TextureLoadType
	{
		Load_Lazy,
		Load_Eager
	};

	enum KeyCode
	{
		SK_UNKNOWN = 0,
		SK_0,
		SK_1,
		SK_2,
		SK_3,
		SK_4,
		SK_5,
		SK_6,
		SK_7,
		SK_8,
		SK_9,
		SK_UP,
		SK_DOWN,
		SK_LEFT,
		SK_RIGHT,
		SK_W,
		SK_A,
		SK_S,
		SK_D,
		SK_SPACE,
		SK_Q,
		SK_E,
		SK_Z,
		SK_C,
		SK_I,
		SK_J,
		SK_K,
		SK_L,
		SK_ESCAPE,
		SK_KEY_COUNT
	};

	enum KeyModifier 
	{
		Mod_None = 0,
		Mod_Shift = 1,
		Mod_Ctrl = 2,
		Mod_Alt = 4	
	};

	enum MouseButton
	{
		MouseButton_Left,
		MouseButton_Middle,
		MouseButton_Right,
		MouseButton_None
	};

}

#endif