modded class ItemBase {
 override bool EEOnDamageCalculated(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  if (!super.EEOnDamageCalculated(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef)) return false;
  return FF_Durability.BeforeNative(this);
 }
 override void EEHitBy(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  super.EEHitBy(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
  FF_Durability.AfterNative(this);
 }
 override void EEHealthLevelChanged(int oldLevel,int newLevel,string zone) {
  if (FF_Durability.HealthLevel(this,oldLevel,newLevel)) return;
  super.EEHealthLevelChanged(oldLevel,newLevel,zone);
 }
 override void EEDelete(EntityAI parent) { FF_Durability.Forget(this); super.EEDelete(parent); }
}

modded class CarScript {
 override bool EEOnDamageCalculated(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  if (!super.EEOnDamageCalculated(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef)) return false;
  return FF_Durability.BeforeNative(this);
 }
 override void EEHitBy(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  super.EEHitBy(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
  FF_Durability.AfterNative(this);
 }
 override void EEHealthLevelChanged(int oldLevel,int newLevel,string zone) {
  if (FF_Durability.HealthLevel(this,oldLevel,newLevel)) return;
  super.EEHealthLevelChanged(oldLevel,newLevel,zone);
 }
 override void EEDelete(EntityAI parent) { FF_Durability.Forget(this); super.EEDelete(parent); }
}

modded class BoatScript {
 override bool EEOnDamageCalculated(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  if (!super.EEOnDamageCalculated(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef)) return false;
  return FF_Durability.BeforeNative(this);
 }
 override void EEHitBy(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef) {
  super.EEHitBy(damageResult,damageType,source,component,dmgZone,ammo,modelPos,speedCoef);
  FF_Durability.AfterNative(this);
 }
 override void EEHealthLevelChanged(int oldLevel,int newLevel,string zone) {
  if (FF_Durability.HealthLevel(this,oldLevel,newLevel)) return;
  super.EEHealthLevelChanged(oldLevel,newLevel,zone);
 }
 override void EEDelete(EntityAI parent) { FF_Durability.Forget(this); super.EEDelete(parent); }
}
