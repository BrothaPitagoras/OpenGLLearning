#include <shadering/Texture.hpp>

Texture::Texture(const std::string& texturePath) {

    glGenTextures(1, &this->texture);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    this->data = stbi_load(texturePath.c_str(), &this->texWidth, &this->texHeight, &this->nrChannels, 0);
    if (this->data)
    {
        if (texturePath.find(".jpg") != std::string::npos)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texWidth, this->texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (texturePath.find(".png") != std::string::npos)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texWidth, this->texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {

}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::bind(GLenum gl_texture, unsigned int texture) {
    glActiveTexture(gl_texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}