// set up the engine, player and controller
var controller
var watchingPlayer = ""
var engine = dataEngine("nowplaying")

// define a few functions
plasmoid.dataUpdated = function(a, b)
{
    print("updated data for " + a)
    if (a == "players") {
        if (watchingPlayer != '') {
            engine.disconnectSource(watchingPlayer)
        }

        watchingPlayer = b.players[0];
        engine.connectSource(watchingPlayer, plasmoid)

        controller = service("nowplaying", watchingPlayer)
        controller.associateWidget(stopButton, "stop")
        controller.associateWidget(progress, "progress")
        controller.finished.connect(plasmoid.jobFinished)
        print("Now watching player " + watchingPlayer);
    } else {
        label.text = "Playing " + b.Title + " by " + b.Artist + ". time: " +
                     Math.floor(b.Position/60) + ":" + (parseInt(b.Position)%60)
        progress.value = 100*b.Position/b.Length
    }
}

plasmoid.jobFinished = function(job)
{
    print("The job " + job.operationName + " is finished.")
}

plasmoid.stop = function()
{
    if (!controller) {
        return
    }

    data = controller.operationDescription("stop")
    print(controller.name)
    for ( var i in data ) {
        print(i + ' -> ' + data[i] )
    }

    job = controller.startOperationCall(controller.operationDescription("stop"))
    print("JOb is..." + job)
    //job.finished.connect(plasmoid.jobFinished)
    print("stopping")
}

plasmoid.setProgress = function(progress)
{
    operation = controller.operationDescription("seek");
    operation.seconds = progress;
    for ( var i in operation ) {
        print(i + ' -> ' + operation[i] );
    }

    controller.startOperationCall(operation);
    print("set progress to " + progress);
}

engine.connectSource("players", plasmoid)

// Set up the UI
layout = new LinearLayout(plasmoid);
layout.orientation = QtVertical;
label = new Label();
layout.addItem(label);

var stopButton = new PushButton();
stopButton.text = "Stop";
layout.addItem(stopButton);

var progress = new Slider();
progress.orientation = QtHorizontal;
layout.addItem(progress);

// Glue things together
stopButton.clicked.connect(plasmoid.stop);
progress.sliderMoved.connect(plasmoid.setProgress);

