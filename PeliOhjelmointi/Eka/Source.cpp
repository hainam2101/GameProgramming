#include <vector>
#include <algorithm>
#include <Windows.h>
#include <iostream>
#include <map>
#include <functional>

using Callbacks = std::map<int, std::function <void(void)>>;
using KeyStates = std::map < int, bool >;

class GameObject 
{
public:
	virtual void update(float delta) = 0;
	virtual ~GameObject() = default;
};

using GameObjects = std::vector < GameObject* >;


class Player : public GameObject {
public:
	virtual void update(float delta) override 
	{
		// std::cout << "player moving" << std::endl;
	}
	~Player() = default;
};

class Enemy : public GameObject 
{
private:
	int hp = 5;
public:
	~Enemy() = default;
	virtual void update(float delta) override 
	{
		// std::cout << "enemy moving" << std::endl;
	}

	void isHit() 
	{ 
		--hp; 
		std::cout << "Enemy is hit by a projectile!" << std::endl;
	}
	bool isAlive() { return hp > 0; }
};

class Projectile : public GameObject 
{
public:
	~Projectile() = default;
	virtual void update(float delta) override {}
};

class PickableItem : public GameObject 
{
public:
	~PickableItem() = default;
	virtual void update(float delta) override {}
};


template <class T>
T* getFirst(GameObjects& objects) 
{
	auto it = std::find_if(std::begin(objects), std::end(objects), [](GameObject* obj) 
	{
		return typeid(*obj) == typeid(T);
	});
	
	if (it == std::end(objects)) return nullptr;
	return static_cast<T*>(*it);
}

template <class T>
void removeFirst(GameObjects& objects) 
{
	auto it = std::find_if(std::begin(objects), std::end(objects), [](GameObject* obj) 
	{
		return typeid(*obj) == typeid(T);
	});
	
	if (it == std::end(objects)) return;
	delete *it;
	objects.erase(it);
}

void makeProjectileCollide(GameObjects& objects) 
{
	Projectile* projectile = getFirst<Projectile>(objects);

	if (projectile == nullptr) return;
	Enemy* enemy = getFirst<Enemy>(objects);

	if (enemy == nullptr) return;
	enemy->isHit();

	if (!enemy->isAlive()) 
	{
		removeFirst<Enemy>(objects);
		std::cout << "Enemy killed, removing enemy from list" << std::endl << std::endl;
	}
}

void makePlayerCollide(GameObjects& objects) 
{
	Player* p = getFirst<Player>(objects);

	if (p == nullptr) return;
	PickableItem* item = getFirst<PickableItem>(objects);

	if (item == nullptr) return;

	removeFirst<PickableItem>(objects);
	std::cout << "Player hit an item! Item removed from list" << std::endl << std::endl;
}

int main(int, char**) 
{
	bool windowIsOpen{ true };

	GameObjects objects
	{
		new Player,
		new Enemy,
		new Projectile,
		new PickableItem
	};

	Callbacks callbacks
	{
		std::make_pair(0x31, [&objects](){ objects.push_back(new Player); std::cout << "New Player added" << std::endl << std::endl;; }),
		std::make_pair(0x32, [&objects](){ objects.push_back(new Enemy); std::cout << "New Enemy added" << std::endl << std::endl;; }),
		std::make_pair(0x33, [&objects](){ objects.push_back(new Projectile); std::cout << "New Projectile added" << std::endl << std::endl;; }),
		std::make_pair(0x34, [&objects](){ objects.push_back(new PickableItem); std::cout << "New Item added" << std::endl << std::endl;; }),
		std::make_pair(0x41, [&objects](){ makeProjectileCollide(objects); }),
		std::make_pair(0x42, [&objects](){ makePlayerCollide(objects); }),
		
		// exit game
		std::make_pair(VK_ESCAPE, [&windowIsOpen]() { windowIsOpen = false; })
	};

	KeyStates states
	{
		std::make_pair(0x31, false),
		std::make_pair(0x32, false),
		std::make_pair(0x33, false),
		std::make_pair(0x34, false),
		std::make_pair(0x41, false),
		std::make_pair(0x42, false)
	};


	while (windowIsOpen) {

		float delta = 100;
		std::for_each(std::begin(objects), std::end(objects), [delta](GameObject* obj) {
			obj->update(delta);
		});

		for (auto& kv : callbacks) {
			bool isPressed = (GetAsyncKeyState(kv.first) & 0x8000) != 0;
			bool wasPressed = states[kv.first];
			// just pressed
			if (!wasPressed && isPressed) {
				kv.second();
			}
			// update the states
			states[kv.first] = isPressed;
		}

		Sleep(100);
	}
	return 0;
}