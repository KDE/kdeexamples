layout = new LinearLayout(plasmoid);
label = new Label();
layout.addItem(label);

//print(dataEngine("time").query("UTC").Time.toString());

plasmoid.dataUpdated = function(a, b)
{
    if (b.DateTime) {
        print("Current date and time is: " + b.DateTime)
    }
    label.text = "It is " + b.Time + " in " + a
}

dataEngine("time").connectSource("UTC", plasmoid, 500)

