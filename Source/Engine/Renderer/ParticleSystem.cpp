#include "ParticleSystem.h"
#include "Renderer.h"

namespace viper {

	bool ParticleSystem::Initialize(int poolSize) {
		//reserve particles in pool
		m_particles.resize(poolSize);


		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0);
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}
	void ParticleSystem::AddParticle(const Particle particle) {
		Particle* pParticle = GetFreeParticle();
		if (pParticle) {
			*pParticle = particle;

			pParticle->active = true;
			
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (particle.active == false) return &particle;
		}

		return nullptr;
	}
}