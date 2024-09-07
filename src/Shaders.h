#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/ext/matrix_clip_space.hpp"

struct ShaderProgramSource {
	std::string VertexShader;
	std::string FragmentShader;
};


class Shader {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader( const std::string& filepath );
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform4f( const std::string& name, float v1,float v2, float v3, float v4 );
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void setUniform1i( const std::string& name, int value);

private:
	ShaderProgramSource ParseShader( const std::string& filepath ) const;
	int getUniformLocation( const std::string& name );
	unsigned int CreateShader( const std::string& vertexShader, const std::string& fragmentShader ) const;
	unsigned int CompileShader( unsigned int type, const std::string& source ) const;
};