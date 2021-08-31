#pragma once

class SceneBase {
public:
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void quit() = 0;
};