#ifndef _Vertex_
#define _Vertex_

namespace smoke
{
	struct Vertex
	{
		Vertex()
		{
			position[0] = 0;
			position[1] = 0;
			position[2] = 0;
			normal[0] = 0;
			normal[1] = 0;
			normal[2] = 0;
			texcoord[0] = 0;
			texcoord[1] = 0;
		}
		Vertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v)
		{
			position[0] = px;
			position[1] = py;
			position[2] = pz;
			normal[0] = nx;
			normal[1] = ny;
			normal[2] = nz;
			texcoord[0] = u;
			texcoord[1] = v;
		}

		float position[3];
		float normal[3];
		float texcoord[2];
	};
}

#endif