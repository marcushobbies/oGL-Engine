#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(){

}

void ShaderProgram::generateProgram() {
	programId = glCreateProgram();
}

void ShaderProgram::loadShader(const char* path, int type) {
	std::ifstream shader(path);
	std::stringstream sSource;
	std::string source;

	sSource << shader.rdbuf();
	source = sSource.str();

	shaderSources.push_back((GLchar*)source.c_str());
	shader.close();

	int id = glCreateShader(type);
	shaderIds.push_back(id);

	glShaderSource(id, 1, &shaderSources[shaderSources.size()-1], NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< type <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}

void ShaderProgram::loadShader(const char* path) {
	std::ifstream shader(path);
	std::stringstream sSource;
	std::string source;

	sSource << shader.rdbuf();
	source = sSource.str();

	shaderSources.push_back((GLchar*)source.c_str());
	shader.close();

	std::string extension = path;
	extension = extension.erase(0, extension.find("."));

	int id = glCreateShader(extensionTypes[std::distance(extensions, std::find(std::begin(extensions), std::end(extensions), extension))]);

	shaderIds.push_back(id);

	glShaderSource(id, 1, &shaderSources[shaderSources.size()-1], NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< extension <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}

void ShaderProgram::attachShaders() {
	for (int id : shaderIds) {
		glAttachShader(programId, id);
	}
	glLinkProgram(programId);

	for (int id : shaderIds) {
        glDetachShader(programId, id);
		glDeleteShader(id);
	}
}


void ShaderProgram::setInt(const char* name, int val) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform1i(locationPath, val);
}
void ShaderProgram::setFloat(const char* name, float val) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform1f(locationPath, val);
}
void ShaderProgram::setVec3(const char* name, float x, float y, float z) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform3f(locationPath, x, y, z);
}
void ShaderProgram::setVec4(const char* name, float x, float y, float z, float w) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform4f(locationPath, x, y, z, w);
}

void ShaderProgram::setVec3(const char* name, glm::vec3 pos) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform3f(locationPath, pos.x, pos.y, pos.z);
}
void ShaderProgram::setVec4(const char* name, glm::vec4 pos) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniform4f(locationPath, pos.x, pos.y, pos.z, pos.w);
}

void ShaderProgram::setMatrix4f(const char* name, GLfloat* val) const{
		int locationPath = glGetUniformLocation(programId, name);
		glUniformMatrix4fv(locationPath, 1, GL_FALSE, val);
}