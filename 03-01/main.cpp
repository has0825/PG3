#include <iostream>

enum class Phase {
	Approach,   // 接近
	Shoot,      // 射撃
	Retreat,    // 離脱
	Max,        // 状態数
};

class Enemy {
public:
	Enemy();
	bool Update();

private:

	using StateFunc = void (Enemy::*)();

	static StateFunc stateTable[];

	Phase phase_;

	void Approach();
	void Shoot();
	void Retreat();
};


Enemy::StateFunc Enemy::stateTable[] = {
	&Enemy::Approach,
	&Enemy::Shoot,
	&Enemy::Retreat
};

Enemy::Enemy() : phase_(Phase::Approach) {

}

void Enemy::Approach() {
	std::cout << "敵の状態:接近" << std::endl;

	phase_ = Phase::Shoot;
}

void Enemy::Shoot() {
	std::cout << "敵の状態:射撃" << std::endl;

	phase_ = Phase::Retreat;
}

void Enemy::Retreat() {
	std::cout << "敵の状態:離脱" << std::endl;

	phase_ = Phase::Max;
}


bool Enemy::Update() {

	if (phase_ >= Phase::Max) {
		return false;
	}

	size_t index = static_cast<size_t>(phase_);

	(this->*stateTable[index])();

	return true;
}

int main() {
	Enemy enemy;

	std::cout << "---開始---" << std::endl;

	while (true) {

		if (!enemy.Update()) {
			break;
		}
	}

	std::cout << "---終了---" << std::endl;

	return 0;
}