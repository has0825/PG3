#include <Novice.h>
#include <memory>

const char kWindowTitle[] = "LE2B_11_シミズグチ_ハル";


class InputManager {
public:
	
	static InputManager* GetInstance() {
		static InputManager instance;
		return &instance;
	}

	void Update() {
		memcpy(preKeys_, keys_, 256);
		Novice::GetHitKeyStateAll(keys_);
	}

	bool Push(int key) {
		return keys_[key] != 0;
	}

	bool Trigger(int key) {
		return keys_[key] != 0 && preKeys_[key] == 0;
	}

private:
	char keys_[256] = { 0 };
	char preKeys_[256] = { 0 };
};


enum class SceneType {
	TITLE,
	STAGE,
	CLEAR,
	COUNT
};

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


	SceneType GetNextScene() const { return nextScene_; }

protected:
	SceneType nextScene_; 
};



// --- タイトルシーン ---
class TitleScene : public IScene {
public:
	TitleScene() { nextScene_ = SceneType::TITLE; }

	void Initialize() override {
		nextScene_ = SceneType::TITLE;
	}

	void Update() override {
		
		if (InputManager::GetInstance()->Trigger(DIK_SPACE)) {
			nextScene_ = SceneType::STAGE;
		}
	}

	void Draw() override {
		Novice::ScreenPrintf(600, 360, "TITLE SCENE");
		Novice::ScreenPrintf(580, 380, "Press SPACE to Start");
	}
};

// --- ステージシーン ---
class StageScene : public IScene {
public:
	StageScene() { nextScene_ = SceneType::STAGE; }

	void Initialize() override {
		nextScene_ = SceneType::STAGE;

		// プレイヤー
		playerX_ = 640;
		playerY_ = 600;
		playerR_ = 20;

		// 敵
		enemyX_ = 600;
		enemyY_ = 100;
		enemyW_ = 64;
		enemyH_ = 64;
		isEnemyAlive_ = true;

		// 弾
		bulletX_ = 0;
		bulletY_ = 0;
		isBulletShot_ = false;
	}

	void Update() override {
		InputManager* input = InputManager::GetInstance();

		// --- プレイヤー移動 ---
		if (input->Push(DIK_LEFT)) playerX_ -= 5;
		if (input->Push(DIK_RIGHT)) playerX_ += 5;

		// --- 発射処理 ---
		if (input->Trigger(DIK_SPACE) && !isBulletShot_) {
			isBulletShot_ = true;
			bulletX_ = playerX_;
			bulletY_ = playerY_;
		}

		// --- 弾の更新 ---
		if (isBulletShot_) {
			bulletY_ -= 10; 

			
			if (bulletY_ < -10) {
				isBulletShot_ = false;
			}


			if (isEnemyAlive_) {
				if (bulletX_ >= enemyX_ && bulletX_ <= enemyX_ + enemyW_ &&
					bulletY_ >= enemyY_ && bulletY_ <= enemyY_ + enemyH_) {

					isEnemyAlive_ = false;
					isBulletShot_ = false;

					nextScene_ = SceneType::CLEAR;
				}
			}
		}
	}

	void Draw() override {
		// 敵の描画
		if (isEnemyAlive_) {
			Novice::DrawBox(enemyX_, enemyY_, enemyW_, enemyH_, 0.0f, RED, kFillModeSolid);
		}

		// プレイヤーの描画
		Novice::DrawEllipse(playerX_, playerY_, playerR_, playerR_, 0.0f, WHITE, kFillModeSolid);

		// 弾の描画
		if (isBulletShot_) {
			Novice::DrawEllipse(bulletX_, bulletY_, 8, 8, 0.0f, 0xFFFF00FF, kFillModeSolid);
		}

		Novice::ScreenPrintf(10, 10, "STAGE SCENE: Move[Arrows] Shot[SPACE]");
	}

private:
	// プレイヤー
	int playerX_, playerY_, playerR_;
	// 敵
	int enemyX_, enemyY_, enemyW_, enemyH_;
	bool isEnemyAlive_;
	// 弾
	int bulletX_, bulletY_;
	bool isBulletShot_;
};

// --- クリアシーン ---
class ClearScene : public IScene {
public:
	ClearScene() { nextScene_ = SceneType::CLEAR; }

	void Initialize() override {
		nextScene_ = SceneType::CLEAR;
	}

	void Update() override {

		if (InputManager::GetInstance()->Trigger(DIK_SPACE)) {
			nextScene_ = SceneType::TITLE;
		}
	}

	void Draw() override {
		Novice::ScreenPrintf(600, 360, "GAME CLEAR!");
		Novice::ScreenPrintf(560, 380, "Press SPACE to Title");
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 入力マネージャの取得
	InputManager* input = InputManager::GetInstance();

	std::unique_ptr<IScene> currentScene = std::make_unique<TitleScene>();
	currentScene->Initialize();

	// 現在のシーンタイプを追跡
	SceneType currentSceneType = SceneType::TITLE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// 入力更新
		input->Update();

		///
		/// ↓更新処理ここから
		///

		currentScene->Update();


		SceneType next = currentScene->GetNextScene();
		if (next != currentSceneType) {
			
			switch (next) {
			case SceneType::TITLE:
				currentScene = std::make_unique<TitleScene>();
				break;
			case SceneType::STAGE:
				currentScene = std::make_unique<StageScene>();
				break;
			case SceneType::CLEAR:
				currentScene = std::make_unique<ClearScene>();
				break;
			}

			currentScene->Initialize();

			currentSceneType = next;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		currentScene->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (input->Trigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}