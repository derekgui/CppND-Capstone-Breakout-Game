#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
    now = SDL_GetTicks();
}

Uint32 FrameTimer::Mark()
{
    const auto last = now;
    now = SDL_GetTicks();
    const Uint32 frameTime = now - last;
    return frameTime;
}

// Uint32 title_timestamp = SDL_GetTicks();
// Uint32 frame_start;
// Uint32 frame_end;
// Uint32 frame_duration;
// int frame_count = 0;

// frame_start = SDL_GetTicks();

// frame_end = SDL_GetTicks();

// // Keep track of how long each loop through the input/update/render cycle
// // takes.
// frame_count++;
// frame_duration = frame_end - frame_start;

// // After every second, update the window title.
// if (frame_end - title_timestamp >= 1000)
// {
//     wnd.UpdateWindowTitle(score, frame_count);
//     frame_count = 0;
//     title_timestamp = frame_end;
// }

// // If the time for this frame is too small (i.e. frame_duration is
// // smaller than the target ms_per_frame), delay the loop to
// // achieve the correct frame rate.
// if (frame_duration < kMsPerFrame)
// {
//     SDL_Delay(kFramesPerSecond - frame_duration);
// }