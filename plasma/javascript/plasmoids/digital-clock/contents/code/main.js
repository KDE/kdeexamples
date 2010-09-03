layout = new LinearLayout(plasmoid);
label = new Label();
layout.addItem(label);

//print(dataEngine("time").query("UTC").Time.toString());

plasmoid.dataUpdated = function(a, b)
{
    label.text = "It is " + b.Time.toString() + " in " + a;
}

dataEngine("time").connectSource("UTC", plasmoid, 500);

