[[cpp11::linking_to("progress")]]

[[cpp11::register]] void
show_progress() {
  RProgress::RProgress pb("Processing [:bar] ETA: :eta");

  pb.tick(0);
  for (int i = 0; i < 100; i++) {
    usleep(2.0 / 100 * 1000000);
    pb.tick();
  }
}
