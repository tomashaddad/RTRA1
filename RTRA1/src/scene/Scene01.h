#pragma once
#include "SceneBase.h"
class Scene01 : public SceneBase {
public:
	virtual void render() override;
	virtual void init() override;
	virtual void quit() override;
};

