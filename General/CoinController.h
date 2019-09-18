#pragma once
#include "EntityComponent.h"

namespace Hesketh
{
	static int CoinsRemaining = 0;
	static int NPCCoinsCollected = 0;
	static int PlayerCoinsCollected = 0;

	class CoinController : public EntityComponent
	{
	private:
		Entity* m_player = nullptr;
		Entity* m_npc = nullptr;
	public:
		CoinController(Entity* player, Entity* npc);
		~CoinController();

		void Start() override;
		void Update() override;
		void FixedUpdate() override;
	};
}