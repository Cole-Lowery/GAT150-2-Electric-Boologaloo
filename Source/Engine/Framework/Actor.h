#pragma once
#include "Framework/Object.h"
#include "Math/Transform.h"
#include "Renderer/Mesh.h"
#include "Scene.h"
#include "Renderer/Texture.h"
#include "Component.h"

#include <vector>
#include <memory>
#include <string>

namespace viper{
	class Component;
	class Actor : public Object {
	public:
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0 };

		bool persistent{ false };

		Transform transform;
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor( const Transform& transform) :
			transform{ transform }
			 {}

		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		virtual void Start();
		virtual void Destroyed();

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other);


		//components
		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

		void Read(const json::value_t& value);
	protected:
		std::vector<std::unique_ptr<Component>> m_components;
		
		

		// Inherited via Serializeable

	};

	template<typename T>
	inline T* Actor::GetComponent() {
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::GetComponents() {
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}
