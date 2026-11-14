// Direct damage can be vetoed before the engine applies it. Scripted wear uses
// native health setters, which cannot be overridden; snapshots cover that path.
class FF_HealthSnapshot {
 EntityAI Item;
 ref map<string,float> Values=new map<string,float>;
 bool Restoring;
 bool NativeDamage;
 void FF_HealthSnapshot(EntityAI item) { Item=item; Capture(); }
 void Capture() {
  if (!Item) return;
  array<string> zones={}; Item.GetDamageZones(zones);
  Values.Clear();
  foreach (string zone:zones) { if (Item.GetMaxHealth(zone,"Health")>0) Values.Set(zone,Item.GetHealth(zone,"Health")); }
  if (Item.GetMaxHealth("","Health")>0) Values.Set("",Item.GetHealth("","Health"));
 }
 bool Check(float chance) {
  if (!Item || Restoring) return false;
  if (NativeDamage) { NativeDamage=false; Capture(); return false; }
  bool loss;
  for (int i=0;i<Values.Count();i++) {
   if (Item.GetHealth(Values.GetKey(i),"Health") < Values.GetElement(i) - 0.00001) { loss=true; break; }
  }
  if (!loss) { Capture(); return false; }
  bool prevent=FF_Durability.Roll(chance);
  if (prevent) {
   Restoring=true;
   ref map<string,float> target=new map<string,float>;
   for (int k=0;k<Values.Count();k++) {
    string key=Values.GetKey(k);
    target.Set(key,Math.Max(Values.GetElement(k),Item.GetHealth(key,"Health")));
   }
   // Clear fatal damage while preserving all unrelated preexisting wear/repairs.
   if (Item.IsRuined()) Item.SetFullHealth();
   for (int n=0;n<target.Count();n++) { string name=target.GetKey(n); if (name!="") Item.SetHealth(name,"Health",target.GetElement(n)); }
   if (target.Contains("")) Item.SetHealth("","Health",target.Get(""));
   Restoring=false;
  }
  Capture();
  return prevent;
 }
}
class FF_Durability {
 static ref map<EntityAI,ref FF_HealthSnapshot> s_Items=new map<EntityAI,ref FF_HealthSnapshot>;
 static bool Roll(float chance) {
  if (chance <= 0.0) { return false; }
  if (chance >= 1.0) { return true; }
  float sample = Math.RandomFloat01();
  return sample < chance;
 }
 static float Chance(PlayerBase player) {
  if (!GetGame() || !GetGame().IsServer() || !FF_Settings.Get().Enabled || !player || !player.IsAlive()) return 0;
  array<EntityAI> inventory={}; player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER,inventory);
  float chance=0;
  foreach (EntityAI entity:inventory) { FF_CoinBase coin=FF_CoinBase.Cast(entity); if (coin) chance=Math.Max(chance,coin.FF_Chance()); }
  return chance;
 }
 static PlayerBase Beneficiary(EntityAI item) {
  if (!item || item.IsInherited(Man)) return null;
  PlayerBase player=PlayerBase.Cast(item.GetHierarchyRootPlayer());
  if (player) return player;
  Transport vehicle=Transport.Cast(item.GetHierarchyRoot());
  if (vehicle) return PlayerBase.Cast(vehicle.CrewMember(0));
  return null;
 }
 static FF_HealthSnapshot Track(EntityAI item) {
  FF_HealthSnapshot state=s_Items.Get(item);
  if (!state) { state=new FF_HealthSnapshot(item); s_Items.Set(item,state); }
  return state;
 }
 static bool BeforeNative(EntityAI item) {
  if (!GetGame() || !GetGame().IsServer()) return true;
  float chance=Chance(Beneficiary(item));
  if (chance<=0) return true;
  FF_HealthSnapshot state=Track(item);
  state.Check(chance);
  if (Roll(chance)) return false;
  state.Capture(); state.NativeDamage=true;
  return true;
 }
 static void AfterNative(EntityAI item) {
  if (!GetGame() || !GetGame().IsServer()) return;
  FF_HealthSnapshot state=s_Items.Get(item);
  if (state && state.NativeDamage) { state.NativeDamage=false; state.Capture(); }
 }
 static bool HealthLevel(EntityAI item,int oldLevel,int newLevel) {
  if (!GetGame() || !GetGame().IsServer() || newLevel<=oldLevel) return false;
  FF_HealthSnapshot state=s_Items.Get(item);
  if (!state || state.Restoring || state.NativeDamage) return false;
  return state.Check(Chance(Beneficiary(item)));
 }
 static void Forget(EntityAI item) { if (s_Items) s_Items.Remove(item); }
 static void Watch(EntityAI item,float chance,map<EntityAI,bool> seen) {
  if (!item || item.IsInherited(Man)) return;
  seen.Set(item,true); Track(item).Check(chance);
 }
 static void CheckPlayer(PlayerBase player,map<EntityAI,bool> seen) {
  float chance=Chance(player);
  if (chance<=0) return;
  array<EntityAI> inventory={}; player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER,inventory);
  foreach (EntityAI item:inventory) Watch(item,chance,seen);
  Transport vehicle=Transport.Cast(player.GetParent());
  if (vehicle && vehicle.CrewMember(0)==player) {
   inventory.Clear(); vehicle.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER,inventory);
   foreach (EntityAI part:inventory) Watch(part,chance,seen);
  }
 }
 static void Tick() {
  if (!GetGame() || !GetGame().IsServer()) return;
  array<Man> players={}; GetGame().GetPlayers(players);
  ref map<EntityAI,bool> seen=new map<EntityAI,bool>;
  foreach (Man man:players) CheckPlayer(PlayerBase.Cast(man),seen);
  for (int i=s_Items.Count() - 1;i>=0;i--) { EntityAI key=s_Items.GetKey(i); if (!seen.Contains(key)) s_Items.Remove(key); }
 }
}
