#include <base/math.h>
#include <base/system.h>

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/storage.h>
#include <engine/textrender.h>

#include <game/generated/protocol.h>

#include <game/client/animstate.h>
#include <game/client/components/chat.h>
#include <game/client/gameclient.h>
#include <game/client/render.h>
#include <game/client/skin.h>
#include <game/client/ui.h>
#include <game/client/ui_listbox.h>
#include <game/client/ui_scrollregion.h>
#include <game/localization.h>

#include <game/client/components/binds.h>
#include <game/client/components/countryflags.h>
#include <game/client/components/menus.h>
#include <game/client/components/skins.h>

#include <string>
#include <vector>
#include <base/color.h>


const float FontSize = 14.0f;
const float EditBoxFontSize = 12.0f;
const float LineSize = 20.0f;
const float ColorPickerLineSize = 25.0f;
const float HeadlineFontSize = 20.0f;
const float StandardFontSize = 14.0f;

const float HeadlineHeight = HeadlineFontSize + 0.0f;
const float Margin = 10.0f;
const float MarginSmall = 5.0f;
const float MarginExtraSmall = 2.5f;
const float MarginBetweenSections = 30.0f;
const float MarginBetweenViews = 30.0f;

const float ColorPickerLabelSize = 13.0f;
const float ColorPickerLineSpacing = 5.0f;


enum
{
	NEBULA_TAB_MAIN = 0,
    NEBULA_TAB_TCLIENT,
    NEBULA_TAB_PULSE,
    NEBULA_TAB_ACLIENT,
    NUMBER_OF_TABS_NEBULA
};

static void SetFlag(int32_t &Flags, int n, bool Value)
{
	if(Value)
		Flags |= (1 << n);
	else
		Flags &= ~(1 << n);
}

static bool IsFlagSet(int32_t Flags, int n)
{
	return (Flags & (1 << n)) != 0;
}

void CMenus::RenderSettingsNebula(CUIRect MainView)
{
    CUIRect TabBar, Column, LeftView, RightView, Button, Label;
    static int s_CurCustomTab = 0;
    int TabCount = NUMBER_OF_TABS_NEBULA;
	for(int Tab = 0; Tab < NUMBER_OF_TABS_NEBULA; ++Tab)
	{
		if(IsFlagSet(g_Config.m_ClNebulaSettingsTab, Tab))
		{
			TabCount--;
			if(s_CurCustomTab == Tab)
				s_CurCustomTab++;
		}
	}
    MainView.HSplitTop(LineSize * 1.2f, &TabBar, &MainView);
	const float TabWidth = TabBar.w / TabCount;
	static CButtonContainer s_aPageTabs[NUMBER_OF_TABS_NEBULA] = {};
	const char *apTabNames[] = {
        ("Main"),
        ("TClient"),
        ("Pulse"),
        ("AClient")
    };
    for(int Tab = 0; Tab < NUMBER_OF_TABS_NEBULA; ++Tab)
	{
		if(IsFlagSet(g_Config.m_ClNebulaSettingsTab, Tab))
			continue;

		TabBar.VSplitLeft(TabWidth, &Button, &TabBar);
		const int Corners = Tab == 0 ? IGraphics::CORNER_L : Tab == NUMBER_OF_TABS_NEBULA - 1 ? IGraphics::CORNER_R : IGraphics::CORNER_NONE;
		if(DoButton_MenuTab(&s_aPageTabs[Tab], apTabNames[Tab], s_CurCustomTab == Tab, &Button, Corners, nullptr, nullptr, nullptr, nullptr, 4.0f))
			s_CurCustomTab = Tab;
	}

    MainView.HSplitTop(MarginSmall, nullptr, &MainView);

    if(s_CurCustomTab == NEBULA_TAB_MAIN)
	{
		RenderSettingsNebulaMain(MainView);
	}
    else if(s_CurCustomTab == NEBULA_TAB_TCLIENT)
    {
        RenderSettingsNebulaTClient(MainView);
    }
    else if(s_CurCustomTab == NEBULA_TAB_PULSE)
    {
        RenderSettingsNebulaPulse(MainView);
    }
    else if(s_CurCustomTab == NEBULA_TAB_ACLIENT)
    {
        RenderSettingsNebulaAClient(MainView);
    }

}
void CMenus::RenderSettingsNebulaMain(CUIRect MainView)
{
    Ui()->DoLabel(&MainView, "Nebula", 20.0f, TEXTALIGN_MC);
}
void CMenus::RenderSettingsNebulaTClient(CUIRect MainView)
{
    Ui()->DoLabel(&MainView, "TClient", 20.0f, TEXTALIGN_MC);
}
void CMenus::RenderSettingsNebulaPulse(CUIRect MainView)
{
    Ui()->DoLabel(&MainView, "Pulse", 20.0f, TEXTALIGN_MC);
}
void CMenus::RenderSettingsNebulaAClient(CUIRect MainView)
{
    Ui()->DoLabel(&MainView, "AClient", 20.0f, TEXTALIGN_MC);
}