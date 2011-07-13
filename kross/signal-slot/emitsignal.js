function emitSignal() {
  if (!Button1.enabled) {
   Button1.clicked();
   Button2.setEnabled(false);
  }
}

connect(Button2, "clicked()", this, "emitSignal()");
