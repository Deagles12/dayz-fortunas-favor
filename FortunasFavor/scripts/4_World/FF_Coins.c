// Coins are passive inventory items. No actions, timers, charges or RPC effects.
class FF_CoinBase extends ItemBase {
 override void OnStoreSave(ParamsWriteContext ctx) {
  super.OnStoreSave(ctx);
  ctx.Write(2);
 }
 override bool OnStoreLoad(ParamsReadContext ctx,int version) {
  if (!super.OnStoreLoad(ctx,version)) return false;
  return FF_ReadState(ctx);
 }
 bool FF_ReadState(ParamsReadContext ctx) {
  int schema;
  if (!ctx.Read(schema)) return false;
  if (schema==2) return true;
  if (schema!=1) return false;
  // Consume legacy state so existing coins survive the mechanics migration.
  bool active,consumed;
  string owner;
  int readyAt;
  if (!ctx.Read(active)) return false;
  if (!ctx.Read(owner)) return false;
  if (!ctx.Read(readyAt)) return false;
  if (!ctx.Read(consumed)) return false;
  return true;
 }
 float FF_Chance() { return 0; }
}
class FF_Copia extends FF_CoinBase {
 override float FF_Chance() { return FF_Settings.Get().CopiaChance; }
}
class FF_Salus extends FF_CoinBase {
 override float FF_Chance() { return FF_Settings.Get().SalusChance; }
}
class FF_Fatum extends FF_CoinBase {
 override float FF_Chance() { return FF_Settings.Get().FatumChance; }
}
class FF_Fatum_Event extends FF_Fatum {}
