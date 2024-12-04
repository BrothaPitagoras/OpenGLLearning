#include <includes.h>
#include <stb_image.h>

class Texture
{
public:
	int texWidth, texHeight, nrChannels;
	unsigned int texture;
	unsigned char* data;

	Texture(const std::string& texturePath);
	~Texture();

	void bind();

	static void bind(GLenum gl_texture ,unsigned int texture);

private:

};
