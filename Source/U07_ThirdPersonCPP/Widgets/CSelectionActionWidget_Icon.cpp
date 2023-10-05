#include "CSelectionActionWidget_Icon.h"
#include "Global.h"
#include "Components/Button.h"
#include "Characters/CPlayer.h"
#include "CSelectAcionWidget_Group.h"

void UCSelectionActionWidget_Icon::NativeConstruct()
{
	Super::NativeConstruct();

	CheckNull(ImageButton);
	ImageButton->OnPressed.AddDynamic(this, &UCSelectionActionWidget_Icon::OnPressed);
	ImageButton->OnHovered.AddDynamic(this, &UCSelectionActionWidget_Icon::OnHover);
	ImageButton->OnUnhovered.AddDynamic(this, &UCSelectionActionWidget_Icon::OnUnHover);
}

void UCSelectionActionWidget_Icon::OnPressed()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Pressed(GetName());
}

void UCSelectionActionWidget_Icon::OnHover()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Hover(GetName());
}

void UCSelectionActionWidget_Icon::OnUnHover()
{
	CheckNull(GetParentWidget());
	GetParentWidget()->Unhover(GetName());
}

UCSelectAcionWidget_Group* UCSelectionActionWidget_Icon::GetParentWidget()
{
	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNullResult(player, nullptr);

	return player->GetSelectActionWidget();
}