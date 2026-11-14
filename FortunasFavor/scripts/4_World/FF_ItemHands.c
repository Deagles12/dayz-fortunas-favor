modded class ModItemRegisterCallbacks {
 override void RegisterOneHanded(DayZPlayerType pType,DayzPlayerItemBehaviorCfg pBehavior) {
  super.RegisterOneHanded(pType,pBehavior);
  pType.AddItemInHandsProfileIK("FF_CoinBase","dz/anims/workspaces/player/player_main/props/player_main_1h_matchbox.asi",pBehavior,"dz/anims/anm/player/ik/gear/Matchbox.anm");
 }
}
