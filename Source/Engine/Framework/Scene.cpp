#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Components/ColliderComponent.h"

namespace viper
{
	void Scene::Update(float dt) {
		for (auto& Actor : m_actors) {
			if (Actor->active) {
				Actor->Update(dt);
			}
		}

		std::erase_if(m_actors, [](auto& actor)
			{
				return (actor->destroyed);
			});

		

		for (auto& ActorA : m_actors) {
			for (auto& ActorB : m_actors) {

				continue;

				if (ActorA == ActorB || (ActorA->destroyed || ActorB->destroyed)) continue;

				auto colliderA = ActorA->GetComponent<ColliderComponent>();
				auto colliderB = ActorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					ActorA->OnCollision(ActorB.get());
					ActorB->OnCollision(ActorA.get());
				}

			}
		}
	}
	void Scene::Draw(Renderer& renderer) {
		for (auto& Actor : m_actors) {
			if (Actor->active) {
				Actor->Draw(renderer);
			}
		}
	}
	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start) {
		actor->m_scene = this;
		if (start) actor->Start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force) {
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if (!(*iter)->persistent || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	bool Scene::Load(const std::string& sceneName) {
		viper::json::document_t document;
		if (!viper::json::Load(sceneName, document)) {
			viper::Logger::Error("Failed to load scene: {}", sceneName);
			return false;
		}
		Read(document);
		for (auto& actor : m_actors) {
			actor->Start();
		}

		return true;
	}


	void Scene::Read(const json::value_t& value) {
		//Read Prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				if (!actor) {
					continue;
				}
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		//Read Actor
		if (JSON_HAS(value, m_actors)) {
			for (auto& actorValue : JSON_GET(value, m_actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}