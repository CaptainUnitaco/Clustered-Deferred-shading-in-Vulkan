#pragma once
#include <string>
#include "Util.h"
#include "Scene.h"

struct GLFWwindow;
class Renderer;

enum class DebugStates : unsigned
{
	disabled,
	albedo,
	normal,
	specular,
	position,
	depth,

	count
};

enum class CullingMethod : int
{
	noculling,
	tiled,
	clustered,
};

class UI
{
public:
	struct Context
	{
		DebugStates debugState = DebugStates::disabled;
		CullingMethod cullingMethod = CullingMethod::clustered;
		bool debugUniformDirtyBit = false;
		bool shaderReloadDirtyBit = false;
		bool sceneReload = false;
		bool cullingMethodChanged = false;

		glm::vec3 lightBoundMin;
		glm::vec3 lightBoundMax;
		int lightsCount = 10;
		float lightSpeed = 0.f;
		int tileSize = 1;
		int currentScene = 0;
		bool vSync = false;
	} mContext;

public:
	UI(GLFWwindow* window, Renderer& renderer);

	DebugStates getDebugIndex() const;
	bool debugStateUniformNeedsUpdate();

	void update();
	void resize();
	void copyDrawData(vk::CommandBuffer& cmd);
	vk::CommandBuffer recordCommandBuffer(size_t cmdIndex);

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
};