#pragma once
#include "pch.h"
#include "Replay.h"
#include <memory>

using namespace cocos2d;

struct TimeAction {
	double time;
	bool hold;
	// no player 2 L
};

class ReplaySystem {
	static ReplaySystem* instance;

	uintptr_t baseAddress;
	bool recording = false;
	bool playing = false;
	std::shared_ptr<Replay> currentReplay;
	float defaultFPS = 120.f;

	size_t curActionIndex = 0;
public:
	std::vector<TimeAction> timeActions;
	static ReplaySystem* getInstance() {
		if (!instance) instance = new ReplaySystem();
		return instance;
	}

	void init(uintptr_t base);

	std::shared_ptr<Replay> getCurrentReplay() {
		return currentReplay;
	}
	void loadReplay(const char* path);
	void saveReplay(const char* path);

	void toggleRecording();
	void togglePlaying();

	bool isRecording() {
		return recording;
	}
	bool isPlaying() {
		return playing;
	}

	float getDefaultFPS() {
		return defaultFPS;
	}

	void setDefaultFPS(float fps) {
		defaultFPS = fps;
	}

	void recordAction(bool hold, bool player1);
	void onReset();
	void playAction(Action);
	void handlePlaying();
};

