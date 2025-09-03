#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"
#include "components/ColliderComponent.h"

namespace viper {
	void Scene::Update(float dt) {
		//update all actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}

		//remove destroyed actors
		std::erase_if(m_actors, [](auto& actor) {
			return (actor->destroyed);
		});
		//for (auto iter = m_actors.begin(); iter != m_actors.end();) {
		//	if ((*iter)->destroyed) {
		//		iter = m_actors.erase(iter);
		//	}
		//	else {
		//		iter++;
		//	}
		//}


	//check for collisions
	for (auto& actorA : m_actors) {
		for (auto& actorB : m_actors) {
			continue;

			if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

			auto colliderA = actorA->GetComponent<viper::ColliderComponent>();
			auto colliderB = actorB->GetComponent<viper::ColliderComponent>();

			//make sure both actors have a collider
			if (!colliderA || !colliderB) continue;

			if (colliderA->CheckCollision(*colliderB)) {
				actorA->OnCollision(actorB.get());
				actorB->OnCollision(actorA.get());
			}
		}
	}


	}


	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) {
			actor->Draw(renderer);
			}

		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start) {
		actor->scene = this;
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
		//load json
		viper::json::document_t document;
		if (viper::json::Load(sceneName, document) == false) {
			Logger::Error("Could not load scene {}", sceneName);
			return false;
		}
		//create scene
		Read(document);
		//start actors
		for (auto& actor : m_actors) {
			actor->Start();
		}
		return true;
	}

	void Scene::Read(const json::value_t& value) {
		//read prototypes
		if (JSON_HAS(value, prototypes)) {
		for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {

			auto actor = Factory::Instance().Create<Actor>("Actor");

			actor->Read(actorValue);

			std::string name = actor->name;
			Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
		}
		}

		//read actor
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");

				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}

	}
	


		
}

