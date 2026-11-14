modded class InspectMenuNew {
 override void SetItem(EntityAI item) {
  super.SetItem(item);
  if (!item || !item.IsInherited(FF_CoinBase) || !layoutRoot) return;
  ItemPreviewWidget preview=ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("ItemFrameWidget"));
  if (preview) preview.SetModelPosition(Vector(0,0,0.8));
 }
}
