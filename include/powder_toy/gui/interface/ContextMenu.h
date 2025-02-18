#pragma once
#include "Window.h"
#include "Appearance.h"
#include "Button.h"

namespace ui
{
	class Button;
	
class ContextMenuItem
{
public:
	int ID;
	PTString Text;
	bool Enabled;
	ContextMenuItem(PTString text, int id, bool enabled) : ID(id), Text(text), Enabled(enabled) {}
};

class ContextMenu: public ui::Window {
	std::vector<Button*> buttons;
	std::vector<ContextMenuItem> items;
	ui::Component * source;
public:
	ui::Appearance Appearance;
	ContextMenu(Component * source);
	virtual ~ContextMenu() = default;
	
	void ActionCallbackItem(ui::Button *sender, int item);
	void AddItem(ContextMenuItem item);
	void RemoveItem(int id);
	void SetItem(int id, PTString text);
	void Show(ui::Point position);
	void OnDraw() override;
	void OnMouseDown(int x, int y, unsigned button) override;
};
}
