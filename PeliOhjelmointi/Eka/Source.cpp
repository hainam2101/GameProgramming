#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>

class GameObject
{
public:
	virtual void update(float deltaTime);
	virtual ~GameObject() = default;
private:
	float deltaTime = 1000;
};

class Player : public GameObject
{
public:
	void update() 
	{ 
		std::cout << "Player: " << std::endl << std::endl;

	};
};

class Enemy : public GameObject
{
public:
	void update()
	{
		std::cout << "Enemy: " << std::endl << std::endl;

	};
	void isHit() { --hp; };
private:
	int hp = 5;
};

class Projectile : public GameObject
{
public:
	void update()
	{
		std::cout << "Projectile: " << std::endl << std::endl;
	};
};

class PickableItem : public GameObject
{

};

int main()
{
	GameObject GO;
	Player player;
	Enemy enemy;
	Projectile projectile;
	PickableItem item;
	std::vector<GameObject>gameObjects;
	bool windowIsOpen = true;

	while (windowIsOpen)
	{
		if (GetAsyncKeyState(0x31))
			gameObjects.push_back(player);

		if (GetAsyncKeyState(0x32))
			gameObjects.push_back(enemy);

		if (GetAsyncKeyState(0x33))
			gameObjects.push_back(projectile);

		if (GetAsyncKeyState(0x34))
			gameObjects.push_back(item);

		if (GetAsyncKeyState(0x41))
		{

			// jos hp == 0 poista enemy
		}

		if (GetAsyncKeyState(0x42))
		{
			// poista item
			std::cout << "Item removed" << std::endl << std::endl;
		}
	}

		GO.update(1000);
		Sleep(1000);
	
}