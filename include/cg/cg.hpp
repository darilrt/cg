#ifndef CG_H
#define CG_H

// include engine core
#include "core/Window.hpp"
#include "core/Material.hpp" 
#include "core/Shader.hpp"
#include "core/Mesh.hpp"
#include "core/MeshRenderer.hpp"
#include "core/Camera.hpp"
#include "core/ParticleSystem.hpp"
// #include "core/socket.hpp" temporalmente no

// namespaces
#include "math.hpp"
#include "time.hpp"
#include "display.hpp"
#include "debug.hpp"
#include "shader.hpp"
#include "random.hpp"
#include "physics.hpp"

// enums
#include "key_code.hpp"

// classes
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include "Scene.hpp"

// components
#include "components/Sprite.hpp"
#include "components/ParticleEmitter.hpp"
#include "components/BoxCollider2D.hpp"

namespace cg {
	void run(cg::Scene *scene);
}

#endif // CG_H