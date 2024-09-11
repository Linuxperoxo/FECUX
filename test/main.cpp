#include <chrono>
#include <thread>

#include "animation.hpp"

int main() {
  std::atomic<bool> *_running = new std::atomic<bool>(true);
  std::thread animation(fecux::utils::animation::run, _running, "Loading");
  std::this_thread::sleep_for(std::chrono::seconds(5));

  _running->store(false);

  animation.join();

  delete _running;

  return 0;
}
