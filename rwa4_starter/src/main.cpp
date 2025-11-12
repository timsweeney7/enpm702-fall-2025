#include <iostream>
#include <string>

#include "maze_api.hpp"

void log(const std::string& text) {
  std::cerr << text << std::endl;
}

using MMS = micro_mouse::MazeControlAPI;

int main() {
  log("Running...");
  MMS::set_color(0, 0, 'G');
  MMS::set_text(0, 0, "S");
  
  MMS::set_text(7, 7, "(7,7)");
  MMS::set_text(7, 8, "(7,8)");
  MMS::set_text(8, 7, "(8,7)");
  MMS::set_text(8, 8, "(8,8)");
  MMS::set_color(7, 7, 'y');
  MMS::set_color(7, 8, 'y');
  MMS::set_color(8, 7, 'y');
  MMS::set_color(8, 8, 'y');
  while (true) {
    if (!MMS::has_wall_left()) {
      MMS::turn_left();
    }
    while (MMS::has_wall_front()) {
      MMS::turn_right();
    }
    MMS::move_forward();
  }
}