class FF_Settings {
 int Version=3;
 bool Enabled=true;
 float CopiaChance=0.02;
 float SalusChance=0.05;
 float FatumChance=0.07;
 static ref FF_Settings s_Instance;
 static FF_Settings Get() {
  if (!s_Instance) {
   s_Instance=new FF_Settings;
   MakeDirectory("$profile:FortunasFavor");
   string path="$profile:FortunasFavor/config.json";
   string error;
   if (FileExist(path)) {
    FF_Settings loaded=new FF_Settings;
    if (JsonFileLoader<FF_Settings>.LoadFile(path,loaded,error) && loaded) {
     if (loaded.Version>=3) s_Instance=loaded;
     else {
      string legacy="$profile:FortunasFavor/config.before-durability.json";
      if (!FileExist(legacy) && !CopyFile(path,legacy)) {
       s_Instance.Enabled=false;
       Print("[FortunasFavor] Migration backup failed; protection disabled.");
      } else if (!JsonFileLoader<FF_Settings>.SaveFile(path,s_Instance,error)) Print("[FortunasFavor] Config migration write failed: "+error);
     }
    } else { s_Instance.Enabled=false; Print("[FortunasFavor] Invalid config, protection disabled: "+error); }
   } else if (!JsonFileLoader<FF_Settings>.SaveFile(path,s_Instance,error)) Print("[FortunasFavor] Cannot save defaults: "+error);
   s_Instance.CopiaChance=Math.Clamp(s_Instance.CopiaChance,0,1);
   s_Instance.SalusChance=Math.Clamp(s_Instance.SalusChance,0,1);
   s_Instance.FatumChance=Math.Clamp(s_Instance.FatumChance,0,1);
  }
  return s_Instance;
 }
}
