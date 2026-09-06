#include "Menu.hpp"

#include "core/commands/Commands.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/backend/FiberPool.hpp"
#include "game/backend/ScriptMgr.hpp"
#include "game/frontend/fonts/Fonts.hpp"
#include "game/pointers/Pointers.hpp"
#include "submenus/Debug.hpp"
#include "submenus/Network.hpp"
#include "submenus/Players.hpp"
#include "submenus/Self.hpp"
#include "submenus/Settings.hpp"
#include "submenus/Teleport.hpp"
#include "submenus/World.hpp"
#include "submenus/Recovery.hpp"


namespace YimMenu
{
	void Menu::Init()
	{

		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::Self>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Teleport>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Network>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Players>());
		UIManager::AddSubmenu(std::make_shared<Submenus::World>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Recovery>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Settings>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Debug>());

		Renderer::AddRendererCallBack(
		    [&] {
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Menu::Font::g_DefaultFont);
			    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(25, 25, 35)));

			    ImGui::SetNextWindowSize(ImVec2((*Pointers.ScreenResX / 3.1), (*Pointers.ScreenResY / 1.5)), ImGuiCond_Once);

			    if (ImGui::Begin("Helix", nullptr, ImGuiWindowFlags_NoDecoration))
			    {
				    if (ImGui::Button("Unload", ImVec2(120, 0)))
				    {
					    if (ScriptMgr::CanTick())
					    {
						    FiberPool::Push([] {
							    Commands::Shutdown();
							    g_Running = false;
						    });
					    }
					    else
					    {
						    g_Running = false;
					    }
				    }

				    UIManager::Draw();

				    ImGui::End();
			    }

			    ImGui::PopStyleColor();
			    ImGui::PopFont();
		    },
		    -1);
	}
	void Menu::SetupStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.06f, 0.06f, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.08f, 0.08f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.04f, 0.04f, 0.95f);

		style.Colors[ImGuiCol_Border] = ImVec4(0.40f, 0.10f, 0.10f, 0.40f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.15f, 0.15f, 0.80f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.20f, 0.20f, 0.90f);

		style.Colors[ImGuiCol_Button] = ImVec4(0.65f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.95f, 0.20f, 0.20f, 1.00f);

		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.06f, 0.06f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.08f, 0.08f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.04f, 0.04f, 1.00f);

		style.Colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.10f, 0.10f, 0.85f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.55f, 0.15f, 0.15f, 0.85f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.70f, 0.15f, 0.15f, 1.00f);

		style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.08f, 0.08f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.12f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.08f, 0.08f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.20f, 0.20f, 1.00f);

		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.20f, 0.20f, 1.00f);

		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.65f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);

		style.Colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.10f, 0.10f, 0.50f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.15f, 0.15f, 0.75f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.80f, 0.20f, 0.20f, 1.00f);

		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.80f, 0.20f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.30f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.15f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.25f, 0.15f, 1.00f);

		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.40f, 0.10f, 0.10f, 0.50f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.15f, 0.15f, 0.75f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.20f, 0.20f, 1.00f);

		style.WindowRounding = 6.0f;
		style.ChildRounding = 6.0f;
		style.FrameRounding = 4.0f;
		style.GrabRounding = 4.0f;
		style.TabRounding = 4.0f;
		style.ScrollbarRounding = 4.0f;
		style.PopupRounding = 6.0f;

		style.WindowPadding = ImVec2(12.0f, 12.0f);
		style.FramePadding = ImVec2(8.0f, 6.0f);
		style.ItemSpacing = ImVec2(8.0f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
	}

	void Menu::SetupFonts()
	{
		auto& IO = ImGui::GetIO();
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		Menu::Font::g_DefaultFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_DefaultFontSize, &FontCfg);
		Menu::Font::g_OptionsFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_OptionsFontSize, &FontCfg);
		Menu::Font::g_ChildTitleFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_ChildTitleFontSize, &FontCfg);
		Menu::Font::g_ChatFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_ChatFontSize, &FontCfg);
		Menu::Font::g_OverlayFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_OverlayFontSize, &FontCfg);

		UIManager::SetOptionsFont(Menu::Font::g_OptionsFont);
	}

}
