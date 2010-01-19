layout = new LinearLayout(plasmoid);
label = new Label();
layout.addItem(label);

dataEngine("time").connectSource("UTC", plasmoid, 500);
//print(dataEngine("time").query("UTC").Time.toString());

plasmoid.dataUpdate = function(a, b)
{
    label.text = "It is " + b.Time.toString() + " in " + a;
}

