#include "Actor.h"
#include"../Renderer/Renderer.h"
#include "components/RendererComponent.h"

namespace viper {
	FACTORY_REGISTER(Actor)

		Actor::Actor(const Actor& other) :
		Object{ other },
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform }
	{
		//copy components
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	void Actor::OnCollision(Actor* other) {
		auto collidables = GetComponents<ICollidable>();
		for (auto& collidable : collidables) {
			collidable->OnCollision(other);
		}
	}
	

	void Actor::Start() {
		for (auto& component : m_components) {
			component->Start();
		}
	}

	void Actor::Destroyed() {
		for (auto& component : m_components) {
			component->Destroyed();
		}
	}

	void viper::Actor::Update(float dt) {
	if (destroyed) return;

	if (lifespan > 0) {
		lifespan -= dt;
		if (lifespan <= 0) {
			destroyed = true;
			return;
		}
	}

	//update all components
	for (auto& component : m_components) {
		if (component->active) component->Update(dt);
	}
}

void viper::Actor::Draw(Renderer& renderer) {
	if (destroyed) return;

	for (auto& component : m_components) {
		if (component->active) { 
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}
			//rendererComponent->Draw(renderer);
		}
	}

	//renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
	component->owner = this;
	m_components.push_back(std::move(component));
}

void Actor::Read(const json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, tag);
	JSON_READ(value, lifespan);
	JSON_READ(value, persistent);

	if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform)); 


	if (JSON_HAS(value, components)) {
		for (auto& componentValue : JSON_GET(value, components).GetArray()) {
			std::string type;
			JSON_READ(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);
			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
}


}
