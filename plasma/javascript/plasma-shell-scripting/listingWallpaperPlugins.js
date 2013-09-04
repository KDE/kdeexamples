var wallpapers = wallpaperPlugins();
for (i in wallpapers) {
  print(i);
  for (j in wallpapers[i]) {
    print("    Mode: " + wallpapers[i][j]);
  }
}