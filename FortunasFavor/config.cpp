class CfgPatches { class FortunasFavor { units[]={"FF_Copia","FF_Salus","FF_Fatum","FF_Fatum_Event"}; weapons[]={}; requiredVersion=0.1; requiredAddons[]={"DZ_Data","DZ_Scripts","DZ_Gear_Consumables"}; }; };
class CfgMods { class FortunasFavor { dir="FortunasFavor"; name="Fortuna's Favor"; type="mod"; dependencies[]={"Game","World","Mission"}; class defs { class gameScriptModule { value=""; files[]={"FortunasFavor/scripts/3_Game"}; }; class worldScriptModule { value=""; files[]={"FortunasFavor/scripts/4_World"}; }; class missionScriptModule { value=""; files[]={"FortunasFavor/scripts/5_Mission"}; }; }; }; };
class CfgVehicles {
 class Inventory_Base;
 class FF_CoinBase: Inventory_Base { scope=0; weight=18; itemSize[]={1,1}; rotationFlags=17; canBeSplit=0; varQuantityInit=0; physLayer="item_small"; class DamageSystem { class GlobalHealth { class Health { hitpoints=100; healthLevels[]={{1,{}},{0,{}}}; }; }; }; };
 class FF_Copia: FF_CoinBase { scope=2; displayName="Fortuna Copia"; descriptionShort="$STR_FF_COPIA_DESC"; model="\FortunasFavor\assets\copia.p3d"; };
 class FF_Salus: FF_CoinBase { scope=2; displayName="Fortuna Salus"; descriptionShort="$STR_FF_SALUS_DESC"; model="\FortunasFavor\assets\salus.p3d"; };
 class FF_Fatum: FF_CoinBase { scope=2; displayName="Fortuna Fatum"; descriptionShort="$STR_FF_FATUM_DESC"; model="\FortunasFavor\assets\fatum.p3d"; };
 class FF_Fatum_Event: FF_Fatum { scope=2; };
};
