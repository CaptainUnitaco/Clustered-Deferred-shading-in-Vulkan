#pragma once
#include <string>
#include "Util.h"

struct GLFWwindow;
class Renderer;

enum class DebugStates : unsigned
{
	disabled,
	albedo,
	normal,
	specular,
	position,

	count
};

inline DebugStates& operator++(DebugStates& s) 
{
	using type = std::underlying_type<DebugStates>::type;
	s = static_cast<DebugStates>((static_cast<type>(s) + 1) % static_cast<type>(DebugStates::count));
	return s;
}

inline DebugStates& operator--(DebugStates& s)
{
	using type = std::underlying_type<DebugStates>::type; // TODO correct it
	s = static_cast<DebugStates>((static_cast<type>(s) - 1) % static_cast<type>(DebugStates::count));
	return s;
}

class UI
{
public:
	struct Context
	{
		DebugStates debugState = DebugStates::disabled;
		bool debugUniformDirtyBit = false;

		int lightsCount = 1;
		bool lightsAnimation = true;
	} mContext;

public:
	UI(GLFWwindow* window, Renderer& renderer);

	void onKeyPress(int key, int action);
	DebugStates getDebugIndex() const;
	bool debugStateUniformNeedsUpdate();

	void update();
	void copyDrawData();
	void recordCommandBuffer();
	vk::UniqueCommandBuffer& getCommandBuffer();

public:
	BufferParameters& getVertexBuffer();
	BufferParameters& getIndexBuffer();

private:
	void setColorScheme();
	void initResources();
	void createPipeline();
	
private:
	Renderer& mRenderer;

	BufferParameters mVertexBuffer;
	BufferParameters mIndexBuffer;
	BufferParameters mStagingBuffer;

	ImageParameters mFontTexture;
	vk::UniqueSampler mSampler;

	std::vector<vk::UniqueCommandBuffer> mCmdBuffers;
	size_t mCommandBufferInUse = 0;
};