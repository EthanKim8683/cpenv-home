#ifdef ETHANKIM8683
void viz(const std::function<void()> &draw) {
  static bool init = true;
  if (init) {
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(30);
    init = false;
  }

  InitWindow(400, 400, "");
  BeginDrawing();
  draw();
  EndDrawing();
  while (!WindowShouldClose()) {
    PollInputEvents();
  }
  CloseWindow();
}
#else
#define viz(...)
#endif
