//#include <shadering/shadering.hpp>
//
//
//const std::string shadering::loadShaderSource(const std::string& filePath) {
//
//    std::string content;
//    std::ifstream fileStream(filePath, std::ios::binary);
//
//    if (!fileStream)
//    {
//        std::cerr << "Error opening file: " << filePath << std::endl;
//        return "";
//    }
//
//    std::stringstream buffer;
//    buffer << fileStream.rdbuf(); // Read the entire file into the stringstream
//    return buffer.str();
//}
//
//
//unsigned int shadering::compileVertexShader(const std::string& vertexShaderSource) {
//    // Error checking variables
//    int success;
//    char infoLog[512];
//
//    // Vertex Shader ----------
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//    // Assign vertex shader source code to vertex shader variable
//    const char* shader_c_str = vertexShaderSource.c_str();
//    glShaderSource(vertexShader, 1, &shader_c_str, NULL);
//
//    // Compile vertex shader
//    glCompileShader(vertexShader);
//
//
//    // Error checking on compilation of vertex shader
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//        return -1;
//    }
//
//    return vertexShader;
//}
//
//unsigned int shadering::compileFragmentShader(const std::string& fragmentShaderSource) {
//
//    // Error checking variables
//    int success;
//    char infoLog[512];
//    
//    // Fragment Shader ---------
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//    // Assign fragment shader source code to fragment shader variable
//    const char* shader_c_str = fragmentShaderSource.c_str();
//    glShaderSource(fragmentShader, 1, &shader_c_str, NULL);
//
//
//    // Compile fragment shader
//    glCompileShader(fragmentShader);
//
//    // Error checking on compilation of fragment shader
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//        return -1;
//    }
//
//    return fragmentShader;
//}
//
//unsigned int shadering::linkShaderProgram(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath) {
//    // Error checking variables
//    int success;
//    char infoLog[512];
//
//    unsigned int shaderProgram;
//
//
//    const std::string vertexShaderSource = shadering::loadShaderSource(vertexShaderSourcePath);
//    const std::string fragmentShaderSource= shadering::loadShaderSource(fragmentShaderSourcePath);
//
//    unsigned int vertexShader = shadering::compileVertexShader(vertexShaderSource);
//    unsigned int fragmentShader = shadering::compileFragmentShader(fragmentShaderSource);
//    shaderProgram = glCreateProgram();
//
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // error checking program linking --
//
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success)
//    {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//        return -1;
//    }
//
//    // after compiling and linking we can clean the shader variables
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    return shaderProgram;
//}
//
