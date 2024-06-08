#include <stdexcept>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "implot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void sgam::Renderer::Init(SDL_Window* pWindow)
{
	m_pWindow = pWindow;
	if (!m_pWindow)
	{
		throw std::runtime_error("Invalid SDL_Window pointer!");
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (!m_pRenderer)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void sgam::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderFlush(m_pRenderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().RenderGUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_pRenderer);
}

void sgam::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void sgam::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	RenderTexture(texture, nullptr, &dst);
}

void sgam::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	RenderTexture(texture, nullptr, &dst);
}

void sgam::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), srcRect, dstRect);
}

void sgam::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, float rotation) const
{
	const SDL_RendererFlip flipState{ static_cast<SDL_RendererFlip>(
		(dstRect->w < 0.0f ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) |
		(dstRect->h < 0.0f ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE)
	) };

	SDL_RenderCopyEx(
		GetSDLRenderer(), texture.GetSDLTexture(),
		srcRect, dstRect,
		rotation, nullptr,
		flipState
	);
}
