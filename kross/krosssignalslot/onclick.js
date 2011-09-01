function changeText() {
  if (Button.enabled) {
    Label.setText('Script is connected to this button');
  } else {
    Label.setText('Button is disabled, this must have been a script!');
  }
  Button.setEnabled(false);
}

connect(Button, "clicked()", this, "changeText()");
