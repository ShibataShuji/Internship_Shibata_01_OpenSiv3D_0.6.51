#pragma once

class EmptyObject : public GameObject
{
private:

public:
	void Init() override { GameObject::Init(); }
	void Uninit() override { GameObject::Uninit(); }
	void Update() override { GameObject::Update(); }
	void Draw() override {}

};
