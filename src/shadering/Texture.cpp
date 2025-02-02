//#include <shadering/Texture.hpp>
//
//Texture::Texture(const std::string& texturePath) {
//    glGenTextures(1, &this->textureId);
//    glBindTexture(GL_TEXTURE_2D, textureId);
//    // set the texture wrapping/filtering options (on the currently bound texture object)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    stbi_set_flip_vertically_on_load(true);
//    this->data = stbi_load(texturePath.c_str(), &this->texWidth, &this->texHeight, &this->nrChannels, 0);
//    if (this->data)
//    {
//        if (texturePath.find(".jpg") != std::string::npos)
//        {
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texWidth, this->texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//            glGenerateMipmap(GL_TEXTURE_2D);
//        }
//        else if (texturePath.find(".png") != std::string::npos)
//        {
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texWidth, this->texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//            glGenerateMipmap(GL_TEXTURE_2D);
//        }
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//}
//
//Texture::~Texture() {
//
//}
//
//void Texture::bind() {
//    glBindTexture(GL_TEXTURE_2D, textureId);
//}
//
//void Texture::activateAndBind(unsigned int activationIndex) {
//    // The main purpose of texture units is to allow us to use more than 1 texture in our shaders.
//    // By assigning texture units to the samplers, we can bind to multiple textures at once as long 
//    // as we activate the corresponding texture unit first. 
//    // Just like glBindTexture we can activate texture units using glActiveTexture passing in the texture unit we'd like to use
//    glActiveTexture(activationIndex);
//    glBindTexture(GL_TEXTURE_2D, textureId);
//}