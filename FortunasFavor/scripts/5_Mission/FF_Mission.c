modded class MissionServer {
 override void OnInit() { super.OnInit(); FF_Settings.Get(); }
 override void OnUpdate(float timeslice) {
  super.OnUpdate(timeslice);
  FF_Durability.Tick();
 }
}
