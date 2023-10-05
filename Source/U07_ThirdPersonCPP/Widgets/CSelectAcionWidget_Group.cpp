#include "CSelectAcionWidget_Group.h"
#include "Global.h"
#include "Components/GridPanel.h"
#include "CSelectionActionWidget_Icon.h"
#include "Components/Border.h"

void UCSelectAcionWidget_Group::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNull(Grid);
	TArray<UWidget*> children = Grid->GetAllChildren();

	// Add Item Widget to Map(with string key)
	for (const auto& child : children)
	{
		UCSelectionActionWidget_Icon* iconWidget = Cast<UCSelectionActionWidget_Icon>(child);
		if (!!iconWidget)
			IconWidgets.Add(child->GetName(), iconWidget);
	}
}

void UCSelectAcionWidget_Group::Pressed(FString InName)
{
	CLog::Print(InName + " is Pressed");
}

void UCSelectAcionWidget_Group::Hover(FString InName)
{
	// Border Color => Red
	UBorder* border = Cast<UBorder>(IconWidgets[InName]->GetWidgetFromName("MyBorder"));
	CheckNull(border);

	border->SetBrushColor(FLinearColor::Red);
}

void UCSelectAcionWidget_Group::Unhover(FString InName)
{
	// Border Color => White
	UBorder* border = Cast<UBorder>(IconWidgets[InName]->GetWidgetFromName("MyBorder"));
	CheckNull(border);

	border->SetBrushColor(FLinearColor::White);
}
