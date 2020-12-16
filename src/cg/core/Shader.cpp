#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <map>

#include "cg/debug.hpp"
#include "cg/core/shader.hpp"

namespace cg {
	using namespace debug;
	namespace core {
		std::string read_lines(const std::string path) {
			try {
				std::ifstream ifs(path);
				
				if (ifs.is_open()) {
					log("Loading file", path);
				}
				else {
					log("Failed to open", path);
					return "";
				}
				
				std::string lines;
				std::string line;

				while (std::getline(ifs, line)) {
					lines += "\n" + line;
				}

				return lines;
			}
			catch (const std::ifstream::failure& e) {
				log("Cannot open file \"" + path + "\"");
				return "";
			}
		}

		void print_shader_log(int shader) {
			if(glIsShader(shader)) {
				int infoLogLength = 0;
				int maxLength = infoLogLength;
				
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				char* infoLog = new char[maxLength];
				
				glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
				if(infoLogLength > 0) {
					log(infoLog);
				}
				
				delete[] infoLog;
			} else {
				std::string _log = "Name ";
				_log += std::to_string(shader);
				_log += " is not a shader";
				log(_log);
			}
		}

		Shader::Shader(const std::string vertex, const std::string fragment) {
			std::string v_source = read_lines(vertex);
			std::string f_source = read_lines(fragment);
			
			GLuint program_id = glCreateProgram();
			
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			const GLchar* vertexShaderSource[] = {v_source.c_str()};
			glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
			glCompileShader(vertexShader);

			GLint vShaderCompiled = GL_FALSE;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

			if(vShaderCompiled != GL_TRUE) {
				log("Unable to compile vertex shader %d!\n", vertexShader);
				print_shader_log(vertexShader);
			}

			glAttachShader(program_id, vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			const GLchar* fragmentShaderSource[] = {f_source.c_str()};
			glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);

			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
			
			if( fShaderCompiled != GL_TRUE ) {
				log("Unable to compile fragment shader");
				print_shader_log(fragmentShader);
			}
			
			glAttachShader(program_id, fragmentShader);

			glLinkProgram(program_id);
			
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			this->vertex_path = vertex;
			this->fragment_path = fragment;
			this->program = program_id;
		}

		void Shader::add_uniform(const std::string name) {
			int uniform = glGetUniformLocation(this->program, name.c_str());
			this->uniforms[name] = uniform;
		}
	}
}