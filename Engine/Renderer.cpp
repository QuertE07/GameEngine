#include "pch.h"
#include "Renderer.h"
#include "Model.h"
#include "Transform.h"
#include "MathUtils.h"
#include "Texture.h"

#include <iostream>

bool gl::Renderer::Initialize(const char* name, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    m_width = width;
    m_height = height;

    m_window = SDL_CreateWindow(name, m_width, m_height, 0);
    if (m_window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (m_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderVSync(m_renderer, 1);

    if (!TTF_Init()) {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void gl::Renderer::Shutdown()
{
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void gl::Renderer::Clear() const
{
    SDL_RenderClear(m_renderer);
}

void gl::Renderer::Present() const
{
    SDL_RenderPresent(m_renderer);
}

void gl::Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void gl::Renderer::SetColor(float r, float g, float b, float a) const
{
    SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
}

void gl::Renderer::SetColor(const Color& color) const
{
    SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, 1.0f);
}

void gl::Renderer::DrawPoint(float x, float y) const
{
    SDL_RenderPoint(m_renderer, x, y);
}

void gl::Renderer::DrawLine(float x1, float y1, float x2, float y2) const
{
    SDL_RenderLine(m_renderer, x1, y1, x2, y2);
}

void gl::Renderer::DrawFillRect(float x, float y, float w, float h) const
{
    SDL_FRect rect{ x, y, w, h };
    SDL_RenderFillRect(m_renderer, &rect);
}

void gl::Renderer::DrawRect(float x, float y, float w, float h) const
{
    SDL_FRect rect{ x, y, w, h };
    SDL_RenderRect(m_renderer, &rect);
}

void gl::Renderer::DrawModel(const Model& model, const Transform& transform) const
{
    for (auto mesh : model.GetMeshes())
    {
        SetColor(mesh.GetColor());

        auto& points = mesh.GetPoints();

        for (int i = 0; i + 1 < points.size(); i++)
        {
            Vector2 v1 = points[i];
            Vector2 v2 = points[i + 1];

            v1 *= transform.scale;
            v2 *= transform.scale;

            v1 = v1.Rotate(transform.rotation * DegToRad);
            v2 = v2.Rotate(transform.rotation * DegToRad);

            v1 += transform.position;
            v2 += transform.position;

            DrawLine(v1.x, v1.y, v2.x, v2.y);
        }
    }

    
}

void gl::Renderer::DrawDebugText(float x, float y, const char* text) const
{
    SDL_RenderDebugText(m_renderer, x, y, text);
}

void gl::Renderer::DrawTexture(Texture* texture, float x, float y)
{
    Vector2 size = texture->GetSize();

        SDL_FRect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = texture->GetSize().x;
    destRect.h = texture->GetSize().y;

    // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
    SDL_RenderTexture(m_renderer, texture->m_texture, NULL, &destRect);
}
