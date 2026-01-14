#include <Novice.h>

const char kWindowTitle[] = "LE2B_11_シミズグチ_ハル";

class Player {
public:
	Player(float x, float y, float speed) {
		x_ = x;
		y_ = y;
		speed_ = speed;
		width_ = 50.0f;
		height_ = 50.0f;
	}

	void MoveRight() {
		x_ += speed_;
	}

	void MoveLeft() {
		x_ -= speed_;
	}

	void Draw() {
		Novice::DrawBox(
			static_cast<int>(x_), static_cast<int>(y_),
			static_cast<int>(width_), static_cast<int>(height_),
			0.0f, WHITE, kFillModeSolid
		);
	}

private:
	float x_;
	float y_;
	float width_;
	float height_;
	float speed_;
};

class ICommand {
public:
	virtual ~ICommand() {}
	virtual void Exec() = 0;
};

class RightCommand : public ICommand {
public:
	
	RightCommand(Player* player) : player_(player) {}

	void Exec() override {
		player_->MoveRight();
	}

private:
	Player* player_;
};

class LeftCommand : public ICommand {
public:
	LeftCommand(Player* player) : player_(player) {}

	void Exec() override {
		player_->MoveLeft();
	}

private:
	Player* player_;
};

class InputHandler {
public:

	ICommand* HandleInput(const char* keys, Player* player) {

		if (keys[DIK_D] || keys[DIK_RIGHT]) {
			return new RightCommand(player);
		}

		if (keys[DIK_A] || keys[DIK_LEFT]) {
			return new LeftCommand(player);
		}


		return nullptr;
	}
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player* player = new Player(640.0f, 360.0f, 2.0f);

	InputHandler* inputHandler = new InputHandler();
	
	ICommand* command = nullptr;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		command = inputHandler->HandleInput(keys, player);

		if (command != nullptr) {
			command->Exec();

			delete command;
			command = nullptr;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// プレイヤーの描画
		player->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// メモリ解放
	delete player;
	delete inputHandler;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}