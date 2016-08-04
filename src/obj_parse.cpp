#include "mesh.hpp"

namespace gfx
{
namespace util
{
	char parse_obj(const char *path, unsigned int *nverts, vertex_t *&vertices)
	{
		std::vector<math::vec3f> temp_locations, out_locations;
		std::vector<math::vec2f> temp_uvs, out_uvs;
		std::vector<math::vec3f> temp_normals, out_normals;

		std::vector<unsigned int> location_indices;
		std::vector<unsigned int> uv_indices;
		std::vector<unsigned int> normal_indices;

		FILE *file = fopen(path, "r");
		if(file == 0)	return -1;

		char line[128], success = 1;
		while(1)
		{
			// read first word of line
			int res = fscanf(file, "%s", line);
			if(res == EOF)	break;

			if(strcmp(line, "v") == 0) // location vertex
			{
				math::vec3f vert;
				if(fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z) != 3)
				{
					printf("ERROR PARSING OBJ: WRONG MATCHES IN V\n");
					success = 0;
					break;
				}

				// printf("vertex: (%f, %f, %f)\n", vert.x, vert.y, vert.z);
				temp_locations.push_back(vert);
			}
			else if(strcmp(line, "vt") == 0) // uv vertex
			{
				math::vec2f uv;
				if(fscanf(file, "%f %f\n", &uv.x, &uv.y) != 2)
				{
					printf("ERROR PARSING OBJ: WRONG MATCHES IN VT\n");
					success = 0;
					break;
				}
				temp_uvs.push_back(uv.normal()); // they are NOT unit vectors by default
			}
			else if(strcmp(line, "vn") == 0) // normal vertex
			{
				math::vec3f normal;
				if(fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z) != 3)
				{
					printf("ERROR PARSING OBJ: WRONG MATCHES IN VN\n");
					success = 0;
					break;
				}
				temp_normals.push_back(normal);
			}
			else if(strcmp(line, "f") == 0)
			{
				unsigned int location_index[3], uv_index[3], normal_index[3];
				if(fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u", 	&location_index[0], &uv_index[0], &normal_index[0],
																&location_index[1], &uv_index[1], &normal_index[1],
																&location_index[2], &uv_index[2], &normal_index[2]) != 9)
				{
					printf("ERROR PARSING OBJ: WRONG MATCHES IN F\n");
					success = 0;
					break;
				}

				location_indices.	push_back(location_index[0]);
				location_indices.	push_back(location_index[1]);
				location_indices.	push_back(location_index[2]);

				uv_indices.			push_back(uv_index[0]);
				uv_indices.			push_back(uv_index[1]);
				uv_indices.			push_back(uv_index[2]);

				normal_indices.		push_back(normal_index[0]);
				normal_indices.		push_back(normal_index[1]);
				normal_indices.		push_back(normal_index[2]);
			}
		}

		fclose(file);

		for(int i = 0; i < location_indices.size(); i++)
		{
			out_locations.	push_back(temp_locations[location_indices[i] - 1]); // subtract 1 because obj files index at 1 while c++ indexes at 0
			out_uvs.		push_back(temp_uvs[uv_indices[i] - 1]);
			out_normals.	push_back(temp_normals[normal_indices[i] - 1]);
		}

		// create array of vertices
		if(vertices != 0) free(vertices);
		vertices = (vertex_t *) malloc(out_locations.size() * sizeof(vertex_t));

		math::vec4f white(1.0f, 1.0f, 1.0f, 1.0f); // temporary
		for(int i = 0; i < location_indices.size(); i++)
		{
			vertices[i] = vertex_t(out_locations[i], out_uvs[i], white, out_normals[i]);
		}

		*nverts = out_locations.size();

		return 0;
	}
};
};